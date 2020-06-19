#pragma once

#include "Neat/Math/Types/TypeVectorN.h"


namespace Neat
{
   // Scalar
   template <typename T>
   T log2(T value);

   template <typename T>
   T sqrt(T value);

   template <typename T>
   T inverseSqrt(T value);

   template <typename T>
   T pow(T value);

   template <typename T>
   T exp(T value);

   template <typename T>
   T log(T value);

   template <typename T>
   T exp2(T value);


   // Vector
   template <UInt32 N, typename T>
   Vector<N, T> log2(const Vector<N, T>& v);

   template <UInt32 N, typename T>
   Vector<N, T> sqrt(const Vector<N, T>& v);

   template <UInt32 N, typename T>
   Vector<N, T> inverseSqrt(const Vector<N, T>& v);

   template <UInt32 N, typename T>
   Vector<N, T> pow(const Vector<N, T>& v);

   template <UInt32 N, typename T>
   Vector<N, T> exp(const Vector<N, T>& v);

   template <UInt32 N, typename T>
   Vector<N, T> log(const Vector<N, T>& v);

   template <UInt32 N, typename T>
   Vector<N, T> exp2(const Vector<N, T>& v);


   // Quaternion
}

#include "Neat/Math/Exponential.inl"