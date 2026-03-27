# Profiling Guide - Complete Instructions

## Quick Reference: Perf Commands

### Prerequisites
```bash
# Install perf if not available
sudo apt-get install linux-tools-common linux-tools-generic

# Grant permissions (may be needed)
sudo sysctl -w kernel.perf_event_paranoid=-1
```

---

## Task 1: Logistic Regression Profiling

### V1 - Serial Version
```bash
perf stat -e instructions,cycles,cache-misses,cache-references,branch-misses,branches \
  ./task1_v1 2>&1 | tee perf_task1_v1.txt
```

**Expected Metrics to Note:**
- **CPU Utilization:** Should be ~1.0 (single CPU)
- **Instructions:** ~3.2-3.5 billion
- **IPC (Instructions Per Cycle):** ~1.3-1.5 (compute-intensive)
- **Cache Miss Rate:** ~15-20% (sequential access, good locality)
- **Branch Mispredict Rate:** ~1-3% (simple control flow)

**Analysis Points for Report:**
- High IPC indicates compute-bound workload
- Good cache performance from sequential record access
- Baseline for comparison with parallel versions

---

### V2 - Multi-threaded (8 Threads, OS Scheduling)
```bash
perf stat -e instructions,cycles,cache-misses,cache-references,branch-misses,branches \
  ./task1_v2 2>&1 | tee perf_task1_v2.txt
```

**Expected Changes from V1:**
- **CPU Utilization:** ~6.0-6.5 (good parallelization)
- **Instructions:** Slightly higher (~3.3-3.6B) due to thread overhead
- **IPC:** Slightly lower (~1.2-1.4) due to cache coherency
- **Cache Miss Rate:** +1-3% increase vs V1
- **Total Time:** ~1/6th of V1

**Analysis Points:**
- CPU utilization matches speedup (6.42×)
- IPC degradation minimal (good parallel efficiency)
- Cache miss increase expected (multi-core cache sharing)
- Still compute-bound (no memory bottleneck)

---

### V3 - Multi-threaded (8 Threads, CPU Affinity)
```bash
perf stat -e instructions,cycles,cache-misses,cache-references,branch-misses,branches \
  ./task1_v3 2>&1 | tee perf_task1_v3.txt
```

**Expected vs V2:**
- **CPU Utilization:** Similar (~6.0-6.5) but slower wall-clock time
- **IPC:** Lower (~1.1-1.3) due to hyper-threading contention
- **Cache Miss Rate:** +2-4% vs V2
- **Why Slower:** Logical core pairing on same physical cores

**Analysis Points:**
- Affinity forces threads onto hyper-threaded pairs
- Shared execution units reduce effective IPC
- Example: Thread 0 (Core 0) and Thread 4 (Core 4 logical) compete
- OS (V2) better distributes load across physical cores

---

## Task 2: SpMV Profiling

### V1 - Serial Version
```bash
perf stat -e instructions,cycles,cache-misses,cache-references,branch-misses,branches \
  -d ./task2_v1 2>&1 | tee perf_task2_v1.txt
```

**Expected Metrics:**
- **IPC:** **VERY LOW (~0.7-0.9)** - Memory bottleneck!
- **Cache Miss Rate:** **HIGH (~40-45%)** - Random access pattern
- **Instructions:** ~150-200M
- **Cycles:** Disproportionately high vs instructions

**Analysis Points:**
- Low IPC confirms memory-bound workload
- High cache miss rate from sparse matrix structure
- CPU stalls waiting for data (memory wall)
- This is the bottleneck, not computation

---

### V2 - Multi-threaded (8 Threads)
```bash
perf stat -e instructions,cycles,cache-misses,cache-references,LLC-loads,LLC-load-misses \
  ./task2_v2 2>&1 | tee perf_task2_v2.txt
```

**Expected:**
- **CPU Utilization:** ~4.0-4.5 (NOT 6+ like Task 1!)
- **IPC:** Still low (~0.7-0.9) - Memory bound persists
- **Cache Miss Rate:** Similar to V1 (~40-45%)
- **Speedup Limited:** Can't exceed memory bandwidth

**Analysis Points:**
- Speedup plateaus at ~4× despite 8 threads
- All cores share memory bus (bandwidth saturated)
- Sorting by row helps (prevents false sharing) but can't overcome bandwidth limit
- LLC (Last Level Cache) misses show memory subsystem bottleneck

**Advanced Metrics (if available):**
```bash
perf stat -e cycles,instructions,cache-misses,cache-references,\
  mem_load_retired.l3_miss,mem_inst_retired.all_loads \
  ./task2_v2
```

---

### V3 - Multi-threaded (8 Threads, Affinity)
```bash
perf stat -e instructions,cycles,cache-misses,cache-references \
  ./task2_v3 2>&1 | tee perf_task2_v3.txt
```

**Expected vs V2:**
- **CPU Utilization:** Similar but slower execution
- **IPC:** Unchanged (still memory-bound)
- **Cache Miss Rate:** May be slightly worse
- **Why Slower (19%):** Affinity prevents NUMA optimization

**Analysis Points:**
- No data reuse → affinity doesn't help cache locality
- OS (V2) can migrate threads closer to memory controller
- V3 pins threads, potentially far from data (NUMA penalty)
- Memory-bound + pinning = worst combination

---

## Task 3: BFS Profiling

### V1 - Serial Version
```bash
perf stat -e instructions,cycles,cache-misses,cache-references,branch-misses,branches \
  ./task3_v1 2>&1 | tee perf_task3_v1.txt
```

