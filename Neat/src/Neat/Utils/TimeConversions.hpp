#pragma once

#include <chrono>

#include "Neat/Core/Types.hpp"

namespace Neat {

template <typename T = double, UIntMaxType Num = 1, UIntMaxType Den = 1,
          typename Rep, typename Period>
T timeCast(const std::chrono::duration<Rep, Period>& duration) {
  return std::chrono::duration_cast<
             std::chrono::duration<T, std::ratio<Num, Den>>>(duration)
      .count();
}

template <typename T = double, typename Rep, typename Period>
T nanosecondsCast(const std::chrono::duration<Rep, Period>& duration) {
  return timeCast<T, 1, 1000000000>(duration);
}

template <typename T = double, typename Rep, typename Period>
T microsecondsCast(const std::chrono::duration<Rep, Period>& duration) {
  return timeCast<T, 1, 1000000>(duration);
}

template <typename T = double, typename Rep, typename Period>
T millisecondsCast(const std::chrono::duration<Rep, Period>& duration) {
  return timeCast<T, 1, 1000>(duration);
}

template <typename T = double, typename Rep, typename Period>
T secondsCast(const std::chrono::duration<Rep, Period>& duration) {
  return timeCast<T>(duration);
}

template <typename T = double, typename Rep, typename Period>
T minutesCast(const std::chrono::duration<Rep, Period>& duration) {
  return timeCast<T, 60, 1>(duration);
}

template <typename T = double, typename Rep, typename Period>
T hoursCast(const std::chrono::duration<Rep, Period>& duration) {
  return timeCast<T, 3600, 1>(duration);
}

template <typename T = double, typename Rep, typename Period>
T daysCast(const std::chrono::duration<Rep, Period>& duration) {
  return timeCast<T, 86400, 1>(duration);
}

}  // namespace Neat