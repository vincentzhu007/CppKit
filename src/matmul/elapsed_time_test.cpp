//
// Created by zgd on 2023/6/22.
//

#include <iostream>
#include "gtest/gtest.h"
#include "elapsed_time.h"

using namespace utils;

namespace {
constexpr int64_t kMicroSecondRoundError = 1000; // 1000us
constexpr int64_t kMilliSecondRoundError = 1; // 1ms

/**
 * Check if t in range [lower, upper).
 */
void AssertRange(int64_t t, int64_t lower, int64_t upper) {
  ASSERT_GE(t, lower);
  ASSERT_LT(t, upper);
}

void AssertApproximateMicroSeconds(int64_t t, int64_t expect) {
  AssertRange(t, expect, expect + kMicroSecondRoundError);
}

void AssertApproximateMilliSeconds(int64_t t, int64_t expect) {
  AssertRange(t, expect, expect + kMilliSecondRoundError);
}
}

TEST(ElapsedTimeTest, AsMicroseconds) {
  ElapsedTime elapsed_time;
  // 第一次耗时1ms，预期测量耗时1000us。
  usleep(1000);
  AssertApproximateMicroSeconds(elapsed_time.AsMicroseconds(), 1000);

  // 第二次，从同一起始时刻测量耗时，预计耗时2000us。
  usleep(1000);
  AssertApproximateMicroSeconds(elapsed_time.AsMicroseconds(), 2000);
}

TEST(ElapsedTimeTest, AsMilliseconds) {
  ElapsedTime elapsed_time;

  // 第一次耗时1ms，预期测量耗时2ms。
  usleep(2000);
  AssertApproximateMilliSeconds(elapsed_time.AsMilliseconds(), 2);

  // 第二次，从同一起始时刻测量耗时，预计耗时4ms。
  usleep(2000);
  AssertApproximateMilliSeconds(elapsed_time.AsMilliseconds(), 4);
}

TEST(ElapsedTimeTest, RollingMicroseconds) {
  ElapsedTime elapsed_time;

  // 第一次耗时1ms，预期测量耗时1000us。
  usleep(1000);
  AssertApproximateMicroSeconds(elapsed_time.RollingMicroseconds(), 1000);

  // 第二次测量，将第一次测量结束作为新的起始时刻，预计耗时1000us。
  usleep(1000);
  AssertApproximateMicroSeconds(elapsed_time.RollingMicroseconds(), 1000);
}

TEST(ElapsedTimeTest, RollingMilliseconds) {
  ElapsedTime elapsed_time;

  // 第一次耗时1ms，预期测量耗时2ms。
  usleep(2000);
  AssertApproximateMilliSeconds(elapsed_time.RollingMilliseconds(), 2);

  // 第二次测量，将第一次测量结束作为新的起始时刻，预计耗时2ms。
  usleep(2000);
  AssertApproximateMilliSeconds(elapsed_time.RollingMilliseconds(), 2);
}

TEST(ElapsedTimeTest, NestedTime) {
  ElapsedTime outside;
  for (int i = 1; i <= 3; i++) {
    ElapsedTime inside;
    usleep(1000);
    AssertApproximateMicroSeconds(inside.RollingMicroseconds(), 1000);
    AssertApproximateMicroSeconds(outside.AsMicroseconds(), 1000 * i);
  }
}

TEST(ElapsedTimeTest, Reset) {
  ElapsedTime elapsed_time;

  // 第一次耗时1ms，预期测量耗时1000us。
  usleep(1000);
  AssertApproximateMicroSeconds(elapsed_time.AsMicroseconds(), 1000);

  // 第二次测量，将第一次测量结束作为新的起始时刻，预计耗时1000us。
  elapsed_time.Reset();
  usleep(1000);
  AssertApproximateMicroSeconds(elapsed_time.AsMicroseconds(), 1000);
}
