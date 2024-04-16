#include <assert.h>

#include "gemm.h"

// colum-major
#define A(i, j) a[(j) * lda + (i)]
#define B(i, j) b[(j) * ldb + (i)]
#define C(i, j) c[(j) * ldc + (i)]

static void add_dot_4x4(int k, float *a, int lda, float *b, int ldb, float *c,
                        int ldc) {
  register float tmp_00 = .0f;
  register float tmp_01 = .0f;
  register float tmp_02 = .0f;
  register float tmp_03 = .0f;

  register float tmp_10 = .0f;
  register float tmp_11 = .0f;
  register float tmp_12 = .0f;
  register float tmp_13 = .0f;

  register float tmp_20 = .0f;
  register float tmp_21 = .0f;
  register float tmp_22 = .0f;
  register float tmp_23 = .0f;

  register float tmp_30 = .0f;
  register float tmp_31 = .0f;
  register float tmp_32 = .0f;
  register float tmp_33 = .0f;

  float *b_0 = &B(0, 0);
  float *b_1 = &B(0, 1);
  float *b_2 = &B(0, 2);
  float *b_3 = &B(0, 3);

  for (int s = 0; s < k; s++) {
    register float tmp_b_0 = *b_0++;
    register float tmp_b_1 = *b_1++;
    register float tmp_b_2 = *b_2++;
    register float tmp_b_3 = *b_3++;

    register float tmp_a_0 = A(0, s);
    register float tmp_a_1 = A(1, s);
    register float tmp_a_2 = A(2, s);
    register float tmp_a_3 = A(3, s);

    // first and second rows
    tmp_00 += tmp_a_0 * tmp_b_0;
    tmp_10 += tmp_a_1 * tmp_b_0;

    tmp_01 += tmp_a_0 * tmp_b_1;
    tmp_11 += tmp_a_1 * tmp_b_1;

    tmp_02 += tmp_a_0 * tmp_b_2;
    tmp_12 += tmp_a_1 * tmp_b_2;

    tmp_03 += tmp_a_0 * tmp_b_3;
    tmp_13 += tmp_a_1 * tmp_b_3;

    // third and fouth rows
    tmp_20 += tmp_a_2 * tmp_b_0;
    tmp_30 += tmp_a_3 * tmp_b_0;

    tmp_21 += tmp_a_2 * tmp_b_1;
    tmp_31 += tmp_a_3 * tmp_b_1;

    tmp_22 += tmp_a_2 * tmp_b_2;
    tmp_32 += tmp_a_3 * tmp_b_2;

    tmp_23 += tmp_a_2 * tmp_b_3;
    tmp_33 += tmp_a_3 * tmp_b_3;
  }

  C(0, 0) += tmp_00;
  C(0, 1) += tmp_01;
  C(0, 2) += tmp_02;
  C(0, 3) += tmp_03;

  C(1, 0) += tmp_10;
  C(1, 1) += tmp_11;
  C(1, 2) += tmp_12;
  C(1, 3) += tmp_13;

  C(2, 0) += tmp_20;
  C(2, 1) += tmp_21;
  C(2, 2) += tmp_22;
  C(2, 3) += tmp_23;

  C(3, 0) += tmp_30;
  C(3, 1) += tmp_31;
  C(3, 2) += tmp_32;
  C(3, 3) += tmp_33;
}

void gemm_4x4_9(int m, int n, int k, float *a, int lda, float *b, int ldb,
                float *c, int ldc) {
  assert(m % 4 == 0);
  assert(n % 4 == 0);

  for (int j = 0; j < n; j += 4) {
    for (int i = 0; i < m; i += 4) {
      add_dot_4x4(k, &A(i, 0), lda, &B(0, j), ldb, &C(i, j), ldc);
    }
  }
}