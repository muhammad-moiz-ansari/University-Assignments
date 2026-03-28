# 23i-0523_F_A3 — Scalable PageRank Engine

**Course:** CS 3006 — Parallel and Distributive Computing  
**Student ID:** 23i-0523 | **Section:** F  
**Dataset:** web-Google (875,713 nodes, 5,105,039 edges)

---

## Overview

A distributed-memory PageRank engine implemented using MPI and ParMETIS.  
The engine partitions the web-Google graph across multiple MPI ranks using  
ParMETIS to minimize cross-rank communication, then computes PageRank using  
three different communication strategies.

---

## Prerequisites

The following must be installed and configured before building:

| Dependency   | Purpose                        |
|--------------|--------------------------------|
| OpenMPI      | MPI runtime and compiler       |
| ParMETIS     | Parallel graph partitioning    |
| METIS        | Required by ParMETIS           |
| GKlib        | Required by METIS              |

Libraries are expected at `/home/moiz129/local/` (include + lib).  
If your path differs, update `INCLUDES` and `LIBS` in the Makefile.

---

## File Structure
```
Assignment-3/
├── 23i-0523_F_A3.cpp     ← main source file (all 3 scenarios)
├── Makefile              ← build and run automation
└── README.md             ← this file
```

---

## Building
```bash
# Compile the program
make
```

This runs:
```bash
mpicxx -O2 -o 23i-0523_F_A3 23i-0523_F_A3.cpp \
  -I/home/moiz129/local/include \
  -L/home/moiz129/local/lib \
  -lparmetis -lmetis \
  -Wl,-rpath,/home/moiz129/local/lib
```

---

## Running

### Run with a specific number of processes
```bash
make run NP=2     # 2 processes  (1 per node)
make run NP=4     # 4 processes  (2 per node)
make run NP=8     # 8 processes  (4 per node, oversubscribed)
make run NP=16    # 16 processes (8 per node, oversubscribed)
```

> `--oversubscribe` is added automatically when NP > 4.

### Run all process counts back to back
```bash
make all
```

This runs 2, 4, 8, and 16 processes sequentially — useful for  
collecting all scaling data in one go.

### Clean build artifacts
```bash
make clean
```

### Show usage help
```bash
make help
```

---

## Hostfile

The Makefile uses `~/hostfile` by default. It should look like:
```
master slots=8
slave1 slots=8
```

Make sure both nodes are reachable via SSH without a password.  
If your hostfile is in a different location, update `HOSTFILE` in the Makefile.

---

## Network Configuration

The program uses the host-only VMware network interface `ens37` for  
MPI communication. This is set via `--mca btl_tcp_if_include ens37`.

If your interface name is different, check with:
```bash
ip a
```
Then update `MPI_IF` in the Makefile accordingly.

---

## What the Program Does

### Step 1 — Graph Loading
Reads `web-Google.txt` and remaps node IDs to a contiguous 0-based  
range (the dataset has gaps in node IDs).

### Step 2 — CSR Construction
Builds a Compressed Sparse Row representation of the graph.  
An undirected version is built for ParMETIS (reverse edges added).

### Step 3 — ParMETIS Partitioning
Calls `ParMETIS_V3_PartKway` to assign nodes to ranks while  
minimizing the number of edges crossing partition boundaries (edge cut).

### Step 4 — Redistribution & Classification
Each rank keeps only its assigned nodes and classifies them:
- **Internal** — all incoming links from the same rank (no communication)
- **Boundary** — at least one incoming link from a remote rank
- **Ghost Cells** — local buffers storing remote PageRank values

### Step 5 — PageRank (3 Scenarios)

| Scenario | Method | Key MPI Calls |
|----------|--------|---------------|
| 1 — Blocking P2P | Manual handshake, sequential | `MPI_Send`, `MPI_Recv` |
| 2 — Collective | One call per iteration | `MPI_Allgatherv` |
| 3 — Async Overlap | Hides comm behind computation | `MPI_Isend`, `MPI_Irecv`, `MPI_Waitall` |

