#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"


namespace Neat
{
   // Determinant
   template <typename T>
   T determinant(const Mat<2, 2, T>& m);

   template <typename T>
   T determinant(const Mat<3, 3, T>& m);

   template <typename T>
   T determinant(const Mat<4, 4, T>& m);

   // Transpose
   template <typename T>
   Mat <2, 2, T> transpose(const Mat<2, 2, T>& m);

   template <typename T>
   Mat<3, 2, T> transpose(const Mat<2, 3, T>& m);

   template <typename T>
   Mat<2, 3, T> transpose(const Mat<3, 2, T>& m);

   template <typename T>
   Mat<3, 3, T> transpose(const Mat<3, 3, T>& m);

   template <typename T>
   Mat<2, 4, T> transpose(const Mat<4, 2, T>& m);

   template <typename T>
   Mat<4, 2, T> transpose(const Mat<2, 4, T>& m);

   template <typename T>
   Mat<3, 4, T> transpose(const Mat<4, 3, T>& m);

   template <typename T>
   Mat<4, 3, T> transpose(const Mat<3, 4, T>& m);

   template <typename T>
   Mat<4, 4, T> transpose(const Mat<4, 4, T>& m);

   // Inverse
   template <typename T>
   Mat<2, 2, T> inverse(const Mat<2, 2, T>& m);

   template <typename T>
   Mat<3, 3, T> inverse(const Mat<3, 3, T>& m);

   template <typename T>
   Mat<4, 4, T> inverse(const Mat<4, 4, T>& m);
}

#include "MatrixOperations.inl"