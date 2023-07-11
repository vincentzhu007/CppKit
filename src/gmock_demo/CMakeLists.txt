add_library(demo_log demo_log.cpp)

add_executable(demo_log_test demo_log_test.cpp)
target_link_libraries(demo_log_test PRIVATE demo_log gtest gmock gtest_main)
