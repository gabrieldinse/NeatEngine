#pragma once

#include "Neat/Core/Types.h"
#include "Neat/Math/Vector/Vector1.h"
#include "Neat/Math/Vector/Vector2.h"
#include "Neat/Math/Vector/Vector3.h"
#include "Neat/Math/Vector/Vector4.h"


namespace Neat
{
   // Predefined Vec names
   using Vec1 = Vec<1, float>;
   using Vec2 = Vec<2, float>;
   using Vec3 = Vec<3, float>;
   using Vec4 = Vec<4, float>;

   using IVec1 = Vec<1, Int>;
   using IVec2 = Vec<2, Int>;
   using IVec3 = Vec<3, Int>;
   using IVec4 = Vec<4, Int>;

   using BVec1 = Vec<1, bool>;
   using BVec2 = Vec<2, bool>;
   using BVec3 = Vec<3, bool>;
   using BVec4 = Vec<4, bool>;

   using DVec1 = Vec<1, double>;
   using DVec2 = Vec<2, double>;
   using DVec3 = Vec<3, double>;
   using DVec4 = Vec<4, double>;
}

