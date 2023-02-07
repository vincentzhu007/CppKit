//
// Created by zgd on 2/7/23.
//

#include "TimeElapse.h"

namespace cppkit {
namespace ai {
namespace utils {
TimeElapse::TimeElapse() {
  Reset();
}

int64_t TimeElapse::Elapsed() const {
  auto now = std::chrono::high_resolution_clock::now();
  auto elapsed = now - begin_;
  begin_ = now;
  return static_cast<int64_t>(std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count());
}

void TimeElapse::Reset() {
  begin_ = std::chrono::high_resolution_clock::now();
}

std::string TimeElapse::ToString() const {
  return "Time elapsed: " + std::to_string(Elapsed()) + " us";
}
} // cppkit
} // ai
} // utils