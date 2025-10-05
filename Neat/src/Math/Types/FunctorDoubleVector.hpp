#pragma once

#include "Core/Types.hpp"

namespace Neat {
template <template <UInt32 N, typename T> class Vector, UInt32 N, typename R,
          typename T>
struct FunctorDoubleVector {};

// Vector1 specialization
template <template <UInt32 N, typename T> class Vector, typename R, typename T>
struct FunctorDoubleVector<Vector, 1, R, T> {
  static Vector<1, R> call(R (*function)(T x, T y), const Vector<1, T> &va,
                           const Vector<1, T> &vb) {
    return Vector<1, R>(function(va.x(), vb.x()));
  }
};

// Vector2 specialization
template <template <UInt32 N, typename T> class Vector, typename R, typename T>
struct FunctorDoubleVector<Vector, 2, R, T> {
  static Vector<2, R> call(R (*function)(T x, T y), const Vector<2, T> &va,
                           const Vector<2, T> &vb) {
    return Vector<2, R>(function(va.x(), vb.x()), function(va.y(), vb.y()));
  }
};

// Vector3 specialization
template <template <UInt32 N, typename T> class Vector, typename R, typename T>
struct FunctorDoubleVector<Vector, 3, R, T> {
  static Vector<3, R> call(R (*function)(T x, T y), const Vector<3, T> &va,
                           const Vector<3, T> &vb) {
    return Vector<3, R>(function(va.x(), vb.x()), function(va.y(), vb.y()),
                        function(va.z(), vb.z()));
  }
};

// Vector4 specialization
template <template <UInt32 N, typename T> class Vector, typename R, typename T>
struct FunctorDoubleVector<Vector, 4, R, T> {
  static Vector<4, R> call(R (*function)(T x, T y), const Vector<4, T> &va,
                           const Vector<4, T> &vb) {
    return Vector<4, R>(function(va.x(), vb.x()), function(va.y(), vb.y()),
                        function(va.z(), vb.z()), function(va.w(), vb.w()));
  }
};
}  // namespace Neat