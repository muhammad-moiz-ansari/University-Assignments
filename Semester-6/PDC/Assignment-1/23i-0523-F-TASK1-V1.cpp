#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

struct Record {
  double label;        // The first column (0 or 1)
  double features[18]; // The 18 features (x1 to x18)
};

class Result {
public:
  int PRED_POS, TP, FP, TN, FN;
  Result() {
    PRED_POS = 0;
    TP = 0;
    FP = 0;
    TN = 0;
    FN = 0;
  }
};

// Record* data;
long total_records = 0;

// Constants
double b = -0.35;
vector<double> w = {0.12, -0.07, 0.05, 0.09,  -0.11, 0.03, 0.08,  -0.02, 0.06,
                    0.04, -0.05, 0.10, -0.08, 0.07,  0.02, -0.03, 0.11,  -0.06};

void parseCSV(vector<Record> &data, string filename) {
  ifstream file(filename);
  data.reserve(5000000);

  string line, word;
  getline(file, line); // Discard header

  int choice = 1; // Change this to change dataset size

  long max_scan_limit = 5000000; // Default
  if (choice == 1)
    max_scan_limit = max_scan_limit * 0.1;
  else if (choice == 2)
    max_scan_limit = max_scan_limit * 0.5;
  else if (choice == 3)
    max_scan_limit = max_scan_limit * 1;

  while (getline(file, line) && total_records < max_scan_limit) {
    stringstream ss(line); // To read each word by splitting string with ','
    vector<string> row;

    while (getline(ss, word, ','))
      row.push_back(word);

    if (row.size() == 19) {
      Record temp;
      temp.label = stod(row[0]);
      for (int i = 0; i < 18; ++i)
        temp.features[i] = stod(row[i + 1]);
      data.push_back(temp);
      total_records++;
    }
  }
}

void regression_model(Result &res, vector<Record> &data) {
  int y, y_;
  double s, p;
  for (int i = 0; i < total_records; ++i) {
    y = data[i].label;
    s = b;
    for (int j = 0; j < w.size(); ++j)
      s += data[i].features[j] * w[j];
    p = 1.0 / (1.0 + exp(-s));

    if (p >= 0.5)
      y_ = 1;
    else
      y_ = 0;

    if (y_ == 1)
      res.PRED_POS++;
    if (y == 1 && y_ == 1)
      res.TP++;
    else if (y == 0 && y_ == 1)
      res.FP++;
    else if (y == 0 && y_ == 0)
      res.TN++;
    else if (y == 1 && y_ == 0)
      res.FN++;
  }
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

  int num_trials = 1;

  for (int trial = 1; trial <= num_trials; ++trial) {
    res.PRED_POS = 0;
    res.TP = 0;
    res.FP = 0;
    res.TN = 0;
    res.FN = 0;

    // ========== START TIMER ==========
    clock_gettime(CLOCK_MONOTONIC, &start);
    // =================================

    regression_model(res, data);

    // ========== STOP TIMER & CALCULATE (in ms) ==========
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1000.0 +
                        (end.tv_nsec - start.tv_nsec) / 1000000.0;
    // ====================================================

    // Print to CSV
    // Format: task, version, threads, chunk, trial, time_ms
    int version_no = 1;
    int num_threads = 1;
    int chunk_size = total_records;
    // cout << "task1," << version_no << "," << num_threads << "," << chunk_size
    //      << "," << trial << "," << time_taken << endl;
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