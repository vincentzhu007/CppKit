add_executable(crop crop.cpp)
add_executable(crop2 crop2.cpp)

add_executable(matmul matmul.cpp)
target_link_libraries(matmul PRIVATE aiutils)