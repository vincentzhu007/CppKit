#include <strings.h>

#include "gemm.h"

// colum-major
#define A(i, j) a[(j) * lda + (i)]
#define B(i, j) b[(j) * ldb + (i)]
#define C(i, j) c[(j) * ldc + (i)]

void gemm_0_ikj(int m, int n, int k, float *a, int lda, float *b, int ldb,
                float *c, int ldc) {
  float *tmp = (float *)malloc(sizeof(float) * n);

  for (int i = 0; i < m; i++) {
    bzero(tmp, n * sizeof(float));

    for (int s = 0; s < k; s++) {
      for (int j = 0; j < n; j++) {
        tmp[j] += A(i, s) * B(s, j);
      }
    }

    for (int j = 0; j < n; j++) {
      C(i, j) = tmp[j];
    }
  }

  free(tmp);
}