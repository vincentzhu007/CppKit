//
// Created by zgd on 2023/10/27.
//
#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "demo_register.h"

class DemoRegisterTest : public ::testing::Test {
 public:
  static void SetUpTestcases()
  {
  }
  static void TearDownTestcases()
  {
  }
  void SetUp()
  {
    DemoRegistry::GetInstance().Clear();
  }
  void TearDown()
  {
  }
};

std::any TestCreator() {
  return std::string("test_creator");
}

TEST_F(DemoRegisterTest, GoodRegister) {
  static DemoRegistrar registrar("test_key", TestCreator);
  auto creator = DemoRegistry::GetInstance().GetCreator("test_key");
  ASSERT_NE(creator, nullptr);
  ASSERT_EQ(std::any_cast<std::string>(creator()), std::any_cast<std::string>(TestCreator()));
}

TEST_F(DemoRegisterTest, BadRegister) {
  static DemoRegistrar registrar("test_key", TestCreator);
  auto creator = DemoRegistry::GetInstance().GetCreator("bad_key");
  ASSERT_EQ(creator, nullptr);
}
