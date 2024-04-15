# third-party module: benchmark
set(BENCHMARK_USE_BUNDLED_GTEST OFF) # disable self-test of benchmark
set(BENCHMARK_ENABLE_LIBPFM ON)
FetchContent_Declare(
        google-benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG        015d1a091af6937488242b70121858bce8fd40e9 # release-1.8.2
)
FetchContent_MakeAvailable(google-benchmark)