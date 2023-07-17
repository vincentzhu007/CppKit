add_library(dag dag.cpp)

add_executable(dag_test dag_test.cpp dag.cpp)
target_include_directories(dag_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(dag_test PRIVATE gtest gtest_main)
