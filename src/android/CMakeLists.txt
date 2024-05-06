cmake_minimum_required(VERSION 3.14)

project(android_test LANGUAGES C CXX)

add_executable(test_set_thread_name test_set_thread_name.c)

add_executable(test_cpp_set_thread_name test_cpp_set_thread_name.cc)

if (CMAKE_SYSTEM_NAME MATCHES "Android")
    target_link_libraries(test_cpp_set_thread_name PUBLIC c++_static)
endif()