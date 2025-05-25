#pragma once

#include <chrono>
#include <utility>

#include "Neat/Core/Exceptions.hpp"
#include "Neat/Core/Types.hpp"

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

    if (not m_started)
      m_started = true;
  }

  template <typename T = double> T stop(TimeUnit timeUnit = TimeUnit::Seconds) {
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
        return nanosecondsElapsed<T>();
      case TimeUnit::Microseconds:
        return microsecondsElapsed<T>();
      case TimeUnit::Milliseconds:
        return millisecondsElapsed<T>();
      case TimeUnit::Seconds:
        return secondsElapsed<T>();
      case TimeUnit::Minutes:
        return minutesElapsed<T>();
      case TimeUnit::Hours:
        return hoursElapsed<T>();
      case TimeUnit::Days:
        return daysElapsed<T>();
      }
    }

    throw TimerNotStartedError();
  }

private:
  template <typename T> T nanosecondsElapsed() const {
    return std::chrono::duration<T, std::ratio<1, 1000000000>>(
               (m_currentTicks - m_startTicks))
        .count();
  }

  template <typename T> T microsecondsElapsed() const {
    return std::chrono::duration<T, std::ratio<1, 1000000>>(
               (m_currentTicks - m_startTicks))
        .count();
  }

  template <typename T> T millisecondsElapsed() const {
    return std::chrono::duration<T, std::ratio<1, 1000>>(
               (m_currentTicks - m_startTicks))
        .count();
  }

  template <typename T> T secondsElapsed() const {
    return std::chrono::duration<T>((m_currentTicks - m_startTicks)).count();
  }

  template <typename T> T minutesElapsed() const {
    return std::chrono::duration<T, std::ratio<60, 1>>(
               (m_currentTicks - m_startTicks))
        .count();
  }

  template <typename T> T hoursElapsed() const {
    return std::chrono::duration<T, std::ratio<3600, 1>>(
               (m_currentTicks - m_startTicks))
        .count();
  }

  template <typename T> T daysElapsed() const {
    return std::chrono::duration<T, std::ratio<86400, 1>>(
               (m_currentTicks - m_startTicks))
        .count();
  }

private:
  std::chrono::high_resolution_clock::time_point m_startTicks;
  std::chrono::high_resolution_clock::time_point m_currentTicks;
  bool m_started = false;
};
} // namespace Neat