#pragma once

#include "Neat/Core/Types.hpp"

namespace Neat {
template <template <UInt32 N, typename T> class Vector, UInt32 N, typename R,
          typename T>
struct FunctorTripleVector {};

// Vector1 specialization
template <template <UInt32 N, typename T> class Vector, typename R, typename T>
struct FunctorTripleVector<Vector, 1, R, T> {
  static Vector<1, R> call(R (*function)(T x, T y, T z), const Vector<1, T> &va,
                           const Vector<1, T> &vb, const Vector<1, T> &vc) {
    return Vector<1, R>(function(va.x(), vb.x(), vc.x()));
  }
};

// Vector2 specialization
template <template <UInt32 N, typename T> class Vector, typename R, typename T>
struct FunctorTripleVector<Vector, 2, R, T> {
  static Vector<2, R> call(R (*function)(T x, T y, T z), const Vector<2, T> &va,
                           const Vector<2, T> &vb, const Vector<2, T> &vc) {
    return Vector<2, R>(function(va.x(), vb.x(), vc.x()),
                        function(va.y(), vb.y(), vc.y()));
  }
};

// Vector3 specialization
template <template <UInt32 N, typename T> class Vector, typename R, typename T>
struct FunctorTripleVector<Vector, 3, R, T> {
  static Vector<3, R> call(R (*function)(T x, T y, T z), const Vector<3, T> &va,
                           const Vector<3, T> &vb, const Vector<3, T> &vc) {
    return Vector<3, R>(function(va.x(), vb.x(), vc.x()),
                        function(va.y(), vb.y(), vc.y()),
                        function(va.z(), vb.z(), vc.z()));
  }
};

// Vector4 specialization
template <template <UInt32 N, typename T> class Vector, typename R, typename T>
struct FunctorTripleVector<Vector, 4, R, T> {
  static Vector<4, R> call(R (*function)(T x, T y, T z), const Vector<4, T> &va,
                           const Vector<4, T> &vb, const Vector<4, T> &vc) {
    return Vector<4, R>(
        function(va.x(), vb.x(), vc.x()), function(va.y(), vb.y(), vc.y()),
        function(va.z(), vb.z(), vc.z()), function(va.w(), vb.w(), vc.w()));
  }
};
}  // namespace Neat