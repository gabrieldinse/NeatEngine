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
   inline T pow(T base, T exponent)
   {
      return std::pow(base, exponent);
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
   inline Vector<N, T> pow(const Vector<N, T>& q, T exponent)
   {
      return FunctorDoubleVector<Vector, N, T, T>::call(
         pow, q, Vector<N, T>(exponent));
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
   template <typename T>
   inline Quat<T> log(const Quat<T>& q)
   {
      T norm_v = norm(q.v);

      // To prevent dividing by 0 later on
      if (norm_v < epsilon<T>)
      {
         if (q.w > zero<T>) // Computes log of a scalar
            return Quat<T>(log(q.w), zero<T>, zero<T>, zero<T>);
         else if (q.w < zero<T>) // Computes log of a scalar
            return Quat<T>(log(-q.w), pi<T>, zero<T>, zero<T>);
         else // Division by 0 anyway
            throw QuaternionLogUndefined();
      }

      T norm_q = norm(q);

      return Quat<T>(log(norm_q), q.v * acos(q.w / norm_q) / norm_v);
   }

   template <typename T>
   inline Quat<T> ln(const Quat<T>& q)
   {
      return log(q);
   }

   template <typename T>
   inline Quat<T> exp(const Quat<T>& q)
   {
      T norm_v = norm(q.v); // or theta

      if (norm_v < epsilon<T>)
         return Quat<T>::identity();

      T exp_w = exp(q.w);
      auto v = q.v * sin(norm_v) / norm_v;

      return Quat<T>(exp_w * cos(norm_v), exp_w * q.v);
   }

   template <typename T>
   inline Quat<T> pow(const Quat<T>& q, T exponent)
   {
      // Raising to the power of 0 should return identity
      if (exponent > -epsilon<T> && exponent < epsilon<T>)
         return Quat<T>::identity();

      T norm_q = norm(q);

      T angle;
      if (abs(q.w / norm_q) > cosOneHalf<T>) // Better using asin for precision
      {
         T norm_v = norm(q.v);
         // To prevent dividing by 0 later on
         if (abs(norm_v) < epsilon<T>) // Computes pow of a scalar
            return Quat<T>(pow(q.w, exponent), zero<T>, zero<T>, zero<T>);

         angle = asin(norm_v / norm_q);
      }
      else // Can use cos normally, shouldn't cause loss of precision
      {
         angle = acos(q.w / norm_q);
      }

      T new_angle = angle * exponent;
      T sin_factor = sin(new_angle) / sin(angle);
      T norm_q_factor = pow(norm_q, exponent - one<T>);

      return Quat<T>(
         cos(new_angle) * norm_q_factor * norm_q,
         sin_factor * norm_q_factor * q.v);
   }
}