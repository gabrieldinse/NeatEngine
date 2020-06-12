#pragma once

#include "Neat/Core/Types.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   constexpr const double   NT_PI            = 3.1415926535897932384626433832795;
   constexpr const double   NT_ONE_OVER_PI   = 0.31830988618379067153776752674503;
   constexpr const double   NT_PI_OVER_180   = 0.01745329251994329576923690768489;
   constexpr const double   NT_180_OVER_PI   = 57.295779513082320876798154814105;
   constexpr const double   NT_E             = 2.7182818284590452353602874713527;
   constexpr const double   NT_SQRT2         = 1.4142135623730950488016887242097;
   constexpr const double   NT_SQRT3         = 1.7320508075688772935274463415059;
   constexpr const double   NT_LOG2_E        = 1.4426950408889634073599246810019;
   constexpr const double   NT_LOG10_E       = 0.43429448190325182765112891891661;
   constexpr const double   NT_LOGE_2        = 0.69314718055994530941723212145818;
   constexpr const double   NT_LOGE_10       = 2.3025850929940456840179914546844;


   // Trigonometric
   template <typename T>
   inline constexpr
   T radians(T angleDegrees);

   template <typename T>
   inline constexpr
   T degrees(T angleRadians);


   // Interpolation
   template<UInt32 N, typename T, typename U>
   Vector<N, T> linearInterpolation(const Vector<N, T>& a,
      const Vector<N, T>& b, const U& t);

   template<UInt32 N, typename T, typename U>
   Vector<N, T> quadraticBezier(const Vector<N, T>& a, const Vector<N, T>& b,
      const Vector<N, T>& c, const U& t);

   template<UInt32 N, typename T, typename U>
   Vector<N, T> cubicBezier(const Vector<N, T>& a, const Vector<N, T>& b,
      const Vector<N, T>& c, const Vector<N, T>& d, const U& t);
}

#include "Neat/Math/Utility.inl"