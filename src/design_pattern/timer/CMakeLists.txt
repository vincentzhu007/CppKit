# timer library
add_library(timer SHARED timer.cpp timer.h)
target_include_directories(timer INTERFACE ${CMAKE_SOURCE_DIR})

add_executable(timer_test timer_test.cpp)
target_link_libraries(timer_test PRIVATE gtest gtest_main)
target_link_libraries(timer_test PRIVATE timer)
target_include_directories(timer_test PRIVATE ${CMAKE_SOURCE_DIR}/src)