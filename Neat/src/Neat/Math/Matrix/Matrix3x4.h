#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"


namespace Neat
{
   template <typename T>
   struct Matrix<3, 4, T>
   {
      constexpr Matrix() : m_flattened{} {}

      constexpr Matrix(
         T m00, T m01, T m02, T m03,
         T m10, T m11, T m12, T m13,
         T m20, T m21, T m22, T m23)
         : m_flattened{
            m00, m01, m02, m03,
            m10, m11, m12, m13,
            m20, m21, m22, m23
            } {}

      constexpr explicit Matrix(T scalar)
         : m_flattened{
            scalar, static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(0), scalar, static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0), scalar, static_cast<T>(0),
            } {}

      constexpr Matrix(const Matrix<3, 4, T>& m)
         : m_flattened{
            m[0], m[1], m[2], m[3],
            m[4], m[5], m[6], m[7],
            m[8], m[9], m[10], m[11]
            } {}


      constexpr std::size_t size() const { return 3 * 4; }

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
         T m_flattened[3 * 4];
         T m_data[3][4];
      };
   };


   template <typename T>
   inline constexpr
   Matrix<3, 4, T> operator+(const Matrix<3, 4, T>& ma, const Matrix<3, 4, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<3, 4, T> operator-(const Matrix<3, 4, T>& ma, const Matrix<3, 4, T>& mb);
}

#include "Neat/Math/Matrix/Matrix3x4.inl"