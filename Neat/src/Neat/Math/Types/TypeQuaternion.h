#pragma once

#include "Neat/Math/Types/TypeVectorN.h"
#include "Neat/Math/Types/TypeMatrixMxN.h"


namespace Neat
{
   template <typename T>
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

      // Matrix constructor
      constexpr explicit Quaternion(const Matrix<3, 3, T>& rotation);
      constexpr explicit Quaternion(const Matrix<4, 4, T>& rotation);

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

      // Static factory constructors
      static constexpr Quaternion<T> fromAngleAxis(T angleRadians,
         const Vector<3, T>& axis);
      static constexpr Quaternion<T> fromEulerAngles(
         const Vector<3, T>& pitchYawRoll);
      static constexpr Quaternion<T> fromEulerAngles(T pitch, T yaw, T roll);
      static constexpr Quaternion<T> identity() { return Quaternion<T>(); }

      // Member converters
      constexpr Matrix<3, 3, T> toMatrix3() const;
      constexpr Matrix<4, 4, T> toMatrix4() const;

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
   using QuaternionF = Quaternion<float>;
   using QuaternionD = Quaternion<double>;


   // Quaternion/Matrix conversion
   template <typename T>
   Matrix<3, 3, T> Matrix3Cast(const Quaternion<T>& q);

   template <typename T>
   Matrix<4, 4, T> Matrix4Cast(const Quaternion<T>& q);

   template <typename T>
   Quaternion<T> QuaternionCast(const Matrix<3, 3, T>& m);

   template<typename T>
   Quaternion<T> QuaternionCast(const Matrix<4, 4, T>& m4);


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
   inline constexpr T dot(const Quaternion<T>& qa, const Quaternion<T>& qb);

   template <typename T>
   inline constexpr Quaternion<T> cross(const Quaternion<T>& qa,
      const Quaternion<T>& qb);

   template <typename T>
   inline constexpr T norm(const Quaternion<T>& q);

   template <typename T>
   inline constexpr Quaternion<T> normalize(const Quaternion<T>& q);

   template <typename T>
   inline constexpr Quaternion<T> conjugate(const Quaternion<T>& q);

   template <typename T>
   inline constexpr Quaternion<T> inverse(const Quaternion<T>& q);

   template<typename T>
   inline constexpr Vector<3, T> rotate(const Quaternion<T>& q,
      const Vector<3, T>& v);

   template<typename T>
   inline constexpr Vector<4, T> rotate(const Quaternion<T>& q,
      const Vector<4, T>& v);
   

   // Ostream operators
   template <typename T, UInt32 N>
   std::ostream& operator<<(std::ostream& os, const Quaternion<T>& q);
}

#include "Neat/Math/Types/TypeQuaternion.inl"