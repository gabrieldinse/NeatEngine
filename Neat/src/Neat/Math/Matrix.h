#pragma once

#include "Neat/Math/Matrix/Matrix2x2.h"
#include "Neat/Math/Matrix/Matrix3x3.h"
#include "Neat/Math/Matrix/Matrix4x4.h"


namespace Neat
{
   // Predefined Matrix names
   using Matrix2      = Matrix<2, 2, float>;
   using Matrix3      = Matrix<3, 3, float>;
   using Matrix4      = Matrix<4, 4, float>;

   using IMatrix2     = Matrix<2, 2, Int>;
   using IMatrix3     = Matrix<3, 3, Int>;
   using IMatrix4     = Matrix<4, 4, Int>;

   using UIMatrix2     = Matrix<2, 2, UInt>;
   using UIMatrix3     = Matrix<3, 3, UInt>;
   using UIMatrix4     = Matrix<4, 4, UInt>;
                    
   using DMatrix2     = Matrix<2, 2, double>;
   using DMatrix3     = Matrix<3, 3, double>;
   using DMatrix4     = Matrix<4, 4, double>;
                     
   using BMatrix2     = Matrix<2, 2, bool>;
   using BMatrix3     = Matrix<3, 3, bool>;
   using BMatrix4     = Matrix<4, 4, bool>;
}
