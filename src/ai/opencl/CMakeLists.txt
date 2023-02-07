find_package(OpenCL REQUIRED)

add_executable(hello_cl)
target_sources(hello_cl PRIVATE hello_cl.cpp)
target_link_libraries(hello_cl PRIVATE OpenCL::OpenCL)

set_target_properties(hello_cl PROPERTIES C_STANDARD 11
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS OFF)
target_compile_definitions(hello_cl PRIVATE CL_TARGET_OPENCL_VERSION=100)

add_executable(add_cl)
target_sources(add_cl PRIVATE add_cl.cpp)
target_link_libraries(add_cl PRIVATE OpenCL::OpenCL aiutils)
target_compile_definitions(add_cl PRIVATE CL_TARGET_OPENCL_VERSION=200)
target_compile_definitions(add_cl PRIVATE CL_HPP_TARGET_OPENCL_VERSION=200)