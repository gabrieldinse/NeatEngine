#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"


namespace Neat
{
   template <typename T>
   struct Matrix<3, 2, T>
   {
      constexpr Matrix() : m_flattened{} {}

      constexpr Matrix(
         T m00, T m01,
         T m10, T m11,
         T m20, T m21)
         : m_flattened{
            m00, m01,
            m10, m11,
            m20, m21
            } {}

      constexpr explicit Matrix(T scalar)
         : m_flattened{
            scalar, static_cast<T>(0),
            static_cast<T>(0), scalar,
            static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0)
            } {}

      constexpr Matrix(const Matrix<3, 2, T>& m)
         : m_flattened{
            m[0], m[1],
            m[2], m[3],
            m[4], m[5]
            } {}


      constexpr std::size_t size() const { return 3 * 2; }

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
         T m_flattened[3 * 2];
         T m_data[3][2];
      };
   };


   template <typename T>
   inline constexpr
   Matrix<3, 2, T> operator+(const Matrix<3, 2, T>& ma, const Matrix<3, 2, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<3, 2, T> operator-(const Matrix<3, 2, T>& ma, const Matrix<3, 2, T>& mb);
}

#include "Neat/Math/Matrix/Matrix3x2.inl"