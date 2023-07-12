cmake_minimum_required(VERSION 3.12)

project(tinyai
        VERSION 0.1
        DESCRIPTION "A tiny ai framework runs onnx format model."
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)

include(cmake/protobuf.cmake)

add_subdirectory(apps)







