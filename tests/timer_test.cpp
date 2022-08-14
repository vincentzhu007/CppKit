//
// Created by zgd on 2022/7/15.
//
#include <iostream>
#include "gtest/gtest.h"
#include "timer/timer.h"

using namespace std;
using namespace cppkit;

class TimerTest : public ::testing::Test {
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

void TimerCallbackStub(const TimerPtr &timer)
{
  cout << "timer callback stub" << endl;
}

TEST_F(TimerTest, Add)
{
  TimerManager timers;
  auto timer = timers.Add(1000, TimerCallbackStub);
  ASSERT_NE(timer, nullptr);
  ASSERT_TRUE(timers.Has(timer));
}

TEST_F(TimerTest, AddTimerWithNullCallback)
{
  TimerManager timers;
  auto timer = timers.Add(1000, nullptr);
  ASSERT_EQ(timer, nullptr);
  ASSERT_FALSE(timers.Has(timer));
}

TEST_F(TimerTest, Remove)
{
  TimerManager timers;
  auto timer = timers.Add(1000, TimerCallbackStub);
  ASSERT_TRUE(timers.Has(timer));

  timers.Remove(timer);
  ASSERT_FALSE(timers.Has(timer));
}

TEST_F(TimerTest, RemoveNullTimer)
{
  TimerManager timers;
  timers.Remove(nullptr);
  ASSERT_FALSE(timers.Has(nullptr));
}



