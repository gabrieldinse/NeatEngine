#pragma once

#include "Neat/Core/Types.h"


namespace Neat
{
   constexpr const Float   pi        = 3.14159265358979323846f;
   constexpr const Float   e         = 2.71828182845904523536f;
   constexpr const Float   sqrt2     = 1.41421356237309504880f;
   constexpr const Float   sqrt3     = 1.73205080756887729352f;
   constexpr const Float   log2_e    = 1.44269504088896340736f;
   constexpr const Float   log10_e   = 0.434294481903251827651f;
   constexpr const Float   loge_2    = 0.693147180559945309417f;
   constexpr const Float   loge_10   = 2.30258509299404568402f;


   Float degreesToRadians(Float angleDegrees);
   Float radiansToDegrees(Float angleRadians);
}