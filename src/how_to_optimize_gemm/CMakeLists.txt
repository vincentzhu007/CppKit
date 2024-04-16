file(GLOB GEMM_SRC gemm*.c)

add_executable(bm_gemm bm_gemm.cpp ${GEMM_SRC})
target_link_libraries(bm_gemm PUBLIC benchmark benchmark_main)