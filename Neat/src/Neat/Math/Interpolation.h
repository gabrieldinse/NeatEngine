#pragma once

#include "Neat/Core/Types.h"
#include "Neat/Math/Types/TypeVectorN.h"


namespace Neat
{
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

}

#include "Neat/Math/Interpolation.inl"