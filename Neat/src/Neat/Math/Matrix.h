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
   using Mat2x3 = Mat<2, 3, float>;
   using Mat2x4 = Mat<2, 4, float>;
   using Mat3x2 = Mat<3, 2, float>;
   using Mat3x4 = Mat<3, 4, float>;
   using Mat4x2 = Mat<4, 2, float>;
   using Mat4x3 = Mat<4, 3, float>;
   using Mat2 = Mat<2, 2, float>;
   using Mat3 = Mat<3, 3, float>;
   using Mat4 = Mat<4, 4, float>;

   using IMat2x3 = Mat<2, 3, Int>;
   using IMat2x4 = Mat<2, 4, Int>;
   using IMat3x2 = Mat<3, 2, Int>;
   using IMat3x4 = Mat<3, 4, Int>;
   using IMat4x2 = Mat<4, 2, Int>;
   using IMat4x3 = Mat<4, 3, Int>;
   using IMat2 = Mat<2, 2, Int>;
   using IMat3 = Mat<3, 3, Int>;
   using IMat4 = Mat<4, 4, Int>;

   using DMat2x3 = Mat<2, 3, double>;
   using DMat2x4 = Mat<2, 4, double>;
   using DMat3x2 = Mat<3, 2, double>;
   using DMat3x4 = Mat<3, 4, double>;
   using DMat4x2 = Mat<4, 2, double>;
   using DMat4x3 = Mat<4, 3, double>;
   using DMat2 = Mat<2, 2, double>;
   using DMat3 = Mat<3, 3, double>;
   using DMat4 = Mat<4, 4, double>;

   using BMat2x3 = Mat<2, 3, bool>;
   using BMat2x4 = Mat<2, 4, bool>;
   using BMat3x2 = Mat<3, 2, bool>;
   using BMat3x4 = Mat<3, 4, bool>;
   using BMat4x2 = Mat<4, 2, bool>;
   using BMat4x3 = Mat<4, 3, bool>;
   using BMat2 = Mat<2, 2, bool>;
   using BMat3 = Mat<3, 3, bool>;
   using BMat4 = Mat<4, 4, bool>;
}
