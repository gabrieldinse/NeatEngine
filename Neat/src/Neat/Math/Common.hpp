#pragma once


namespace Neat
{
   // Scalar
   template <typename T>
   T min(T a, T b);

   template <typename T>
   T abs(T value);

   template <typename T>
   T round(T value);

   template <typename T>
   T floor(T value);

   template <typename T>
   T max(T a, T b);

   template <typename T>
   T ceil(T value);

   template <typename T>
   T trunc(T value);

   template <typename T>
   T fract(T value);

   template <typename T>
   T mod(T a, T b);

   template <typename T>
   T clamp(T value, T low, T high);


   // Vector
   template <UInt32 N, typename T>
   Vector<N, T> min(const Vector<N, T>& va, const Vector<N, T>& vb);

   template <UInt32 N, typename T>
   Vector<N, T> max(const Vector<N, T>& va, const Vector<N, T>& vb);

   template <UInt32 N, typename T>
   Vector<N, T> abs(const Vector<N, T>& v);

   template <UInt32 N, typename T>
   Vector<N, T> round(const Vector<N, T>& v);

   template <UInt32 N, typename T>
   Vector<N, T> floor(const Vector<N, T>& v);

   template <UInt32 N, typename T>
   Vector<N, T> ceil(const Vector<N, T>& v);

   template <UInt32 N, typename T>
   Vector<N, T> trunc(const Vector<N, T>& v);

   template <UInt32 N, typename T>
   Vector<N, T> fract(const Vector<N, T>& v);

   template <UInt32 N, typename T>
   Vector<N, T> mod(const Vector<N, T>& v, T value);

   template <UInt32 N, typename T>
   Vector<N, T> mod(const Vector<N, T>& va, const Vector<N, T>& vb);

   template <UInt32 N, typename T>
   Vector<N, T> clamp(const Vector<N, T>& v, T low, T high);

   template <UInt32 N, typename T>
   Vector<N, T> clamp(const Vector<N, T>& v, const Vector<N, T>& low,
      const Vector<N, T>& high);

   template <UInt32 N, typename T>
   Vector<N, T> reflect(const Vector<N, T>& v, const Vector<N, T>& normal);

   template <UInt32 N, typename T>
   Vector<N, T> refract(const Vector<N, T>& v, const Vector<N, T>& normal,
      const T& eta);


   // Quaternion
}

#include "Neat/Math/Common.inl"