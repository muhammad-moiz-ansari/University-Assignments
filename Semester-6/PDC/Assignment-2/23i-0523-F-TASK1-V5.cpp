#include <algorithm>
#include <fstream>
#include <immintrin.h> // ALL AVX2 intrinsics
#include <iostream>
#include <nmmintrin.h> // _mm_popcnt_u32
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
int num_threads = 1;
double baseline_time = 2.19481; // Default

int dataset_no = 3; // Change this to change dataset size

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

  // Rotation masks
  // Added 'static' to bake them into read-only memory
  const __m256i rot1 = _mm256_set_epi32(0, 7, 6, 5, 4, 3, 2, 1);
  const __m256i rot2 = _mm256_set_epi32(1, 0, 7, 6, 5, 4, 3, 2);
  const __m256i rot3 = _mm256_set_epi32(2, 1, 0, 7, 6, 5, 4, 3);
  const __m256i rot4 = _mm256_set_epi32(3, 2, 1, 0, 7, 6, 5, 4);
  const __m256i rot5 = _mm256_set_epi32(4, 3, 2, 1, 0, 7, 6, 5);
  const __m256i rot6 = _mm256_set_epi32(5, 4, 3, 2, 1, 0, 7, 6);
  const __m256i rot7 = _mm256_set_epi32(6, 5, 4, 3, 2, 1, 0, 7);

  while (i + 8 <= sizeA && j + 8 <= sizeB) {
    // Load from list
    __m256i vecA = _mm256_loadu_si256((__m256i *)&A[i]);
    __m256i vecB = _mm256_loadu_si256((__m256i *)&B[j]);

    // ALL Comparison of B with 8 rotations
    // Rotation 0 (Original position)
    __m256i cmp0 = _mm256_cmpeq_epi32(vecA, vecB);

    // Rotation 1 to 7
    __m256i b1 = _mm256_permutevar8x32_epi32(vecB, rot1);
    __m256i cmp1 = _mm256_cmpeq_epi32(vecA, b1);

    __m256i b2 = _mm256_permutevar8x32_epi32(vecB, rot2);
    __m256i cmp2 = _mm256_cmpeq_epi32(vecA, b2);

    __m256i b3 = _mm256_permutevar8x32_epi32(vecB, rot3);
    __m256i cmp3 = _mm256_cmpeq_epi32(vecA, b3);

    __m256i b4 = _mm256_permutevar8x32_epi32(vecB, rot4);
    __m256i cmp4 = _mm256_cmpeq_epi32(vecA, b4);

    __m256i b5 = _mm256_permutevar8x32_epi32(vecB, rot5);
    __m256i cmp5 = _mm256_cmpeq_epi32(vecA, b5);

    __m256i b6 = _mm256_permutevar8x32_epi32(vecB, rot6);
    __m256i cmp6 = _mm256_cmpeq_epi32(vecA, b6);

    __m256i b7 = _mm256_permutevar8x32_epi32(vecB, rot7);
    __m256i cmp7 = _mm256_cmpeq_epi32(vecA, b7);

    // Combining all results
    __m256i result = _mm256_or_si256(
        cmp0,
        _mm256_or_si256(
            cmp1,
            _mm256_or_si256(
                cmp2,
                _mm256_or_si256(
                    cmp3, _mm256_or_si256(
                              cmp4, _mm256_or_si256(
                                        cmp5, _mm256_or_si256(cmp6, cmp7)))))));

    // Convert to bitmask and count set bits
    int mask = _mm256_movemask_ps(_mm256_castsi256_ps(result));
    count += _mm_popcnt_u32(mask);

    // Pointers based tail comparison
    int tailA = A[i + 7];
    int tailB = B[j + 7];
    if (tailA < tailB)
      i += 8;
    else if (tailB < tailA)
      j += 8;
    else {
      i += 8;
      j += 8;
    }
  }

  // Scalar Tail Handler (Remaining elements comparison)
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
  omp_set_num_threads(num_threads);

#pragma omp parallel for schedule(dynamic, 16) reduction(+ : total_count)
  for (int vi = 0; vi < V; ++vi) {
    // Adj>(vi) = neighbors[offset[vi] .. offset[vi+1]-1]
    int *A = neighbors.data() + offset[vi]; // For safety of edge cases
    int sizeA = offset[vi + 1] - offset[vi];

    for (int j = 0; j < sizeA; ++j) {
      int vj = A[j];
      int *B = neighbors.data() + offset[vj]; // For safety of edge cases
      int sizeB = offset[vj + 1] - offset[vj];

      // Intersect count (SIMD version)
      total_count += intersectCount(A + j + 1, sizeA - (j + 1), B, sizeB);
    }
  }
  return total_count;
}

// ================ RUNNER FUNCTION ================
void runOMP_SIMDVersion(const vector<int> &offset, vector<int> &neighbors,
                        int V) {
  cout << "Running OpenMP + SIMD version...\n";
  // ---------- INITIALIZE TIMER VARIABLES ----------
  struct timespec start, end;

  int start_th_num = 1;
  for (int i = start_th_num; i <= 8; i *= 2) {
    num_threads = i;
#pragma omp parallel num_threads(num_threads)
    {
    } // empty warmup

    int test_nums = 4;
    for (int j = 0; j < test_nums; ++j) {

      // ----------------- START TIMER ------------------
      clock_gettime(CLOCK_MONOTONIC, &start);
      // ------------------------------------------------

      long count = countTriangles(offset, neighbors, V);

      // -------- STOP TIMER & CALCULATE (in ms) --------
      clock_gettime(CLOCK_MONOTONIC, &end);
      double time_taken = (end.tv_sec - start.tv_sec) * 1000.0 +
                          (end.tv_nsec - start.tv_nsec) / 1000000.0;
      // ------------------------------------------------

      double speedup = baseline_time / time_taken;

      if (j == 0) {
        cout << "Dataset No: " << dataset_no << endl;
        cout << "Baseline Time: " << baseline_time << " ms\n";
        cout << "Triangles found: " << count << endl;
        cout << "Threads used: " << num_threads << endl;
      }
      cout << "Time Taken: " << time_taken << " ms\t";
      cout << "Speedup: " << speedup << endl;
    }
    cout << endl;
  }
}

void setDatasetParameters(int dataset_no, string &filename) {
  if (dataset_no == 1) {
    filename = "datasets/email-Eu-core.txt";
    baseline_time = 2.19481;
    max_edges = 25572;
    max_nodes = 1005;
  } else if (dataset_no == 2) {
    filename = "datasets/facebook_combined.txt";
    baseline_time = 12.3207;
    max_edges = 88234;
    max_nodes = 4039;
  } else if (dataset_no == 3) {
    filename = "datasets/com-lj.ungraph.txt";
    baseline_time = 7477.61;
    max_edges = 34681189;
    max_nodes = 4136524;
  } else if (dataset_no == 4) {
    filename = "datasets/com-friendster.ungraph.txt";
    max_edges = 1806067135;
    max_nodes = 65608366;
  }
}

int main() {
  string filename = "datasets/email-Eu-core.txt"; // Default
  vector<int> offset;
  vector<int> neighbors;
  int V, E;

  setDatasetParameters(dataset_no, filename);

  buildGraph(filename, offset, neighbors, V, E);

  printGraphStats(V, E);

  runOMP_SIMDVersion(offset, neighbors, V);

  return 0;
}