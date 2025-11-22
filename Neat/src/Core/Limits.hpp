#pragma once

#include <limits>

namespace Neat {
namespace Limits {
template <typename T>
inline constexpr T Max = std::numeric_limits<T>::max();

template <typename T>
inline constexpr T Min = std::numeric_limits<T>::min();

template <typename T>
inline constexpr T Epsilon = std::numeric_limits<T>::epsilon();

template <typename T>
inline constexpr T Infinity = std::numeric_limits<T>::infinity();

template <typename T>
inline constexpr T NaN = std::numeric_limits<T>::quiet_NaN();

template <typename T>
inline constexpr T SignalNaN = std::numeric_limits<T>::signaling_NaN();
}  // namespace Limits
}  // namespace Neat