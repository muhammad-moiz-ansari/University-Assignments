#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <sstream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>
using namespace std;

struct Record {
  double label;        // The first column (0 or 1)
  double features[18]; // The 18 features (x1 to x18)
};

class Result {
public:
  long PRED_POS, TP, FP, TN, FN;
  Result() {
    PRED_POS = 0;
    TP = 0;
    FP = 0;
    TN = 0;
    FN = 0;
  }
};

struct ThreadData {
  int tid;
  long start_ind, end_ind;
  const vector<Record> *data;
  Result local_res;
};

// GLOBALS
long total_records = 0;
int dataset_size_op = 1; // Change this to change dataset size

// Constants
const int w_size = 18;
double b = -0.35;
double w[w_size] = {0.12, -0.07, 0.05, 0.09,  -0.11, 0.03, 0.08,  -0.02, 0.06,
                    0.04, -0.05, 0.10, -0.08, 0.07,  0.02, -0.03, 0.11,  -0.06};

void parseCSV(vector<Record> &data, string filename) {
  ifstream file(filename);
  data.reserve(5000000);

  string line, word;
  getline(file, line); // Discard header

  long max_scan_limit = 5000000; // Default
  if (dataset_size_op == 1)
    max_scan_limit = max_scan_limit * 0.1;
  else if (dataset_size_op == 2)
    max_scan_limit = max_scan_limit * 0.5;
  else
    max_scan_limit = max_scan_limit * 1;
  while (getline(file, line) && total_records < max_scan_limit) {
    stringstream ss(line); // To read each word by splitting string with ','
    vector<string> row;

    while (getline(ss, word, ','))
      row.push_back(word);

    if (row.size() == 19) {
      Record temp;
      temp.label = stod(row[0]);
      for (int i = 0; i < w_size; ++i)
        temp.features[i] = stod(row[i + 1]);
      data.push_back(temp);
      total_records++;
    }
  }
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

void *regression_model(void *arg) {
  ThreadData *tdata = (ThreadData *)arg;

  // Pin Thread
  int num_cores = sysconf(_SC_NPROCESSORS_ONLN); // Total cores (8)
  pin_thread_to_core(tdata->tid % num_cores);

  long start_ind = tdata->start_ind;
  long end_ind = tdata->end_ind;
  const vector<Record> &data = *(tdata->data);

  int y, y_;
  double s, p;
  for (int i = start_ind; i < end_ind; ++i) {
    y = data[i].label;
    s = b;
    for (int j = 0; j < w_size; ++j)
      s += data[i].features[j] * w[j];
    p = 1.0 / (1.0 + exp(-s));

    if (p >= 0.5)
      y_ = 1;
    else
      y_ = 0;

    if (y_ == 1)
      tdata->local_res.PRED_POS++;
    if (y == 1 && y_ == 1)
      tdata->local_res.TP++;
    else if (y == 0 && y_ == 1)
      tdata->local_res.FP++;
    else if (y == 0 && y_ == 0)
      tdata->local_res.TN++;
    else if (y == 1 && y_ == 0)
      tdata->local_res.FN++;
  }
  pthread_exit(NULL);
}

int main() {
  // No. of rows in SUSY.csv: 5000000 (5M)
  vector<Record> data;
  Result res;
  string filename = "supersymmetry_dataset.csv";

  // cout << "Scanning csv file...\n";
  parseCSV(data, filename);
  // cout << total_records << " rows of data read successfully!\n\n";

  // ====== INITIALIZE TIMER VARIABLES =====
  struct timespec start, end;

  int num_trials = 5;

  for (int k = 1; k <= 8; k = k * 2) {
    int num_threads = k;
    vector<double> speedups;
    for (int trial = 1; trial <= num_trials; ++trial) {
      res.PRED_POS = 0;
      res.TP = 0;
      res.FP = 0;
      res.TN = 0;
      res.FN = 0;

      // ========== START TIMER ==========
      clock_gettime(CLOCK_MONOTONIC, &start);
      // =================================

      // Threading Stuff
      long int chunk_size = total_records / num_threads;
      pthread_t threads[num_threads];
      ThreadData tdata[num_threads];

      for (int i = 0; i < num_threads; ++i) {
        tdata[i].tid = i;
        tdata[i].data = &data;
        tdata[i].start_ind = i * chunk_size;
        if (i == num_threads - 1) // For last chunk
          tdata[i].end_ind = total_records;
        else
          tdata[i].end_ind = (i + 1) * chunk_size;

        pthread_create(&threads[i], NULL, regression_model, (void *)&tdata[i]);
      }

      for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);

        res.PRED_POS += tdata[i].local_res.PRED_POS;
        res.TP += tdata[i].local_res.TP;
        res.FP += tdata[i].local_res.FP;
        res.TN += tdata[i].local_res.TN;
        res.FN += tdata[i].local_res.FN;
      }

      // ========== STOP TIMER & CALCULATE (in ms) ==========
      clock_gettime(CLOCK_MONOTONIC, &end);
      double time_taken = (end.tv_sec - start.tv_sec) * 1000.0 +
                          (end.tv_nsec - start.tv_nsec) / 1000000.0;
      // ====================================================

      // ========= SPEEDUP =========
      double v1_time;
      if (dataset_size_op == 1)
        v1_time = 78.28;
      else if (dataset_size_op == 2)
        v1_time = 420.25;
      else
        v1_time = 833.48;
      double speedup = v1_time / time_taken;
      speedups.push_back(speedup);
      // ===========================

      // Print to CSV
      // Format: task, version, threads, chunk, trial, time_ms
      int version_no = 3;
      // cout << "task1," << version_no << "," << num_threads << "," <<
      // chunk_size
      //      << "," << trial << "," << time_taken << endl;
    }
    for (int i = 0; i < num_trials; ++i)
      // cout << speedups[i] << ",";
      sort(speedups.begin(), speedups.end());
    // cout << "\nMax Speedup: " << speedups[speedups.size() - 1] << "\n\n";
  }

  // Output
  cout << "N " << total_records << endl;
  cout << "PRED_POS " << res.PRED_POS << endl;
  cout << "TP " << res.TP << endl;
  cout << "FP " << res.FP << endl;
  cout << "TN " << res.TN << endl;
  cout << "FN " << res.FN << endl;

  return 0;
}