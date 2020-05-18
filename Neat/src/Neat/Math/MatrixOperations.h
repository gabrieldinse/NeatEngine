#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"


namespace Neat
{
   // Determinant
   template <typename T>
   T determinant(const Matrix<2, 2, T>& m);

   template <typename T>
   T determinant(const Matrix<3, 3, T>& m);

   template <typename T>
   T determinant(const Matrix<4, 4, T>& m);

   // Transpose
   template <typename T>
   Matrix <2, 2, T> transpose(const Matrix<2, 2, T>& m);

   template <typename T>
   Matrix<3, 2, T> transpose(const Matrix<2, 3, T>& m);

   template <typename T>
   Matrix<2, 3, T> transpose(const Matrix<3, 2, T>& m);

   template <typename T>
   Matrix<3, 3, T> transpose(const Matrix<3, 3, T>& m);

   template <typename T>
   Matrix<2, 4, T> transpose(const Matrix<4, 2, T>& m);

   template <typename T>
   Matrix<4, 2, T> transpose(const Matrix<2, 4, T>& m);

   template <typename T>
   Matrix<3, 4, T> transpose(const Matrix<4, 3, T>& m);

   template <typename T>
   Matrix<4, 3, T> transpose(const Matrix<3, 4, T>& m);

   template <typename T>
   Matrix<4, 4, T> transpose(const Matrix<4, 4, T>& m);

   // Inverse
   template <typename T>
   Matrix<2, 2, T> inverse(const Matrix<2, 2, T>& m);

   template <typename T>
   Matrix<3, 3, T> inverse(const Matrix<3, 3, T>& m);

   template <typename T>
   Matrix<4, 4, T> inverse(const Matrix<4, 4, T>& m);
}

#include "MatrixOperations.inl"