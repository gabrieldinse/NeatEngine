#pragma once

#include "Neat/Core/Types.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   constexpr const double   NT_PI        = 3.14159265358979323846;
   constexpr const double   NT_E         = 2.71828182845904523536;
   constexpr const double   NT_SQRT2     = 1.41421356237309504880;
   constexpr const double   NT_SQRT3     = 1.73205080756887729352;
   constexpr const double   NT_LOG2_E    = 1.44269504088896340736;
   constexpr const double   NT_LOG10_E   = 0.434294481903251827651;
   constexpr const double   NT_LOGE_2    = 0.693147180559945309417;
   constexpr const double   NT_LOGE_10   = 2.30258509299404568402;


   // Trigonometric
   float degreesToRadians(float angleDegrees);
   float radiansToDegrees(float angleRadians);
   double degreesToRadiansD(double angleDegrees);
   double radiansToDegreesD(double angleRadians);

   // Interpolation
   template<UInt N, typename T, typename U>
   Vector<N, T> linearInterpolation(const Vector<N, T>& a,
      const Vector<N, T>& b, U t);

   template<UInt N, typename T, typename U>
   Vector<N, T> quadraticBezier(const Vector<N, T>& a, const Vector<N, T>& b,
      const Vector<N, T>& c, U t);

   template<UInt N, typename T, typename U>
   Vector<N, T> cubicBezier(const Vector<N, T>& a, const Vector<N, T>& b,
      const Vector<N, T>& c, const Vector<N, T>& d, U t);
}

#include "Neat/Math/Utility.inl"