#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"
#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Mat<2, 2, T>
   {
      // Default constructor
      constexpr
      Mat() : m_flattened{} {}


      // Basic constructors
      constexpr
      Mat(
         T m00, T m01,
         T m10, T m11)
         : m_flattened{
            m00, m01,
            m10, m11
         }
      {}

      constexpr explicit
      Mat(T scalar)
         : m_flattened{
            scalar, static_cast<T>(0),
            static_cast<T>(0), scalar
            } {}

      constexpr
      Mat(const Mat<2, 2, T>& m)
         : m_flattened{
            m[0], m[1],
            m[2], m[3]
            } {}


      // Conversion constructors
      template <
         typename X1, typename Y1,
         typename X2, typename Y2>
      constexpr
      Mat(
         X1 m00, Y1 m01,
         X2 m10, Y2 m11)
         : m_flattened{
            static_cast<T(m00), static_cast<T(m01),
            static_cast<T(m10), static_cast<T(m11)
         }
      {}

      template <typename U>
      constexpr explicit
      Mat(const Mat<2, 2, U>& m)
         : m_flattened{
            static_cast<T(m[0]), static_cast<T(m[1]),
            static_cast<T(m[2]), static_cast<T(m[3])
            } {}

      template <typename U>
      constexpr explicit
      Mat(const Mat<4, 4, U>& m)
         : m_flattened{
            static_cast<T(m[0]), static_cast<T(m[1]),
            static_cast<T(m[4]), static_cast<T(m[5])
            } {}

      template <typename U>
      constexpr explicit
      Mat(const Mat<3, 3, U>& m)
         : m_flattened{
            static_cast<T(m[0]), static_cast<T(m[1]),
            static_cast<T(m[3]), static_cast<T(m[4])
            } {}


      constexpr std::size_t size() const { return 2 * 2; }

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
         T m_flattened[2 * 2];
         T m_data[2][2];
      };
   };


   template <typename T>
   inline constexpr
   Mat<2, 2, T> operator+(const Mat<2, 2, T>& ma, const Mat<2, 2, T>& mb);

   template <typename T>
   inline constexpr
   Mat<2, 2, T> operator-(const Mat<2, 2, T>& ma, const Mat<2, 2, T>& mb);

   template <typename T>
   inline constexpr
   Mat<2, 2, T> operator*(const Mat<2, 2, T>& ma, const Mat<2, 2, T>& mb);

   template <typename T>
   inline constexpr
   Mat<2, 2, T> operator*(T scalar, const Mat<2, 2, T>& m);

   template <typename T>
   inline constexpr
   Mat<2, 2, T> operator*(const Mat<2, 2, T>& m, T scalar);

   template <typename T>
   inline constexpr
   Vec<2, T> operator*(const Mat<2, 2, T>& m, const Vec<2, T>& v);
}

#include "Neat/Math/Matrix/Matrix2x2.inl"