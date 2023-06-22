//
// Created by zgd on 2023/6/7.
//

#include "matmul.h"

/**
 * 单精度矩阵乘法：SGEMMNaive。
 *
 * 实现C = A * B，其中A形状是M*K，B是K*N，C是M*N。
 * 采用3层循环实现。
 */
void SGEMMNaive(const float *A, const float *B, float *C,
                size_t M, size_t N, size_t K) {
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      float sum = 0.0;
      for (size_t s = 0; s < K; s++) {
          sum += (*(A + i * K + s)) * (*(B + s * N + j));
      }
      *(C + i * N + j) = sum;
    }
  }
}
