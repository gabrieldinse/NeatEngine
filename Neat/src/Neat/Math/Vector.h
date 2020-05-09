#pragma once

#include "Neat/Core/Types.h"
#include "Neat/Math/Vector/Vector1.h"
#include "Neat/Math/Vector/Vector2.h"
#include "Neat/Math/Vector/Vector3.h"
#include "Neat/Math/Vector/Vector4.h"


namespace Neat
{
   // Predefined Vec names
   using Vec1 = Vec<1, Float>;
   using Vec2 = Vec<2, Float>;
   using Vec3 = Vec<3, Float>;
   using Vec4 = Vec<4, Float>;

   using IVec1 = Vec<1, Int>;
   using IVec2 = Vec<2, Int>;
   using IVec3 = Vec<3, Int>;
   using IVec4 = Vec<4, Int>;

   using BVec1 = Vec<1, Bool>;
   using BVec2 = Vec<2, Bool>;
   using BVec3 = Vec<3, Bool>;
   using BVec4 = Vec<4, Bool>;

   using DVec1 = Vec<1, Double>;
   using DVec2 = Vec<2, Double>;
   using DVec3 = Vec<3, Double>;
   using DVec4 = Vec<4, Double>;
}

