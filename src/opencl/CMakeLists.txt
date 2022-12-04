find_package(OpenCL)
add_executable(hello_cl hello_cl.cpp)
target_link_libraries(hello_cl PRIVATE )