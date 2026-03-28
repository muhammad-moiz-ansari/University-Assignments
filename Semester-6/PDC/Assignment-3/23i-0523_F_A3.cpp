#include <algorithm>
#include <fstream>
#include <iostream>
#include <mpi.h>
#include <parmetis.h>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

void parse_graph(string filename, vector<pair<int, int>> &edges, int &numNodes,
                 unordered_map<int, int> &nodeRemap) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Could not open file!" << endl;
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  string line;
  int nextID = 0;

  while (getline(file, line)) {
    if (line[0] == '#')
      continue;

    istringstream iss(line);
    int from, to;
    iss >> from >> to;

    if (nodeRemap.find(from) == nodeRemap.end())
      nodeRemap[from] = nextID++;
    if (nodeRemap.find(to) == nodeRemap.end())
      nodeRemap[to] = nextID++;

    edges.push_back({nodeRemap[from], nodeRemap[to]});
  }

  file.close();
  numNodes = nextID;
}

// Building CSR from edge list
// xadj and adjncy --> two CSR arrays
// numNodes = maxNode + 1
void build_csr(vector<pair<int, int>> &edges, int numNodes, vector<int> &xadj,
               vector<int> &adjncy) {

  // Make graph undirected by adding reverse edges
  // ParMETIS requires undirected graph (both A->B and B->A must exist)
  vector<pair<int, int>> allEdges = edges;
  for (auto &e : edges)
    allEdges.push_back({e.second, e.first});

  // Remove duplicate edges (in case original graph already had some reverse
  // edges)
  sort(allEdges.begin(), allEdges.end());
  allEdges.erase(unique(allEdges.begin(), allEdges.end()), allEdges.end());

  // Also remove self-loops (A->A) which ParMETIS doesn't allow
  allEdges.erase(
      remove_if(allEdges.begin(), allEdges.end(),
                [](const pair<int, int> &e) { return e.first == e.second; }),
      allEdges.end());

  // Counting no. of neighbors for each node
  // (number of outgoing edges from node i)
  vector<int> degree(numNodes, 0);
  for (auto &e : allEdges)
    degree[e.first]++;

  // Building xadj using a prefix sum of degrees
  // xadj[i] = sum of degrees of nodes 0..i-1
  xadj.resize(numNodes + 1, 0);
  for (int i = 0; i < numNodes; i++)
    xadj[i + 1] = xadj[i] + degree[i];

  // Filling adjncy with actual neighbor IDs
  // Temp array "pos" to track insertion position per node
  adjncy.resize(allEdges.size());
  vector<int> pos(xadj.begin(), xadj.end());

  for (auto &e : allEdges) {
    int from = e.first;
    int to = e.second;
    adjncy[pos[from]++] = to;
  }
}

