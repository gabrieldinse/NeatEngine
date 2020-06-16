#pragma once


namespace Neat
{
   template <typename T>
   inline constexpr
   T radians(T angleDegrees);

   template <typename T>
   inline constexpr
   T degrees(T angleRadians);

   template <typename T>
   T wrapPi(T angleRadians);

   template <typename T>
   T wrap2Pi(T angleRadians);
}

#include "Neat/Math/Utility.inl"