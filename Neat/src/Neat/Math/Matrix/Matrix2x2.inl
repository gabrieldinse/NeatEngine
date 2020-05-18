#pragma once


namespace Neat
{
   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator+(const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb)
   {
      return Matrix<2, 2, T>(
         ma[0] + mb[0], ma[1] + mb[1],
         ma[2] + mb[2], ma[3] + mb[3]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator-(const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb)
   {
      return Matrix<2, 2, T>(
         ma[0] - mb[0], ma[1] - mb[1],
         ma[2] - mb[2], ma[3] - mb[3]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator*(const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb)
   {
      return Matrix<2, 2, T>(
         ma(0, 0) * mb(0, 0) + ma(0, 1) * mb(1, 0),
         ma(1, 0) * mb(0, 0) + ma(1, 1) * mb(1, 0),
         ma(0, 0) * mb(0, 1) + ma(0, 1) * mb(1, 1),
         ma(1, 0) * mb(0, 1) + ma(1, 1) * mb(1, 1),
         );
   }

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator*(T scalar, const Matrix<2, 2, T>& m)
   {
      return Matrix<2, 2, T>(
         scalar * m[0], scalar * m[1],
         scalar * m[2], scalar * m[3]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator*(const Matrix<2, 2, T>& m, T scalar)
   {
      return scalar * m;
   }

   template <typename T>
   inline constexpr
   Vector<2, T> operator*(const Matrix<2, 2, T>& m, const Vector<2, T>& v)
   {
      return Vector<2, T>(
         m[0] * v[0] + m[1] * v[1],
         m[2] * v[0] + m[3] * v[1]
         );
   }
}