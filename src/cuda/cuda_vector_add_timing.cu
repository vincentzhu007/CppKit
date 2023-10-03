//
// Created by zgd on 2023/10/2.
//
#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <sys/time.h>

#define CHECK(call)       \
  do {                    \
    const cudaError_t error = call; \
    if (error != cudaSuccess) {     \
      printf("Error: %s: %d, ", __FILE__, __LINE__); \
      printf("code: %d, reason: %s\n", error, cudaGetErrorString(error)); \
      exit(1);            \
    }                     \
  } while(0)

double CpuSeconds() {
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return ((double)tp.tv_sec + (double)tp.tv_usec * 1e-6);
}

void InitWithRandom(float *f, int n_elem) {
  for (int i = 0; i < n_elem; i++) {
    f[i] = rand() * 1.0 / RAND_MAX;
  }
}

void CpuAdd(int n_elem, float *a, float *b, float *c) {
  auto start_time = CpuSeconds();
  for (int i = 0; i < n_elem; i++) {
    c[i] = a[i] + b[i];
  }
  printf("cpu add elapsed:  %.6lfs\n", CpuSeconds() - start_time);
}

__global__ void kernelAdd(float *d_a, float *d_b, float *d_c, int n_elem) {
  int id = threadIdx.x + blockIdx.x * blockDim.x;
  if (id < n_elem) {
    d_c[id] = d_a[id] + d_b[id];
  }
}

void CudaAdd(int n_elem, float *h_a, float *h_b, float *gpu_ref, int max_thread_per_block) {
  float *d_a, *d_b, *d_c;
  int n_size = n_elem * sizeof(float);
  CHECK(cudaMalloc(&d_a, n_size));
  CHECK(cudaMalloc(&d_b, n_size));
  CHECK(cudaMalloc(&d_c, n_size));

  // 拷贝输入到device侧
  CHECK(cudaMemcpy(d_a, h_a, n_size, cudaMemcpyHostToDevice));
  CHECK(cudaMemcpy(d_b, h_b, n_size, cudaMemcpyHostToDevice));


  dim3 block(std::min(n_elem, max_thread_per_block));
  dim3 grid((n_elem + block.x - 1) / block.x);
  printf("cuda block:(%d, %d, %d), grid:(%d, %d, %d)\n",
         block.x, block.y, block.z, grid.x, grid.y, grid.z);

  auto start_time = CpuSeconds();
  // kernel调用是异步的，下句执行后会立即返回到host侧，需要手动调用cuda同步函数等待所有线程执行完毕。
  kernelAdd<<<grid, block>>>(d_a, d_b, d_c, n_elem);
  cudaDeviceSynchronize();
  printf("cuda add elapsed: %.6lfs\n", CpuSeconds() - start_time);

  // 拷贝结果到host侧
  CHECK(cudaMemcpy(gpu_ref, d_c, n_size, cudaMemcpyDeviceToHost));

  CHECK(cudaFree(d_a));
  CHECK(cudaFree(d_b));
  CHECK(cudaFree(d_c));
}

bool AllClose(int n_elem, float *cpu_data, float *gpu_data, float abs_error = 1e-5) {
  for (int i = 0; i < n_elem; i++) {
    if (cpu_data[i] - gpu_data[i] >= abs_error) {
      printf("cpu: %f and gpu: %f mismatched at index %d.\n",
             cpu_data[i], gpu_data[i], i);
      return false;
    }
  }
  return true;
}

std::string Array2Str(float *a, int n_elem, int visible_elem = 10) {
  std::stringstream ss;
  ss << "[";
  for (int i = 0; i < n_elem && i < visible_elem; i++) {
    ss << std::fixed << std::setprecision(6) << a[i];
    if (i < n_elem - 1) {
      ss << ", ";
    }
  }
  if (visible_elem < n_elem) {
    ss << "...";
  }
  ss << "]";
  return ss.str();
}

int main() {
  printf("CUDA Demo: add two vectors.\n");
  cudaDeviceProp device_prop;
  int dev = 0;
  CHECK(cudaGetDeviceProperties_v2(&device_prop, dev));
  printf("Using device %d: %s, maxThreadsPerBlock: %d.\n\n",
         dev, device_prop.name, device_prop.maxThreadsPerBlock);
  CHECK(cudaSetDevice(dev));

  std::vector<int> elem_levels = {1<<24};
  for (auto n_elem: elem_levels) {
    printf("testing n_elem: %d ...\n", n_elem);
    float *h_a = (float *)malloc(sizeof(float) * n_elem);
    float *h_b = (float *)malloc(sizeof(float) * n_elem);
    float *h_c = (float *)malloc(sizeof(float) * n_elem);

    // Fill inputs with random data.
    InitWithRandom(h_a, n_elem);
    InitWithRandom(h_b, n_elem);

    // Run Add() on CPU.
    CpuAdd(n_elem, h_a, h_b, h_c);

    // Run Add() on CUDA.
    float *gpu_ref = (float *)malloc(sizeof(float) * n_elem);
    int max_thread_per_block = device_prop.maxThreadsPerBlock;
    CudaAdd(n_elem, h_a, h_b, gpu_ref, max_thread_per_block);
    printf("cpu result : %s\n", Array2Str(h_c, n_elem).c_str());
    printf("cuda result: %s\n", Array2Str(gpu_ref, n_elem).c_str());

    // Compare results.
    printf("cuda equals to cpu? %s.\n\n",
           AllClose(n_elem, h_c, gpu_ref, 1e-9) ? "yes" : "no");

    free(h_a);
    free(h_b);
    free(h_c);
    free(gpu_ref);
  }
  return 0;
}