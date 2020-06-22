#pragma once

#include "Neat/Math/Types/TypeVectorN.h"
#include "Neat/Math/Types/TypeMatrixMxN.h"


namespace Neat
{
   template <typename T>
   struct Quat
   {
      using Type = Quat<T>;
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
      constexpr Quat();

      // Basic constructors
      constexpr Quat(T s, const Vector<3, T>& v);
      constexpr Quat(T w, T x, T y, T z);

      // Copy constructor
      constexpr Quat(const Quat<T>& q);

      // Conversion constructors
      template <typename U>
      constexpr explicit Quat(const Quat<U>& q);

      // Euler angles constructors
      constexpr explicit Quat(const Vector<3, T>& eulerAngles);
      constexpr explicit Quat(const Matrix<3, 3, T>& rotation);
      constexpr explicit Quat(const Matrix<4, 4, T>& rotation);

      // Assignment operators
      constexpr Quat<T>& operator=(const Quat<T>& q) = default;
      template <typename U>
      constexpr Quat<T>& operator=(const Quat<U>& q);

      // Compound assignment operators
      template <typename U>
      constexpr Quat<T>& operator+=(const Quat<U>& q);
      template <typename U>
      constexpr Quat<T>& operator-=(const Quat<U>& q);
      template <typename U>
      constexpr Quat<T>& operator*=(const Quat<U>& q);
      template <typename U>
      constexpr Quat<T>& operator*=(U scalar);
      template <typename U>
      constexpr Quat<T>& operator/=(U scalar);

      // Static factory constructors
      static constexpr Quat<T> fromAngleAxis(T angleRadians,
         const Vector<3, T>& n);
      static constexpr Quat<T> identity() { return Quat<T>(); }

      // Explicit conversion operators
      explicit operator Matrix<3, 3, T>() const;
      explicit operator Matrix<4, 4, T>() const;

      // Element accessing
      constexpr T& operator[](UInt32 pos);
      constexpr const T& operator[](UInt32 pos) const;

      // Static member functions
      static constexpr UInt32 size() { return 4; }
      static constexpr UInt32 length() { return size(); }
   };


   // Predefined types
   using Quaternion = Quat<float>;
   using DQuaternion = Quat<double>;


   // Non members operators
   template <typename T>
   inline constexpr Quat<T> operator+(const Quat<T>& qa,
      const Quat<T>& qb);

   template <typename T>
   inline constexpr Quat<T> operator-(const Quat<T>& q);

   template <typename T>
   inline constexpr Quat<T> operator-(const Quat<T>& qa,
      const Quat<T>& qb);

   template <typename T>
   inline constexpr Quat<T> operator*(const Quat<T>& qa,
      const Quat<T>& qb);

   template <typename T>
   inline constexpr Vector<3, T> operator*(const Quat<T>& q,
      const Vector<3, T>& v);

   template <typename T>
   inline constexpr Vector<3, T> operator*(const Vector<3, T>& v,
      const Quat<T>& q);

   template <typename T>
   inline constexpr Vector<4, T> operator*(const Quat<T>& q,
      const Vector<4, T>& v);

   template <typename T>
   inline constexpr Vector<4, T> operator*(const Vector<4, T>& v,
      const Quat<T>& q);

   template <typename T>
   inline constexpr Quat<T> operator*(const Quat<T>& q,
      T const& scalar);

   template <typename T>
   inline constexpr Quat<T> operator*(T const& scalar,
      const Quat<T>& q);

   template <typename T>
   inline constexpr Quat<T> operator/(const Quat<T>& q,
      T const& scalar);


   // Relational operators
   template <typename T>
   inline constexpr bool operator==(const Quat<T>& qa,
      const Quat<T>& qb);

   template <typename T>
   inline constexpr bool operator!=(const Quat<T>& qa,
      const Quat<T>& qb);


   // Quaternion operations
   template<typename T>
   constexpr T dot(const Quat<T>& qa, const Quat<T>& qb);

   template<typename T>
   constexpr Quat<T> cross(const Quat<T>& qa, const Quat<T>& qb);

   template<typename T>
   constexpr T norm(const Quat<T>& q);

   template<typename T>
   constexpr Quat<T> normalize(const Quat<T>& q);

   template<typename T>
   constexpr Quat<T> conjugate(const Quat<T>& q);

   template<typename T>
   constexpr Quat<T> inverse(const Quat<T>& q);
   

   // Ostream operators
   template <typename T, UInt32 N>
   std::ostream& operator<<(std::ostream& os, const Quat<T>& q);
}

#include "Neat/Math/Types/TypeQuaternion.inl"