//
// Created by zgd on 2022/12/4.
//

#include <iostream>
#include "gtest/gtest.h"
#include "error/error.h"

using namespace std;
using namespace cppkit;

class ErrorTest : public ::testing::Test {
 public:
  static void SetUpTestcases()
  {
  }
  static void TearDownTestcases()
  {
  }
  void SetUp()
  {
  }
  void TearDown()
  {
  }
};

TEST_F(ErrorTest, Construct) {
  Error error;
  ASSERT_TRUE(error.IsOk());
  ASSERT_TRUE(error.Message().empty());

  Error error2(cppkit::ErrorCode::kNullPoint);
  ASSERT_TRUE(error2.IsNullPoint());
  ASSERT_TRUE(error2.Message().empty());

  std::string message = "config file path is null";
  Error error3(cppkit::ErrorCode::kBadFuncParm, message);
  ASSERT_TRUE(error3.EqualCode(cppkit::ErrorCode::kBadFuncParm));
  ASSERT_TRUE(error3.Message() == message);
}




