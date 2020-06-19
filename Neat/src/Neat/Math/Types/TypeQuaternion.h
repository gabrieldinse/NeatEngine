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
      constexpr explicit Quaternion(const Vector<3, T>& eulerAngles);
      constexpr explicit Quaternion(Matrix<3, 3, T> const& rotation);
      constexpr explicit Quaternion(Matrix<4, 4, T> const& rotation);

      // Assignment operators
      constexpr Quaternion<T>& operator=(const Quaternion<T>& q) = default;
      template <typename U>
      constexpr Quaternion<T>& operator=(const Quaternion<U>& q);

      // Compound assignment operators
      template <typename U>
      constexpr Quaternion<T>& operator+=(const Quaternion<U>& q);
      template <typename U>
      constexpr Quaternion<T>& operator-=(const Quaternion<U>& q);
      template <typename U>
      constexpr Quaternion<T>& operator*=(const Quaternion<U>& q);
      template <typename U>
      constexpr Quaternion<T>& operator*=(U scalar);
      template <typename U>
      constexpr Quaternion<T>& operator/=(U scalar);

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


   // Predefined types
   using DQuaternion = Quaternion<double>;


   // Non members operators
   template <typename T>
   inline constexpr Quaternion<T> operator+(const Quaternion<T>& qa,
      const Quaternion<T>& qb);

   template <typename T>
   inline constexpr Quaternion<T> operator-(const Quaternion<T>& q);

   template <typename T>
   inline constexpr Quaternion<T> operator-(const Quaternion<T>& qa,
      const Quaternion<T>& qb);

   template <typename T>
   inline constexpr Quaternion<T> operator*(const Quaternion<T>& qa,
      const Quaternion<T>& qb);

   template <typename T>
   inline constexpr Vector<3, T> operator*(const Quaternion<T>& q,
      const Vector<3, T>& v);

   template <typename T>
   inline constexpr Vector<3, T> operator*(const Vector<3, T>& v,
      const Quaternion<T>& q);

   template <typename T>
   inline constexpr Vector<4, T> operator*(const Quaternion<T>& q,
      const Vector<4, T>& v);

   template <typename T>
   inline constexpr Vector<4, T> operator*(const Vector<4, T>& v,
      const Quaternion<T>& q);

   template <typename T>
   inline constexpr Quaternion<T> operator*(const Quaternion<T>& q,
      T const& scalar);

   template <typename T>
   inline constexpr Quaternion<T> operator*(T const& scalar,
      const Quaternion<T>& q);

   template <typename T>
   inline constexpr Quaternion<T> operator/(const Quaternion<T>& q,
      T const& scalar);


   // Relational operators
   template <typename T>
   inline constexpr bool operator==(const Quaternion<T>& qa,
      const Quaternion<T>& qb);

   template <typename T>
   inline constexpr bool operator!=(const Quaternion<T>& qa,
      const Quaternion<T>& qb);


   // Quaternion operations
   template <typename T>
   inline constexpr Quaternion<T> conjugate(const Quaternion<T>& q);

   template <typename T>
   inline constexpr Quaternion<T> inverse(const Quaternion<T>& q);
}

#include "Neat/Math/Types/TypeQuaternion.inl"