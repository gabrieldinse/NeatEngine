#include "Neat/Math/Constants.h"


namespace Neat
{
   template <typename T>
   inline constexpr
   T radians(T angleDegrees)
   {
      return angleDegrees * degreeInRadians<T>;
   }

   template <typename T>
   inline constexpr
   T degrees(T angleRadians)
   {
      return angleRadians * radianInDegrees<T>;
   }

   template <typename T>
   T wrapPi(T angleRadians)
   {
      if (std::fabs(angleRadians) > pi<T>)
      {
         T revolutions = std::floor(
            oneOverTwoPi<T> * (angleRadians + pi<T>));
         angleRadians -= revolutions * twoPi<T>;
      }

      return angleRadians;
   }

   template <typename T>
   T wrap2Pi(T angleRadians)
   {
      if (std::fabs(angleRadians) > twoPi<T>)
      {
         T revolutions = std::floor(oneOverTwoPi<T> * angleRadians);
         angleRadians -= revolutions * twoPi<T>;
      }

      return angleRadians;
   }
}
