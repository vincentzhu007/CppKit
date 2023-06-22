//
// Created by zgd on 2023/6/22.
//

#ifndef CPPKIT_SRC_MATMUL_MATMUL_H_
#define CPPKIT_SRC_MATMUL_MATMUL_H_

#include <stddef.h>

void SGEMMNaive(const float *A, const float *B, float *C, size_t M, size_t N, size_t K);

#endif //CPPKIT_SRC_MATMUL_MATMUL_H_
