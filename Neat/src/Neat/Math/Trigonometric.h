#pragma once

#include "Neat/Math/Types/TypeVectorN.h"


namespace Neat
{
   // Utility
   template <typename T>
   inline constexpr T radians(T angleDegrees);

   template <typename T>
   inline constexpr T degrees(T angleRadians);

   template <typename T>
   inline constexpr T wrapPi(T angleRadians);

   template <typename T>
   inline constexpr T wrap2Pi(T angleRadians);


   // Trigonometric functions
   template <typename T>
   T sin(T value);
   template <UInt32 N, typename T>
   Vector<N, T> sin(const Vector<N, T>& v);

   template <typename T>
   T cos(T value);
   template <UInt32 N, typename T>
   Vector<N, T> cos(const Vector<N, T>& v);

   template <typename T>
   T tan(T value);
   template <UInt32 N, typename T>
   Vector<N, T> tan(const Vector<N, T>& v);

   template <typename T>
   T asin(T value);
   template <UInt32 N, typename T>
   Vector<N, T> asin(const Vector<N, T>& v);

   template <typename T>
   T acos(T value);
   template <UInt32 N, typename T>
   Vector<N, T> acos(const Vector<N, T>& v);

   template <typename T>
   T atan(T value);
   template <UInt32 N, typename T>
   Vector<N, T> atan(const Vector<N, T>& v);

   template <typename T>
   T sinh(T value);
   template <UInt32 N, typename T>
   Vector<N, T> sinh(const Vector<N, T>& v);

   template <typename T>
   T cosh(T value);
   template <UInt32 N, typename T>
   Vector<N, T> cosh(const Vector<N, T>& v);

   template <typename T>
   T tanh(T value);
   template <UInt32 N, typename T>
   Vector<N, T> tanh(const Vector<N, T>& v);

   template <typename T>
   T asinh(T value);
   template <UInt32 N, typename T>
   Vector<N, T> asinh(const Vector<N, T>& v);

   template <typename T>
   T acosh(T value);
   template <UInt32 N, typename T>
   Vector<N, T> acosh(const Vector<N, T>& v);

   template <typename T>
   T atanh(T value);
   template <UInt32 N, typename T>
   Vector<N, T> atanh(const Vector<N, T>& v);
}

#include "Neat/Math/Trigonometric.inl"