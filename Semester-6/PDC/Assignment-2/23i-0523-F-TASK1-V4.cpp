#include <algorithm>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// vector<pair<int, int>> edges;

// Global data
int max_edges = 25572, max_nodes = 1005, edges_scanned = 0, total_edges = 0,
    max_degree = 0, max_out_deg = 0;
int dataset_no = 1; // Change this to change dataset size

///////////////////////////////////////////
//                                       //
//              BUILD GRAPH              //
//                                       //
///////////////////////////////////////////

// ================ PARSE TXT FILE ================
int parseTXT(vector<pair<int, int>> &edges, string filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "ERROR: File not opened!\n";
    exit(1);
  }
  string line;
  int src, dest;
  int max_vertex_id = 0;
  // File Format [From_node To_node]

  long max_scan_limit = max_edges;

  // Ignore comments
  while (getline(file, line)) {
    if (line.empty() || line[0] == '#')
      continue;

    // We will reach here when first real line found
    stringstream ss(line);
    ss >> src >> dest;
    if (src < max_nodes && dest < max_nodes) {
      ++edges_scanned;
      if (src == dest) // Skip self loops
        break;
      edges.push_back({src, dest});
      edges.push_back({dest, src});
      total_edges += 2;
      if (src > max_vertex_id)
        max_vertex_id = src;
      if (dest > max_vertex_id)
        max_vertex_id = dest;
    } else {
      cout << "ERROR: Node index exceeds max_nodes limit!\n";
      cout << src << "  " << dest << endl;
      exit(1);
    }
    break;
  }
  while (file >> src >> dest && edges_scanned < max_scan_limit) {
    edges_scanned++;
    if (src < max_nodes && dest < max_nodes) {
      if (src == dest) // Skip self loops
        continue;
      edges.push_back({src, dest});
      edges.push_back({dest, src});
      total_edges += 2;
      if (src > max_vertex_id)
        max_vertex_id = src;
      if (dest > max_vertex_id)
        max_vertex_id = dest;
    } else {
      cout << "ERROR: Node index exceeds max_nodes limit!\n";
      cout << src << "  " << dest << endl;
      exit(1);
    }
  }
  return max_vertex_id;
}

// ================ REMOVE DUPLICATES ================
int removeDuplicates(vector<pair<int, int>> &edges) {
  sort(edges.begin(), edges.end());
  edges.erase(unique(edges.begin(), edges.end()), edges.end());
  return edges.size(); // cleaned edges
}

// ================ COMPUTE DEGREES ================
vector<int> computeDegrees(const vector<pair<int, int>> &edges, int V) {
  vector<int> degree(V, 0);

  for (const auto &edge : edges) {
    degree[edge.first]++;
  }
  for (int i = 0; i < degree.size(); ++i) {
    if (degree[i] > max_degree)
      max_degree = degree[i];
  }

  /*
  cout << "\nOut-Degrees:\n";
  for (int i = 0; i < V; ++i) {
    cout << i << ": " << degree[i] << endl;
  }
  */
  return degree;
}

// ================ REORDER DEGREES ================
void degreeReorder(const vector<int> &degree, vector<int> &new_id,
                   vector<int> &old_id, int V) {
  // Creating pairs of (degree, original_id)
  vector<pair<int, int>> pairs;
  for (int i = 0; i < V; ++i)
    pairs.push_back({degree[i], i});

  // Sorting by degree ascending order
  sort(pairs.begin(), pairs.end());

  // Building mapping arrays
  for (int i = 0; i < V; ++i) {
    int original = pairs[i].second;
    new_id[original] = i;
    old_id[i] = original;
  }
}

// ================ REMAP AND FILTER (Upper Edges) ================
vector<pair<int, int>> remapAndFilter(const vector<pair<int, int>> &edges,
                                      const vector<int> &new_id) {
  vector<pair<int, int>> upper_edges;

  for (auto edge : edges) {
    int u_new = new_id[edge.first];
    int v_new = new_id[edge.second];

    // Upper triangle filtering
    if (u_new < v_new)
      upper_edges.push_back({u_new, v_new});
  }
  // Sort and clean again
  sort(upper_edges.begin(), upper_edges.end());
  upper_edges.erase(unique(upper_edges.begin(), upper_edges.end()),
                    upper_edges.end());

  return upper_edges;
}

// ================ BUILD CSR ================
int buildCSR(vector<int> &offset, vector<int> &neighbors,
             const vector<pair<int, int>> &upper_edges, int V) {
  // No. of neighbors in each vertex
  vector<int> count(V, 0);
  for (auto edge : upper_edges)
    count[edge.first]++;

  // Max out degree (the degree after reorder)
  for (int i = 0; i < V; ++i) {
    if (count[i] > max_out_deg) {
      max_out_deg = count[i];
    }
  }

  // Building offset array (Sum of previous offset and sum)
  offset.resize(V + 1);
  offset[0] = 0;
  for (int i = 1; i <= V; ++i)
    offset[i] = offset[i - 1] + count[i - 1];

  // Total edges in upper triangle
  int E_upper_count = offset[V];

  // Neighbors array
  neighbors.resize(E_upper_count);
  vector<int> fill_pos = offset;
  for (auto edge : upper_edges) {
    neighbors[fill_pos[edge.first]] = edge.second;
    fill_pos[edge.first]++;
  }
  return E_upper_count;
}

// ================ SORT ADJACENCY LIST ================
void sortAdjList(vector<int> &offset, vector<int> &neighbors, int V) {
  for (int i = 0; i < V; ++i) {
    int start = offset[i];
    int end = offset[i + 1];
    sort(neighbors.begin() + start, neighbors.begin() + end);
  }
}

