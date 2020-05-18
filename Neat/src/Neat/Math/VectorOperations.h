#pragma once

#include <cmath>

#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   // Inner/Dot product
   template <typename T>
   T dotProduct(const Vector<1, T>& va, const Vector<1, T>& vb);

   template <typename T>
   T dotProduct(const Vector<2, T>& va, const Vector<2, T>& vb);

   template <typename T>
   T dotProduct(const Vector<3, T>& va, const Vector<3, T>& vb);

   template <typename T>
   T dotProduct(const Vector<4, T>& va, const Vector<4, T>& vb);

   template <typename T, UInt N>
   T innerProduct(const Vector<N, T>& va, const Vector<N, T>& vb);

   // Cross product
   template <typename T>
   Vector<3, T> crossProduct(const Vector<3, T>& va, const Vector<3, T>& vb);

   // Norm
   template <typename T>
   T norm(const Vector<1, T>& v);

   template <typename T>
   T norm(const Vector<2, T>& v);

   template <typename T>
   T norm(const Vector<3, T>& v);

   template <typename T>
   T norm(const Vector<4, T>& v);

   // Normalize
   template <typename T>
   Vector<1, T> normalize(const Vector<1, T>& v);

   template <typename T>
   Vector<2, T> normalize(const Vector<2, T>& v);

   template <typename T>
   Vector<3, T> normalize(const Vector<3, T>& v);

   template <typename T>
   Vector<4, T> normalize(const Vector<4, T>& v);
}

#include "Neat/Math/VectorOperations.inl"