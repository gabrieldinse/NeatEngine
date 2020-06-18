#include "TypeQuaternion.h"


namespace Neat
{
   // Default constructor
   template <typename T>
   inline constexpr Quaternion<T>::Quaternion()
      : w(zero<T>), x(zero<T>), y(zero<T>), z(zero<T>) {}


   // Basic constructors
   template <typename T>
   inline constexpr Quaternion<T>::Quaternion(T s, const Vector<3, T>& v)
      : s(s), v(v) {}

   template <typename T>
   inline constexpr Quaternion<T>::Quaternion(T w, T x, T y, T z)
      : w(w), x(x), y(y), z(z) {}


   // Copy Constructor
   template <typename T>
   inline constexpr Quaternion<T>::Quaternion(const Quaternion<T>& q)
      : w(q.w), x(q.x), y(q.y), z(q.z) {}

   
   // Conversion constructors
   template <typename T>
   template <typename U>
   inline constexpr Quaternion<T>::Quaternion(const Quaternion<U>& q)
      : w(static_cast<T>(q.w))
      , x(static_cast<T>(q.x))
      , y(static_cast<T>(q.y))
      , z(static_cast<T>(q.z)) {}


   // Explicit conversion operators
   template <typename T>
   inline Quaternion<T>::operator Matrix<3, 3, T>() const
   {
      // TODO
      return Matrix<3, 3, T>();
   }

   template <typename T>
   inline Quaternion<T>::operator Matrix<4, 4, T>() const
   {
      // TODO
      return Matrix<4, 4, T>();
   }


   // Elements accessing
   template <typename T>
   inline constexpr T& Quaternion<T>::operator[](UInt32 pos)
   {
      if (pos >= 3)
         throw QuaternionDimensionError();

      return (&w)[pos];
   }

   template <typename T>
   inline constexpr const T& Quaternion<T>::operator[](UInt32 pos) const
   {
      if (pos >= 3)
         throw QuaternionDimensionError();

      return (&w)[pos];
   }
}