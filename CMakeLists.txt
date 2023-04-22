cmake_minimum_required(VERSION 3.14)

project(CppKit LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# CppKit build options
option(ENABLE_CPPKIT_TEST "Enable CppKit test?" ON)
message(STATUS "Enable CppKit test? " ${ENABLE_CPPKIT_TEST})

# third party dependencies
add_subdirectory(third_party)

# source
add_subdirectory(src)

# tests
if(ENABLE_CPPKIT_TEST)
    include(CTest)
    add_subdirectory(tests)
endif()

