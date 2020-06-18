#include <cmath>

#include "Neat/Math/Types/FunctorVector.h"
#include "Neat/Math/Constants.h"


namespace Neat
{
   template<typename T>
   T log2(T value)
   {
      return std::log2(value);
   }

   template<UInt32 N, typename T>
   Vector<N, T> log2(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(log2, v);
   }

   template<typename T>
   T sqrt(T value)
   {
      return std::sqrt(value);
   }

   template<UInt32 N, typename T>
   Vector<N, T> sqrt(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(sqrt, v);
   }

   template<typename T>
   T inverseSqrt(T value)
   {
      return one<T> / sqrt(value);
   }

   template<UInt32 N, typename T>
   Vector<N, T> inverseSqrt(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(inverseSqrt, v);
   }

   template<typename T>
   T pow(T value)
   {
      return std::pow(value);
   }

   template<UInt32 N, typename T>
   Vector<N, T> pow(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(pow, v);
   }

   template<typename T>
   T exp(T value)
   {
      return std::exp(value);
   }

   template<UInt32 N, typename T>
   Vector<N, T> exp(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(exp, v);
   }

   template<typename T>
   T log(T value)
   {
      return std::log(value);
   }

   template<UInt32 N, typename T>
   Vector<N, T> log(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(log, v);
   }

   template<typename T>
   T exp2(T value)
   {
      return std::exp2(value);
   }

   template<UInt32 N, typename T>
   Vector<N, T> exp2(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(exp2, v);
   }
}