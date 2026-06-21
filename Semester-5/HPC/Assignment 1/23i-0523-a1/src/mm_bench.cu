#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

// Function to initialize a matrix with random values
void initMatrix(float *matrix, int size) {
    for (int i = 0; i < size; i++) {
        matrix[i] = (float)(rand() % 100);
    }
}

// CPU matrix multiplication
void matrixMulCPU(float *A, float *B, float *C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float sum = 0.0;
            for (int k = 0; k < n; k++)
                sum += A[i * n + k] * B[k * n + j];
            C[i * n + j] = sum;
        }
    }
}

// GPU matrix multiplication 1D kernel
__global__ void matrixMulGPU_1D(float *A, float *B, float *C, int n)
{
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int row = index / n;
  int col = index % n;

    if (row < n && col < n) 
    {
        float sum = 0.0f;
        for (int k = 0; k < n; k++)
            sum += A[row * n + k] * B[k * n + col];
        C[row * n + col] = sum;
    }
}

// GPU matrix multiplication 2D kernel
__global__ void matrixMulGPU_2D(float *A, float *B, float *C, int n)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;  // from Y
    int col = blockIdx.x * blockDim.x + threadIdx.x;  // from X

    if (row < n && col < n) 
    {
        float sum = 0.0f;
        for (int k = 0; k < n; k++)
            sum += A[row * n + k] * B[k * n + col];
        C[row * n + col] = sum;
    }
}

