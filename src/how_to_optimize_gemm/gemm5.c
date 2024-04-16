#include <assert.h>

#include "gemm.h"

// colum-major
#define A(i, j) a[(j) * lda + (i)]
#define B(i, j) b[(j) * ldb + (i)]
#define C(i, j) c[(j) * ldc + (i)]

// vector dot-mul and acc
static void add_dot(int k, float *a, int lda, float *b, float *c) {
  for (int s = 0; s < k; s++) {
    *c += a[s * lda] * b[s];
  }
}

static void add_dot_1x4(int k, float *a, int lda, float *b, int ldb, float *c,
                        int ldc) {
  for (int s = 0; s < k; s++) {
    C(0, 0) += A(0, s) * B(s, 0);
    C(0, 1) += A(0, s) * B(s, 1);
    C(0, 2) += A(0, s) * B(s, 2);
    C(0, 3) += A(0, s) * B(s, 3);
  }
}

void gemm_5(int m, int n, int k, float *a, int lda, float *b, int ldb, float *c,
            int ldc) {
  assert(n % 4 == 0);

  for (int j = 0; j < n; j += 4) {
    for (int i = 0; i < m; i++) {
      add_dot_1x4(k, &A(i, 0), lda, &B(0, j), ldb, &C(i, j), ldc);
    }
  }
}