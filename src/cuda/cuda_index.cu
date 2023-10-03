//
// Created by zgd on 2023/10/2.
//

#include <cuda_runtime.h>
#include <stdio.h>

__global__ void CheckIndex(void) {
  printf("Device: threadIdx:(%d, %d, %d), blockIdx:(%d, %d, %d), "
         "blockDim:(%d, %d, %d), gridDim:(%d, %d, %d)\n",
         threadIdx.x, threadIdx.y, threadIdx.z, blockIdx.x, blockIdx.y, blockIdx.z,
         blockDim.x, blockDim.y, blockDim.z, gridDim.x, gridDim.y, gridDim.z);
}

int main() {
  printf("CUDA Demo: illustrate block and thread index.\n\n");

  int n_elem = 6;
  // 计算block和grid数量：1个grid包含多个block，1个block包含多个thread.
  dim3 block(3); // block内的thread分布
  dim3 grid((n_elem + block.x - 1) / block.x); // grid中的block分布

  printf("Host: block:(%d, %d, %d), grid:(%d, %d, %d)\n\n",
         block.x, block.y, block.z, grid.x, grid.y, grid.z);

  CheckIndex<<<grid, block>>>();
  cudaDeviceReset();
}