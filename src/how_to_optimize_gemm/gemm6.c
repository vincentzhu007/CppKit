#include <assert.h>

#include "gemm.h"

// colum-major
#define A(i, j) a[(j) * lda + (i)]
#define B(i, j) b[(j) * ldb + (i)]
#define C(i, j) c[(j) * ldc + (i)]

static void add_dot_1x4(int k, float *a, int lda, float *b, int ldb, float *c,
                        int ldc) {
  register float tmp_0 = .0f;
  register float tmp_1 = .0f;
  register float tmp_2 = .0f;
  register float tmp_3 = .0f;

  for (int s = 0; s < k; s++) {
    register float tmp_a = A(0, s);
    tmp_0 += tmp_a * B(s, 0);
    tmp_1 += tmp_a * B(s, 1);
    tmp_2 += tmp_a * B(s, 2);
    tmp_3 += tmp_a * B(s, 3);
  }

  C(0, 0) = tmp_0;
  C(0, 1) = tmp_1;
  C(0, 2) = tmp_2;
  C(0, 3) = tmp_3;
}

void gemm_6(int m, int n, int k, float *a, int lda, float *b, int ldb, float *c,
            int ldc) {
  assert(n % 4 == 0);

  for (int j = 0; j < n; j += 4) {
    for (int i = 0; i < m; i++) {
      add_dot_1x4(k, &A(i, 0), lda, &B(0, j), ldb, &C(i, j), ldc);
    }
  }
}