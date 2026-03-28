#include <algorithm>
#include <cmath>
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

// ----------------------------------------------------------
// ---------------- Scenario 1: Blocking P2P ----------------
// ----------------------------------------------------------
void pagerank_p2p(vector<int> &localNodes, vector<vector<int>> &inEdges,
                  vector<int> &ghostNodes, unordered_map<int, int> &ghostIndex,
                  vector<int> &outDegree, vector<int> &part,
                  unordered_set<int> &localSet, int numNodes, int rank,
                  int numRanks, MPI_Comm comm) {

  const double d = 0.85;
  const double tau = 1e-7;
  int N = numNodes;
  int localN = localNodes.size();

  // Initialize all local PR values to 1/N
  vector<double> pr(localN, 1.0 / N);

  // Ghost buffer holds PR values of remote nodes we need
  vector<double> ghostPR(ghostNodes.size(), 1.0 / N);

  // Build local index map: globalID -> local index
  unordered_map<int, int> localIndex;
  for (int i = 0; i < localN; i++)
    localIndex[localNodes[i]] = i;

  // Pre-compute communication structure (done once before iterations)
  // For each rank r: which of our local nodes does rank r need from us?
  // Answer: whichever of our local nodes appear as ghosts on rank r
  // We find this by checking: for each ghost node g we need,
  // part[g] tells us which rank owns g -> that rank needs to send it to us
  // Symmetrically: if rank r has g as ghost and part[g]==rank, we send to r

  // sendList[r] = local node indices we must send to rank r each iteration
  vector<vector<int>> sendList(numRanks);
  // recvList[r] = ghost indices we receive from rank r each iteration
  vector<vector<int>> recvList(numRanks);

  // For each ghost node we need, find its owner rank
  for (int gi = 0; gi < (int)ghostNodes.size(); gi++) {
    int g = ghostNodes[gi];
    int owner = part[g];
    recvList[owner].push_back(gi); // we receive ghost index gi from rank owner
  }

  // For each other rank, tell them which of their nodes we need and find out
  // which of our nodes they need
  for (int r = 0; r < numRanks; r++) {
    if (r == rank)
      continue;

    vector<int> needIDs(recvList[r].size());
    for (int i = 0; i < (int)recvList[r].size(); i++)
      needIDs[i] = ghostNodes[recvList[r][i]];
    int needCount = needIDs.size();

    int theirNeedCount;
    vector<int> theirNeedIDs;

    if (rank < r) {
      // lower rank sends first, then receives
      MPI_Send(&needCount, 1, MPI_INT, r, 10, comm);
      // send the global IDs of nodes we need from rank r
      MPI_Send(needIDs.data(), needCount, MPI_INT, r, 11, comm);
      MPI_Recv(&theirNeedCount, 1, MPI_INT, r, 10, comm, MPI_STATUS_IGNORE);
      theirNeedIDs.resize(theirNeedCount);
      MPI_Recv(theirNeedIDs.data(), theirNeedCount, MPI_INT, r, 11, comm,
               MPI_STATUS_IGNORE);
    } else {
      // higher rank receives first, then sends
      // receive count of nodes rank r needs from us
      MPI_Recv(&theirNeedCount, 1, MPI_INT, r, 10, comm, MPI_STATUS_IGNORE);
      theirNeedIDs.resize(theirNeedCount);
      // receive the global IDs rank r needs from us
      MPI_Recv(theirNeedIDs.data(), theirNeedCount, MPI_INT, r, 11, comm,
               MPI_STATUS_IGNORE);
      MPI_Send(&needCount, 1, MPI_INT, r, 10, comm);
      MPI_Send(needIDs.data(), needCount, MPI_INT, r, 11, comm);
    }

    // convert those global IDs to local indices for fast lookup during
    // iterations
    for (int g : theirNeedIDs)
      sendList[r].push_back(localIndex[g]);
  }

  // Pre-compute source lookup for each local node's incoming edges
  // srcType[i][j] = 0 means local, 1 means ghost
  // srcIdx[i][j]  = index into pr[] or ghostPR[]
  vector<vector<pair<int, int>>> srcLookup(localN);
  for (int i = 0; i < localN; i++) {
    for (int src : inEdges[i]) {
      if (localSet.count(src))
        srcLookup[i].push_back({0, localIndex[src]});
      else
        srcLookup[i].push_back({1, ghostIndex[src]});
    }
  }

  // PageRank iterations
  int iter = 0;
  double globalDiff = 1.0;

  double startTime = MPI_Wtime();

  while (globalDiff > tau) {
    // Exchange ghost PR values with other ranks
    for (int r = 0; r < numRanks; r++) {
      if (r == rank)
        continue;

      // Pack PR values to send to rank r
      vector<double> sendBuf(sendList[r].size());
      for (int i = 0; i < (int)sendList[r].size(); i++)
        sendBuf[i] = pr[sendList[r][i]];

      vector<double> recvBuf(recvList[r].size());

      // Send our values, receive their values
      if (rank < r) {
        MPI_Send(sendBuf.data(), sendBuf.size(), MPI_DOUBLE, r, 20, comm);
        MPI_Recv(recvBuf.data(), recvBuf.size(), MPI_DOUBLE, r, 20, comm,
                 MPI_STATUS_IGNORE);
      } else {
        MPI_Recv(recvBuf.data(), recvBuf.size(), MPI_DOUBLE, r, 20, comm,
                 MPI_STATUS_IGNORE);
        MPI_Send(sendBuf.data(), sendBuf.size(), MPI_DOUBLE, r, 20, comm);
      }

      // Store received values in ghost buffer
      for (int i = 0; i < (int)recvList[r].size(); i++)
        ghostPR[recvList[r][i]] = recvBuf[i];
    }

    // Compute new PR values for all local nodes
    vector<double> newPR(localN, (1.0 - d) / N);

    for (int i = 0; i < localN; i++) {
      for (int j = 0; j < (int)srcLookup[i].size(); j++) {
        int src = inEdges[i][j];
        int deg = outDegree[src];
        if (deg == 0)
          continue;
        double srcPR = (srcLookup[i][j].first == 0)
                           ? pr[srcLookup[i][j].second]
                           : ghostPR[srcLookup[i][j].second];
        newPR[i] += d * srcPR / deg;
      }
    }

    // Compute local L1 difference
    double localDiff = 0.0;
    for (int i = 0; i < localN; i++)
      localDiff += fabs(newPR[i] - pr[i]);

    // Reduce to get global L1 difference across all ranks
    MPI_Allreduce(&localDiff, &globalDiff, 1, MPI_DOUBLE, MPI_SUM, comm);

    pr = newPR;
    iter++;

    // if (rank == 0 && iter % 10 == 0)
    //  cout << "Iteration " << iter << " diff: " << globalDiff << endl;
  }

  double endTime = MPI_Wtime();

  if (rank == 0) {
    cout << "Converged in " << iter << " iterations" << endl;
    cout << "Time: " << (endTime - startTime) << " seconds" << endl;

    // Print top 5 nodes by PR value (local to rank 0 only for now)
    vector<pair<double, int>> ranked;
    for (int i = 0; i < localN; i++)
      ranked.push_back({pr[i], localNodes[i]});
    sort(ranked.rbegin(), ranked.rend());
    cout << "\nTop 5 nodes (rank 0 local):" << endl;
    for (int i = 0; i < 5 && i < (int)ranked.size(); i++)
      cout << "  Node " << ranked[i].second << " PR=" << ranked[i].first
           << endl;
  }
}

