#pragma once

#include "Neat/Math/Types/TypeMatrixMxN.h"
#include "Neat/Math/Types/TypeVectorN.h"


namespace Neat
{
   // Vector
   template <typename T>
   Matrix<4, 4, T> translate(const Vector<3, T>& v);

   template <typename T>
   Matrix<4, 4, T> translate(const Matrix<4, 4, T>& m, const Vector<3, T>& v);

   template <typename T>
   Matrix<4, 4, T> rotate(const T& angleRadians,
      const Vector<3, T>& rotationAxis);

   template <typename T>
   Matrix<4, 4, T> rotate(const Matrix<4, 4, T>& m, const T& angleRadians,
      const Vector<3, T>& rotationAxis);

   template <typename T>
   Matrix<4, 4, T> scale(const Vector<3, T>& v);

   template <typename T>
   Matrix<4, 4, T> scale(const Matrix<4, 4, T>& m, const Vector<3, T>& v);


   // Quaternion
   template <typename T>
   Quat<T> rotate(const T& angleRadians, Vector<3, T>& rotationAxis);

   template <typename T>
   Quat<T> rotate(const Quat<T>& q, const T& angleRadians,
      Vector<3, T>& rotationAxis);
}

#include "Neat/Math/Transform.inl"