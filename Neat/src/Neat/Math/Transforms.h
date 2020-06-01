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
   Matrix<4, 4, T> rotate(T angleRadians, const Vector<3, T>& v);

   template <typename T>
   Matrix<4, 4, T> rotate(const Matrix<4, 4, T>& m, T angleRadians, const Vector<3, T>& v);

   template <typename T>
   Matrix<4, 4, T> scale(const Vector<3, T>& v);

   template <typename T>
   Matrix<4, 4, T> scale(const Matrix<4, 4, T>& m, const Vector<3, T>& v);

   template <typename T>
   Matrix<4, 4, T> orthographicProjection(T left, T right, T bottom, T top,
      T zNear, T zFar);
}

#include "Neat/Math/Transforms.inl"