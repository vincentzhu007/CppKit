
add_executable(bench_demo bench_demo.cpp)
target_link_libraries(bench_demo PUBLIC benchmark benchmark_main)

add_executable(bench_usleep bench_usleep.cpp)
target_link_libraries(bench_usleep PUBLIC benchmark benchmark_main)
