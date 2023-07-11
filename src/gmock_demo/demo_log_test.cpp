//
// Created by zgd on 7/11/23.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "demo_log.h"

using namespace testing;

class MockedDemoLog : public DemoLog {
 public:
  MOCK_METHOD2(WriteLog, void(DemoLog::Level level, const std::string &));

  MockedDemoLog() {
    ON_CALL(*this, WriteLog(_, _))
        .WillByDefault(Invoke(this, &MockedDemoLog::MockedWriteLog));
  }

 public:
  DemoLog::Level GetLevel() const { return level_; }
  std::string GetMessage() const { return message_; }

 private:
  void MockedWriteLog(DemoLog::Level level, const std::string &message) {
    level_ = level;
    message_ = message;
  }

  DemoLog::Level level_;
  std::string message_;
};

class DemoLogTest: public testing::Test {
 public:
  void SetUp() {}
  void TearDown() {}
};

TEST_F(DemoLogTest, TestInfoLog) {
  DemoLog demo_log;
  demo_log.Info("Hello");
  demo_log.Info("World");
}

TEST_F(DemoLogTest, TestMockedInfoLog) {
  MockedDemoLog mocked_log;
  mocked_log.Info("Hello");
  EXPECT_EQ(mocked_log.GetLevel(), DemoLog::Level::INFO);
  EXPECT_EQ(mocked_log.GetMessage(), "Hello");

  mocked_log.Info("This is a test log");
  EXPECT_EQ(mocked_log.GetLevel(), DemoLog::Level::INFO);
  EXPECT_EQ(mocked_log.GetMessage(), "This is a test log");
}

