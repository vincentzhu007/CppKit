//
// Created by zgd on 2/7/23.
//

#ifndef CPPKIT_SRC_AI_UTILS_ELAPSED_TIME_H_
#define CPPKIT_SRC_AI_UTILS_ELAPSED_TIME_H_

#include <cstdint>
#include <string>
#include <chrono>

namespace utils {
/**
 * 测试消耗的时间，采用RAII设计，将时间测量的起始时刻与ElapsedTime对象的构造时间相结合。
 */
class ElapsedTime {
 public:
  ElapsedTime();
  ElapsedTime(const ElapsedTime &) = delete;
  ElapsedTime &operator=(const ElapsedTime &) = delete;

  int64_t AsMicroseconds() const;
  int64_t AsMilliseconds() const;
  int64_t RollingMicroseconds() const;
  int64_t RollingMilliseconds() const;
  void Reset();
  std::string ToString() const;

 private:
  mutable std::chrono::time_point<std::chrono::high_resolution_clock> begin_;
};
} // cppkit

#endif //CPPKIT_SRC_AI_UTILS_ELAPSED_TIME_H_
