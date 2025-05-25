#pragma once

#include "Neat/Core/Types.hpp"

namespace Neat {
template <template <UInt32 N, typename T> class Vector, UInt32 N, typename R,
          typename T>
struct FunctorVector {};

// Vector1 specialization
template <template <UInt32 N, typename T> class Vector, typename R, typename T>
struct FunctorVector<Vector, 1, R, T> {
  static Vector<1, R> call(R (*function)(T x), const Vector<1, T> &v) {
    return Vector<1, R>(function(v.x));
  }
};

// Vector2 specialization
template <template <UInt32 N, typename T> class Vector, typename R, typename T>
struct FunctorVector<Vector, 2, R, T> {
  static Vector<2, R> call(R (*function)(T x), const Vector<2, T> &v) {
    return Vector<2, R>(function(v.x), function(v.y));
  }
};

// Vector3 specialization
template <template <UInt32 N, typename T> class Vector, typename R, typename T>
struct FunctorVector<Vector, 3, R, T> {
  static Vector<3, R> call(R (*function)(T x), const Vector<3, T> &v) {
    return Vector<3, R>(function(v.x), function(v.y), function(v.z));
  }
};

// Vector4 specialization
template <template <UInt32 N, typename T> class Vector, typename R, typename T>
struct FunctorVector<Vector, 4, R, T> {
  static Vector<4, R> call(R (*function)(T x), const Vector<4, T> &v) {
    return Vector<4, R>(function(v.x), function(v.y), function(v.z),
                        function(v.w));
  }
};
} // namespace Neat