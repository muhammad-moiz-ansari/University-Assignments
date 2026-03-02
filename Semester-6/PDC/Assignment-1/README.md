# PDC Assignment 1 - Build and Run Guide

## Prerequisites
- g++ compiler with C++11 support
- pthread library
- Linux OS (Ubuntu 24.04 recommended)

## Compilation
```bash
make all
```

Or individually:
```bash
g++ -std=c++11 -pthread -O2 23i-0523-F-TASK1-V1.cpp -o task1_v1
g++ -std=c++11 -pthread -O2 23i-0523-F-TASK1-V2.cpp -o task1_v2
# ... etc
```

## Execution

### Task 1
```bash
./task1_v1  # Serial version
./task1_v2  # Multi-threaded (OS scheduling)
./task1_v3  # Multi-threaded (CPU affinity)
```

### Task 2
```bash
./task2_v1
./task2_v2
./task2_v3
```

### Task 3
```bash
./task3_v1
./task3_v2
./task3_v3
```

## Dataset Locations
- Task 1: `supersymmetry_dataset.csv`
- Task 2: `webbase-1M.mtx`
- Task 3: `web-Google.txt`

Place datasets in the same directory as executables.

## Output
Programs write timing data to stdout in CSV format: