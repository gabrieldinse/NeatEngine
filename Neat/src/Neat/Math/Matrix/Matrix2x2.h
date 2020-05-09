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
      Mat() : flattened{} {}


      // Basic constructors
      constexpr
      Mat(
         T m00, T m01,
         T m10, T m11)
         : flattened{
            m00, m01,
            m10, m11
         }
      {}

      constexpr explicit
      Mat(T scalar)
         : flattened{
            scalar, static_cast<T>(0),
            static_cast<T>(0), scalar
            } {}

      constexpr
      Mat(const Mat<2, 2, T>& m)
         : flattened{
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
         : flattened{
            static_cast<T(m00), static_cast<T(m01),
            static_cast<T(m10), static_cast<T(m11)
         }
      {}

      template <typename U>
      constexpr explicit
      Mat(const Mat<2, 2, U>& m)
         : flattened{
            static_cast<T(m[0]), static_cast<T(m[1]),
            static_cast<T(m[2]), static_cast<T(m[3])
            } {}

      template <typename U>
      constexpr explicit
      Mat(const Mat<4, 4, U>& m)
         : flattened{
            static_cast<T(m[0]), static_cast<T(m[1]),
            static_cast<T(m[4]), static_cast<T(m[5])
            } {}

      template <typename U>
      constexpr explicit
      Mat(const Mat<3, 3, U>& m)
         : flattened{
            static_cast<T(m[0]), static_cast<T(m[1]),
            static_cast<T(m[3]), static_cast<T(m[4])
            } {}


      constexpr SizeType size() const { return 2 * 2; }

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
         T flattened[2 * 2];
         T data[2][2];
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