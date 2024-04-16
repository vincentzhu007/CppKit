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

static void add_dot_4x4(int k, float *a, int lda, float *b, int ldb, float *c,
                        int ldc) {
  add_dot(k, &A(0, 0), lda, &B(0, 0), &C(0, 0));
  add_dot(k, &A(0, 0), lda, &B(0, 1), &C(0, 1));
  add_dot(k, &A(0, 0), lda, &B(0, 2), &C(0, 2));
  add_dot(k, &A(0, 0), lda, &B(0, 3), &C(0, 3));

  add_dot(k, &A(1, 0), lda, &B(0, 0), &C(1, 0));
  add_dot(k, &A(1, 0), lda, &B(0, 1), &C(1, 1));
  add_dot(k, &A(1, 0), lda, &B(0, 2), &C(1, 2));
  add_dot(k, &A(1, 0), lda, &B(0, 3), &C(1, 3));

  add_dot(k, &A(2, 0), lda, &B(0, 0), &C(2, 0));
  add_dot(k, &A(2, 0), lda, &B(0, 1), &C(2, 1));
  add_dot(k, &A(2, 0), lda, &B(0, 2), &C(2, 2));
  add_dot(k, &A(2, 0), lda, &B(0, 3), &C(2, 3));

  add_dot(k, &A(3, 0), lda, &B(0, 0), &C(3, 0));
  add_dot(k, &A(3, 0), lda, &B(0, 1), &C(3, 1));
  add_dot(k, &A(3, 0), lda, &B(0, 2), &C(3, 2));
  add_dot(k, &A(3, 0), lda, &B(0, 3), &C(3, 3));
}

void gemm_4x4_3(int m, int n, int k, float *a, int lda, float *b, int ldb,
                float *c, int ldc) {
  assert(m % 4 == 0);
  assert(n % 4 == 0);

  for (int j = 0; j < n; j += 4) {
    for (int i = 0; i < m; i += 4) {
      add_dot_4x4(k, &A(i, 0), lda, &B(0, j), ldb, &C(i, j), ldc);
    }
  }
}