// Partitions the graph using ParMETIS
// Returns part[] array: part[i] = which rank owns node i
void parmetis_partition(vector<int> &xadj, vector<int> &adjncy, int numNodes,
                        int numRanks, vector<int> &part, MPI_Comm comm) {

  // Building vtxdist
  // vtxdist[i] = first node owned by rank i
  // vtxdist[numRanks] = total nodes (end marker)
  vector<idx_t> vtxdist(numRanks + 1);
  vtxdist[0] = 0;
  for (int i = 0; i < numRanks; i++)
    vtxdist[i + 1] = vtxdist[i] + (numNodes / numRanks);
  vtxdist[numRanks] = numNodes;

  // Each rank extracts its local slice of CSR
  // rank i owns nodes from vtxdist[rank] to vtxdist[rank+1]-1
  int rank;
  MPI_Comm_rank(comm, &rank);

  int localStart = vtxdist[rank];
  int localEnd = vtxdist[rank + 1];
  int localN = localEnd - localStart;

  // Extract local portion of xadj
  // ParMETIS wants local xadj to start from 0, not from global offset
  vector<idx_t> local_xadj(localN + 1);
  int edgeOffset = xadj[localStart];
  for (int i = 0; i <= localN; i++)
    local_xadj[i] = xadj[localStart + i] - edgeOffset;

  // Extract local portion of adjncy
  int localEdges = xadj[localEnd] - xadj[localStart];
  vector<idx_t> local_adjncy(localEdges);
  for (int i = 0; i < localEdges; i++)
    local_adjncy[i] = adjncy[edgeOffset + i];

  // Set up ParMETIS parameters
  idx_t ncon = 1;
  idx_t nparts = numRanks;
  idx_t edgecut = 0;
  idx_t wgtflag = 0;
  idx_t numflag = 0;
  real_t ubvec = 1.05f;
  vector<real_t> tpwgts(nparts * ncon, 1.0f / nparts);
  idx_t options[3] = {0, 0, 0};
  vector<idx_t> local_part(localN);

  // Calling ParMETIS
  ParMETIS_V3_PartKway(vtxdist.data(), local_xadj.data(), local_adjncy.data(),
                       NULL, NULL, &wgtflag, &numflag, &ncon, &nparts,
                       tpwgts.data(), &ubvec, options, &edgecut,
                       local_part.data(), &comm);

  // Gather all local parts into global part array on rank 0
  vector<int> recvcounts(numRanks), displs(numRanks);
  for (int i = 0; i < numRanks; i++) {
    recvcounts[i] = vtxdist[i + 1] - vtxdist[i];
    displs[i] = vtxdist[i];
  }

  part.resize(numNodes);
  // Collecting variable-size arrays from all ranks into rank 0
  MPI_Gatherv(local_part.data(), localN, MPI_INT, part.data(),
              recvcounts.data(), displs.data(), MPI_INT, 0, comm);

  if (rank == 0) {
    cout << "Edge cut: " << edgecut << endl;

    // Counting how many nodes went to each rank
    vector<int> count(numRanks, 0);
    for (int i = 0; i < numNodes; i++)
      count[part[i]]++;
    for (int i = 0; i < numRanks; i++)
      cout << "Rank " << i << " owns " << count[i] << " nodes" << endl;
  }
}

void redistribute_graph(vector<pair<int, int>> &edges, vector<int> &part,
                        int numNodes, int rank, int numRanks,
                        vector<int> &localNodes, vector<vector<int>> &inEdges,
                        vector<int> &ghostNodes,
                        unordered_map<int, int> &ghostIndex,
                        unordered_set<int> &localSet) {

  // Step 1: collect which nodes belong to this rank
  for (int i = 0; i < numNodes; i++)
    if (part[i] == rank)
      localNodes.push_back(i);

  // Step 2: build a fast lookup -> is node i owned by this rank?
  localSet = unordered_set<int>(localNodes.begin(), localNodes.end());

  // Step 3: for each local node, find all incoming edges from the original
  // directed graph and store them
  // inEdges[i] = list of nodes that point INTO localNodes[i]
  inEdges.resize(localNodes.size());

  // build a map: globalNodeID -> index in localNodes array
  unordered_map<int, int> localIndex;
  for (int i = 0; i < (int)localNodes.size(); i++)
    localIndex[localNodes[i]] = i;

  // scan all edges, keep only those where destination is a local node
  for (auto &e : edges) {
    int from = e.first;
    int to = e.second;

    // we only care about edges pointing INTO our local nodes
    if (localIndex.find(to) == localIndex.end())
      continue;

    int idx = localIndex[to];
    inEdges[idx].push_back(from);

    // Step 4: if the source node is remote, it becomes a ghost node
    if (localSet.find(from) == localSet.end()) {
      if (ghostIndex.find(from) == ghostIndex.end()) {
        ghostIndex[from] = ghostNodes.size();
        ghostNodes.push_back(from);
      }
    }
  }
}

void classify_vertices(vector<vector<int>> &inEdges,
                       unordered_set<int> &localSet, vector<int> &internalNodes,
                       vector<int> &boundaryNodes) {

  for (int i = 0; i < (int)inEdges.size(); i++) {
    bool isBoundary = false;

    for (int src : inEdges[i]) {
      if (localSet.find(src) == localSet.end()) {
        isBoundary = true;
        break;
      }
    }

    if (isBoundary)
      boundaryNodes.push_back(i);
    else
      internalNodes.push_back(i);
  }
}

