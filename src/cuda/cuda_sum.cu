//
// Created by zgd on 2023/10/2.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

void InitWithRandom(float *f, int n_elem) {
  for (int i = 0; i < n_elem; i++) {
    f[i] = rand() * 1.0 / RAND_MAX;
  }
}

void CpuAdd(int n_elem, float *a, float *b, float *c) {
  for (int i = 0; i < n_elem; i++) {
    c[i] = a[i] + b[i];
  }
}

__global__ void kernelSum(float *d_a, float *d_b, float *d_c) {
  int id = threadIdx.x;
  d_c[id] = d_a[id] + d_b[id];
  printf("  -> cuda kernel id[%d], d_a=%.6f, d_b=%.6f, d_c=%.6f\n", id, d_a[id], d_b[id], d_c[id]);
}

void CudaAdd(int n_elem, float *h_a, float *h_b, float *gpu_ref) {
  float *d_a, *d_b, *d_c;
  int n_size = n_elem * sizeof(float);
  cudaMalloc(&d_a, n_size);
  cudaMalloc(&d_b, n_size);
  cudaMalloc(&d_c, n_size);

  // 拷贝输入到device侧
  cudaMemcpy(d_a, h_a, n_size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, h_b, n_size, cudaMemcpyHostToDevice);

  kernelSum <<<1, n_elem>>>(d_a, d_b, d_c);

  // 拷贝结果到host侧
  cudaMemcpy(gpu_ref, d_c, n_size, cudaMemcpyDeviceToHost);

  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
}

bool AllClose(int n_elem, float *h_a, float *h_b, float abs_error = 1e-5) {
  for (int i = 0; i < n_elem; i++) {
    if (h_a[i] - h_b[i] >= abs_error) {
      return false;
    }
  }
  return true;
}

std::string Array2Str(float *a, int n_elem) {
  std::stringstream ss;
  ss << "[";
  for (int i = 0; i < n_elem; i++) {
    ss << std::fixed << std::setprecision(6) << a[i];
    if (i < n_elem - 1) {
      ss << ", ";
    }
  }
  ss << "]";
  return ss.str();
}

int main() {
  printf("CUDA Demo: add two arrays.\n\n");

  int n_elem = 6;

  float *h_a = (float *)malloc(sizeof(float) * n_elem);
  float *h_b = (float *)malloc(sizeof(float) * n_elem);
  float *h_c = (float *)malloc(sizeof(float) * n_elem);

  // Setup inputs.
  InitWithRandom(h_a, n_elem);
  InitWithRandom(h_b, n_elem);

  // Run Add() on CPU.
  CpuAdd(n_elem, h_a, h_b, h_c);

  printf("          a = %s\n", Array2Str(h_a, n_elem).c_str());
  printf("          b = %s\n", Array2Str(h_b, n_elem).c_str());
  printf("CPU:  a + b = %s\n", Array2Str(h_c, n_elem).c_str());

  // Run Add() on CUDA.
  float *gpu_ref = (float *)malloc(sizeof(float) * n_elem);
  CudaAdd(n_elem, h_a, h_b, gpu_ref);
  printf("CUDA: a + b = %s\n", Array2Str(gpu_ref, n_elem).c_str());

  // Compare results.
  printf("CUDA result equals to CPU? %s.",
         AllClose(n_elem, h_c, gpu_ref, 1e-9) ? "True" : "False");

  free(h_a);
  free(h_b);
  free(h_c);
  free(gpu_ref);
}