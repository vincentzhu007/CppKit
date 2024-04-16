#include "gemm.h"

// colum-major
#define A(i, j) a[(j) * lda + (i)]
#define B(i, j) b[(j) * ldb + (i)]
#define C(i, j) c[(j) * ldc + (i)]

void gemm_0(int m, int n, int k, float *a, int lda, float *b, int ldb, float *c,
            int ldc) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      for (int s = 0; s < k; s++) {
        C(i, j) = C(i, j) + A(i, s) * B(s, j);
      }
    }
  }
}