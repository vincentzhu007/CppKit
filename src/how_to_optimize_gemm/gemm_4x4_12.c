#include <assert.h>
#include <emmintrin.h>  // SSE3
#include <mmintrin.h>
#include <pmmintrin.h>  // SSE2
#include <stdio.h>
#include <xmmintrin.h>  // SSE

#include "gemm.h"

// colum-major
#define A(i, j) a[(j) * lda + (i)]
#define B(i, j) b[(j) * ldb + (i)]
#define C(i, j) c[(j) * ldc + (i)]

// block size
#define mc 256
#define kc 128

#define min(x, y) ((x) < (y) ? (x) : (y))

typedef union {
  __m128 v;
  float f[4];
} v2f_t;

// 将原始的A矩阵：
// 0 16 32
// 1 17 33
// 2 18 34
// 3 19 35
// . .
// 打包成：每4行为一组
// 0 1 2 3 16 17 18 19 32 33 34 35 ...

static void pack_a(int k, float *a, int lda, float *dst_a) {
  for (int j = 0; j < k; j++) {  // loop over column of A
    float *a_ij_ptr = &A(0, j);

    *dst_a++ = *a_ij_ptr;
    *dst_a++ = *(a_ij_ptr + 1);
    *dst_a++ = *(a_ij_ptr + 2);
    *dst_a++ = *(a_ij_ptr + 3);
  }
}

static void add_dot_4x4(int k, float *a, int lda, float *b, int ldb, float *c,
                        int ldc) {
  v2f_t vreg_c_x0;
  v2f_t vreg_c_x1;
  v2f_t vreg_c_x2;
  v2f_t vreg_c_x3;

  vreg_c_x0.v = _mm_setzero_ps();
  vreg_c_x1.v = _mm_setzero_ps();
  vreg_c_x2.v = _mm_setzero_ps();
  vreg_c_x3.v = _mm_setzero_ps();

  v2f_t vreg_a_xs;

  v2f_t vreg_b_s0;
  v2f_t vreg_b_s1;
  v2f_t vreg_b_s2;
  v2f_t vreg_b_s3;

  float *b_0 = &B(0, 0);
  float *b_1 = &B(0, 1);
  float *b_2 = &B(0, 2);
  float *b_3 = &B(0, 3);

  for (int s = 0; s < k; s++) {
    vreg_b_s0.v = _mm_set1_ps(*b_0++);
    vreg_b_s1.v = _mm_set1_ps(*b_1++);
    vreg_b_s2.v = _mm_set1_ps(*b_2++);
    vreg_b_s3.v = _mm_set1_ps(*b_3++);

    vreg_a_xs.v = _mm_load_ps(&A(0, s));  // load a(0~3,s)

    vreg_c_x0.v += vreg_a_xs.v * vreg_b_s0.v;
    vreg_c_x1.v += vreg_a_xs.v * vreg_b_s1.v;
    vreg_c_x2.v += vreg_a_xs.v * vreg_b_s2.v;
    vreg_c_x3.v += vreg_a_xs.v * vreg_b_s3.v;
  }

  C(0, 0) += vreg_c_x0.f[0];
  C(1, 0) += vreg_c_x0.f[1];
  C(2, 0) += vreg_c_x0.f[2];
  C(3, 0) += vreg_c_x0.f[3];

  C(0, 1) += vreg_c_x1.f[0];
  C(1, 1) += vreg_c_x1.f[1];
  C(2, 1) += vreg_c_x1.f[2];
  C(3, 1) += vreg_c_x1.f[3];

  C(0, 2) += vreg_c_x2.f[0];
  C(1, 2) += vreg_c_x2.f[1];
  C(2, 2) += vreg_c_x2.f[2];
  C(3, 2) += vreg_c_x2.f[3];

  C(0, 3) += vreg_c_x3.f[0];
  C(1, 3) += vreg_c_x3.f[1];
  C(2, 3) += vreg_c_x3.f[2];
  C(3, 3) += vreg_c_x3.f[3];
}

// small matrix
static void inner_kernel(int m, int n, int k, float *a, int lda, float *b,
                         int ldb, float *c, int ldc) {
  assert(m % 4 == 0);
  assert(n % 4 == 0);

  float *tmp_a = (float *)malloc(m * k * sizeof(float));
  assert(tmp_a != NULL);

  for (int j = 0; j < n; j += 4) {
    for (int i = 0; i < m; i += 4) {
      pack_a(k, &A(i, 0), lda, tmp_a);
      add_dot_4x4(k, &tmp_a[i * k], 4, &B(0, j), ldb, &C(i, j), ldc);
    }
  }

  free(tmp_a);
}

void gemm_4x4_12(int m, int n, int k, float *a, int lda, float *b, int ldb,
                 float *c, int ldc) {
  for (int s = 0; s < k; s += kc) {
    int sb = min(k - s, kc);

    for (int i = 0; i < m; i += mc) {
      int ib = min(m - i, mc);

      inner_kernel(ib, n, sb, &A(i, s), lda, &B(s, 0), ldb, &C(i, 0), ldc);
    }
  }
}
