#pragma once

#include <cmath>

#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   // Inner/Dot product
   template <typename T>
   T dot(const Vector<1, T>& va, const Vector<1, T>& vb);

   template <typename T>
   T dot(const Vector<2, T>& va, const Vector<2, T>& vb);

   template <typename T>
   T dot(const Vector<3, T>& va, const Vector<3, T>& vb);

   template <typename T>
   T dot(const Vector<4, T>& va, const Vector<4, T>& vb);

   template <typename T, UInt32 N>
   T inner(const Vector<N, T>& va, const Vector<N, T>& vb);

   // Cross product
   template <typename T>
   Vector<3, T> cross(const Vector<3, T>& va, const Vector<3, T>& vb);

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

   // Reflect
   template <UInt32 N, typename T>
   Vector<N, T> reflect(const Vector<N, T>& v, const Vector<N, T>& normal);

   // Refract
   template <UInt32 N, typename T>
   Vector<N, T> refract(
      const Vector<N, T>& v, const Vector<N, T>& normal, const T& eta);
}

#include "Neat/Math/VectorOperations.inl"