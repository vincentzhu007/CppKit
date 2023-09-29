//
// Created by zgd on 2022/7/15.
//

#include "timer.h"
#include <time.h>
#include <cstring>

namespace cppkit {
Timer::Timer(uint64_t delayMs, TimeCallback callback)
  : delayMs_(delayMs), callback_(callback)
{
}

TimerManager::TimerManager()
{
  isRunning_ = true;
  thread_ = std::thread(std::bind(&TimerManager::Loop, this));
}

TimerManager::~TimerManager()
{
  {
    std::lock_guard<std::mutex> lock(mutex_);
    isRunning_ = false;
    conv_.notify_all();
  }
  if (thread_.joinable()) {
    thread_.join();
  }
}

TimerPtr TimerManager::Add(uint64_t delayMs, TimeCallback callback)
{
  if (callback == nullptr) {
    return nullptr;
  }
  auto timer = std::make_shared<Timer>(delayMs, callback);
  (void)timers_.emplace(delayMs, timer);
  return timer;
}

bool TimerManager::Has(const TimerPtr &timer) const
{
  if (timer == nullptr) {
    return false;
  }
  auto pair = timers_.equal_range(timer->delayMs_);
  for (auto iter = pair.first; iter != pair.second; iter++) {
    if (iter->second == timer) {
      return true;
    }
  }
  return false;
}

void TimerManager::Remove(const TimerPtr &timer)
{
  if (timer == nullptr) {
    return;
  }
  auto pair = timers_.equal_range(timer->delayMs_);
  for (auto iter = pair.first; iter != pair.second; iter++) {
    if (iter->second == timer) {
      (void)timers_.erase(iter);
      return;
    }
  }
}

void TimerManager::Loop()
{
  while (isRunning_)
  {
    auto timer = Next();
    if (Wait(timer)) {
      Callback(timer);
    }
  }
}

bool TimerManager::Wait(const TimerPtr &timer)
{
  uint64_t timeout = 10000; // 10s
  if (timer != nullptr) {
    uint64_t now = MonotonicTime();
    timeout = now < timer->expired_ ? (timer->expired_ - now) : 0U;
  }

  std::unique_lock<std::mutex> lock(mutex_);
  auto status = conv_.wait_for(lock, std::chrono::milliseconds(timeout), [&]() {
    return !isRunning_;
  });
  return !status;
}

uint64_t TimerManager::MonotonicTime()
{
  struct timespec tp;
  if (clock_gettime(CLOCK_MONOTONIC, &tp) == -1) {
    std::cerr << "get monotonic clock error, " << strerror(errno) << std::endl;
    return 0U;
  }
  return (tp.tv_sec * 1000U) + (tp.tv_nsec % 1000U);
}

void TimerManager::Callback(const TimerPtr &timer)
{
  timer->callback_(timer);
}

TimerPtr TimerManager::Next()
{
  std::lock_guard<std::mutex> lock(mutex_);
  return timers_.empty() ? nullptr : timers_.begin()->second;
}

} // cppkit