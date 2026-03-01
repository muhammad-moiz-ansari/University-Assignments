# ============================================================
# PDC Assignment 2 - Parallel Triangle Counting
# Name   : [Your Name]
# ID     : 23i-0523
# Section: F
# ============================================================

CXX      = g++
CXXFLAGS = -O3
AVX2     = -mavx2 -mpopcnt
OMP      = -fopenmp

# Output binaries
V1 = v1
V2 = v2
V3 = v3
V4 = v4
V5 = v5
V6 = v6

# Source files
SRC1 = 23i-0523-F-TASK1-V1.cpp
SRC2 = 23i-0523-F-TASK1-V2.cpp
SRC3 = 23i-0523-F-TASK1-V3.cpp
SRC4 = 23i-0523-F-TASK1-V4.cpp
SRC5 = 23i-0523-F-TASK1-V5.cpp
SRC6 = 23i-0523-F-TASK1-V6.cpp

# ── Default: build all ──────────────────────────────────────
all: $(V1) $(V2) $(V3) $(V4) $(V5) $(V6)
	@echo ""
	@echo "  Build complete. All binaries ready."
	@echo "  Run 'make run' to execute all versions."
	@echo ""

# ── Individual targets ───────────────────────────────────────

# V1: Scalar Baseline — no special flags
$(V1): $(SRC1)
	@echo "[BUILD] V1 Scalar Baseline..."
	$(CXX) $(CXXFLAGS) $(SRC1) -o $(V1)

# V2: SIMD AVX2 — requires AVX2 + popcount
$(V2): $(SRC2)
	@echo "[BUILD] V2 AVX2 SIMD..."
	$(CXX) $(CXXFLAGS) $(AVX2) $(SRC2) -o $(V2)

# V3: OpenMP SIMD — requires OpenMP + AVX2
$(V3): $(SRC3)
	@echo "[BUILD] V3 OpenMP SIMD..."
	$(CXX) $(CXXFLAGS) $(AVX2) $(OMP) $(SRC3) -o $(V3)

# V4: OpenMP Threads — requires OpenMP only
$(V4): $(SRC4)
	@echo "[BUILD] V4 OpenMP Threads..."
	$(CXX) $(CXXFLAGS) $(OMP) $(SRC4) -o $(V4)

# V5: Hybrid OMP Threads + AVX2 — requires both
$(V5): $(SRC5)
	@echo "[BUILD] V5 Hybrid (OMP Threads + AVX2)..."
	$(CXX) $(CXXFLAGS) $(AVX2) $(OMP) $(SRC5) -o $(V5)

# V6: Hybrid OMP Threads + OMP SIMD — requires both
$(V6): $(SRC6)
	@echo "[BUILD] V6 Hybrid (OMP Threads + OMP SIMD)..."
	$(CXX) $(CXXFLAGS) $(AVX2) $(OMP) $(SRC6) -o $(V6)

# ── Run all versions sequentially ────────────────────────────
run: all
	@echo ""
	@echo "========================================"
	@echo "  Running V1: Scalar Baseline"
	@echo "========================================"
	./$(V1)
	@echo ""
	@echo "========================================"
	@echo "  Running V2: AVX2 SIMD"
	@echo "========================================"
	./$(V2)
	@echo ""
	@echo "========================================"
	@echo "  Running V3: OpenMP SIMD"
	@echo "========================================"
	./$(V3)
	@echo ""
	@echo "========================================"
	@echo "  Running V4: OpenMP Threads"
	@echo "========================================"
	./$(V4)
	@echo ""
	@echo "========================================"
	@echo "  Running V5: Hybrid (OMP + AVX2)"
	@echo "========================================"
	./$(V5)
	@echo ""
	@echo "========================================"
	@echo "  Running V6: Hybrid (OMP + OMP SIMD)"
	@echo "========================================"
	./$(V6)

# ── Run individual versions ───────────────────────────────────
run1: $(V1)
	./$(V1)

run2: $(V2)
	./$(V2)

run3: $(V3)
	./$(V3)

run4: $(V4)
	./$(V4)

run5: $(V5)
	./$(V5)

run6: $(V6)
	./$(V6)

# ── Clean binaries ────────────────────────────────────────────
clean:
	@echo "[CLEAN] Removing binaries..."
	rm -f $(V1) $(V2) $(V3) $(V4) $(V5) $(V6)
	@echo "Done."

# ── Help ─────────────────────────────────────────────────────
help:
	@echo ""
	@echo "PDC Assignment 2 - Build System"
	@echo "================================"
	@echo "  make          Build all versions"
	@echo "  make run      Build and run all versions"
	@echo "  make run1     Run V1 (Scalar Baseline)"
	@echo "  make run2     Run V2 (AVX2 SIMD)"
	@echo "  make run3     Run V3 (OpenMP SIMD)"
	@echo "  make run4     Run V4 (OpenMP Threads)"
	@echo "  make run5     Run V5 (Hybrid OMP+AVX2)"
	@echo "  make run6     Run V6 (Hybrid OMP+SIMD)"
	@echo "  make clean    Remove all binaries"
	@echo ""
	@echo "Requirements: g++, OpenMP, AVX2-capable CPU"
	@echo ""

.PHONY: all run run1 run2 run3 run4 run5 run6 clean help