// Function to compare CPU and GPU results
bool verifyResults(float *c_cpu, float *c_gpu, int n)
{
    bool isOk = true;
    double total_error = 0.0;

    printf("----- CPU vs GPU Matrix VERIFICATION -----\n\n");

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            float diff = fabs(c_cpu[i * n + j] - c_gpu[i * n + j]);
            if (diff > 0.0001f)
            {
                // Uncomment if you want detailed mismatches:
                // printf("Mismatch at [%d][%d]: CPU=%f, GPU=%f, diff=%f\n",
                //        i, j, c_cpu[i*n+j], c_gpu[i*n+j], diff);
                isOk = false;
            }
            total_error += diff;
        }
    }

    if (isOk)
    {
        printf("ALL RESULTS VERIFIED!\n");
    }
    else
    {
        double avg_error = total_error / (n * n);
        printf("Average absolute error across all elements = %e\n", avg_error);
    }

    printf("-------------------------------------\n");
    return isOk;
}


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <N> [mode]\nModes: 1d (default) or 2d\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    const char *mode = (argc >= 3) ? argv[2] : "2d";
    
    srand(time(NULL));
    int size = N * N * sizeof(float);
    
    // Allocate host memory
    float *h_A = (float *)malloc(size);
    float *h_B = (float *)malloc(size);
    float *h_C_CPU = (float *)malloc(size);
    float *h_C_GPU = (float *)malloc(size);

    // Initialize matrices
    initMatrix(h_A, N * N);
    initMatrix(h_B, N * N);

    // CUDA Events
    cudaEvent_t startCPU, endCPU;
    cudaEvent_t startH2D, endH2D;
    cudaEvent_t startKernel, endKernel;
    cudaEvent_t startD2H, endD2H;
    cudaEvent_t startGPUTotal, endGPUTotal;

    
    cudaEventCreate(&startCPU);
    cudaEventCreate(&endCPU);
    cudaEventCreate(&startH2D);
    cudaEventCreate(&endH2D);
    cudaEventCreate(&startKernel);
    cudaEventCreate(&endKernel);
    cudaEventCreate(&startD2H);
    cudaEventCreate(&endD2H);
    cudaEventCreate(&startGPUTotal);
    cudaEventCreate(&endGPUTotal);

    // CUDA Events for CPU Timing
    cudaEventRecord(startCPU);
    matrixMulCPU(h_A, h_B, h_C_CPU, N);
    cudaEventRecord(endCPU);
    cudaEventSynchronize(endCPU);
    
    float cpu_time;
    cudaEventElapsedTime(&cpu_time, startCPU, endCPU);
    printf("CPU Execution Time: %f ms\n", cpu_time);

    // Allocate device memory
    float *d_a, *d_b, *d_c;
    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_c, size);

    // Start total GPU timer (H2D + Kernel + D2H)
    cudaEventRecord(startGPUTotal);

    // Copy data from host to device (GPU)
    cudaEventRecord(startH2D);
      cudaMemcpy(d_a, h_A, size, cudaMemcpyHostToDevice);
      cudaMemcpy(d_b, h_B, size, cudaMemcpyHostToDevice);
    cudaEventRecord(endH2D);
    cudaEventSynchronize(endH2D);

    float h2d_time;
    cudaEventElapsedTime(&h2d_time, startH2D, endH2D);
    printf("Data Transfer Time (H2D): %f ms\n", h2d_time);

    // CUDA Events for GPU Timing
    cudaEventRecord(startKernel);
    if(strcmp(mode, "1d") == 0)
    {
      // Define grid and block dimensions for 1D grid and block
      int threadsPerBlock = 512;  // We can adjust this value
      long int totalThreads = (long)N * N;
      int blocksPerGrid = (totalThreads + threadsPerBlock - 1) / threadsPerBlock;
      printf("Blocks per grid: %d\n", blocksPerGrid);
      
      // Launch kernel
      matrixMulGPU_1D<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, N);
    }
    else
    {
      // Define grid and block dimensions for 2D grid and block
      dim3 threadsPerBlock(32, 32);  // We can adjust this value
      dim3 blocksPerGrid((N + threadsPerBlock.x - 1) / threadsPerBlock.x, (N + threadsPerBlock.y - 1) / threadsPerBlock.y);
      printf("Blocks per grid: (%d, %d)\n", blocksPerGrid.x, blocksPerGrid.y);

      // Launch kernel
      matrixMulGPU_2D<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, N);
    }
    cudaDeviceSynchronize();
    cudaEventRecord(endKernel);
    cudaEventSynchronize(endKernel);

    // Calculate GPU execution time
    float kernel_time;
    cudaEventElapsedTime(&kernel_time, startKernel, endKernel);
    printf("GPU Execution Time: %f ms\n", kernel_time);

    // Copy results back, from device to host (D2H)
    cudaEventRecord(startD2H);
    cudaMemcpy(h_C_GPU, d_c, size, cudaMemcpyDeviceToHost);
    cudaEventRecord(endD2H);
    cudaEventSynchronize(endD2H);
    float d2h_time = 0.0f;
    cudaEventElapsedTime(&d2h_time, startD2H, endD2H);
    printf("Data Transfer Time (D2H): %f ms\n", d2h_time);

    // End total GPU timer
    cudaEventRecord(endGPUTotal);
    cudaEventSynchronize(endGPUTotal);
    float total_gpu_time;
    cudaEventElapsedTime(&total_gpu_time, startGPUTotal, endGPUTotal);
    printf("Total GPU Time (H2D + Kernel + D2H): %f ms\n", total_gpu_time);

    // Check for kernel launch errors
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        printf("CUDA launch error: %s\n", cudaGetErrorString(err));
    }
    
    // Verify results
    int ok = verifyResults(h_C_CPU, h_C_GPU, N);

    // print a single machine-parseable line (CSV-like)
    // SIZE,<N>,MODE,<mode>,CPU,<cpu_time>,H2D,<h2d_time>,KERNEL,<kernel_time>,D2H,<d2h_time>,TOTAL_GPU,<total_gpu_time>,VERIFIED,<0/1>
    printf("SIZE,%d,MODE,%s,CPU,%.6f,H2D,%.6f,KERNEL,%.6f,D2H,%.6f,TOTAL_GPU,%.6f,VERIFIED,%d\n",
           N, mode, cpu_time, h2d_time, kernel_time, d2h_time, total_gpu_time, ok);

    // Cleanup
    free(h_A);
    free(h_B);
    free(h_C_CPU);
    free(h_C_GPU);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    
    // Destroy CUDA events
    cudaEventDestroy(startCPU);
    cudaEventDestroy(endCPU);
    cudaEventDestroy(startH2D);
    cudaEventDestroy(endH2D);
    cudaEventDestroy(startKernel);
    cudaEventDestroy(endKernel);
    cudaEventDestroy(startD2H);
    cudaEventDestroy(endD2H);
    cudaEventDestroy(startGPUTotal);
    cudaEventDestroy(endGPUTotal);

    return 0;
}
