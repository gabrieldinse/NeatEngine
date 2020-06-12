#pragma once

#include "Neat/Math/Matrix.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   template <typename T>
   Matrix<4, 4, T> translate(const Vector<3, T>& v);

   template <typename T>
   Matrix<4, 4, T> translate(const Matrix<4, 4, T>& m, const Vector<3, T>& v);

   template <typename T>
   Matrix<4, 4, T> rotate(const T& angleRadians, const Vector<3, T>& v);

   template <typename T>
   Matrix<4, 4, T> rotate(const Matrix<4, 4, T>& m, const T& angleRadians,
      const Vector<3, T>& v);

   template <typename T>
   Matrix<4, 4, T> scale(const Vector<3, T>& v);

   template <typename T>
   Matrix<4, 4, T> scale(const Matrix<4, 4, T>& m, const Vector<3, T>& v);
}

#include "Neat/Math/Transform.inl"