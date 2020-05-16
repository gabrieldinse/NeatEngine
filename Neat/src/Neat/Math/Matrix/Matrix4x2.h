#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"


namespace Neat
{
   template <typename T>
   struct Mat<4, 2, T>
   {
      constexpr Mat() : m_flattened{} {}

      constexpr Mat(
         T m00, T m01,
         T m10, T m11,
         T m20, T m21,
         T m30, T m31)
         : m_flattened{
            m00, m01,
            m10, m11,
            m20, m21,
            m30, m31
            } {}

      constexpr explicit Mat(T scalar)
         : m_flattened{
            scalar, static_cast<T>(0),
            static_cast<T>(0), scalar,
            static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0)
            } {}

      constexpr Mat(const Mat<4, 2, T>& m)
         : m_flattened{
            m[0], m[1],
            m[2], m[3],
            m[4], m[5],
            m[6], m[7]
            } {}


      constexpr std::size_t size() const { return 4 * 2; }


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
         T m_flattened[4 * 2];
         T m_data[4][2];
      };
   };
   

   template <typename T>
   inline constexpr
   Mat<4, 2, T> operator+(const Mat<4, 2, T>& ma, const Mat<4, 2, T>& mb);

   template <typename T>
   inline constexpr
   Mat<4, 2, T> operator-(const Mat<4, 2, T>& ma, const Mat<4, 2, T>& mb);
}

#include "Neat/Math/Matrix/Matrix4x2.inl"