
#include <benchmark/benchmark.h>

#include "gemm.h"

namespace bm = benchmark;

/**
 * bench gemm_0
 */
static void bm_gemm0(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_0(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm0)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_1
 */
static void bm_gemm1(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_1(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm1)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_2
 */
static void bm_gemm2(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_2(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm2)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_3
 */
static void bm_gemm3(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_3(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm3)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_4
 */
static void bm_gemm4(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_5
 */
static void bm_gemm5(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_5(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm5)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_6
 */
static void bm_gemm6(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_6(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm6)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_7
 */
static void bm_gemm7(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_7(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm7)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_8
 */
static void bm_gemm8(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_8(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm8)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_9
 */
static void bm_gemm9(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_9(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm9)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_4x4_3
 */
static void bm_gemm4x4_3(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4x4_3(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4x4_3)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_4x4_4
 */
static void bm_gemm4x4_4(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4x4_4(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4x4_4)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_4x4_5
 */
static void bm_gemm4x4_5(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4x4_5(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4x4_5)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_4x4_6
 */
static void bm_gemm4x4_6(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4x4_6(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4x4_6)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_4x4_7
 */
static void bm_gemm4x4_7(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4x4_7(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4x4_7)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_4x4_8
 */
static void bm_gemm4x4_8(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4x4_8(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4x4_8)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_4x4_9
 */
static void bm_gemm4x4_9(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4x4_9(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4x4_9)->MinWarmUpTime(10)->RangeMultiplier(2)->Range(16, 1024);

/**
 * bench gemm_4x4_10
 */
static void bm_gemm4x4_10(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4x4_10(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4x4_10)
    ->MinWarmUpTime(10)
    ->RangeMultiplier(2)
    ->Range(16, 1024);

/**
 * bench gemm_4x4_11
 */
static void bm_gemm4x4_11(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4x4_11(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4x4_11)
    ->MinWarmUpTime(10)
    ->RangeMultiplier(2)
    ->Range(16, 1024);

/**
 * bench gemm_4x4_12
 */
static void bm_gemm4x4_12(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4x4_12(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4x4_12)
    ->MinWarmUpTime(10)
    ->RangeMultiplier(2)
    ->Range(16, 1024);

/**
 * bench gemm_4x4_13
 */
static void bm_gemm4x4_13(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4x4_13(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4x4_13)
    ->MinWarmUpTime(10)
    ->RangeMultiplier(2)
    ->Range(16, 1024);

/**
 * bench gemm_4x4_14
 */
static void bm_gemm4x4_14(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4x4_14(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4x4_14)
    ->MinWarmUpTime(10)
    ->RangeMultiplier(2)
    ->Range(16, 1024);

/**
 * bench gemm_4x4_15
 */
static void bm_gemm4x4_15(bm::State &state) {
  int m, n, k;
  m = n = k = static_cast<int>(state.range(0));

  std::vector<float> a(m * k);
  std::vector<float> b(k * n);
  std::vector<float> c(m * n, 0.0);
  std::generate(a.begin(), a.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });
  std::generate(b.begin(), b.end(),
                []() { return std::rand() * 0.1 / RAND_MAX; });

  for (auto _ : state) {
    gemm_4x4_15(m, n, k, a.data(), m, b.data(), k, c.data(), m);
  }
}

BENCHMARK(bm_gemm4x4_15)
    ->MinWarmUpTime(10)
    ->RangeMultiplier(2)
    ->Range(16, 1024);