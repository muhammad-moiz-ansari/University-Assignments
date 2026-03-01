#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

struct Element {
  int r, c;   // Row, Column
  double val; // Values
};

// GLOBALS (Rows, Cols, Non-zeros)
int M, N, NZ, total_nonzeros;

int dataset_size_op = 1; // Change this to change dataset size

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
}

void sparse_vec_mul(const vector<Element> &data, const vector<double> &x,
                    vector<double> &y) {
  for (int i = 0; i < total_nonzeros; ++i)
    y[data[i].r] += data[i].val * x[data[i].c];
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
  num_trials = 1; // for profiling

  for (int trial = 1; trial <= num_trials; ++trial) {
    checksum = 0.0;
    for (int i = 0; i < M; ++i)
      y[i] = 0.0;

    // ========== START TIMER ==========
    clock_gettime(CLOCK_MONOTONIC, &start);
    // =================================

    sparse_vec_mul(data, x, y);

    // ========== STOP TIMER & CALCULATE (in ms) ==========
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1000.0 +
                        (end.tv_nsec - start.tv_nsec) / 1000000.0;
    // ====================================================

    // Checksum
    for (int i = 0; i < M; ++i)
      checksum += y[i];

    // Print to CSV
    // Format: task, version, threads, chunk, trial, time_ms
    int version_no = 1;
    int num_threads = 1;
    int chunk_size = total_nonzeros;
    // cout << "task2," << version_no << "," << num_threads << "," <<
    // chunk_size<< "," << trial << "," << time_taken << endl;
  }

  // Output
  cout << "M " << M << " N " << N << " NZ " << NZ << endl;
  cout << "CHECKSUM " << fixed << setprecision(6) << checksum << endl;

  return 0;
}