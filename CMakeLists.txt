cmake_minimum_required(VERSION 3.14)

project(CppKit LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# third party dependencies
add_subdirectory(third_party)

# source
add_subdirectory(src)

# tests
include(CTest)

