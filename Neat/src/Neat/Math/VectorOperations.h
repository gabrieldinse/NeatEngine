#pragma once

#include <cmath>

#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   // Inner/Dot product
   template <typename T>
   T dotProduct(const Vec<1, T>& va, const Vec<1, T>& vb);

   template <typename T>
   T dotProduct(const Vec<2, T>& va, const Vec<2, T>& vb);

   template <typename T>
   T dotProduct(const Vec<3, T>& va, const Vec<3, T>& vb);

   template <typename T>
   T dotProduct(const Vec<4, T>& va, const Vec<4, T>& vb);

   template <typename T, std::size_t N>
   T innerProduct(const Vec<N, T>& va, const Vec<N, T>& vb);

   // Cross product
   template <typename T>
   Vec<3, T> crossProduct(const Vec<3, T>& va, const Vec<3, T>& vb);

   // Norm
   template <typename T>
   T norm(const Vec<1, T>& v);

   template <typename T>
   T norm(const Vec<2, T>& v);

   template <typename T>
   T norm(const Vec<3, T>& v);

   template <typename T>
   T norm(const Vec<4, T>& v);

   // Normalize
   template <typename T>
   Vec<1, T> normalize(const Vec<1, T>& v);

   template <typename T>
   Vec<2, T> normalize(const Vec<2, T>& v);

   template <typename T>
   Vec<3, T> normalize(const Vec<3, T>& v);

   template <typename T>
   Vec<4, T> normalize(const Vec<4, T>& v);
}

#include "Neat/Math/VectorOperations.inl"