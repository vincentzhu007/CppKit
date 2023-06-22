//
// Created by zgd on 2/7/23.
//

#include "elapsed_time.h"

namespace utils {
ElapsedTime::ElapsedTime() {
  Reset();
}

int64_t ElapsedTime::AsMicroseconds() const {
  auto now = std::chrono::high_resolution_clock::now();
  auto elapsed = now - begin_;
  return static_cast<int64_t>(std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count());
}

int64_t ElapsedTime::AsMilliseconds() const {
  auto now = std::chrono::high_resolution_clock::now();
  auto elapsed = now - begin_;
  return static_cast<int64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count());
}

int64_t ElapsedTime::RollingMicroseconds() const {
  auto now = std::chrono::high_resolution_clock::now();
  auto elapsed = now - begin_;
  begin_ = now;
  return static_cast<int64_t>(std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count());
}

int64_t ElapsedTime::RollingMilliseconds() const {
  auto now = std::chrono::high_resolution_clock::now();
  auto elapsed = now - begin_;
  begin_ = now;
  return static_cast<int64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count());
}

void ElapsedTime::Reset() {
  begin_ = std::chrono::high_resolution_clock::now();
}

std::string ElapsedTime::ToString() const {
  return "Elapsed " + std::to_string(RollingMilliseconds()) + " ms";
}
} // utils