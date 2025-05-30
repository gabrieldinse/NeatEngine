#pragma once

#include "Neat/Math/Types/TypeQuaternion.hpp"
#include "Neat/Math/Types/TypeVectorN.hpp"

namespace Neat {
// Scalar
template <typename T>
inline T log2(T value);

template <typename T>
inline T log10(T value);

template <typename T>
inline T sqrt(T value);

template <typename T>
inline T inverseSqrt(T value);

template <typename T>
inline T pow(T base, T exponent);

template <typename T>
inline T exp(T value);

template <typename T>
inline T log(T value);

template <typename T>
inline T ln(T value);

template <typename T>
inline T exp2(T value);

// Vector
template <UInt32 N, typename T>
inline Vector<N, T> log2(const Vector<N, T> &v);

template <UInt32 N, typename T>
inline Vector<N, T> log10(const Vector<N, T> &v);

template <UInt32 N, typename T>
inline Vector<N, T> sqrt(const Vector<N, T> &v);

template <UInt32 N, typename T>
inline Vector<N, T> inverseSqrt(const Vector<N, T> &v);

template <UInt32 N, typename T>
inline Vector<N, T> pow(const Vector<N, T> &q, T exponent);

template <UInt32 N, typename T>
inline Vector<N, T> exp(const Vector<N, T> &v);

template <UInt32 N, typename T>
inline Vector<N, T> log(const Vector<N, T> &v);

template <UInt32 N, typename T>
inline Vector<N, T> ln(const Vector<N, T> &v);

template <UInt32 N, typename T>
inline Vector<N, T> exp2(const Vector<N, T> &v);

// Quaternion
template <typename T>
inline Quaternion<T> log(const Quaternion<T> &q);

template <typename T>
inline Quaternion<T> ln(const Quaternion<T> &q);

template <typename T>
inline Quaternion<T> exp(const Quaternion<T> &q);

template <typename T>
inline Quaternion<T> pow(const Quaternion<T> &q, T exponent);
}  // namespace Neat

#include "Neat/Math/Exponential.inl"