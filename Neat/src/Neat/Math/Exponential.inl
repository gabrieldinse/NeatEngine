#include <cmath>

#include "Neat/Math/Types/FunctorVector.h"
#include "Neat/Math/Constants.h"


namespace Neat
{
   // Scalar
   template<typename T>
   T log2(T value)
   {
      return std::log2(value);
   }

   template<typename T>
   T sqrt(T value)
   {
      return std::sqrt(value);
   }

   template<typename T>
   T inverseSqrt(T value)
   {
      return one<T> / sqrt(value);
   }

   template<typename T>
   T pow(T value)
   {
      return std::pow(value);
   }

   template<typename T>
   T exp(T value)
   {
      return std::exp(value);
   }

   template<typename T>
   T log(T value)
   {
      return std::log(value);
   }

   template<typename T>
   T exp2(T value)
   {
      return std::exp2(value);
   }


   // Vector
   template<UInt32 N, typename T>
   Vector<N, T> log2(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(log2, v);
   }

   template<UInt32 N, typename T>
   Vector<N, T> sqrt(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(sqrt, v);
   }

   template<UInt32 N, typename T>
   Vector<N, T> inverseSqrt(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(inverseSqrt, v);
   }

   template<UInt32 N, typename T>
   Vector<N, T> pow(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(pow, v);
   }

   template<UInt32 N, typename T>
   Vector<N, T> exp(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(exp, v);
   }

   template<UInt32 N, typename T>
   Vector<N, T> log(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(log, v);
   }

   template<UInt32 N, typename T>
   Vector<N, T> exp2(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(exp2, v);
   }


   // Quaternion
}