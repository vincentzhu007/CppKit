cmake_minimum_required(VERSION 3.14)

project(CppKit LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

# third party dependencies
add_subdirectory(third_party)

# source
add_subdirectory(src)

# tests
option(CPP_KIT_WITH_TESTS "build tests?" ON)
message(STATUS "build tests? " ${CPP_KIT_WITH_TESTS})

if(CPP_KIT_WITH_TESTS)
    include(CTest)
    add_subdirectory(tests)
endif()

