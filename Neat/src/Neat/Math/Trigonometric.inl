#include <cmath>

#include "Neat/Math/Types/FunctorVector.h"


namespace Neat
{
   // Utility
   template <typename T>
   inline constexpr T radians(T angleDegrees)
   {
      return angleDegrees * degreeInRadians<T>;
   }

   template <typename T>
   inline constexpr T degrees(T angleRadians)
   {
      return angleRadians * radianInDegrees<T>;
   }

   template <typename T>
   inline constexpr T wrapPi(T angleRadians)
   {
      if (fabs(angleRadians) > pi<T>)
      {
         T revolutions = std::floor(
            oneOverTwoPi<T> * (angleRadians + pi<T>));
         angleRadians -= revolutions * twoPi<T>;
      }

      return angleRadians;
   }

   template <typename T>
   inline constexpr T wrap2Pi(T angleRadians)
   {
      if (fabs(angleRadians) > twoPi<T>)
      {
         T revolutions = std::floor(oneOverTwoPi<T> * angleRadians);
         angleRadians -= revolutions * twoPi<T>;
      }

      return angleRadians;
   }


   // Trigonometric functions -------------------------------------------------
   // Scalar
   template <typename T>
   T sin(T value)
   {
      return std::sin(value);
   }

   template <typename T>
   T cos(T value)
   {
      return std::cos(value);
   }

   template <typename T>
   T tan(T value)
   {
      return std::tan(value);
   }

   template <typename T>
   T asin(T value)
   {
      return std::asin(value);
   }

   template <typename T>
   T acos(T value)
   {
      return std::acos(value);
   }

   template <typename T>
   T atan(T value)
   {
      return std::atan(value);
   }

   template <typename T>
   T sinh(T value)
   {
      return std::sinh(value);
   }

   template <typename T>
   T cosh(T value)
   {
      return std::cosh(value);
   }

   template <typename T>
   T tanh(T value)
   {
      return std::tanh(value);
   }

   template <typename T>
   T asinh(T value)
   {
      return std::asinh(value);
   }

   template <typename T>
   T acosh(T value)
   {
      return std::acosh(value);
   }

   template <typename T>
   T atanh(T value)
   {
      return std::atanh(value);
   }


   // Vector
   template <UInt32 N, typename T>
   Vector<N, T> sin(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(sin, v);
   }

   template <UInt32 N, typename T>
   Vector<N, T> cos(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(cos, v);
   }

   template<UInt32 N, typename T>
   Vector<N, T> tan(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(tan, v);
   }

   template <UInt32 N, typename T>
   Vector<N, T> asin(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(asin, v);
   }

   template <UInt32 N, typename T>
   Vector<N, T> acos(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(acos, v);
   }

   template <UInt32 N, typename T>
   Vector<N, T> atan(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(atan, v);
   }

   template <UInt32 N, typename T>
   Vector<N, T> sinh(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(sinh, v);
   }

   template <UInt32 N, typename T>
   Vector<N, T> cosh(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(cosh, v);
   }

   template <UInt32 N, typename T>
   Vector<N, T> tanh(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(tanh, v);
   }

   template <UInt32 N, typename T>
   Vector<N, T> asinh(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(asinh, v);
   }

   template <UInt32 N, typename T>
   Vector<N, T> acosh(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(acosh, v);
   }

   template <UInt32 N, typename T>
   Vector<N, T> atanh(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(atanh, v);
   }
}