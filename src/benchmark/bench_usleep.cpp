#include <benchmark/benchmark.h>
#include <unistd.h>

namespace bm = benchmark;

static void demo_usleep(bm::State &state) {
  for (auto _ : state) {
    usleep(1);
  }
}

BENCHMARK(demo_usleep);
