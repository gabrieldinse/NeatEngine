#include <cmath>

#include "Neat/Math/Types/FunctorVector.hpp"
#include "Neat/Math/Types/FunctorDoubleVector.hpp"
#include "Neat/Math/Common.hpp"
#include "Trigonometric.hpp"


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
      if (abs(angleRadians) > pi<T>)
      {
         T revolutions = floor(
            oneOverTwoPi<T> * (angleRadians + pi<T>));
         angleRadians -= revolutions * twoPi<T>;
      }

      return angleRadians;
   }

   template <typename T>
   inline constexpr T wrapTwoPi(T angleRadians)
   {
      if (abs(angleRadians) > twoPi<T>)
      {
         T revolutions = floor(oneOverTwoPi<T> * angleRadians);
         angleRadians -= revolutions * twoPi<T>;
      }

      return angleRadians;
   }

   template<typename T>
   inline constexpr T wrap180(T angleDegrees)
   {
      if (abs(angleDegrees) > static_cast<T>(180))
      {
         T revolutions = floor(
            static_cast<T>(1.0 / 360) * (angleDegrees + static_cast<T>(180)));
         angleDegrees -= revolutions * static_cast<T>(360);   
      }

      return angleDegrees;
   }

   template<typename T>
   inline constexpr T wrap360(T angleDegrees)
   {
      if (abs(angleDegrees) > static_cast<T>(360))
      {
         T revolutions = floor(static_cast<T>(1.0 / 360) * angleDegrees);
         angleDegrees -= revolutions * static_cast<T>(360);
      }

      return angleDegrees;
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

   template<typename T>
   T atan2(T y, T x)
   {
      return std::atan2(y, x);
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

   template <UInt32 N, typename T>
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

   template<UInt32 N, typename T>
   Vector<N, T> atan2(const Vector<N, T>& vy, const Vector<N, T>& vx)
   {
      return FunctorDoubleVector<Vector, N, T, T>::call(atan2, vy, vx);
   }
}