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

TEST_F(MoneyTest, TestMultiplication) {
  MoneyPtr five = Money::Dollar(5);
  ASSERT_TRUE(Money::Dollar(10)->Equals(five->Times(2)));
  ASSERT_TRUE(Money::Dollar(15)->Equals(five->Times(3)));
}

TEST_F(MoneyTest, TestDollar) {
  ASSERT_TRUE(Money::Dollar(5)->Equals(Money::Dollar(5)));
  ASSERT_FALSE(Money::Dollar(5)->Equals(Money::Dollar(6)));
  ASSERT_FALSE(Money::Dollar(5)->Equals(Money::Franc(5)));
}

TEST_F(MoneyTest, TestCurrency) {
  ASSERT_EQ(Money::Dollar(1)->Currency(), "USD");
  ASSERT_EQ(Money::Franc(1)->Currency(), "CHF");
}
//
//TEST_F(MoneyTest, TestSimpleAddition) {
//  ASSERT_TRUE(Money::Dollar(10)->Equals(
//      Money::Dollar(5)->Plus(Money::Dollar(5))));
//}

TEST_F(MoneyTest, TestSimpleAddition) {
  MoneyPtr five = Money::Dollar(5);
  ExpressionPtr sum = five->Plus(Money::Dollar(5));
  Bank bank {};
  MoneyPtr reduced = bank.Reduce(sum, "USD"); // 归一到美元
  ASSERT_TRUE(Money::Dollar(10)->Equals(reduced));
}
