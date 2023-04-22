# timer test
add_executable(timer_test timer_test.cpp)
target_link_libraries(timer_test PRIVATE gtest gtest_main)
target_link_libraries(timer_test PRIVATE timer)
target_include_directories(timer_test PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_executable(error_test error_test.cpp)
target_link_libraries(error_test PRIVATE gtest gtest_main)
target_link_libraries(error_test PRIVATE timer)
target_include_directories(error_test PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_executable(temp_file_test temp_file_test.cpp)
target_link_libraries(temp_file_test PRIVATE gtest gtest_main)
target_link_libraries(temp_file_test PRIVATE temp_file_obj)

add_executable(mmap_buffer_test mmap_buffer_test.cpp)
target_link_libraries(mmap_buffer_test PRIVATE gtest gtest_main)
target_link_libraries(mmap_buffer_test PRIVATE mmap_buffer_obj temp_file_obj)
