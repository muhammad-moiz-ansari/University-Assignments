# Compiler and flags
NVCC = nvcc
SRC = mm_bench.cu
OUT = mm

# Default size if not provided
N ?= 512

# Default target: build only
all: $(OUT)

$(OUT): $(SRC)
	$(NVCC) $(SRC) -o $(OUT)

# Run with GPU 1D kernel
gpu1d: $(OUT)
	./$(OUT) $(N) 1d

# Run with GPU 2D kernel
gpu2d: $(OUT)
	./$(OUT) $(N) 2d

# Clean compiled binary
clean:
	rm -f $(OUT)
