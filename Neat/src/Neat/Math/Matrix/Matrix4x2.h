#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"


namespace Neat
{
   template <typename T>
   struct Mat<4, 2, T>
   {
      constexpr Mat() : flattened{} {}

      constexpr Mat(
         T m00, T m01,
         T m10, T m11,
         T m20, T m21,
         T m30, T m31)
         : flattened{
            m00, m01,
            m10, m11,
            m20, m21,
            m30, m31
            } {}

      constexpr explicit Mat(T scalar)
         : flattened{
            scalar, static_cast<T>(0),
            static_cast<T>(0), scalar,
            static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0)
            } {}

      constexpr Mat(const Mat<4, 2, T>& m)
         : flattened{
            m[0], m[1],
            m[2], m[3],
            m[4], m[5],
            m[6], m[7]
            } {}


      constexpr SizeType size() const { return 4 * 2; }


      // Elements acessing
      constexpr T* dataPointer() { return this->flattened; }
      constexpr const T* dataPointer() const { return this->flattened; }

      constexpr T& operator[](SizeType pos) { return this->flattened[pos]; }
      constexpr const T& operator[](SizeType pos) const { return this->flattened[pos]; }

      constexpr T& operator()(SizeType i, SizeType j) { return this->data[i][j]; }
      constexpr const T& operator()(SizeType i, SizeType j) const { return this->data[i][j]; }
      constexpr T& operator()(SizeType i) { return this->flattened[i]; }
      constexpr const T& operator()(SizeType i) const { return this->flattened[i]; }

   private:
      // Class data
      union
      {
         T flattened[4 * 2];
         T data[4][2];
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