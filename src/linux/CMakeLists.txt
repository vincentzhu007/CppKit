add_library(mmap_buffer_obj OBJECT mmap_buffer.cpp)
target_include_directories(mmap_buffer_obj PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_library(temp_file_obj OBJECT temp_file.cpp)
target_include_directories(temp_file_obj PUBLIC ${CMAKE_SOURCE_DIR}/src)