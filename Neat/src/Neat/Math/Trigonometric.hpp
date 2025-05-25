#pragma once

#include "Neat/Math/Types/TypeVectorN.hpp"

namespace Neat {
// Utility
template <typename T> inline constexpr T radians(T angleDegrees);

template <typename T> inline constexpr T degrees(T angleRadians);

template <typename T> inline constexpr T wrapPi(T angleRadians);

template <typename T> inline constexpr T wrapTwoPi(T angleRadians);

template <typename T> inline constexpr T wrap180(T angleDegrees);

template <typename T> inline constexpr T wrap360(T angleDegrees);

// Trigonometric functions -------------------------------------------------
// Scalar
template <typename T> inline T sin(T value);

template <typename T> inline T cos(T value);

template <typename T> inline T tan(T value);

template <typename T> inline T asin(T value);

template <typename T> inline T acos(T value);

template <typename T> inline T atan(T value);

template <typename T> inline T sinh(T value);

template <typename T> inline T cosh(T value);

template <typename T> inline T tanh(T value);

template <typename T> inline T asinh(T value);

template <typename T> inline T acosh(T value);

template <typename T> inline T atanh(T value);

template <typename T> inline T atan2(T y, T x);

// Vector
template <UInt32 N, typename T> inline Vector<N, T> sin(const Vector<N, T> &v);

template <UInt32 N, typename T> inline Vector<N, T> cos(const Vector<N, T> &v);

template <UInt32 N, typename T> inline Vector<N, T> tan(const Vector<N, T> &v);

template <UInt32 N, typename T> inline Vector<N, T> asin(const Vector<N, T> &v);

template <UInt32 N, typename T> inline Vector<N, T> acos(const Vector<N, T> &v);

template <UInt32 N, typename T> inline Vector<N, T> atan(const Vector<N, T> &v);

template <UInt32 N, typename T> inline Vector<N, T> sinh(const Vector<N, T> &v);

template <UInt32 N, typename T> inline Vector<N, T> cosh(const Vector<N, T> &v);

template <UInt32 N, typename T> inline Vector<N, T> tanh(const Vector<N, T> &v);

template <UInt32 N, typename T>
inline Vector<N, T> asinh(const Vector<N, T> &v);

template <UInt32 N, typename T>
inline Vector<N, T> acosh(const Vector<N, T> &v);

template <UInt32 N, typename T>
inline Vector<N, T> atanh(const Vector<N, T> &v);

template <UInt32 N, typename T>
inline Vector<N, T> atan2(const Vector<N, T> &vy, const Vector<N, T> &vx);
} // namespace Neat

#include "Neat/Math/Trigonometric.inl"