#pragma once

#include "Neat/Core/Types.h"


namespace Neat
{
   template <typename T = double>
   constexpr
   T pi = static_cast<T>(3.1415926535897932384626433832795);

   template <typename T = double>
   inline constexpr
   T twoPi = static_cast<T>(6.283185307179586476925286766559);

   template <typename T = double>
   inline constexpr
   T threePi = static_cast<T>(9.4247779607693797153879301498385);

   template <typename T = double>
   inline constexpr
   T piOverTwo = static_cast<T>(1.5707963267948966192313216916398);

   template <typename T = double>
   inline constexpr
   T piOverThree = static_cast<T>(1.0471975511965977461542144610932);

   template <typename T = double>
   inline constexpr
   T twoPiOverThree = static_cast<T>(2.0943951023931954923084289221863);

   template <typename T = double>
   inline constexpr
   T threePiOverTwo = static_cast<T>(4.7123889803846898576939650749193);

   template <typename T = double>
   inline constexpr
   T degreeInRadians = static_cast<T>(0.01745329251994329576923690768489);

   template <typename T = double>
   inline constexpr
   T radianInDegrees = static_cast<T>(57.295779513082320876798154814105);

   template <typename T = double>
   inline constexpr
   T oneOverPi = static_cast<T>(0.31830988618379067153776752674503);

   template <typename T = double>
   inline constexpr
   T oneOverTwoPi = static_cast<T>(0.15915494309189533576888376337251);

   template <typename T = double>
   inline constexpr
   T oneOverThreePi = static_cast<T>(0.10610329539459689051258917558168);

   template <typename T = double>
   inline constexpr
   T twoOverPi = static_cast<T>(0.63661977236758134307553505349006);

   template <typename T = double>
   inline constexpr
   T twoOverThreePi = static_cast<T>(0.21220659078919378102517835116335);

   template <typename T = double>
   inline constexpr
   T threeOverPi = static_cast<T>(0.95492965855137201461330258023509);

   template <typename T = double>
   inline constexpr
   T threeOverTwoPi = static_cast<T>(0.47746482927568600730665129011754);

   template <typename T = double>
   inline constexpr
   T e = static_cast<T>(2.7182818284590452353602874713527);

   template <typename T = double>
   inline constexpr
   T sqrtTwo = static_cast<T>(1.4142135623730950488016887242097);

   template <typename T = double>
   inline constexpr
   T oneOverSqrtTwo = static_cast<T>(0.70710678118654752440084436210485);

   template <typename T = double>
   inline constexpr
   T sqrtThree = static_cast<T>(1.7320508075688772935274463415059);

   template <typename T = double>
   inline constexpr
   T oneOverSqrtThree = static_cast<T>(0.57735026918962576450914878050196);

   template <typename T = double>
   inline constexpr
   T logTwoE = static_cast<T>(1.4426950408889634073599246810019);

   template <typename T = double>
   inline constexpr
   T logTenE = static_cast<T>(0.43429448190325182765112891891661);

   template <typename T = double>
   inline constexpr
   T logETwo = static_cast<T>(0.69314718055994530941723212145818);

   template <typename T = double>
   inline constexpr
   T logETen = static_cast<T>(2.3025850929940456840179914546844);
}