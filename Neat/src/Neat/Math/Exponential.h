#pragma once

#include "Neat/Math/Types/TypeVectorN.h"


namespace Neat
{
   template <typename T>
   T log2(T value);
   template <UInt32 N, typename T>
   Vector<N, T> log2(const Vector<N, T>& v);

   template <typename T>
   T sqrt(T value);
   template <UInt32 N, typename T>
   Vector<N, T> sqrt(const Vector<N, T>& v);

   template <typename T>
   T inverseSqrt(T value);
   template <UInt32 N, typename T>
   Vector<N, T> inverseSqrt(const Vector<N, T>& v);

   template <typename T>
   T pow(T value);
   template <UInt32 N, typename T>
   Vector<N, T> pow(const Vector<N, T>& v);

   template <typename T>
   T exp(T value);
   template <UInt32 N, typename T>
   Vector<N, T> exp(const Vector<N, T>& v);

   template <typename T>
   T log(T value);
   template <UInt32 N, typename T>
   Vector<N, T> log(const Vector<N, T>& v);

   template <typename T>
   T exp2(T value);
   template <UInt32 N, typename T>
   Vector<N, T> exp2(const Vector<N, T>& v);
}

#include "Neat/Math/Exponential.inl"