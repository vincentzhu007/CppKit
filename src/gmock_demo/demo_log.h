//
// Created by zgd on 7/11/23.
//

#ifndef CPPKIT_SRC_GMOCK_DEMO_DEMO_LOG_H_
#define CPPKIT_SRC_GMOCK_DEMO_DEMO_LOG_H_

#include <string>

class DemoLog {
 public:
  enum class Level: int {
    DEBUG = 0,
    INFO = 1,
    ERROR = 2,
    FATAL = 3,
  };

 public:
  void Info(const std::string &message);

 private:
  virtual void WriteLog(Level level, const std::string &message);
};

#endif //CPPKIT_SRC_GMOCK_DEMO_DEMO_LOG_H_
