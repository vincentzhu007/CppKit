# error
add_executable(error_test error_test.cpp)
target_link_libraries(error_test PRIVATE gtest gtest_main)
target_link_libraries(error_test PRIVATE timer)
target_include_directories(error_test PRIVATE ${CMAKE_SOURCE_DIR}/src)