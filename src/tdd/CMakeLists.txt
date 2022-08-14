
# money library
add_library(money money.cpp)
target_include_directories(money INTERFACE ${CMAKE_SOURCE_DIR}/src)

# money test
add_executable(money_test money_test.cpp)
target_link_libraries(money_test PRIVATE gtest gtest_main)
target_link_libraries(money_test PRIVATE money)