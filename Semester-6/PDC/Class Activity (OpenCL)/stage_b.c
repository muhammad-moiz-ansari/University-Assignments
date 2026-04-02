#define CL_TARGET_OPENCL_VERSION 120
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <CL/cl.h>

#define M 176
#define N 128
#define K 144
#define TS 8

const char *kernel_src =
"#define TS 8\n"
"__kernel void similarity_tiled(__global float* Q,\n"
"                               __global float* D,\n"
"                               __global float* S,\n"
"                               int M, int N, int K) {\n"
"    __local float tileQ[TS][TS];\n"
"    __local float tileD[TS][TS];\n"
"    int row = get_group_id(0) * TS + get_local_id(0);\n"
"    int col = get_group_id(1) * TS + get_local_id(1);\n"
"    int li  = get_local_id(0);\n"
"    int lj  = get_local_id(1);\n"
"    float sum = 0.0f;\n"
"    int numTiles = (K + TS - 1) / TS;\n"
"    for (int t = 0; t < numTiles; t++) {\n"
"        int kQ = t * TS + lj;\n"
"        int kD = t * TS + li;\n"
"        tileQ[li][lj] = (row < M && kQ < K) ? Q[row * K + kQ] : 0.0f;\n"
"        tileD[li][lj] = (col < N && kD < K) ? D[col * K + kD] : 0.0f;\n"
"        barrier(CLK_LOCAL_MEM_FENCE);\n"
"        for (int k = 0; k < TS; k++)\n"
"            sum += tileQ[li][k] * tileD[k][lj];\n"
"        barrier(CLK_LOCAL_MEM_FENCE);\n"
"    }\n"
"    if (row < M && col < N)\n"
"        S[row * N + col] = sum;\n"
"}\n";

double get_time_ms(struct timespec s, struct timespec e) {
    return (e.tv_sec - s.tv_sec)*1000.0 + (e.tv_nsec - s.tv_nsec)/1e6;
}

int main() {
    float *Q     = malloc(M*K*sizeof(float));
    float *D     = malloc(N*K*sizeof(float));
    float *S     = malloc(M*N*sizeof(float));
    float *S_ref = malloc(M*N*sizeof(float));

    for (int i=0;i<M;i++) for (int k=0;k<K;k++) Q[i*K+k]=((i+k)%17)*0.1f;
    for (int j=0;j<N;j++) for (int k=0;k<K;k++) D[j*K+k]=((j+2*k)%19)*0.1f;
    for (int i=0;i<M;i++) for (int j=0;j<N;j++) {
        float s=0; for (int k=0;k<K;k++) s+=Q[i*K+k]*D[j*K+k];
        S_ref[i*N+j]=s;
    }

    cl_platform_id platform; cl_device_id device; cl_int err;
    clGetPlatformIDs(1,&platform,NULL);
    clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,1,&device,NULL);
    char dev_name[256];
    clGetDeviceInfo(device,CL_DEVICE_NAME,sizeof(dev_name),dev_name,NULL);
    printf("Device: %s\n",dev_name);

    cl_context ctx=clCreateContext(NULL,1,&device,NULL,NULL,&err);
    cl_command_queue queue=clCreateCommandQueue(ctx,device,CL_QUEUE_PROFILING_ENABLE,&err);

    cl_mem bufQ=clCreateBuffer(ctx,CL_MEM_READ_ONLY, M*K*sizeof(float),NULL,&err);
    cl_mem bufD=clCreateBuffer(ctx,CL_MEM_READ_ONLY, N*K*sizeof(float),NULL,&err);
    cl_mem bufS=clCreateBuffer(ctx,CL_MEM_WRITE_ONLY,M*N*sizeof(float),NULL,&err);

    struct timespec t0,t1;
    clock_gettime(CLOCK_MONOTONIC,&t0);
    clEnqueueWriteBuffer(queue,bufQ,CL_TRUE,0,M*K*sizeof(float),Q,0,NULL,NULL);
    clEnqueueWriteBuffer(queue,bufD,CL_TRUE,0,N*K*sizeof(float),D,0,NULL,NULL);
    clFinish(queue);
    clock_gettime(CLOCK_MONOTONIC,&t1);
    double h2d_ms=get_time_ms(t0,t1);

    cl_program prog=clCreateProgramWithSource(ctx,1,&kernel_src,NULL,&err);
    err=clBuildProgram(prog,1,&device,NULL,NULL,NULL);
    if(err!=CL_SUCCESS){
        char log[4096];
        clGetProgramBuildInfo(prog,device,CL_PROGRAM_BUILD_LOG,sizeof(log),log,NULL);
        printf("Build error:\n%s\n",log); return 1;
    }
    cl_kernel kernel=clCreateKernel(prog,"similarity_tiled",&err);
    clSetKernelArg(kernel,0,sizeof(cl_mem),&bufQ);
    clSetKernelArg(kernel,1,sizeof(cl_mem),&bufD);
    clSetKernelArg(kernel,2,sizeof(cl_mem),&bufS);
    clSetKernelArg(kernel,3,sizeof(int),&(int){M});
    clSetKernelArg(kernel,4,sizeof(int),&(int){N});
    clSetKernelArg(kernel,5,sizeof(int),&(int){K});

    size_t global[2]={((M+TS-1)/TS)*TS,((N+TS-1)/TS)*TS};
    size_t local[2]={TS,TS};

    clock_gettime(CLOCK_MONOTONIC,&t0);
    clEnqueueNDRangeKernel(queue,kernel,2,NULL,global,local,0,NULL,NULL);
    clFinish(queue);
    clock_gettime(CLOCK_MONOTONIC,&t1);
    double kernel_ms=get_time_ms(t0,t1);

    clock_gettime(CLOCK_MONOTONIC,&t0);
    clEnqueueReadBuffer(queue,bufS,CL_TRUE,0,M*N*sizeof(float),S,0,NULL,NULL);
    clFinish(queue);
    clock_gettime(CLOCK_MONOTONIC,&t1);
    double d2h_ms=get_time_ms(t0,t1);

    int pass=1;
    for(int i=0;i<M*N;i++){
        if(fabs(S[i]-S_ref[i])>1e-2){
            printf("MISMATCH at %d: got %f expected %f\n",i,S[i],S_ref[i]);
            pass=0; break;
        }
    }

    printf("Correctness: %s\n",pass?"PASS":"FAIL");
    printf("Tile size:   %d\n",TS);
    printf("H2D time:    %.4f ms\n",h2d_ms);
    printf("Kernel time: %.4f ms\n",kernel_ms);
    printf("D2H time:    %.4f ms\n",d2h_ms);
    printf("Total time:  %.4f ms\n",h2d_ms+kernel_ms+d2h_ms);

    clReleaseMemObject(bufQ); clReleaseMemObject(bufD); clReleaseMemObject(bufS);
    clReleaseKernel(kernel); clReleaseProgram(prog);
    clReleaseCommandQueue(queue); clReleaseContext(ctx);
    free(Q); free(D); free(S); free(S_ref);
    return 0;
}