**Expected Metrics:**
- **IPC:** Moderate (~1.0-1.2) - Mixed compute/memory
- **Cache Miss Rate:** Moderate (~25-35%) - Graph locality
- **Branch Mispredict:** Low (~2-3%) - Simple BFS logic
- **Characteristics:** Between Task 1 (compute) and Task 2 (memory)

---

### V2 - Multi-threaded (8 Threads)
```bash
perf stat -e instructions,cycles,cache-misses,cache-references \
  ./task3_v2 2>&1 | tee perf_task3_v2.txt
```

**Expected:**
- **CPU Utilization:** ~4.0 (plateau at 8 threads)
- **IPC:** Lower than V1 due to atomic overhead
- **Speedup:** ~4× (limited by synchronization)

**Analysis Points:**
- Plateau from 4T→8T shows synchronization bottleneck
- Atomic CAS creates contention
- Barriers every BFS level add overhead
- Irregular frontier sizes cause load imbalance

**Additional Insight:**
```bash
# Check atomic operation overhead
perf stat -e cpu-clock,task-clock,context-switches ./task3_v2
```

---

### V3 - Multi-threaded (8 Threads, Affinity)
```bash
perf stat -e instructions,cycles,cache-misses,cache-references \
  ./task3_v3 2>&1 | tee perf_task3_v3.txt
```

**Expected vs V2:**
- **CPU Utilization:** Similar
- **Speedup:** 7% slower than V2
- **Why:** Graph traversal too random for affinity to help

---

## Sample Output Format

Here's what a good perf stat output looks like:

```
 Performance counter stats for './task1_v1':

        833.482616 msec task-clock                #    0.999 CPUs utilized
                45 context-switches                #    0.054 K/sec
                 2 cpu-migrations                  #    0.002 K/sec
            89,234 page-faults                     #    0.107 M/sec
     3,245,678,901 cycles                          #    3.895 GHz
     4,598,234,567 instructions                    #    1.42  insn per cycle
       892,345,678 branches                        #  1070.789 M/sec
        15,234,567 branch-misses                   #    1.71% of all branches
       124,567,234 cache-references                #  149.456 M/sec
        18,934,567 cache-misses                    #   15.20 % of all cache refs

       0.834123456 seconds time elapsed

       0.823456789 seconds user
       0.010234567 seconds sys
```

**Key Metrics Highlighted:**
- `insn per cycle`: IPC = 1.42 (good for compute)
- `cache-miss %`: 15.20% (reasonable)
- `branch-miss %`: 1.71% (excellent)
- `CPUs utilized`: 0.999 (fully serial)

---

## How to Take Screenshots

### Option 1: Terminal Screenshot
1. Run perf command
2. Take screenshot (PrtScn or Snipping Tool)
3. Crop to show just the stats table
4. Save as `perf_task1_v1.png`

### Option 2: Save Text and Format
1. Run: `perf stat ... 2>&1 | tee output.txt`
2. Copy relevant lines into report in code block:
   ```
   Performance counter stats for './task1_v1':
   
           833.48 msec task-clock                #    0.999 CPUs utilized
        3,245,678,901 cycles
        4,598,234,567 instructions              #    1.42  insn per cycle
   ```

---

## Analysis Template for Report

Use this structure for each profiling result:

**Task X - VY Profiling Analysis:**

1. **Key Metrics:**
   - IPC: X.XX (interpretation)
   - Cache Miss Rate: XX.X%
   - CPU Utilization: X.XX cores

2. **Bottleneck Identification:**
   - [Compute-bound / Memory-bound / Sync-bound]
   - Evidence: [cite specific metrics]

3. **Comparison to Baseline:**
   - IPC change: +/- X.X%
   - Cache behavior: [improved/degraded/similar]
   - Reason: [explain why]

4. **Performance Implications:**
   - Why this explains speedup/slowdown
   - What could be optimized

---

## Advanced Profiling (Optional - Extra Credit)

### Cache Hierarchy Analysis
```bash
perf stat -e L1-dcache-load-misses,L1-dcache-loads,\
  LLC-load-misses,LLC-loads ./task2_v2
```

### Memory Bandwidth Measurement
```bash
perf stat -e uncore_imc/data_reads/,uncore_imc/data_writes/ ./task2_v2
```

### Context Switch Overhead
```bash
perf stat -e context-switches,cpu-migrations,page-faults ./task3_v2
```

---

## Checklist: All Required Profiling

- [ ] Task 1 V1 perf output
- [ ] Task 1 V2 perf output
- [ ] Task 1 V3 perf output
- [ ] Task 2 V1 perf output
- [ ] Task 2 V2 perf output
- [ ] Task 2 V3 perf output
- [ ] Task 3 V1 perf output
- [ ] Task 3 V2 perf output
- [ ] Task 3 V3 perf output

**Total: 9 profiling results needed**

---

## Quick Troubleshooting

**Error: "perf not found"**
```bash
sudo apt-get install linux-tools-$(uname -r)
```

**Error: "Permission denied"**
```bash
sudo sysctl -w kernel.perf_event_paranoid=-1
# Or run with sudo
sudo perf stat ...
```

**Error: "Event not found"**
```bash
# Use simpler event set
perf stat -e instructions,cycles ./program
```

**No output / hangs:**
- Make sure program actually runs and exits
- Check dataset files are in correct location
- Verify program doesn't wait for input

---

## Final Tip

**Order of running profiling:**
1. Start with V1 (establish baseline)
2. Compare V2 to V1 (see parallel overhead)
3. Compare V3 to V2 (see affinity impact)

This narrative flow makes your analysis clearer in the report!

---

*Generated: February 2026*
*For: PDC Assignment 1 Profiling Requirements*
