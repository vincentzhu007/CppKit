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

void gemm_1(int m, int n, int k, float *a, int lda, float *b, int ldb, float *c,
            int ldc) {
  assert(n % 4 == 0);

  for (int j = 0; j < n; j++) {
    for (int i = 0; i < m; i++) {
      add_dot(k, &A(i, 0), lda, &B(0, j), &C(i, j));
    }
  }
}