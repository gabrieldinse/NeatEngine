#pragma once

#include "Neat/Math/Types/TypeMatrix2x2.h"
#include "Neat/Math/Types/TypeMatrix3x3.h"
#include "Neat/Math/Types/TypeMatrix4x4.h"
#include "Neat/Math/MatrixOperations.h"


namespace Neat
{
   // Predefined Matrix names
   using Matrix2     = Matrix<2, 2, float>;
   using Matrix3     = Matrix<3, 3, float>;
   using Matrix4     = Matrix<4, 4, float>;

   using IMatrix2    = Matrix<2, 2, Int32>;
   using IMatrix3    = Matrix<3, 3, Int32>;
   using IMatrix4    = Matrix<4, 4, Int32>;

   using UIMatrix2   = Matrix<2, 2, UInt32>;
   using UIMatrix3   = Matrix<3, 3, UInt32>;
   using UIMatrix4   = Matrix<4, 4, UInt32>;
                    
   using DMatrix2    = Matrix<2, 2, double>;
   using DMatrix3    = Matrix<3, 3, double>;
   using DMatrix4    = Matrix<4, 4, double>;

   using BMatrix2    = Matrix<2, 2, bool>;
   using BMatrix3    = Matrix<3, 3, bool>;
   using BMatrix4    = Matrix<4, 4, bool>;
}
