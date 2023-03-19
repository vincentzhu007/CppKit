//
// Created by Vincent Zhu on 2023/3/19.
//

/**
* 矩阵计算性能优化
*/

#include <stdio.h>
#include <string.h>
#include <random>

#include "ai/utils/TimeElapse.h"

using cppkit::ai::utils::TimeElapse;

/**
* C(m ,k) = A(m x n) * B(n, k)
*/

// ijk
void GemmV0(const float *a, const float *b, float *c, int m, int n, int k) {
  float value = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < k; j++) {
      value = 0;
      for (int s = 0; s < n; s++) {
        value += a[i * n + s] * b[s * k + j];
      }
      c[i * k + j] = value;
    }
  }
}

// jik
void GemmV1(const float *a, const float *b, float *c, int m, int n, int k) {
  float value = 0;
  for (int j = 0; j < k; j++) {
    for (int i = 0; i < m; i++) {
      value = 0;
      for (int s = 0; s < n; s++) {
        value += a[i * n + s] * b[s * k + j];
      }
      c[i * k + j] = value;
    }
  }
}

// kij
void GemmV2(const float *a, const float *b, float *c, int m, int n, int k) {
  float value = 0;
  for (int s = 0; s < n; s++) {
    for (int i = 0; i < m; i++) {
      float value_a = a[i * n + s];
      for (int j = 0; j < k; j++) {
        c[i * k + j] += value_a * b[s * k + j];
      }
    }
  }
}

void TestPersicion() {
  float a[] = {1, 2, 3, 4};
  float b[] = {1, 2, 3, 4, 5, 6};
  float c[6] = {0};
  GemmV0(a, b, c, 2, 2, 3);

  for (int i = 0; i < 6; i++) {
    // Would be: {9 ,12, 15, 19, 26, 33}
    printf("c[%d]=%.1f\n", i, c[i]);
  }
}

void FillRandom(float *data, size_t len) {
  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::normal_distribution<float> distrib(0, 1);
  for (int i = 0; i < len; i++) {
    data[i] = distrib(gen);
  }
}

void TestPerformance() {
  int loop_cout = 20;
  const int N = 1000;
  float *a = new float[N * N];
  float *b = new float[N * N];
  float *c = new float[N * N];

  int64_t sum_elapsed = 0;
  TimeElapse time_elapse;


  for (int k = 0; k < loop_cout; k++) {
    FillRandom(a, N * N);
    FillRandom(b, N * N);

    time_elapse.Reset();
    memset(c, 0, sizeof(float) * N * N);

//    GemmV0(a, b, c, N, N, N);
//    GemmV1(a, b, c, N, N, N);
    GemmV2(a, b, c, N, N, N);
    sum_elapsed += time_elapse.ElapsedInUs();
  }

  printf("GEMM 1000x1000 x 1000x1000 average elapsed: %ld us\n",
         sum_elapsed / loop_cout);
  delete[] a;
  delete[] b;
  delete[] c;
}


int main() {
//  TestPersicion();

  TestPerformance();
}
