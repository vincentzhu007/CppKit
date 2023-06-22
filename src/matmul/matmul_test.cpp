//
// Created by zgd on 2023/6/22.
//

#include <vector>
#include "gtest/gtest.h"
#include "matmul.h"

namespace {
/* 2x2 matrix instance. */
const std::vector<float> kA_2x2 = {
    1, 2,
    3, 4};
const std::vector<float> kB_2x2 = {
    5, 6,
    7, 8};
const std::vector<float> kExpect_2x2 = {
    19, 22,
    43, 50};

/* 3x3 matrix instance. */
const std::vector<float> kA_3x3 = {
    1.1, 2.2, 3.3,
    4.4, 5.5, 6.6,
    7.7, 8.8, 9.9};
const std::vector<float> kB_3x3 = {
    9.1, 8.2, 7.3,
    6.4, 5.5, 4.6,
    3.7, 2.8, 1.9};
const std::vector<float> kExpect_3x3 = {
    36.3 ,  30.36,  24.42,
    99.66,  84.81,  69.96,
    163.02, 139.26, 115.5};

/**
 * Check if all float in result is close to the expect one.
 */
void AssertAllClose(const std::vector<float> &result, const std::vector<float> &expect) {
  ASSERT_EQ(result.size(), expect.size());
  for(size_t i = 0; i < expect.size(); i++) {
    ASSERT_FLOAT_EQ(result[i], expect[i]);
  }
}
}

TEST(MatmulTest, SGEMMNativeAccuracy) {
  std::vector<float> result_2x2(2 * 2, 0.0);
  SGEMMNaive(kA_2x2.data(), kB_2x2.data(), result_2x2.data(), 2, 2, 2);
  AssertAllClose(result_2x2, kExpect_2x2);

  std::vector<float> result_3x3(3 * 3, 0.0);
  SGEMMNaive(kA_3x3.data(), kB_3x3.data(), result_3x3.data(), 3, 3, 3);
  AssertAllClose(result_3x3, kExpect_3x3);
}

