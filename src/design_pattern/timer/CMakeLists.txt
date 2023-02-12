# timer library
add_library(timer SHARED timer.cpp timer.h)
target_include_directories(timer INTERFACE ${CMAKE_SOURCE_DIR})