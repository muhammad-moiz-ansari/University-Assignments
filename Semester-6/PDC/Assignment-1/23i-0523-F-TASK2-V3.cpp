#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <sched.h>
#include <sstream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>
using namespace std;

struct Element {
  int r, c;   // Row, Column
  double val; // Values
};

struct ThreadData {
  int tid;
  long start_ind, end_ind;
  const vector<Element> *data;
  const vector<double> *x;
  vector<double> *y;
};

// GLOBALS (Rows, Cols, Non-zeros)
int M, N, NZ, total_nonzeros;
mutex code;

int dataset_size_op = 1; // Change this to change dataset size

bool compareByRow(const Element &a, const Element &b) {
  if (a.r != b.r)
    return a.r < b.r;
  return a.c < b.c; // else
}

void parseMTX(vector<Element> &data, string filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "ERROR: File not opened!\n";
    exit(1);
  }
  string line;
  int r, c;
  double v;
  long total_count = 0;

  // Ignore comments
  while (getline(file, line)) {
    if (line.length() > 0 && line[0] != '%')
      break;
  }

  // Data Dimensions (Rows, Cols, Non-zeros)
  stringstream ts(line);
  ts >> M >> N >> NZ;

  long max_scan_limit = NZ; // Default
  if (dataset_size_op == 1)
    max_scan_limit = max_scan_limit * 0.1;
  else if (dataset_size_op == 2)
    max_scan_limit = max_scan_limit * 0.5;

  data.reserve(max_scan_limit);
  while (getline(file, line) && total_count < max_scan_limit) {
    Element temp;
    stringstream ss(line);

    // Row or col missing
    if (!(ss >> r >> c))
      continue;

    // Non-zero missing (Def to 1.0)
    if (!(ss >> v))
      v = 1.0;

    // 1-based index -> 0-based index
    temp.r = r - 1;
    temp.c = c - 1;
    temp.val = v;

    data.push_back(temp);
    total_count++;
  }
  total_nonzeros = data.size();

  // Sort the data
  sort(data.begin(), data.end(), compareByRow);
}

// For pinning thread to a specific core
void pin_thread_to_core(int core_id) {
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(core_id, &cpuset);

  pthread_t current_thread = pthread_self();
  if (pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset) != 0) {
    cout << "Error: Could not pin thread " << core_id << endl;
  }
}

void *sparse_vec_mul(void *args) {
  ThreadData *tdata = (ThreadData *)args;

  // Pin Thread
  int num_cores = sysconf(_SC_NPROCESSORS_ONLN); // Total cores (8)
  pin_thread_to_core(tdata->tid % num_cores);

  const vector<Element> &data = *(tdata->data);
  const vector<double> &x = *(tdata->x);
  vector<double> &y = *(tdata->y);

  for (long i = tdata->start_ind; i < tdata->end_ind; ++i) {
    y[data[i].r] += data[i].val * x[data[i].c];
  }

  pthread_exit(NULL);
}

int main() {
  // No. of rows in webbase-1M.mtx:
  vector<Element> data;
  string filename = "webbase-1M.mtx";
  double checksum;

  // cout << "Scanning mtx file...\n";
  parseMTX(data, filename);
  // cout << total_nonzeros << " non-zero data read successfully (M: " << M<< ",
  // N: " << N << ")!\n\n";

  vector<double> x(N);
  vector<double> y(M, 0.0);

  // Fixed Constants
  for (int j = 0; j < N; ++j)
    x[j] = ((j + 1) % 1000) / 1000.0;

  // ====== INITIALIZE TIMER VARIABLES =====
  struct timespec start, end;

  int num_trials = 5;
  int start_threads = 1;

  // For profiling
  num_trials = 1;
  start_threads = 8;

  int max_threads = 8;
  for (int k = start_threads; k <= max_threads; k = k * 2) {
    int num_threads = k;
    vector<double> speedups;
    for (int trial = 1; trial <= num_trials; ++trial) {
      checksum = 0.0;
      for (int i = 0; i < M; ++i)
        y[i] = 0.0;

      // Threading Stuff
      pthread_t threads[num_threads];
      ThreadData tdata[num_threads];
      long chunk_size = total_nonzeros / num_threads;
      long start_curr = 0, end_next;

      // ========== START TIMER ==========
      clock_gettime(CLOCK_MONOTONIC, &start);
      // =================================

      for (int i = 0; i < num_threads; ++i) {
        tdata[i].tid = i;
        tdata[i].data = &data;
        tdata[i].start_ind = start_curr;
        end_next = start_curr + chunk_size;

        if (i == num_threads - 1) // For last chunk
          end_next = total_nonzeros;
        else {
          while (end_next < total_nonzeros &&
                 data[end_next - 1].r == data[end_next].r)
            end_next++;
        }
        tdata[i].x = &x;
        tdata[i].y = &y;
        tdata[i].end_ind = end_next;
        start_curr = end_next;

        pthread_create(&threads[i], NULL, sparse_vec_mul, (void *)&tdata[i]);
      }

      for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
      }

      // ========== STOP TIMER & CALCULATE (in ms) ==========
      clock_gettime(CLOCK_MONOTONIC, &end);
      double time_taken = (end.tv_sec - start.tv_sec) * 1000.0 +
                          (end.tv_nsec - start.tv_nsec) / 1000000.0;
      // ====================================================

      // ========= SPEEDUP =========
      double v1_time;
      if (dataset_size_op == 1)
        v1_time = 4.938974;
      else if (dataset_size_op == 2)
        v1_time = 20.18474;
      else
        v1_time = 41.63804;
      double speedup = v1_time / time_taken;
      speedups.push_back(speedup);
      // ===========================

      // Print to CSV
      // Format: task, version, threads, chunk, trial, time_ms
      int version_no = 3;
      // cout << "task2," << version_no << "," << num_threads << "," <<
      // chunk_size<< "," << trial << "," << time_taken << endl;
    }
    for (int i = 0; i < num_trials; ++i)
      // cout << speedups[i] << ",";
      sort(speedups.begin(), speedups.end());
    // cout << "\nMax Speedup: " << speedups[speedups.size() - 1] << "\n\n";
  }

  // Checksum
  for (int i = 0; i < M; ++i)
    checksum += y[i];

  // Output
  cout << "M " << M << " N " << N << " NZ " << NZ << endl;
  cout << "CHECKSUM " << fixed << setprecision(6) << checksum << endl;

  return 0;
}