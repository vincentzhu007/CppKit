cmake_minimum_required(VERSION 3.14)
project(cuda_test CXX CUDA)

add_executable(hello_cuda hello_cuda.cu)
add_executable(cuda_sum cuda_sum.cu)
