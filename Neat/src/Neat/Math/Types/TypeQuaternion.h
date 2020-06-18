#pragma once

#include "Neat/Math/Types/TypeVectorN.h"


namespace Neat
{
   template <typename T = float>
   struct Quaternion
   {
      using Type = Quaternion<T>;
      using ValueType = T;


      // Class data
      union
      {
         struct { T w, x, y, z; };
         struct { T a, b, c, d; };
         struct { T q0, q1, q2, q3; };
         struct { T s; Vector<3, T> v; };
      };


      // Default constructor
      constexpr Quaternion();

      // Basic constructors
      constexpr Quaternion(T s, const Vector<3, T>& v);
      constexpr Quaternion(T w, T x, T y, T z);

      // Copy constructor
      constexpr Quaternion(const Quaternion<T>& q);

      // Conversion constructors
      template <typename U>
      constexpr explicit Quaternion(const Quaternion<U>& q);

      // Euler angles constructors
      constexpr explicit Quaternion(Vector<3, T> const& eulerAngles);
      constexpr explicit Quaternion(Matrix<3, 3, T> const& rotation);
      constexpr explicit Quaternion(Matrix<4, 4, T> const& rotation);

      // Explicit conversion operators
      explicit operator Matrix<3, 3, T>() const;
      explicit operator Matrix<4, 4, T>() const;

      // Element accessing
      constexpr T& operator[](UInt32 pos);
      constexpr const T& operator[](UInt32 pos) const;

      // Static member functions
      static constexpr Quaternion<T> identity()
      {
         return Quaternion(one<T>, zero<T>, zero<T>, zero<T>);
      }
      static constexpr UInt32 size() { return 4; }
      static constexpr UInt32 length() { return size(); }
   };
}

#include "TypeQuaternion.inl"