// ================ BUILD GRAPH ================
void buildGraph(string filename, vector<int> &offset, vector<int> &neighbors,
                int &V, int &E) {
  vector<pair<int, int>> edges;
  cout << "Scanning graph edges file...\n";

  V = parseTXT(edges, filename) + 1;
  cout << "No. of edges scanned: " << edges_scanned << endl << endl;
  cout << "Graph of " << total_edges << " edges made successfully!\n";
  cout << "Max vertex ID: " << V << endl;
  total_edges = removeDuplicates(edges);
  cout << "No. of unique edges: " << total_edges << endl;
  vector<int> degree = computeDegrees(edges, V);

  // Degree reorder
  vector<int> new_id(V);
  vector<int> old_id(V);
  degreeReorder(degree, new_id, old_id, V);

  // Remapping edges & Building upper triangle
  vector<pair<int, int>> upper_edges = remapAndFilter(edges, new_id);
  cout << "No. of Upper Edges: " << upper_edges.size() << endl;

  // Building CSR
  E = buildCSR(offset, neighbors, upper_edges, V);
  cout << "No. of Upper Edges (CSR): " << E << endl;

  // Sorting adj list
  sortAdjList(offset, neighbors, V);
}

// ================ PRINT GRAPH STATS ================
void printGraphStats(int V, int E) {
  cout << "\n╔═══════════════════════════════════════════════════════╗\n"
       << "║                    Graph Statistics                   ║\n"
       << "╟───────────────────────────────────────────────────────╢\n"
       << "║ Vertices      : " << V << "\t\t\t\t\t║" << endl
       << "║ Edges (total) : " << total_edges << "\t\t\t\t\t║" << endl
       << "║ Edges (upper) : " << E << "\t\t\t\t\t║" << endl
       << "║ Max degree    : " << max_degree << " (before reorder)\t\t\t║\n"
       << "║ Max out-deg   : " << max_out_deg
       << " (after reorder, upper triangle)\t║\n"
       << "╚═══════════════════════════════════════════════════════╝\n\n";
}

//\
// \\
//   \\
//     \\
//       \\
//         \\
//           \\
//             \\
//               \\
//                 \\
//                   \\
//  COUNT TRIANGLES    \\
//                       \\
//                         \\
//                           \\
//                             \\
//////////////////\\\\\\\\\\\\\\\\\.

// ================ COUNT INTERSECTIONS ================
long intersectCount(int *A, int sizeA, int *B, int sizeB) {
  int i = 0, j = 0;
  long count = 0;

  while (i < sizeA && j < sizeB) {
    if (A[i] < B[j])
      i++;
    else if (B[j] < A[i])
      j++;
    else { // if both are equal, means intersection, means triangle found!
      count++;
      i++;
      j++;
    }
  }
  return count;
}

// ================ COUNT TRIANGLES ================
long countTriangles(const vector<int> &offset, vector<int> &neighbors, int V) {
  long total_count = 0;
  omp_set_num_threads(8);

#pragma omp parallel for schedule(dynamic, 16) reduction(+ : total_count)
  for (int vi = 0; vi < V; ++vi) {
    // Adj>(vi) = neighbors[offset[vi] .. offset[vi+1]-1]
    int *A = neighbors.data() + offset[vi]; // For safety of edge cases
    int sizeA = offset[vi + 1] - offset[vi];

    for (int j = 0; j < sizeA; ++j) {
      int vj = A[j];
      int *B = neighbors.data() + offset[vj]; // For safety of edge cases
      int sizeB = offset[vj + 1] - offset[vj];

      // Intersect Adj>(vi) with Adj>(vj)
      total_count += intersectCount(A + j + 1, sizeA - (j + 1), B, sizeB);
    }
  }
  return total_count;
}

// ================ RUNNER FUNCTION ================
void runOMPVersion(const vector<int> &offset, vector<int> &neighbors, int V,
                   int num_threads) {
  cout << "Running OpenMP version...\n";
  // ---------- INITIALIZE TIMER VARIABLES ----------
  struct timespec start, end;

#pragma omp parallel num_threads(num_threads)
  {
  } // empty warmup

  int test_nums = 8;
  for (int i = 0; i < test_nums; ++i) {

    // ----------------- START TIMER ------------------
    clock_gettime(CLOCK_MONOTONIC, &start);
    // ------------------------------------------------

    long count = countTriangles(offset, neighbors, V);

    // -------- STOP TIMER & CALCULATE (in ms) --------
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1000.0 +
                        (end.tv_nsec - start.tv_nsec) / 1000000.0;
    // ------------------------------------------------

    double baseline_time = 2.19481; // Default
    if (dataset_no == 1)
      baseline_time = 2.19481;
    double speedup = baseline_time / time_taken;

    if (i == 0) {
      cout << "Triangles found: " << count << endl;
      cout << "Threads used: " << num_threads << endl;
    }
    cout << "Time Taken: " << time_taken << " ms\t";
    cout << "Speedup: " << speedup << endl;
  }
}

int main() {
  string filename = "datasets/email-Eu-core.txt"; // Default
  vector<int> offset;
  vector<int> neighbors;
  int V, E;

  if (dataset_no == 1)
    filename = "datasets/email-Eu-core.txt";

  buildGraph(filename, offset, neighbors, V, E);

  printGraphStats(V, E);

  runOMPVersion(offset, neighbors, V, 8);

  return 0;
}