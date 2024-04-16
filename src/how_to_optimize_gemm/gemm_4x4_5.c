#include <assert.h>

#include "gemm.h"

// colum-major
#define A(i, j) a[(j) * lda + (i)]
#define B(i, j) b[(j) * ldb + (i)]
#define C(i, j) c[(j) * ldc + (i)]

static void add_dot_4x4(int k, float *a, int lda, float *b, int ldb, float *c,
                        int ldc) {
  for (int s = 0; s < k; s++) {
    C(0, 0) += A(0, s) * B(s, 0);
    C(0, 1) += A(0, s) * B(s, 1);
    C(0, 2) += A(0, s) * B(s, 2);
    C(0, 3) += A(0, s) * B(s, 3);

    C(1, 0) += A(1, s) * B(s, 0);
    C(1, 1) += A(1, s) * B(s, 1);
    C(1, 2) += A(1, s) * B(s, 2);
    C(1, 3) += A(1, s) * B(s, 3);

    C(2, 0) += A(2, s) * B(s, 0);
    C(2, 1) += A(2, s) * B(s, 1);
    C(2, 2) += A(2, s) * B(s, 2);
    C(2, 3) += A(2, s) * B(s, 3);

    C(3, 0) += A(3, s) * B(s, 0);
    C(3, 1) += A(3, s) * B(s, 1);
    C(3, 2) += A(3, s) * B(s, 2);
    C(3, 3) += A(3, s) * B(s, 3);
  }
}

void gemm_4x4_5(int m, int n, int k, float *a, int lda, float *b, int ldb,
                float *c, int ldc) {
  assert(m % 4 == 0);
  assert(n % 4 == 0);

  for (int j = 0; j < n; j += 4) {
    for (int i = 0; i < m; i += 4) {
      add_dot_4x4(k, &A(i, 0), lda, &B(0, j), ldb, &C(i, j), ldc);
    }
  }
}