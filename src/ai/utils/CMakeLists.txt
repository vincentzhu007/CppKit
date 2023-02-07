add_library(aiutils)
target_sources(aiutils PRIVATE TimeElapse.cpp)
target_include_directories(aiutils INTERFACE ${CMAKE_SOURCE_DIR}/src)