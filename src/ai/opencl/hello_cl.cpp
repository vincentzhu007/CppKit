//
// Created by zgd on 10/16/22.
//

#include <stdio.h>
#include <CL/cl.h>

int main()
{
  // 获取平台ID
  cl_platform_id platform_id;
  cl_uint numPlatforms = 0;

  auto ret = clGetPlatformIDs( 1, &platform_id, nullptr);
  if (ret != CL_SUCCESS) {
    printf("clGetPlatformIDs failed, ret: %d\n", ret);
    return EXIT_FAILURE;
  }

  // 获取设备ID
  cl_device_id device_id;
  cl_uint num_devices = 0;
  ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, nullptr);
  if (ret != CL_SUCCESS) {
    printf("clGetDeviceIDs failed, ret %i\n", ret);
    return EXIT_FAILURE;
  }

  // 获取设备名称
  size_t size;
  (void)clGetDeviceInfo(device_id, CL_DEVICE_NAME, 0, nullptr, &size);
  char *device_name = (char *) malloc(size);
  (void) clGetDeviceInfo(device_id, CL_DEVICE_NAME, size, device_name, nullptr);
  printf("device name: %s\n", device_name);

  // 获取最大内存
  size_t maxGlobalMem = 0;
  (void) clGetDeviceInfo(device_id, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(maxGlobalMem), &maxGlobalMem, nullptr);
  printf("max global mem: %luM\n", maxGlobalMem / 1024 / 1024);

  size_t maxConstantBufferMem = 0;
  (void) clGetDeviceInfo(device_id, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(maxConstantBufferMem), &maxConstantBufferMem, nullptr);
  printf("max constant buffer mem: %luM\n", maxConstantBufferMem / 1024 / 1024);

  size_t maxLocalMem = 0;
  (void) clGetDeviceInfo(device_id, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(maxLocalMem), &maxLocalMem, nullptr);
  printf("max local mem: %luM\n", maxLocalMem / 1024 / 1024);

  return 0;
}