#pragma once

#include "Neat/Math/Matrix.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   template <typename T>
   Mat<4, 4, T> translate(const Vec<3, T>& v);

   template <typename T>
   Mat<4, 4, T> translate(const Mat<4, 4, T>& m, const Vec<3, T>& v);

   template <typename T>
   Mat<4, 4, T> rotate(T angleRadians, const Vec<3, T>& v);

   template <typename T>
   Mat<4, 4, T> rotate(const Mat<4, 4, T>& m, T angleRadians, const Vec<3, T>& v);

   template <typename T>
   Mat<4, 4, T> scale(const Vec<3, T>& v);

   template <typename T>
   Mat<4, 4, T> scale(const Mat<4, 4, T>& m, const Vec<3, T>& v);

   template <typename T>
   Mat<4, 4, T> orthographic(T left, T right, T bottom, T top, T zNear, T zFar);
}

#include "Neat/Math/Transforms.inl"