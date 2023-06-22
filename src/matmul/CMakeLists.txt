cmake_minimum_required(VERSION 3.12)

project(matmul LANGUAGES C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

# Options for target build.
option(ENABLE_TESTS "Enable tests, which need google test. install it with 'sudo apt-get install libgtest-dev'" ON)

# Functionality targets
add_library(utils_obj OBJECT elapsed_time.cpp)
target_include_directories(utils_obj INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(matmul_naive matmul_naive.cpp)
target_link_libraries(matmul_naive PRIVATE utils_obj)

# Test targets
if(ENABLE_TESTS)
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    add_executable(elapsed_time_test elapsed_time_test.cpp)
    target_link_libraries(elapsed_time_test PRIVATE utils_obj)
    target_link_libraries(elapsed_time_test PRIVATE gtest gtest_main)
endif()

