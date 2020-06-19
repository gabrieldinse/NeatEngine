#include <cmath>

#include "Neat/Math/Types/TypeVectorN.h"
#include "Neat/Math/Types/TypeQuaternion.h"
#include "Neat/Math/Types/FunctorVector.h"
#include "Neat/Math/Types/FunctorDoubleVector.h"
#include "Neat/Math/Constants.h"


namespace Neat
{
   // Scalar
   template<typename T>
   inline T log2(T value)
   {
      return std::log2(value);
   }

   template<typename T>
   inline T log10(T value)
   {
      return std::log10(value);
   }

   template<typename T>
   inline T sqrt(T value)
   {
      return std::sqrt(value);
   }

   template<typename T>
   inline T inverseSqrt(T value)
   {
      return one<T> / sqrt(value);
   }

   template<typename T>
   inline T pow(T value, T n)
   {
      return std::pow(value, n);
   }

   template<typename T>
   inline T exp(T value)
   {
      return std::exp(value);
   }

   template<typename T>
   inline T log(T value)
   {
      return std::log(value);
   }

   template<typename T>
   inline T ln(T value)
   {
      return log(value);
   }

   template<typename T>
   inline T exp2(T value)
   {
      return std::exp2(value);
   }


   // Vector
   template<UInt32 N, typename T>
   inline Vector<N, T> log2(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(log2, v);
   }

   template<UInt32 N, typename T>
   inline Vector<N, T> log10(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(log10, v);
   }

   template<UInt32 N, typename T>
   inline Vector<N, T> sqrt(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(sqrt, v);
   }

   template<UInt32 N, typename T>
   inline Vector<N, T> inverseSqrt(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(inverseSqrt, v);
   }

   template<UInt32 N, typename T>
   inline Vector<N, T> pow(const Vector<N, T>& q, T n)
   {
      return FunctorDoubleVector<Vector, N, T, T>::call(
         pow, q, Vector<N, T>(n));
   }

   template<UInt32 N, typename T>
   inline Vector<N, T> exp(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(exp, v);
   }

   template<UInt32 N, typename T>
   inline Vector<N, T> log(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(log, v);
   }

   template<UInt32 N, typename T>
   inline Vector<N, T> ln(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(log, v);
   }

   template<UInt32 N, typename T>
   inline Vector<N, T> exp2(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(exp2, v);
   }


   // Quaternion
   template<UInt32 N, typename T>
   inline Quaternion<T> log(const Quaternion<T>& q)
   {
      T norm_q = norm(q);
      T v = Vector<3, T>(q.x, q.y, q.z);
      T norm_v = norm(v);

      if (norm_q < epsilon<T>)
         throw QuaternionLogArgumentOverflow();

      return Quaternion<T>(log(norm_q), v * acos(q.w / norm_q) / norm_v);
   }

   template<UInt32 N, typename T>
   inline Quaternion<T> ln(const Quaternion<T>& q)
   {
      return log(q);
   }

   template<UInt32 N, typename T>
   inline Quaternion<T> exp(const Quaternion<T>& q)
   {
      T v = Vector<3, T>(q.x, q.y, q.z);
      T norm_v = norm(v); // or theta

      if (norm_v < epsilon<T>)
         return Quaternion<T>();

      T exp_w = exp(q.w);
      v = v * sin(norm_v) / norm_v;

      return Quaternion<T>(exp_w * cos(norm_v), exp_w * v);
   }

   template<UInt32 N, typename T>
   inline Quaternion<T> pow(const Quaternion<T>& q, T n)
   {
      return exp(n * ln(q));
   }
}