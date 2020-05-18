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
   // Predefined Matrix names
   using Matrix2x3    = Matrix<2, 3, float>;
   using Matrix2x4    = Matrix<2, 4, float>;
   using Matrix3x2    = Matrix<3, 2, float>;
   using Matrix3x4    = Matrix<3, 4, float>;
   using Matrix4x2    = Matrix<4, 2, float>;
   using Matrix4x3    = Matrix<4, 3, float>;
   using Matrix2      = Matrix<2, 2, float>;
   using Matrix3      = Matrix<3, 3, float>;
   using Matrix4      = Matrix<4, 4, float>;
                    
   using IMatrix2x3   = Matrix<2, 3, Int>;
   using IMatrix2x4   = Matrix<2, 4, Int>;
   using IMatrix3x2   = Matrix<3, 2, Int>;
   using IMatrix3x4   = Matrix<3, 4, Int>;
   using IMatrix4x2   = Matrix<4, 2, Int>;
   using IMatrix4x3   = Matrix<4, 3, Int>;
   using IMatrix2     = Matrix<2, 2, Int>;
   using IMatrix3     = Matrix<3, 3, Int>;
   using IMatrix4     = Matrix<4, 4, Int>;

   using UIMatrix2x3   = Matrix<2, 3, UInt>;
   using UIMatrix2x4   = Matrix<2, 4, UInt>;
   using UIMatrix3x2   = Matrix<3, 2, UInt>;
   using UIMatrix3x4   = Matrix<3, 4, UInt>;
   using UIMatrix4x2   = Matrix<4, 2, UInt>;
   using UIMatrix4x3   = Matrix<4, 3, UInt>;
   using UIMatrix2     = Matrix<2, 2, UInt>;
   using UIMatrix3     = Matrix<3, 3, UInt>;
   using UIMatrix4     = Matrix<4, 4, UInt>;
                    
   using DMatrix2x3   = Matrix<2, 3, double>;
   using DMatrix2x4   = Matrix<2, 4, double>;
   using DMatrix3x2   = Matrix<3, 2, double>;
   using DMatrix3x4   = Matrix<3, 4, double>;
   using DMatrix4x2   = Matrix<4, 2, double>;
   using DMatrix4x3   = Matrix<4, 3, double>;
   using DMatrix2     = Matrix<2, 2, double>;
   using DMatrix3     = Matrix<3, 3, double>;
   using DMatrix4     = Matrix<4, 4, double>;
                     
   using BMatrix2x3   = Matrix<2, 3, bool>;
   using BMatrix2x4   = Matrix<2, 4, bool>;
   using BMatrix3x2   = Matrix<3, 2, bool>;
   using BMatrix3x4   = Matrix<3, 4, bool>;
   using BMatrix4x2   = Matrix<4, 2, bool>;
   using BMatrix4x3   = Matrix<4, 3, bool>;
   using BMatrix2     = Matrix<2, 2, bool>;
   using BMatrix3     = Matrix<3, 3, bool>;
   using BMatrix4     = Matrix<4, 4, bool>;
}
