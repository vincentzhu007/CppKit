//
// Created by zgd on 7/11/23.
//

#include "demo_log.h"
#include <stdio.h>

const std::string kLevelNames[4] = {
    "DEBUG", "INFO", "ERROR", "FATAL"
};

void DemoLog::Info(const std::string &message) {
  WriteLog(Level::INFO, message);
}

void DemoLog::WriteLog(Level level, const std::string &message) {
  printf("[%5s] %s\n", kLevelNames[static_cast<int>(level)].c_str(), message.c_str());
}