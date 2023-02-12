//
// Created by zgd on 2022/7/15.
//

#ifndef CPPKIT_TIMER_H
#define CPPKIT_TIMER_H

#include <iostream>
#include <memory>
#include <functional>
#include <map>
#include <condition_variable>
#include <thread>

namespace cppkit {
class Timer;
using TimerPtr = std::shared_ptr<Timer>;
using TimeCallback = std::function<void (const std::shared_ptr<Timer> &)>;

class Timer {
 public:
  Timer(uint64_t delayMs, TimeCallback callback);
  uint64_t delayMs_ = 0U;
  uint64_t expired_ = 0U;
  TimeCallback callback_ = nullptr;
};

class TimerManager {
 public:
  TimerManager();
  ~TimerManager();
  TimerPtr Add(uint64_t delayMs, TimeCallback callback);
  bool Has(const TimerPtr &timer) const;
  void Remove(const TimerPtr &timer);
 private:
  void Loop();
  TimerPtr Next();
  bool Wait(const TimerPtr &timer);
  void Callback(const TimerPtr &timer);
  static uint64_t MonotonicTime();

  std::multimap<uint64_t, TimerPtr> timers_;
  bool isRunning_ {false};
  mutable std::mutex mutex_;
  std::condition_variable conv_;
  std::thread thread_ {};
};
} // cppkit

#endif //CPPKIT_TIMER_H
