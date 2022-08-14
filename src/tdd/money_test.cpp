//
// Created by zgd on 2022/8/5.
//

#include <iostream>
#include "gtest/gtest.h"
#include "tdd/money.h"

using namespace cppkit;

class MoneyTest : public ::testing::Test {
 public:
  static void SetUpTestcases() {
  }
  static void TearDownTestcases() {
  }
  void SetUp() {
  }
  void TearDown() {
  }
};

TEST_F(MoneyTest, TestDollarMultiplication) {
  MoneyPtr five = Money::NewDollar(5);
  ASSERT_TRUE(Money::NewDollar(10)->Equals(five->Times(2)));
  ASSERT_TRUE(Money::NewDollar(15)->Equals(five->Times(3)));
}

TEST_F(MoneyTest, TestDollarEquality) {
  MoneyPtr five = Money::NewDollar(5);
  ASSERT_TRUE(five->Equals(Money::NewDollar(5)));
  ASSERT_FALSE(five->Equals(Money::NewDollar(6)));
}

TEST_F(MoneyTest, TestFrancMultiplication) {
  MoneyPtr five = Money::NewFranc(5);
  ASSERT_TRUE(Money::NewFranc(10)->Equals(five->Times(2)));
  ASSERT_TRUE(Money::NewFranc(15)->Equals(five->Times(3)));
}

TEST_F(MoneyTest, TestFrancEquality) {
  MoneyPtr five = Money::NewFranc(5);
  ASSERT_TRUE(five->Equals(Money::NewFranc(5)));
  ASSERT_FALSE(five->Equals(Money::NewFranc(6)));
}

TEST_F(MoneyTest, TestCurrency) {
  ASSERT_EQ(Money::NewDollar(1)->Currency(),"USD");
  ASSERT_EQ(Money::NewFranc(1)->Currency(),"CHF");
}
