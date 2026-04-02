#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define M 176
#define N 128
#define K 144

const char *kernel_src =
"__kernel void similarity(__global float* Q,\n"
"                         __global float* D,\n"
"                         __global float* S,\n"
"                         int M, int N, int K) {\n"
"    int i = get_global_id(0);\n"
"    int j = get_global_id(1);\n"
"    if (i >= M || j >= N) return;\n"
"    float sum = 0.0f;\n"
"    for (int k = 0; k < K; k++) {\n"
"        sum += Q[i*K + k] * D[j*K + k];\n"
"    }\n"
"    S[i*N + j] = sum;\n"
"}\n";

double get_time_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec)*1000.0 +
           (end.tv_nsec - start.tv_nsec)/1e6;
}

int main() {
    // --- Generate Data ---
    float *Q = (float*)malloc(M * K * sizeof(float));
    float *D = (float*)malloc(N * K * sizeof(float));
    float *S = (float*)malloc(M * N * sizeof(float));
    float *S_ref = (float*)malloc(M * N * sizeof(float));

    for (int i = 0; i < M; i++)
        for (int k = 0; k < K; k++)
            Q[i*K + k] = ((i + k) % 17) * 0.1f;

    for (int j = 0; j < N; j++)
        for (int k = 0; k < K; k++)
            D[j*K + k] = ((j + 2*k) % 19) * 0.1f;

    // --- CPU Reference ---
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) {
            float sum = 0.0f;
            for (int k = 0; k < K; k++)
                sum += Q[i*K+k] * D[j*K+k];
            S_ref[i*N+j] = sum;
        }

    // --- OpenCL Setup ---
    cl_platform_id platform;
    cl_device_id device;
    cl_int err;

    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);

    char dev_name[256];
    clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(dev_name), dev_name, NULL);
    printf("Device: %s\n", dev_name);

    cl_context ctx = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    cl_command_queue queue = clCreateCommandQueue(ctx, device, CL_QUEUE_PROFILING_ENABLE, &err);

    // --- Buffers ---
    cl_mem bufQ = clCreateBuffer(ctx, CL_MEM_READ_ONLY,  M*K*sizeof(float), NULL, &err);
    cl_mem bufD = clCreateBuffer(ctx, CL_MEM_READ_ONLY,  N*K*sizeof(float), NULL, &err);
    cl_mem bufS = clCreateBuffer(ctx, CL_MEM_WRITE_ONLY, M*N*sizeof(float), NULL, &err);

    // --- H2D Transfer ---
    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    clEnqueueWriteBuffer(queue, bufQ, CL_TRUE, 0, M*K*sizeof(float), Q, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufD, CL_TRUE, 0, N*K*sizeof(float), D, 0, NULL, NULL);
    clFinish(queue);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double h2d_ms = get_time_ms(t0, t1);

    // --- Build Kernel ---
    cl_program prog = clCreateProgramWithSource(ctx, 1, &kernel_src, NULL, &err);
    clBuildProgram(prog, 1, &device, NULL, NULL, NULL);
    cl_kernel kernel = clCreateKernel(prog, "similarity", &err);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufQ);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufD);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufS);
    clSetKernelArg(kernel, 3, sizeof(int), &(int){M});
    clSetKernelArg(kernel, 4, sizeof(int), &(int){N});
    clSetKernelArg(kernel, 5, sizeof(int), &(int){K});

    // --- Kernel Execution ---
    size_t global[2] = {M, N};
    cl_event evt;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global, NULL, 0, NULL, &evt);
    clFinish(queue);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double kernel_ms = get_time_ms(t0, t1);

    // --- D2H Transfer ---
    clock_gettime(CLOCK_MONOTONIC, &t0);
    clEnqueueReadBuffer(queue, bufS, CL_TRUE, 0, M*N*sizeof(float), S, 0, NULL, NULL);
    clFinish(queue);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double d2h_ms = get_time_ms(t0, t1);

    // --- Correctness Check ---
    int pass = 1;
    for (int i = 0; i < M*N; i++) {
        if (fabs(S[i] - S_ref[i]) > 1e-2) {
            printf("MISMATCH at %d: got %f expected %f\n", i, S[i], S_ref[i]);
            pass = 0;
            break;
        }
    }

    printf("Correctness: %s\n", pass ? "PASS" : "FAIL");
    printf("H2D time:    %.4f ms\n", h2d_ms);
    printf("Kernel time: %.4f ms\n", kernel_ms);
    printf("D2H time:    %.4f ms\n", d2h_ms);
    printf("Total time:  %.4f ms\n", h2d_ms + kernel_ms + d2h_ms);

    // --- Cleanup ---
    clReleaseMemObject(bufQ);
    clReleaseMemObject(bufD);
    clReleaseMemObject(bufS);
    clReleaseKernel(kernel);
    clReleaseProgram(prog);
    clReleaseCommandQueue(queue);
    clReleaseContext(ctx);
    free(Q); free(D); free(S); free(S_ref);
    return 0;
}
