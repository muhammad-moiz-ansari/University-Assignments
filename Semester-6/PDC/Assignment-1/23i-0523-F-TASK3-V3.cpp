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

struct ThreadData {
  int tid;
  int num_threads;
  vector<int> local_next_frontier;
};

// GLOBALS
const int max_nodes = 920000, max_edges = 5105039;
int edges_scanned = 0, reacheable = 0, maxdist = 0;
vector<int> lvls;
vector<int> *adj = new vector<int>[max_nodes];
int dist[max_nodes];

// For Parallel BFS
vector<int> curr_frontier;
vector<int> next_frontier;

int dataset_size_op = 1; // Change this to change dataset size

void parseTXT(vector<int> *adj, string filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "ERROR: File not opened!\n";
    exit(1);
  }
  string line;
  int src, dest;
  // File Format [From_node To_node]

  long max_scan_limit = max_edges; // Default
  if (dataset_size_op == 1)
    max_scan_limit = max_scan_limit * 0.1;
  else if (dataset_size_op == 2)
    max_scan_limit = max_scan_limit * 0.5;

  // Ignore comments
  while (getline(file, line)) {
    if (line.empty() || line[0] == '#')
      continue;

    // We will reach here when first real line found
    stringstream ss(line);
    ss >> src >> dest;
    if (src < max_nodes && dest < max_nodes) {
      adj[src].push_back(dest);
      ++edges_scanned;
    } else {
      cout << "ERROR: Node index exceeds max_nodes limit!\n";
      cout << src << "  " << dest << endl;
      exit(1);
    }
    break;
  }

  while (file >> src >> dest && edges_scanned < max_scan_limit) {
    if (src < max_nodes && dest < max_nodes) {
      adj[src].push_back(dest);
    } else {
      cout << "ERROR: Node index exceeds max_nodes limit!\n";
      cout << src << "  " << dest << endl;
      exit(1);
    }
    edges_scanned++;
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

void *bfs(void *args) {
  ThreadData *tdata = (ThreadData *)args;

  // Pin Thread
  int num_cores = sysconf(_SC_NPROCESSORS_ONLN); // Total cores (8)
  pin_thread_to_core(tdata->tid % num_cores);

  tdata->local_next_frontier.clear();

  // Curr_frontier static chunking
  long total_size = curr_frontier.size();
  long chunk_size = (total_size + tdata->num_threads - 1) / tdata->num_threads;
  long start = tdata->tid * chunk_size;
  long end = min(start + chunk_size, total_size);

  int curr_lvl = 0;
  if (total_size > 0)
    curr_lvl = dist[curr_frontier[0]];

  for (long i = start; i < end; ++i) {
    int u = curr_frontier[i];
    for (int v : adj[u]) {
      if (dist[v] == -1) {
        if (__sync_bool_compare_and_swap(&dist[v], -1, curr_lvl + 1)) {
          tdata->local_next_frontier.push_back(v);
        }
      }
    }
  }
  pthread_exit(NULL);
}

int main() {
  // No. of rows in web-Google.txt:
  string filename = "web-Google.txt";

  // cout << "Scanning graph edges file...\n";
  parseTXT(adj, filename);
  // cout << "Graph of " << edges_scanned << " edges made successfully!\n\n";

  // ====== INITIALIZE TIMER VARIABLES =====
  struct timespec start, end;
  int start_node = 0;

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
      reacheable = 0;
      maxdist = 0;
      lvls.clear();
      curr_frontier.clear();
      next_frontier.clear();
      for (int i = 0; i < max_nodes; ++i)
        dist[i] = -1;

      // ========== START TIMER ==========
      clock_gettime(CLOCK_MONOTONIC, &start);
      // =================================

      dist[start_node] = 0;
      curr_frontier.push_back(start_node);
      reacheable = 1;
      lvls.push_back(1);

      // BFS Loop
      while (!curr_frontier.empty()) {
        next_frontier.clear();

        // Threading Stuff
        pthread_t threads[num_threads];
        ThreadData tdata[num_threads];

        // Threads created
        for (int i = 0; i < num_threads; ++i) {
          tdata[i].tid = i;
          tdata[i].num_threads = num_threads;
          pthread_create(&threads[i], NULL, bfs, (void *)&tdata[i]);
        }

        // Threads joining
        for (int i = 0; i < num_threads; ++i) {
          pthread_join(threads[i], NULL);
          next_frontier.insert(next_frontier.end(),
                               tdata[i].local_next_frontier.begin(),
                               tdata[i].local_next_frontier.end());
        }

        // Update stats
        if (!next_frontier.empty()) {
          reacheable += next_frontier.size();
          int lvl = dist[next_frontier[0]];
          if (lvl > maxdist)
            maxdist = lvl;
          if (lvls.size() <= lvl)
            lvls.resize(lvl + 1, 0);
          lvls[lvl] += next_frontier.size();
        }
        curr_frontier = next_frontier;
      }

      // ========== STOP TIMER & CALCULATE (in ms) ==========
      clock_gettime(CLOCK_MONOTONIC, &end);
      double time_taken = (end.tv_sec - start.tv_sec) * 1000.0 +
                          (end.tv_nsec - start.tv_nsec) / 1000000.0;
      // ====================================================

      // ========= SPEEDUP =========
      double v1_time;
      if (dataset_size_op == 1)
        v1_time = 30.41674;
      else if (dataset_size_op == 2)
        v1_time = 132.8354;
      else
        v1_time = 261.339;
      double speedup = v1_time / time_taken;
      speedups.push_back(speedup);
      // ===========================

      // Print to CSV
      // Format: task, version, threads, chunk, trial, time_ms
      int version_no = 3;
      int chunk_size = edges_scanned;
      // cout << "task3," << version_no << "," << num_threads << "," <<
      // chunk_size
      //  << "," << trial << "," << time_taken << endl;
    }
    for (int i = 0; i < num_trials; ++i) {
      // cout << speedups[i] << ",";
    }
    sort(speedups.begin(), speedups.end());
    // cout << "\nMax Speedup: " << speedups[speedups.size() - 1] << "\n\n";
  }

  // Output
  cout << "SOURCE " << start_node << endl;
  cout << "REACHABLE " << reacheable << endl;
  cout << "MAXDIST " << maxdist << endl;
  for (int i = 0; i <= maxdist; ++i) {
    cout << i << " " << lvls[i] << endl;
  }

  return 0;
}