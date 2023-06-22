//
// Created by zgd on 2023/6/22.
//

#include <iostream>
#include "gtest/gtest.h"
#include "elapsed_time.h"

using namespace utils;

TEST(ElapsedTimeTest, AsMicroseconds) {
  ElapsedTime elapsed_time;
  // 第一次耗时1ms，预期测量耗时1000us。
  usleep(1000);
  std::cout << "Firstly elapsed: " << elapsed_time.AsMicroseconds() << " us." << std::endl;
  ASSERT_GE(elapsed_time.AsMicroseconds(), 1000);
  ASSERT_LT(elapsed_time.AsMicroseconds(), 1500);

  // 第二次，从同一起始时刻测量耗时，预计耗时2000us。
  usleep(1000);
  std::cout << "Secondly elapsed: " << elapsed_time.AsMicroseconds() << " us." << std::endl;
  ASSERT_GE(elapsed_time.AsMicroseconds(), 2000);
  ASSERT_LT(elapsed_time.AsMicroseconds(), 2500);
}

TEST(ElapsedTimeTest, AsMilliseconds) {
  ElapsedTime elapsed_time;

  // 第一次耗时1ms，预期测量耗时2ms。
  usleep(2000);
  std::cout << "Firstly elapsed: " << elapsed_time.AsMilliseconds() << " ms." << std::endl;
  ASSERT_GE(elapsed_time.AsMilliseconds(), 2);

  // 第二次，从同一起始时刻测量耗时，预计耗时4ms。
  usleep(2000);
  std::cout << "Secondly elapsed: " << elapsed_time.AsMilliseconds() << " ms." << std::endl;
  ASSERT_GE(elapsed_time.AsMilliseconds(), 4);
}

TEST(ElapsedTimeTest, RollingMicroseconds) {
  ElapsedTime elapsed_time;

  // 第一次耗时1ms，预期测量耗时1000us。
  usleep(1000);
  ASSERT_GE(elapsed_time.RollingMicroseconds(), 1000);

  // 第二次测量，将第一次测量结束作为新的起始时刻，预计耗时1000us。
  usleep(1000);
  ASSERT_GE(elapsed_time.RollingMicroseconds(), 1000);
}

TEST(ElapsedTimeTest, RollingMilliseconds) {
  ElapsedTime elapsed_time;

  // 第一次耗时1ms，预期测量耗时2ms。
  usleep(2000);
  ASSERT_GE(elapsed_time.RollingMilliseconds(), 2);

  // 第二次测量，将第一次测量结束作为新的起始时刻，预计耗时2ms。
  usleep(2000);
  ASSERT_GE(elapsed_time.RollingMilliseconds(), 2);
}
