#pragma once

#include <limits>

#include "Core/Types.hpp"

namespace Neat {
template <typename T = float>
inline constexpr T Zero = static_cast<T>(0);

template <typename T = float>
inline constexpr T OneSixth =
    static_cast<T>(0.16666666666666666666666666666667);

template <typename T = float>
inline constexpr T OneEighth = static_cast<T>(0.125);

template <typename T = float>
inline constexpr T OneTenth = static_cast<T>(0.1);

template <typename T = float>
inline constexpr T OneFifth = static_cast<T>(0.2);

template <typename T = float>
inline constexpr T OneForth = static_cast<T>(0.25);

template <typename T = float>
inline constexpr T OneThird =
    static_cast<T>(0.33333333333333333333333333333333);

template <typename T = float>
inline constexpr T OneHalf = static_cast<T>(0.5);

template <typename T = float>
inline constexpr T TwoThirds =
    static_cast<T>(0.66666666666666666666666666666667);

template <typename T = float>
inline constexpr T One = static_cast<T>(1);

template <typename T = float>
inline constexpr T OneAndOneHalf = static_cast<T>(1.5);

template <typename T = float>
inline constexpr T Two = static_cast<T>(2);

template <typename T = float>
inline constexpr T TwoAndOneHalf = static_cast<T>(2.5);

template <typename T = float>
inline constexpr T Three = static_cast<T>(3);

template <typename T = float>
inline constexpr T E = static_cast<T>(2.7182818284590452353602874713527);

template <typename T = float>
inline constexpr T Euler = E<T>;

template <typename T = float>
inline constexpr T Pi = static_cast<T>(3.1415926535897932384626433832795);

template <typename T = float>
inline constexpr T GoldenRatio =
    static_cast<T>(1.61803398874989484820458683436563811);

template <typename T = float>
inline constexpr T TwoPi = static_cast<T>(6.283185307179586476925286766559);

template <typename T = float>
inline constexpr T ThreePi = static_cast<T>(9.4247779607693797153879301498385);

template <typename T = float>
inline constexpr T HalfPi = static_cast<T>(1.5707963267948966192313216916398);

template <typename T = float>
inline constexpr T ThirdPi = static_cast<T>(1.0471975511965977461542144610932);

template <typename T = float>
inline constexpr T TwoThirdsPi =
    static_cast<T>(2.0943951023931954923084289221863);

template <typename T = float>
inline constexpr T ThreeHalfPi =
    static_cast<T>(4.7123889803846898576939650749193);

template <typename T = float>
inline constexpr T QuarterPi =
    static_cast<T>(0.78539816339744830961566084581988);

template <typename T = float>
inline constexpr T FifthPi = static_cast<T>(0.6283185307179586476925286766559);

template <typename T = float>
inline constexpr T SixthPi = static_cast<T>(0.52359877559829887307710723054658);

template <typename T = float>
inline constexpr T OneOverPi =
    static_cast<T>(0.31830988618379067153776752674503);

template <typename T = float>
inline constexpr T OneOverTwoPi =
    static_cast<T>(0.15915494309189533576888376337251);

template <typename T = float>
inline constexpr T OneOverThreePi =
    static_cast<T>(0.10610329539459689051258917558168);

template <typename T = float>
inline constexpr T TwoOverPi =
    static_cast<T>(0.63661977236758134307553505349006);

template <typename T = float>
inline constexpr T TwoOverThreePi =
    static_cast<T>(0.21220659078919378102517835116335);

template <typename T = float>
inline constexpr T ThreeOverPi =
    static_cast<T>(0.95492965855137201461330258023509);

template <typename T = float>
inline constexpr T ThreeOverTwoPi =
    static_cast<T>(0.47746482927568600730665129011754);

template <typename T = float>
inline constexpr T DegreeInRadians =
    static_cast<T>(0.01745329251994329576923690768489);

template <typename T = float>
inline constexpr T RadianInDegrees =
    static_cast<T>(57.295779513082320876798154814105);

template <typename T = float>
inline constexpr T SinSixthPi = static_cast<T>(0.5);

template <typename T = float>
inline constexpr T SinQuarterPi =
    static_cast<T>(0.70710678118654752440084436210485);

template <typename T = float>
inline constexpr T SinThirdPi =
    static_cast<T>(0.86602540378443864676372317075294);

template <typename T = float>
inline constexpr T SinOneHalf =
    static_cast<T>(0.47942553860420300027328793521557);

template <typename T = float>
inline constexpr T SinOne = static_cast<T>(0.8414709848078965066525023216303);

template <typename T = float>
inline constexpr T CosSixthPi =
    static_cast<T>(0.86602540378443864676372317075294);

template <typename T = float>
inline constexpr T CosQuarterPi =
    static_cast<T>(0.70710678118654752440084436210485);

template <typename T = float>
inline constexpr T CosThirdPi = static_cast<T>(0.5);

template <typename T = float>
inline constexpr T CosOneHalf =
    static_cast<T>(0.87758256189037271611628158260383);

template <typename T = float>
inline constexpr T CosOne = static_cast<T>(0.54030230586813971740093660744298);

template <typename T = float>
inline constexpr T SqrtTwo = static_cast<T>(1.4142135623730950488016887242097);

template <typename T = float>
inline constexpr T OneOverSqrtTwo =
    static_cast<T>(0.70710678118654752440084436210485);

template <typename T = float>
inline constexpr T SqrtThree =
    static_cast<T>(1.7320508075688772935274463415059);

template <typename T = float>
inline constexpr T OneOverSqrtThree =
    static_cast<T>(0.57735026918962576450914878050196);

template <typename T = float>
inline constexpr T SqrtFive = static_cast<T>(2.2360679774997896964091736687313);

template <typename T = float>
inline constexpr T OneOverSqrtFive =
    static_cast<T>(0.44721359549995793928183473374626);

template <typename T = float>
inline constexpr T LogTwoE = static_cast<T>(1.4426950408889634073599246810019);

template <typename T = float>
inline constexpr T LogTenE = static_cast<T>(0.43429448190325182765112891891661);

template <typename T = float>
inline constexpr T LogETwo = static_cast<T>(0.69314718055994530941723212145818);

template <typename T = float>
inline constexpr T LogETen = static_cast<T>(2.3025850929940456840179914546844);
}  // namespace Neat