void compute_outdegree(vector<pair<int, int>> &edges, int numNodes,
                       vector<int> &outDegree) {
  // count outgoing edges for each node from the directed edge list
  outDegree.assign(numNodes, 0);
  for (auto &e : edges)
    outDegree[e.first]++;
}

int main(int argc, char *argv[]) {
  string filename = "/home/moiz129/cloud/web-Google.txt";
  vector<pair<int, int>> edges;
  unordered_map<int, int> nodeRemap;
  int numNodes = 0;

  MPI_Init(&argc, &argv);
  int rank, numRanks;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numRanks);

  if (rank == 0) {
    parse_graph(filename, edges, numNodes, nodeRemap);
    cout << "Edges loaded: " << edges.size() << endl;
    cout << "Total nodes after remap: " << numNodes << endl;
  }

  // Broadcasting numNodes to all ranks
  MPI_Bcast(&numNodes, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // Building CSR on rank 0
  vector<int> xadj, adjncy;
  if (rank == 0) {
    build_csr(edges, numNodes, xadj, adjncy);
    nodeRemap.clear();
  }

  int xadjSize = 0, adjncySize = 0;
  if (rank == 0) {
    xadjSize = xadj.size();
    adjncySize = adjncy.size();
  }
  MPI_Bcast(&xadjSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&adjncySize, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank != 0) {
    xadj.resize(xadjSize);
    adjncy.resize(adjncySize);
  }
  MPI_Bcast(xadj.data(), xadjSize, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(adjncy.data(), adjncySize, MPI_INT, 0, MPI_COMM_WORLD);

  // Run ParMETIS partitioning
  vector<int> part;
  parmetis_partition(xadj, adjncy, numNodes, numRanks, part, MPI_COMM_WORLD);

  // Broadcast part[] to all ranks so everyone knows who owns what
  if (rank != 0)
    part.resize(numNodes);
  MPI_Bcast(part.data(), numNodes, MPI_INT, 0, MPI_COMM_WORLD);

  // Broadcast edges to all ranks so redistribution works on all ranks
  int edgeCount = 0;
  if (rank == 0)
    edgeCount = edges.size();
  MPI_Bcast(&edgeCount, 1, MPI_INT, 0, MPI_COMM_WORLD);
  if (rank != 0)
    edges.resize(edgeCount);

  // Send edges as flat int array (from, to pairs)
  vector<int> edgeFlat;
  if (rank == 0) {
    for (auto &e : edges) {
      edgeFlat.push_back(e.first);
      edgeFlat.push_back(e.second);
    }
  }
  edgeFlat.resize(edgeCount * 2);
  MPI_Bcast(edgeFlat.data(), edgeCount * 2, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank != 0) {
    for (int i = 0; i < edgeCount; i++)
      edges[i] = {edgeFlat[i * 2], edgeFlat[i * 2 + 1]};
  }
  edgeFlat.clear();

  // Compute outDegree BEFORE clearing edges
  vector<int> outDegree;
  if (rank == 0)
    compute_outdegree(edges, numNodes, outDegree);

  // Broadcast outDegree to all ranks
  outDegree.resize(numNodes);
  MPI_Bcast(outDegree.data(), numNodes, MPI_INT, 0, MPI_COMM_WORLD);

  // Run redistribution on all ranks
  vector<int> localNodes;
  vector<vector<int>> inEdges;
  vector<int> ghostNodes;
  unordered_map<int, int> ghostIndex;
  unordered_set<int> localSet;

  redistribute_graph(edges, part, numNodes, rank, numRanks, localNodes, inEdges,
                     ghostNodes, ghostIndex, localSet);

  edges.clear();

  vector<int> internalNodes, boundaryNodes;
  classify_vertices(inEdges, localSet, internalNodes, boundaryNodes);

  // Print summary from each rank
  cout << "Rank " << rank << ": " << localNodes.size() << " local nodes, "
       << ghostNodes.size() << " ghost nodes, " << internalNodes.size()
       << " internal, " << boundaryNodes.size() << " boundary" << endl;

  MPI_Finalize();
  return 0;
}