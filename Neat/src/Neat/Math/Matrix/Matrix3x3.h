#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"
#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Matrix<3, 3, T>
   {
      // Default constructor
      constexpr
      Matrix() : m_flattened{} {}


      // Basic constructors
      constexpr
      Matrix(
         T m00, T m01, T m02,
         T m10, T m11, T m12,
         T m20, T m21, T m22)
         : m_flattened{
            m00, m01, m02,
            m10, m11, m12,
            m20, m21, m22
            } {}

      constexpr explicit
      Matrix(T scalar)
         : m_flattened{
            scalar, static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(0), scalar, static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0), scalar
            } {}


      // Copy constrcutor
      constexpr
      Matrix(const Matrix<3, 3, T>& m)
         : m_flattened{
            m[0], m[1], m[2],
            m[3], m[4], m[5],
            m[6], m[7], m[8]
            } {}


      // Conversion constructors
      template <
         typename X1, typename Y1, typename Z1,
         typename X2, typename Y2, typename Z2,
         typename X3, typename Y3, typename Z3>
      constexpr
      Matrix(
         X1 m00, Y1 m01, Z1 m02,
         X2 m10, Y2 m11, Z2 m12,
         X3 m20, Y3 m21, Z3 m22)
         : m_flattened{
            static_cast<T>(m00), static_cast<T>(m01), static_cast<T>(m02),
            static_cast<T>(m10), static_cast<T>(m11), static_cast<T>(m12),
            static_cast<T>(m20), static_cast<T>(m21), static_cast<T>(m22)
            } {}

      template <typename U>
      constexpr explicit
      Matrix(const Matrix<3, 3, U>& m)
         : m_flattened{
            static_cast<T>(m[0]), static_cast<T>(m[1]), static_cast<T>(m[2]),
            static_cast<T>(m[3]), static_cast<T>(m[4]), static_cast<T>(m[5]),
            static_cast<T>(m[6]), static_cast<T>(m[7]), static_cast<T>(m[8])
            } {}

      template <typename U>
      constexpr explicit
      Matrix(const Matrix<4, 4, U>& m)
         : m_flattened{
            static_cast<T>(m[0]), static_cast<T>(m[1]), static_cast<T>(m[2]),
            static_cast<T>(m[4]), static_cast<T>(m[5]), static_cast<T>(m[6]),
            static_cast<T>(m[8]), static_cast<T>(m[9]), static_cast<T>(m[10])
            } {}

      template <typename U>
      constexpr explicit
         Matrix(const Matrix<2, 2, U>& m)
         : m_flattened{
            static_cast<T>(m[0]), static_cast<T>(m[1]), static_cast<T>(0),
            static_cast<T>(m[2]), static_cast<T>(m[3]), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)
            } {}


      constexpr std::size_t size() const { return 3 * 3; }

      // Elements acessing
      constexpr T* dataPointer() { return m_flattened; }
      constexpr const T* dataPointer() const { return m_flattened; }

      constexpr T& operator[](std::size_t pos) { return m_flattened[pos]; }
      constexpr const T& operator[](std::size_t pos) const { return m_flattened[pos]; }

      constexpr T& operator()(std::size_t i, std::size_t j) { return m_data[i][j]; }
      constexpr const T& operator()(std::size_t i, std::size_t j) const { return m_data[i][j]; }
      constexpr T& operator()(std::size_t i) { return m_flattened[i]; }
      constexpr const T& operator()(std::size_t i) const { return m_flattened[i]; }

   private:
      // Class data
      union
      {
         T m_flattened[3 * 3];
         T m_data[3][3];
      };
   };


   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator+(const Matrix<3, 3, T>& ma, const Matrix<3, 3, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator-(const Matrix<3, 3, T>& ma, const Matrix<3, 3, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& ma, const Matrix<3, 3, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator*(T scalar, const Matrix<3, 3, T>& m);

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& m, T scalar);

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(const Matrix<3, 3, T>& m, const Vector<3, T>& v);
}

#include "Neat/Math/Matrix/Matrix3x3.inl"