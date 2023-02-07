//
// Created by zgd on 2/7/23.
//

#ifndef CPPKIT_SRC_AI_UTILS_TIMEELAPSE_H_
#define CPPKIT_SRC_AI_UTILS_TIMEELAPSE_H_

#include <cstdint>
#include <string>
#include <chrono>

namespace cppkit {
namespace ai {
namespace utils {
class TimeElapse {
 public:
  TimeElapse();
  TimeElapse(const TimeElapse &) = delete;
  TimeElapse &operator=(const TimeElapse &) = delete;

  int64_t Elapsed() const;
  void Reset();
  std::string ToString() const;

 private:
  mutable std::chrono::time_point<std::chrono::high_resolution_clock> begin_;
};
} // cppkit
} // ai
} // utils

#endif //CPPKIT_SRC_AI_UTILS_TIMEELAPSE_H_
