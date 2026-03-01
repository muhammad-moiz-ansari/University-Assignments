#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

// GLOBALS
int max_nodes = 920000, max_edges = 5105039, edges_scanned = 0, reacheable = 0,
    maxdist = 0;
vector<int> lvls;
vector<int> *adj = new vector<int>[max_nodes];
vector<int> dist(max_nodes);

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

void bfs(int start_node) {
  queue<int> q;

  dist[start_node] = 0;
  q.push(start_node);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    reacheable++;
    if (dist[u] > maxdist)
      maxdist = dist[u];

    // Levels
    if (dist[u] >= lvls.size())
      lvls.resize(dist[u] + 1, 0);
    lvls[dist[u]]++;

    for (int v : adj[u]) {
      if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }
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
  num_trials = 1; // for profiling

  for (int trial = 1; trial <= num_trials; ++trial) {
    reacheable = 0;
    maxdist = 0;
    lvls.clear();
    for (int i = 0; i < dist.size(); ++i)
      dist[i] = -1;

    // ========== START TIMER ==========
    clock_gettime(CLOCK_MONOTONIC, &start);
    // =================================

    bfs(start_node);

    // ========== STOP TIMER & CALCULATE (in ms) ==========
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1000.0 +
                        (end.tv_nsec - start.tv_nsec) / 1000000.0;
    // ====================================================

    // Print to CSV
    // Format: task, version, threads, chunk, trial, time_ms
    int version_no = 1;
    int num_threads = 1;
    int chunk_size = edges_scanned;
    // cout << "task3," << version_no << "," << num_threads << "," << chunk_size
    //      << "," << trial << "," << time_taken << endl;
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