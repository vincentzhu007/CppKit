#include <benchmark/benchmark.h>

#include <algorithm>
#include <cmath>
#include <cstring>
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

namespace bm = benchmark;

static void naive_row_major_sgemm(const float *a, const float *b, float *c,
                                  int m, int n, int k) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      float sum = 0;
      for (int s = 0; s < k; s++) {
        sum += a[i * k + s] * b[s * n + j];
      }
      c[i * n + j] = sum;
    }
  }
}

static void bm_naive_row_major_sgemm(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));
  std::vector<float> a(m * n, 0.1);
  std::vector<float> b(m * n, 0.1);
  std::vector<float> c(m * n, 0.0);
  for (auto _ : state) {
    naive_row_major_sgemm(a.data(), b.data(), c.data(), m, n, k);
  }
}

BENCHMARK(bm_naive_row_major_sgemm)
    ->MinWarmUpTime(10)
    ->RangeMultiplier(2)
    ->Range(64, 1024);

// 循环优化
static void optimze_row_major_sgemm_with_loop(const float *a, const float *b,
                                              float *c, int m, int n, int k) {
  memset(c, 0, m * n * sizeof(float));

  for (int mi = 0; mi < m; mi++) {
    for (int ki = 0; ki < k; ki++) {
      for (int ni = 0; ni < n; ni++) {
        c[mi * n + ni] += a[mi * k + ki] * b[ki * n + ni];
      }
    }
  }
}

static void bm_optimze_row_major_sgemm_with_loop(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));
  std::vector<float> a(m * n, 0.1);
  std::vector<float> b(m * n, 0.1);
  std::vector<float> c(m * n, 0.0);
  for (auto _ : state) {
    optimze_row_major_sgemm_with_loop(a.data(), b.data(), c.data(), m, n, k);
  }
}

BENCHMARK(bm_optimze_row_major_sgemm_with_loop)
    ->MinWarmUpTime(10)
    ->RangeMultiplier(2)
    ->Range(64, 1024);

/**
 * BLAS GEMM API
 *
 * C := alpha x A x B + beta x C
 */

// 实现一个列主序的gemm
void naive_col_major_segmm(char transa, char transb, int M, int N, int K,
                           const float alpha, const float *src_a, int lda,
                           const float *src_b, int ldb, const float beta,
                           float *dst, int ldc) {
  int a_stride_m =
      (transa == 'n' ? 1
                     : lda);  // 列优先，这里lda = m，不转置的情况下stride为1
  int a_stride_k = (transa == 'n' ? lda : 1);
  int b_stride_k =
      (transb == 'n' ? 1
                     : ldb);  // 列优先，这里ldb = k，不转置的情况下stride为1
  int b_stride_n = (transb == 'n' ? ldb : 1);

  for (int m = 0; m < M; m++) {
    for (int n = 0; n < N; n++) {
      float acc = 0.0f;
      const float *a = src_a + m * a_stride_m;
      const float *b = src_b + n * b_stride_n;

      for (int k = 0; k < K; k++) {
        acc += a[k * a_stride_k] + b[k * b_stride_n];
      }
      dst[m + n * ldc] = alpha * acc + beta * dst[m + n * ldc];
    }
  }
}

// #define DivUp(x, y) (((x) + (y)-1) / (y))

// #define CACHE_LINE 32

// // 循环优化 + 数据打包
// static void naive_row_major_sgemm_opt_loop_pack(const float *a, const float
// *b,
//                                                 float *c, int m, int n, int
//                                                 k) {
//   constexpr int Mr = 64;
//   constexpr int Kr = 256;
//   constexpr int nr = 6;

//   float *pack_a = (float *)aligned_alloc(
//       CACHE_LINE, Mr * Kr * sizeof(float));  // Mr * Kr = 64 * 256
//   float *pack_b = (float *)aligned_alloc(
//       CACHE_LINE, Kr * DivUp(n, nr) * sizeof(float));  // Kr * n = 256 * n;

//   float *tmp_pack_a = pack_a;
//   float *tmp_pack_b = pack_b;

//   for (int ki = 0; ki < k; ki += Kr) {
//     int cur_k = std::min(k - ki, Kr);

//     // jump to k-th row of matrix B
//     pack_no_trans(b + k * ldb, tmp_pack_b, Kr, cur_k,
//                   n);  // 给b的一个Kr * n的块进行打包

//     for (int mi = 0; mi < m; mi += Mr) {
//       int cur_m = std::min(m - Mr, Mr);

//       pack_trans(a + mi + ki *)
//     }
//   }

//   memset(c, 0, m * n * sizeof(float));

//   for (int mi = 0; mi < m; mi++) {
//     for (int ki = 0; ki < k; ki++) {
//       for (int ni = 0; ni < n; ni++) {
//         c[mi * n + ni] += a[mi * k + ki] * b[ki * n + ni];
//       }
//     }
//   }

//   free(pack_a);
//   free(pack_b);
// }

// static void bm_naive_row_major_sgemm_opt_loop_pack(bm::State &state) {
//   int m, n, k;
//   m = n = k = static_cast<int>(state.range(0));
//   std::vector<float> a(m * n, 0.1);
//   std::vector<float> b(m * n, 0.1);
//   std::vector<float> c(m * n, 0.0);
//   for (auto _ : state) {
//     naive_row_major_sgemm_opt_loop_pack(a.data(), b.data(), c.data(), m, n,
//     k);
//   }
// }

// BENCHMARK(bm_naive_row_major_sgemm_opt_loop_pack)
//     ->MinWarmUpTime(10)
//     ->RangeMultiplier(2)
//     ->Range(64, 1024);