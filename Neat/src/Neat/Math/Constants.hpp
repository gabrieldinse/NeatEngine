#pragma once

#include <limits>

#include "Neat/Core/Types.hpp"

namespace Neat {
template <typename T>
inline constexpr T zero = static_cast<T>(0);

template <typename T>
inline constexpr T oneSixth =
    static_cast<T>(0.16666666666666666666666666666667);

template <typename T>
inline constexpr T oneTenth = static_cast<T>(0.1);

template <typename T>
inline constexpr T oneFifth = static_cast<T>(0.2);

template <typename T>
inline constexpr T oneForth = static_cast<T>(0.25);

template <typename T>
inline constexpr T oneThird =
    static_cast<T>(0.33333333333333333333333333333333);

template <typename T>
inline constexpr T oneHalf = static_cast<T>(0.5);

template <typename T>
inline constexpr T twoThirds =
    static_cast<T>(0.66666666666666666666666666666667);

template <typename T>
inline constexpr T one = static_cast<T>(1);

template <typename T>
inline constexpr T oneAndOneHalf = static_cast<T>(1.5);

template <typename T>
inline constexpr T two = static_cast<T>(2);

template <typename T>
inline constexpr T twoAndOneHalf = static_cast<T>(2.5);

template <typename T>
inline constexpr T e = static_cast<T>(2.7182818284590452353602874713527);

template <typename T>
inline constexpr T pi = static_cast<T>(3.1415926535897932384626433832795);

template <typename T>
inline constexpr T goldenRatio =
    static_cast<T>(1.61803398874989484820458683436563811);

template <typename T>
inline constexpr T twoPi = static_cast<T>(6.283185307179586476925286766559);

template <typename T>
inline constexpr T threePi = static_cast<T>(9.4247779607693797153879301498385);

template <typename T>
inline constexpr T halfPi = static_cast<T>(1.5707963267948966192313216916398);

template <typename T>
inline constexpr T thirdPi = static_cast<T>(1.0471975511965977461542144610932);

template <typename T>
inline constexpr T twoThirdsPi =
    static_cast<T>(2.0943951023931954923084289221863);

template <typename T>
inline constexpr T threeHalfPi =
    static_cast<T>(4.7123889803846898576939650749193);

template <typename T>
inline constexpr T quarterPi =
    static_cast<T>(0.78539816339744830961566084581988);

template <typename T>
inline constexpr T fitfhPi = static_cast<T>(0.6283185307179586476925286766559);

template <typename T>
inline constexpr T sixthPi = static_cast<T>(0.52359877559829887307710723054658);

template <typename T>
inline constexpr T oneOverPi =
    static_cast<T>(0.31830988618379067153776752674503);

template <typename T>
inline constexpr T oneOverTwoPi =
    static_cast<T>(0.15915494309189533576888376337251);

template <typename T>
inline constexpr T oneOverThreePi =
    static_cast<T>(0.10610329539459689051258917558168);

template <typename T>
inline constexpr T twoOverPi =
    static_cast<T>(0.63661977236758134307553505349006);

template <typename T>
inline constexpr T twoOverThreePi =
    static_cast<T>(0.21220659078919378102517835116335);

template <typename T>
inline constexpr T threeOverPi =
    static_cast<T>(0.95492965855137201461330258023509);

template <typename T>
inline constexpr T threeOverTwoPi =
    static_cast<T>(0.47746482927568600730665129011754);

template <typename T>
inline constexpr T degreeInRadians =
    static_cast<T>(0.01745329251994329576923690768489);

template <typename T>
inline constexpr T radianInDegrees =
    static_cast<T>(57.295779513082320876798154814105);

template <typename T>
inline constexpr T sinSixthPi = static_cast<T>(0.5);

template <typename T>
inline constexpr T sinQuarterPi =
    static_cast<T>(0.70710678118654752440084436210485);

template <typename T>
inline constexpr T sinThirdPi =
    static_cast<T>(0.86602540378443864676372317075294);

template <typename T>
inline constexpr T sinOneHalf =
    static_cast<T>(0.47942553860420300027328793521557);

template <typename T>
inline constexpr T sinOne = static_cast<T>(0.8414709848078965066525023216303);

template <typename T>
inline constexpr T cosSixthPi =
    static_cast<T>(0.86602540378443864676372317075294);

template <typename T>
inline constexpr T cosQuarterPi =
    static_cast<T>(0.70710678118654752440084436210485);

template <typename T>
inline constexpr T cosThirdPi = static_cast<T>(0.5);

template <typename T>
inline constexpr T cosOneHalf =
    static_cast<T>(0.87758256189037271611628158260383);

template <typename T>
inline constexpr T cosOne = static_cast<T>(0.54030230586813971740093660744298);

template <typename T>
inline constexpr T sqrtTwo = static_cast<T>(1.4142135623730950488016887242097);

template <typename T>
inline constexpr T oneOverSqrtTwo =
    static_cast<T>(0.70710678118654752440084436210485);

template <typename T>
inline constexpr T sqrtThree =
    static_cast<T>(1.7320508075688772935274463415059);

template <typename T>
inline constexpr T oneOverSqrtThree =
    static_cast<T>(0.57735026918962576450914878050196);

template <typename T>
inline constexpr T sqrtFive = static_cast<T>(2.2360679774997896964091736687313);

template <typename T>
inline constexpr T oneOverSqrtFive =
    static_cast<T>(0.44721359549995793928183473374626);

template <typename T>
inline constexpr T logTwoE = static_cast<T>(1.4426950408889634073599246810019);

template <typename T>
inline constexpr T logTenE = static_cast<T>(0.43429448190325182765112891891661);

template <typename T>
inline constexpr T logETwo = static_cast<T>(0.69314718055994530941723212145818);

template <typename T>
inline constexpr T logETen = static_cast<T>(2.3025850929940456840179914546844);
}  // namespace Neat