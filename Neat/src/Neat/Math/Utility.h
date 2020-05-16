#pragma once

#include "Neat/Core/Types.h"


namespace Neat
{
   constexpr const float   NT_PI        = 3.14159265358979323846f;
   constexpr const float   NT_E         = 2.71828182845904523536f;
   constexpr const float   NT_SQRT2     = 1.41421356237309504880f;
   constexpr const float   NT_SQRT3     = 1.73205080756887729352f;
   constexpr const float   NT_LOG2_E    = 1.44269504088896340736f;
   constexpr const float   NT_LOG10_E   = 0.434294481903251827651f;
   constexpr const float   NT_LOGE_2    = 0.693147180559945309417f;
   constexpr const float   NT_LOGE_10   = 2.30258509299404568402f;


   float degreesToRadians(float angleDegrees);
   float radiansToDegrees(float angleRadians);
}