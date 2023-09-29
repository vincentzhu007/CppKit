#include <stdio.h>

__global__ void helloFromGPU(void) {
  printf("Hello World from GPU thread %d!\n", threadIdx.x);
}

int main(void) {
  printf("Hello World from CPU!\n");

  helloFromGPU <<<1, 5>>>();

  // 销毁当前进程所管理设备的所有资源。
//  cudaDeviceReset();
  cudaDeviceSynchronize();

  return 0;
}
