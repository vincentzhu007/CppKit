cmake_minimum_required(VERSION 3.14)
project(cuda_test CXX CUDA)

add_executable(hello_cuda hello_cuda.cu)
add_executable(cuda_vector_add cuda_vector_add.cu)
add_executable(cuda_vector_add_timing cuda_vector_add_timing.cu)
add_executable(cuda_index cuda_index.cu)
