#pragma once

#include "Neat/Math/Matrix/Matrix2x2.h"
#include "Neat/Math/Matrix/Matrix2x3.h"
#include "Neat/Math/Matrix/Matrix2x4.h"
#include "Neat/Math/Matrix/Matrix3x2.h"
#include "Neat/Math/Matrix/Matrix3x3.h"
#include "Neat/Math/Matrix/Matrix3x4.h"
#include "Neat/Math/Matrix/Matrix4x2.h"
#include "Neat/Math/Matrix/Matrix4x3.h"
#include "Neat/Math/Matrix/Matrix4x4.h"


namespace Neat
{
   // Predefined Mat names
   using Mat2x3 = Mat<2, 3, Float>;
   using Mat2x4 = Mat<2, 4, Float>;
   using Mat3x2 = Mat<3, 2, Float>;
   using Mat3x4 = Mat<3, 4, Float>;
   using Mat4x2 = Mat<4, 2, Float>;
   using Mat4x3 = Mat<4, 3, Float>;
   using Mat2 = Mat<2, 2, Float>;
   using Mat3 = Mat<3, 3, Float>;
   using Mat4 = Mat<4, 4, Float>;

   using IMat2x3 = Mat<2, 3, Int>;
   using IMat2x4 = Mat<2, 4, Int>;
   using IMat3x2 = Mat<3, 2, Int>;
   using IMat3x4 = Mat<3, 4, Int>;
   using IMat4x2 = Mat<4, 2, Int>;
   using IMat4x3 = Mat<4, 3, Int>;
   using IMat2 = Mat<2, 2, Int>;
   using IMat3 = Mat<3, 3, Int>;
   using IMat4 = Mat<4, 4, Int>;

   using DMat2x3 = Mat<2, 3, Double>;
   using DMat2x4 = Mat<2, 4, Double>;
   using DMat3x2 = Mat<3, 2, Double>;
   using DMat3x4 = Mat<3, 4, Double>;
   using DMat4x2 = Mat<4, 2, Double>;
   using DMat4x3 = Mat<4, 3, Double>;
   using DMat2 = Mat<2, 2, Double>;
   using DMat3 = Mat<3, 3, Double>;
   using DMat4 = Mat<4, 4, Double>;

   using BMat2x3 = Mat<2, 3, Bool>;
   using BMat2x4 = Mat<2, 4, Bool>;
   using BMat3x2 = Mat<3, 2, Bool>;
   using BMat3x4 = Mat<3, 4, Bool>;
   using BMat4x2 = Mat<4, 2, Bool>;
   using BMat4x3 = Mat<4, 3, Bool>;
   using BMat2 = Mat<2, 2, Bool>;
   using BMat3 = Mat<3, 3, Bool>;
   using BMat4 = Mat<4, 4, Bool>;
}
