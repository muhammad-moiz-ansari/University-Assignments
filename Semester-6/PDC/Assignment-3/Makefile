# ============================================================
#  Makefile for 23i-0523_F_A3
#  Usage:
#    make          -> compile only
#    make run NP=2  -> compile + run with 2 processes
#    make run NP=4  -> compile + run with 4 processes
#    make run NP=8  -> compile + run with 8 processes
#    make run NP=16 -> compile + run with 16 processes
#    make clean     -> remove binary
#    make all       -> compile + run all (2, 4, 8, 16)
# ============================================================

TARGET   = 23i-0523_F_A3
SRC      = 23i-0523_F_A3.cpp
CXX      = mpicxx
INCLUDES = -I/home/moiz129/local/include
LIBS     = -L/home/moiz129/local/lib -lparmetis -lmetis -Wl,-rpath,/home/moiz129/local/lib
CXXFLAGS = -O2

HOSTFILE = $(HOME)/hostfile
MPI_IF   = ens37
MPI_ENV  = LD_LIBRARY_PATH=/home/moiz129/local/lib

# Default NP if not specified
NP ?= 2

# Oversubscribe flag only needed for NP > 4 (more than 2 slots per node)
OVERSUB  = $(shell [ $(NP) -gt 4 ] && echo "--oversubscribe")

# ── Targets ─────────────────────────────────────────────────

.PHONY: all run clean help

# Default target: compile only
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(INCLUDES) $(LIBS)
	@echo ""
	@echo "  Compiled successfully -> $(TARGET)"
	@echo ""

# run: compile then launch with NP processes
run: $(TARGET)
	@echo ""
	@echo "  Launching with $(NP) processes..."
	@echo ""
	mpirun -np $(NP) \
		--hostfile $(HOSTFILE) \
		-x $(MPI_ENV) \
		--mca btl_tcp_if_include $(MPI_IF) \
		$(OVERSUB) \
		./$(TARGET)

# all: run all process counts back to back
all: $(TARGET)
	@echo ""
	@echo "  ══════════════════════════════════"
	@echo "   Running with 2 processes"
	@echo "  ══════════════════════════════════"
	mpirun -np 2 --hostfile $(HOSTFILE) \
		-x $(MPI_ENV) --mca btl_tcp_if_include $(MPI_IF) \
		./$(TARGET)

	@echo ""
	@echo "  ══════════════════════════════════"
	@echo "   Running with 4 processes"
	@echo "  ══════════════════════════════════"
	mpirun -np 4 --hostfile $(HOSTFILE) \
		-x $(MPI_ENV) --mca btl_tcp_if_include $(MPI_IF) \
		./$(TARGET)

	@echo ""
	@echo "  ══════════════════════════════════"
	@echo "   Running with 8 processes"
	@echo "  ══════════════════════════════════"
	mpirun -np 8 --hostfile $(HOSTFILE) \
		-x $(MPI_ENV) --mca btl_tcp_if_include $(MPI_IF) \
		--oversubscribe ./$(TARGET)

	@echo ""
	@echo "  ══════════════════════════════════"
	@echo "   Running with 16 processes"
	@echo "  ══════════════════════════════════"
	mpirun -np 16 --hostfile $(HOSTFILE) \
		-x $(MPI_ENV) --mca btl_tcp_if_include $(MPI_IF) \
		--oversubscribe ./$(TARGET)

# clean: remove compiled binary
clean:
	rm -f $(TARGET)
	@echo "  Cleaned -> $(TARGET) removed"

# help: show usage
help:
	@echo ""
	@echo "  ┌─────────────────────────────────────────────┐"
	@echo "  │              MAKEFILE USAGE                 │"
	@echo "  ├─────────────────────────────────────────────┤"
	@echo "  │  make              compile only             │"
	@echo "  │  make run NP=2     compile + run  2 procs   │"
	@echo "  │  make run NP=4     compile + run  4 procs   │"
	@echo "  │  make run NP=8     compile + run  8 procs   │"
	@echo "  │  make run NP=16    compile + run 16 procs   │"
	@echo "  │  make all          run 2, 4, 8, 16 in order │"
	@echo "  │  make clean        remove binary            │"
	@echo "  │  make help         show this message        │"
	@echo "  └─────────────────────────────────────────────┘"
	@echo ""