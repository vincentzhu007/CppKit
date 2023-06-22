//
// Created by zgd on 2023/6/22.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include "elapsed_time.h"
#include "matmul.h"

/**
 * 测试不同的单精度方阵计算
 * @param K 方阵尺寸
 */
void TestSGEMM(const size_t &K) {
  std::cout << "Perform sgemm of size: " << K << std::flush;

  std::vector<float> A(K * K , 1.0);
  std::vector<float> B(K * K, 2.0);
  std::vector<float> C(K * K, 0.0);

  utils::ElapsedTime elapsedTime;
  SGEMMNaive(A.data(), B.data(), C.data(), K, K, K);
  std::cout << " OK. Elapsed " << elapsedTime.AsMilliseconds() << " ms.\n" << std::endl;
}

int main() {
  std::vector<size_t> matrixSizes = {100, 200, 300, 500, 700, 900};
  std::for_each(matrixSizes.begin(), matrixSizes.end(), TestSGEMM);
}