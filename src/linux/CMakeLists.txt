add_library(mmap_buffer_obj OBJECT mmap_buffer.cpp)
target_include_directories(mmap_buffer_obj PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_library(temp_file_obj OBJECT temp_file.cpp)
target_include_directories(temp_file_obj PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(temp_file_test temp_file_test.cpp)
target_link_libraries(temp_file_test PRIVATE gtest gtest_main)
target_link_libraries(temp_file_test PRIVATE temp_file_obj)

add_executable(mmap_buffer_test mmap_buffer_test.cpp)
target_link_libraries(mmap_buffer_test PRIVATE gtest gtest_main)
target_link_libraries(mmap_buffer_test PRIVATE mmap_buffer_obj temp_file_obj)