// ========================================================
// ---------------- Scenario 2: Collective ----------------
// ========================================================
void pagerank_collective(vector<int> &localNodes, vector<vector<int>> &inEdges,
                         vector<int> &outDegree, vector<int> &part,
                         unordered_set<int> &localSet, int numNodes, int rank,
                         int numRanks, MPI_Comm comm) {

  const double d = 0.85;
  const double tau = 1e-7;
  int N = numNodes;
  int localN = localNodes.size();

  // Build local index map: globalID -> local index
  unordered_map<int, int> localIndex;
  for (int i = 0; i < localN; i++)
    localIndex[localNodes[i]] = i;

  // Initialize local PR values to 1/N
  vector<double> pr(localN, 1.0 / N);

  // globalPR holds the full PR array for all nodes across all ranks
  // every rank maintains this after each Allgatherv call
  vector<double> globalPR(numNodes, 1.0 / N);

  // Allgatherv needs to know how many elements each rank contributes
  // and where each rank's data starts in the global array
  vector<int> recvcounts(numRanks, 0);
  vector<int> displs(numRanks, 0);

  // Count how many local nodes each rank has
  int myCount = localN;
  MPI_Allgather(&myCount, 1, MPI_INT, recvcounts.data(), 1, MPI_INT, comm);

  // Compute displacements: where in globalPR does each rank's data go?
  // But Allgatherv fills a contiguous buffer, so we need a mapping
  // rank 0's data goes at displs[0], rank 1's at displs[1], etc.
  displs[0] = 0;
  for (int r = 1; r < numRanks; r++)
    displs[r] = displs[r - 1] + recvcounts[r - 1];

  // recvBuf is a contiguous buffer where Allgatherv puts all ranks' PR values
  // recvBuf layout: [rank0 PR values][rank1 PR values]...
  vector<double> recvBuf(displs[numRanks - 1] + recvcounts[numRanks - 1]);

  // We need a mapping: for each position in recvBuf, which global node is it?
  // Since each rank sends its localNodes[] in order, we gather all localNodes
  // to build this mapping
  vector<int> allLocalNodes(displs[numRanks - 1] + recvcounts[numRanks - 1]);
  MPI_Allgatherv(localNodes.data(), localN, MPI_INT, allLocalNodes.data(),
                 recvcounts.data(), displs.data(), MPI_INT, comm);

  // Pre-compute srcLookup using globalPR indices
  // srcLookup[i][j] = index into globalPR for the j-th incoming neighbor of
  // local node i
  vector<vector<int>> srcLookup(localN);
  for (int i = 0; i < localN; i++) {
    for (int src : inEdges[i]) {
      srcLookup[i].push_back(
          src); // src is global node ID, index directly into globalPR
    }
  }

  // PageRank iterations
  int iter = 0;
  double globalDiff = 1.0;
  double startTime = MPI_Wtime();

  while (globalDiff > tau) {
    // Allgatherv: every rank shares its current PR values with all other ranks
    // Each rank sends pr[] (its local values), everyone receives into recvBuf
    MPI_Allgatherv(pr.data(), localN, MPI_DOUBLE, recvBuf.data(),
                   recvcounts.data(), displs.data(), MPI_DOUBLE, comm);

    // Map recvBuf values into globalPR using allLocalNodes mapping
    for (int i = 0; i < (int)allLocalNodes.size(); i++)
      globalPR[allLocalNodes[i]] = recvBuf[i];

    // Compute new PR values for all local nodes
    vector<double> newPR(localN, (1.0 - d) / N);

    for (int i = 0; i < localN; i++) {
      for (int src : srcLookup[i]) {
        int deg = outDegree[src];
        if (deg == 0)
          continue;
        newPR[i] += d * globalPR[src] / deg;
      }
    }

    // Compute local L1 difference
    double localDiff = 0.0;
    for (int i = 0; i < localN; i++)
      localDiff += fabs(newPR[i] - pr[i]);

    // Reduce to get global L1 difference
    MPI_Allreduce(&localDiff, &globalDiff, 1, MPI_DOUBLE, MPI_SUM, comm);

    pr = newPR;
    iter++;

    // if (rank == 0 && iter % 10 == 0)
    //  cout << "Iteration " << iter << " diff: " << globalDiff << endl;
  }

  double endTime = MPI_Wtime();

  if (rank == 0) {
    cout << "Converged in " << iter << " iterations" << endl;
    cout << "Time: " << (endTime - startTime) << " seconds" << endl;

    vector<pair<double, int>> ranked;
    for (int i = 0; i < localN; i++)
      ranked.push_back({pr[i], localNodes[i]});
    sort(ranked.rbegin(), ranked.rend());
    cout << "\nTop 5 nodes (rank 0 local):" << endl;
    for (int i = 0; i < 5 && i < (int)ranked.size(); i++)
      cout << "  Node " << ranked[i].second << " PR=" << ranked[i].first
           << endl;
  }
}