**Parameters:**
- Damping factor `d = 0.85`
- Convergence threshold `τ = 10⁻⁷` (L1 norm)
- Dataset converges in **75 iterations**

---

## Expected Output (2 processes)
```
╔══════════════════════════════════════════╗
║           GRAPH INFORMATION              ║
╠══════════════════════════════════════════╣
║  Edges Loaded  : 5105039                 ║
║  Total Nodes   : 875713                  ║
╚══════════════════════════════════════════╝

┌──────────────────────────────────────────┐
│           PARTITION RESULTS              │
├──────────────────────────────────────────┤
│  Rank 0   owns 439084                    │
│  Rank 1   owns 436629                    │
└──────────────────────────────────────────┘

  Edge cut: 27866

┌──────────────────────────────────────────┐
│       Scenario 1: Blocking P2P           │
└──────────────────────────────────────────┘
Converged in 75 iterations
Time: ~15 seconds

┌──────────────────────────────────────────┐
│       Scenario 2: Collective             │
└──────────────────────────────────────────┘
Converged in 75 iterations
Time: ~13 seconds

┌──────────────────────────────────────────┐
│       Scenario 3: Async Overlap          │
└──────────────────────────────────────────┘
Converged in 75 iterations
Time: ~13 seconds
Overlap efficiency: ~17%

╔══════════════════════════════════════════════════════════════╗
║              PARTITION SUMMARY (ALL RANKS)                  ║
╠══════════╦══════════════╦═════════════╦══════════╦══════════╣
║  Rank    ║  Local Nodes ║  Ghost Nodes║ Internal ║ Boundary ║
╠══════════╬══════════════╬═════════════╬══════════╬══════════╣
║  0       ║  439084      ║  8292       ║  433342  ║  5742    ║
║  1       ║  436629      ║  8255       ║  430526  ║  6103    ║
╚══════════╩══════════════╩═════════════╩══════════╩══════════╝
```

---

## Performance Summary

| Processes | S1 P2P (s) | S2 Collective (s) | S3 Async (s) |
|-----------|------------|-------------------|--------------|
| 2         | 15.25      | 12.88             | 13.48        |
| 4         | 10.95      | 10.12             | 9.23         |
| 8         | 7.80       | 7.66              | 6.08         |
| 16*       | 15.47      | 16.58             | 8.65         |

> \* 16 processes are oversubscribed on 2 physical VMs — regression is expected for S1 and S2.  
> S3 Async is most resilient due to communication-computation overlap.

---

## Compilation Flags Reference

| Flag | Purpose |
|------|---------|
| `-O2` | Optimization level 2 |
| `-I/home/moiz129/local/include` | ParMETIS/METIS headers |
| `-L/home/moiz129/local/lib` | ParMETIS/METIS libraries |
| `-lparmetis -lmetis` | Link against ParMETIS and METIS |
| `-Wl,-rpath,...` | Embed library path in binary (no need to set LD_LIBRARY_PATH) |

---

## Troubleshooting

**`libmetis.so: cannot open shared object file`**  
The library path is not set on the remote node. Run on slave1:
```bash
echo 'export LD_LIBRARY_PATH=/home/moiz129/local/lib' >> ~/.bash_profile
```
Or the Makefile already passes `-x LD_LIBRARY_PATH=...` to handle this automatically.

**Program hangs on startup**  
MPI deadlock or network issue. Make sure `ens37` is the correct  
interface name and both nodes can ping each other:
```bash
ping 192.168.5.11   # from master
ping 192.168.5.10   # from slave1
```

**`--oversubscribe` warning**  
Normal when running more processes than physical cores.  
Results are valid but reflect software-simulated parallelism.

---

*Assignment 3 — CS 3006 | 23i-0523 Section F*