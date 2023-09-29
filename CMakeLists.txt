cmake_minimum_required(VERSION 3.14)

project(CppKit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# CppKit build options
option(CPPKIT_ENABLE_TEST "Enable CppKit test?" ON)
option(CPPKIT_ENABLE_CUDA "Enable CUDA?" OFF)
message(STATUS "Enable CppKit test? " ${CPPKIT_ENABLE_TEST})
message(STATUS "Enable CUDA? " ${CPPKIT_ENABLE_CUDA})

# Configure CCache if available
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

# third party dependencies
add_subdirectory(third_party)

# source
add_subdirectory(src)

# tests
include(CTest)

