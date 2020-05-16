#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"
#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Mat<4, 4, T>
   {
      // Default constructor
      constexpr
      Mat() : m_flattened{} {}


      // Basic constructors
      constexpr
      Mat(
         T m00, T m01, T m02, T m03,
         T m10, T m11, T m12, T m13,
         T m20, T m21, T m22, T m23,
         T m30, T m31, T m32, T m33)
         : m_flattened{
            m00, m01, m02, m03,
            m10, m11, m12, m13,
            m20, m21, m22, m23,
            m30, m31, m32, m33
            } {}

      constexpr explicit
      Mat(T scalar)
         : m_flattened{
            scalar, static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(0), scalar, static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0), scalar, static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), scalar
            } {}


      // Copy constructor
      constexpr
      Mat(const Mat<4, 4, T>& m)
         : m_flattened{
            m[0], m[1], m[2], m[3],
            m[4], m[5], m[6], m[7],
            m[8], m[9], m[10], m[11],
            m[12], m[13], m[14], m[15]
            } {}


      // Conversion constructors
      template <
         typename X1, typename Y1, typename Z1, typename W1,
         typename X2, typename Y2, typename Z2, typename W2,
         typename X3, typename Y3, typename Z3, typename W3,
         typename X4, typename Y4, typename Z4, typename W4>
      constexpr
      Mat(
         X1 m00, Y1 m01, Z1 m02, W1 m03,
         X2 m10, Y2 m11, Z2 m12, W2 m13,
         X3 m20, Y3 m21, Z3 m22, W3 m23,
         X4 m30, Y4 m31, Z4 m32, W4 m33)
         : m_flattened{
            static_cast<T>(m00), static_cast<T>(m01), static_cast<T>(m02), static_cast<T>(m03),
            static_cast<T>(m10), static_cast<T>(m11), static_cast<T>(m12), static_cast<T>(m13),
            static_cast<T>(m20), static_cast<T>(m21), static_cast<T>(m22), static_cast<T>(m23),
            static_cast<T>(m30), static_cast<T>(m31), static_cast<T>(m32), static_cast<T>(m33)
            } {}

      template <typename U>
      constexpr explicit
      Mat(const Mat<4, 4, U>& m)
         : m_flattened{
            static_cast<T>(m[0]), static_cast<T>(m[1]), static_cast<T>(m[2]), static_cast<T>(m[3]),
            static_cast<T>(m[4]), static_cast<T>(m[5]), static_cast<T>(m[6]), static_cast<T>(m[7]),
            static_cast<T>(m[8]), static_cast<T>(m[9]), static_cast<T>(m[10]), static_cast<T>(m[11]),
            static_cast<T>(m[12]), static_cast<T>(m[13]), static_cast<T>(m[14]), static_cast<T>(m[15])
            } {}

      template <typename U>
      constexpr explicit
      Mat(const Mat<3, 3, U>& m)
         : m_flattened{
            static_cast<T>(m[0]), static_cast<T>(m[1]), static_cast<T>(m[2]), static_cast<T>(0),
            static_cast<T>(m[3]), static_cast<T>(m[4]), static_cast<T>(m[5]), static_cast<T>(0),
            static_cast<T>(m[6]), static_cast<T>(m[7]), static_cast<T>(m[8]), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)
            } {}

      template <typename U>
      constexpr explicit
      Mat(const Mat<2, 2, U>& m)
         : m_flattened{
            static_cast<T>(m[0]), static_cast<T>(m[1]), static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(m[2]), static_cast<T>(m[3]), static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)
            } {}


      // Assignment operators

      constexpr std::size_t size() const { return 4 * 4; }

      // Elements acessing
      constexpr T* dataPointer() { return m_flattened; }
      constexpr const T* dataPointer() const { return m_flattened; }

      constexpr T& operator[](std::size_t pos) { return m_flattened[pos]; }
      constexpr const T& operator[](std::size_t pos) const { return m_flattened[pos]; }

      constexpr T& operator()(std::size_t i, std::size_t j) { return m_data[i][j]; }
      constexpr const T& operator()(std::size_t i, std::size_t j) const { return m_data[i][j]; }
      constexpr T& operator()(std::size_t i) { return m_flattened[i]; }
      constexpr const T& operator()(std::size_t i) const { return m_flattened[i]; }

      // Class data
      union
      {
         T m_flattened[4 * 4];
         T m_data[4][4];
      };
   };
   

   template <typename T>
   inline constexpr
   Mat<4, 4, T> operator+(const Mat<4, 4, T>& ma, const Mat<4, 4, T>& mb);

   template <typename T>
   inline constexpr
   Mat<4, 4, T> operator-(const Mat<4, 4, T>& ma, const Mat<4, 4, T>& mb);

   template <typename T>
   inline constexpr
   Mat<4, 4, T> operator*(const Mat<4, 4, T>& ma, const Mat<4, 4, T>& mb);

   template <typename T>
   inline constexpr
   Mat<4, 4, T> operator*(T scalar, const Mat<4, 4, T>& m);

   template <typename T>
   inline constexpr
   Mat<4, 4, T> operator*(const Mat<4, 4, T>& m, T scalar);

   template <typename T>
   inline constexpr
   Vec<4, T> operator*(const Mat<4, 4, T>& m, const Vec<4, T>& v);
}

#include "Neat/Math/Matrix/Matrix4x4.inl"