// ========================================================
// ----------- Scenario 3: Asynchronous Overlap -----------
// ========================================================
void pagerank_async(vector<int> &localNodes, vector<vector<int>> &inEdges,
                    vector<int> &ghostNodes,
                    unordered_map<int, int> &ghostIndex, vector<int> &outDegree,
                    vector<int> &part, unordered_set<int> &localSet,
                    vector<int> &internalNodes, vector<int> &boundaryNodes,
                    int numNodes, int rank, int numRanks, MPI_Comm comm) {

  const double d = 0.85;
  const double tau = 1e-7;
  int N = numNodes;
  int localN = localNodes.size();

  // Build local index map: globalID -> local index
  unordered_map<int, int> localIndex;
  for (int i = 0; i < localN; i++)
    localIndex[localNodes[i]] = i;

  // Initialize PR values
  vector<double> pr(localN, 1.0 / N);
  vector<double> ghostPR(ghostNodes.size(), 1.0 / N);

  // Build send/recv lists same as Scenario 1
  vector<vector<int>> sendList(numRanks);
  vector<vector<int>> recvList(numRanks);

  for (int gi = 0; gi < (int)ghostNodes.size(); gi++) {
    int g = ghostNodes[gi];
    int owner = part[g];
    recvList[owner].push_back(gi);
  }

  for (int r = 0; r < numRanks; r++) {
    if (r == rank)
      continue;

    vector<int> needIDs(recvList[r].size());
    for (int i = 0; i < (int)recvList[r].size(); i++)
      needIDs[i] = ghostNodes[recvList[r][i]];
    int needCount = needIDs.size();
    int theirNeedCount;
    vector<int> theirNeedIDs;

    if (rank < r) {
      MPI_Send(&needCount, 1, MPI_INT, r, 10, comm);
      MPI_Send(needIDs.data(), needCount, MPI_INT, r, 11, comm);
      MPI_Recv(&theirNeedCount, 1, MPI_INT, r, 10, comm, MPI_STATUS_IGNORE);
      theirNeedIDs.resize(theirNeedCount);
      MPI_Recv(theirNeedIDs.data(), theirNeedCount, MPI_INT, r, 11, comm,
               MPI_STATUS_IGNORE);
    } else {
      MPI_Recv(&theirNeedCount, 1, MPI_INT, r, 10, comm, MPI_STATUS_IGNORE);
      theirNeedIDs.resize(theirNeedCount);
      MPI_Recv(theirNeedIDs.data(), theirNeedCount, MPI_INT, r, 11, comm,
               MPI_STATUS_IGNORE);
      MPI_Send(&needCount, 1, MPI_INT, r, 10, comm);
      MPI_Send(needIDs.data(), needCount, MPI_INT, r, 11, comm);
    }

    for (int g : theirNeedIDs)
      sendList[r].push_back(localIndex[g]);
  }

  // Pre-compute srcLookup for internal and boundary nodes separately
  vector<vector<pair<int, int>>> srcLookupInternal(internalNodes.size());
  for (int ii = 0; ii < (int)internalNodes.size(); ii++) {
    int i = internalNodes[ii];
    for (int src : inEdges[i]) {
      srcLookupInternal[ii].push_back({0, localIndex[src]});
    }
  }

  vector<vector<pair<int, int>>> srcLookupBoundary(boundaryNodes.size());
  for (int bi = 0; bi < (int)boundaryNodes.size(); bi++) {
    int i = boundaryNodes[bi];
    for (int src : inEdges[i]) {
      if (localSet.count(src))
        srcLookupBoundary[bi].push_back({0, localIndex[src]});
      else
        srcLookupBoundary[bi].push_back({1, ghostIndex[src]});
    }
  }

  // send/recv buffers allocated once outside loop
  vector<vector<double>> sendBufs(numRanks), recvBufs(numRanks);
  for (int r = 0; r < numRanks; r++) {
    sendBufs[r].resize(sendList[r].size());
    recvBufs[r].resize(recvList[r].size());
  }

  // MPI request handles for non-blocking operations
  // 2 requests per rank pair: one Isend + one Irecv
  vector<MPI_Request> requests(numRanks * 2, MPI_REQUEST_NULL);

  int iter = 0;
  double globalDiff = 1.0;

  // Timing variables to measure overlap efficiency
  double commTime = 0.0, totalTime = 0.0;
  double startTime = MPI_Wtime();

  while (globalDiff > tau) {

    // Step 1: pack send buffers
    for (int r = 0; r < numRanks; r++) {
      if (r == rank)
        continue;
      for (int i = 0; i < (int)sendList[r].size(); i++)
        sendBufs[r][i] = pr[sendList[r][i]];
    }

    // Step 2: launch ALL non-blocking sends and receives immediately
    // this starts the communication in the background
    double commStart = MPI_Wtime();
    for (int r = 0; r < numRanks; r++) {
      if (r == rank)
        continue;
      MPI_Isend(sendBufs[r].data(), sendBufs[r].size(), MPI_DOUBLE, r, 20, comm,
                &requests[r * 2]);
      MPI_Irecv(recvBufs[r].data(), recvBufs[r].size(), MPI_DOUBLE, r, 20, comm,
                &requests[r * 2 + 1]);
    }

    // Step 3: compute INTERNAL nodes while communication is in progress
    // internal nodes don't need ghost values so we can compute them now
    vector<double> newPR(localN, (1.0 - d) / N);

    for (int ii = 0; ii < (int)internalNodes.size(); ii++) {
      int i = internalNodes[ii];
      for (int j = 0; j < (int)srcLookupInternal[ii].size(); j++) {
        int src = inEdges[i][j];
        int deg = outDegree[src];
        if (deg == 0)
          continue;
        newPR[i] += d * pr[srcLookupInternal[ii][j].second] / deg;
      }
    }

    // Step 4: wait for ALL communication to finish
    MPI_Waitall(numRanks * 2, requests.data(), MPI_STATUSES_IGNORE);
    commTime += MPI_Wtime() - commStart;

    // Step 5: unpack received ghost values
    for (int r = 0; r < numRanks; r++) {
      if (r == rank)
        continue;
      for (int i = 0; i < (int)recvList[r].size(); i++)
        ghostPR[recvList[r][i]] = recvBufs[r][i];
    }

    // Step 6: compute BOUNDARY nodes now that ghost values are available
    for (int bi = 0; bi < (int)boundaryNodes.size(); bi++) {
      int i = boundaryNodes[bi];
      for (int j = 0; j < (int)srcLookupBoundary[bi].size(); j++) {
        int src = inEdges[i][j];
        int deg = outDegree[src];
        if (deg == 0)
          continue;
        double srcPR = (srcLookupBoundary[bi][j].first == 0)
                           ? pr[srcLookupBoundary[bi][j].second]
                           : ghostPR[srcLookupBoundary[bi][j].second];
        newPR[i] += d * srcPR / deg;
      }
    }

    // Compute local L1 difference
    double localDiff = 0.0;
    for (int i = 0; i < localN; i++)
      localDiff += fabs(newPR[i] - pr[i]);

    MPI_Allreduce(&localDiff, &globalDiff, 1, MPI_DOUBLE, MPI_SUM, comm);

    pr = newPR;
    iter++;

    // if (rank == 0 && iter % 10 == 0)
    //  cout << "Iteration " << iter << " diff: " << globalDiff << endl;
  }

  double endTime = MPI_Wtime();
  totalTime = endTime - startTime;

  if (rank == 0) {
    cout << "Converged in " << iter << " iterations" << endl;
    cout << "Time: " << totalTime << " seconds" << endl;
    cout << "Communication time: " << commTime << " seconds" << endl;
    cout << "Overlap efficiency: " << (1.0 - commTime / totalTime) * 100.0
         << "% of comm hidden" << endl;

    vector<pair<double, int>> ranked;
    for (int i = 0; i < localN; i++)
      ranked.push_back({pr[i], localNodes[i]});
    sort(ranked.rbegin(), ranked.rend());
    cout << "\nTop 5 nodes (rank 0 local):" << endl;
    for (int i = 0; i < 5 && i < (int)ranked.size(); i++)
      cout << "  Node " << ranked[i].second << " PR=" << ranked[i].first
           << endl;
  }
}

////////////////////////////
//                        //
//          MAIN          //
//                        //
////////////////////////////

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

  if (rank == 0)
    cout << "\n--- Scenario 1: Blocking P2P ---" << endl;
  pagerank_p2p(localNodes, inEdges, ghostNodes, ghostIndex, outDegree, part,
               localSet, numNodes, rank, numRanks, MPI_COMM_WORLD);

  if (rank == 0)
    cout << "\n--- Scenario 2: Collective ---" << endl;
  pagerank_collective(localNodes, inEdges, outDegree, part, localSet, numNodes,
                      rank, numRanks, MPI_COMM_WORLD);

  if (rank == 0)
    cout << "\n--- Scenario 3: Async Overlap ---" << endl;
  pagerank_async(localNodes, inEdges, ghostNodes, ghostIndex, outDegree, part,
                 localSet, internalNodes, boundaryNodes, numNodes, rank,
                 numRanks, MPI_COMM_WORLD);

  // Print summary from each rank
  cout << "Rank " << rank << ": " << localNodes.size() << " local nodes, "
       << ghostNodes.size() << " ghost nodes, " << internalNodes.size()
       << " internal, " << boundaryNodes.size() << " boundary" << endl;

  MPI_Finalize();
  return 0;
}