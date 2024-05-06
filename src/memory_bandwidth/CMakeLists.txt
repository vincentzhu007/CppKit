add_executable(stream stream.c)
target_compile_definitions(stream PRIVATE STREAM_TYPE=double)
target_compile_definitions(stream PRIVATE STREAM_ARRAY_SIZE=1024*1024*32)
target_compile_definitions(stream PRIVATE OFFSET=0)