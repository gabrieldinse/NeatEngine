#pragma once

#include <chrono>
#include <utility>

#include "Neat/Core/Exceptions.hpp"
#include "Neat/Core/Types.hpp"
#include "Neat/Utils/TimeConversions.hpp"

namespace Neat {
enum class TimeUnit {
  Nanoseconds,
  Microseconds,
  Milliseconds,
  Seconds,
  Minutes,
  Hours,
  Days
};

class Timer {
 public:
  Timer() = default;

  void start() {
    m_startTicks = std::chrono::high_resolution_clock::now();

    if (not m_started) m_started = true;
  }

  template <typename T = double>
  T stop(TimeUnit timeUnit = TimeUnit::Seconds) {
    auto elapsed_time = elapsed<T>(timeUnit);
    m_started = false;

    return elapsed_time;
  }

  template <typename T = double>
  T restart(TimeUnit timeUnit = TimeUnit::Seconds) {
    auto elapsed_time = elapsed<T>(timeUnit);
    m_startTicks = m_currentTicks;

    return elapsed_time;
  }

  template <typename T = double>
  T elapsed(TimeUnit timeUnit = TimeUnit::Seconds) {
    if (m_started) {
      m_currentTicks = std::chrono::high_resolution_clock::now();

      switch (timeUnit) {
        case TimeUnit::Nanoseconds:
          return nanosecondsCast<T>((m_currentTicks - m_startTicks));
        case TimeUnit::Microseconds:
          return microsecondsCast<T>((m_currentTicks - m_startTicks));
        case TimeUnit::Milliseconds:
          return millisecondsCast<T>((m_currentTicks - m_startTicks));
        case TimeUnit::Seconds:
          return secondsCast<T>((m_currentTicks - m_startTicks));
        case TimeUnit::Minutes:
          return minutesCast<T>((m_currentTicks - m_startTicks));
        case TimeUnit::Hours:
          return hoursCast<T>((m_currentTicks - m_startTicks));
        case TimeUnit::Days:
          return daysCast<T>((m_currentTicks - m_startTicks));
      }
    }

    throw TimerNotStartedError();
  }

  template <typename T = double>
  T currentTimeSinceEpoch(TimeUnit timeUnit = TimeUnit::Seconds) const {
    switch (timeUnit) {
      case TimeUnit::Nanoseconds:
        return nanosecondsCast<T>(m_currentTicks.time_since_epoch());
      case TimeUnit::Microseconds:
        return microsecondsCast<T>(m_currentTicks.time_since_epoch());
      case TimeUnit::Milliseconds:
        return millisecondsCast<T>(m_currentTicks.time_since_epoch());
      case TimeUnit::Seconds:
        return secondsCast<T>(m_currentTicks.time_since_epoch());
      case TimeUnit::Minutes:
        return minutesCast<T>(m_currentTicks.time_since_epoch());
      case TimeUnit::Hours:
        return hoursCast<T>(m_currentTicks.time_since_epoch());
      case TimeUnit::Days:
        return daysCast<T>(m_currentTicks.time_since_epoch());
    }
  }

  template <typename T = double>
  T startTimeSinceEpoch(TimeUnit timeUnit = TimeUnit::Seconds) const {
    switch (timeUnit) {
      case TimeUnit::Nanoseconds:
        return nanosecondsCast<T>(m_startTicks.time_since_epoch());
      case TimeUnit::Microseconds:
        return microsecondsCast<T>(m_startTicks.time_since_epoch());
      case TimeUnit::Milliseconds:
        return millisecondsCast<T>(m_startTicks.time_since_epoch());
      case TimeUnit::Seconds:
        return secondsCast<T>(m_startTicks.time_since_epoch());
      case TimeUnit::Minutes:
        return minutesCast<T>(m_startTicks.time_since_epoch());
      case TimeUnit::Hours:
        return hoursCast<T>(m_startTicks.time_since_epoch());
      case TimeUnit::Days:
        return daysCast<T>(m_startTicks.time_since_epoch());
    }
  }

 private:
  std::chrono::high_resolution_clock::time_point m_startTicks;
  std::chrono::high_resolution_clock::time_point m_currentTicks;
  bool m_started = false;
};
}  // namespace Neat