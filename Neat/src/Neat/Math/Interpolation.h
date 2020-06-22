#pragma once

#include "Neat/Core/Types.h"
#include "Neat/Math/Types/TypeVectorN.h"


namespace Neat
{
   // Scalar
   template <typename T, typename U>
   inline constexpr T mix(const T& a, const T& b, const U& t);


   // Vector
   template <UInt32 N, typename T, typename U>
   inline constexpr Vector<N, T> mix(const Vector<N, T>& a,
      const Vector<N, T>& b, const U& t);

   template <UInt32 N, typename T, typename U>
   inline constexpr Vector<N, T> quadraticBezier(const Vector<N, T>& a,
      const Vector<N, T>& b, const Vector<N, T>& c, const U& t);

   template <UInt32 N, typename T, typename U>
   inline constexpr Vector<N, T> cubicBezier(const Vector<N, T>& a,
      const Vector<N, T>& b, const Vector<N, T>& c, const Vector<N, T>& d,
      const U& t);


   // Quaternion
   template <typename T, typename U>
   inline constexpr Quat<T> mix(const Quat<T>& a,
      const Quat<T>& b, const U& t);

   template <typename T, typename U>
   inline constexpr Quat<T> lerp(const Quat<T>& a,
      const Quat<T>& b, const U& t);

   template <typename T, typename U>
   inline constexpr Quat<T> slerp(const Quat<T>& a,
      const Quat<T>& b, const U& t);
}

#include "Neat/Math/Interpolation.inl"