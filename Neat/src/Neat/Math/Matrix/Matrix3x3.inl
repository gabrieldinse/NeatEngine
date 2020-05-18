#pragma once


namespace Neat
{
   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator+(const Matrix<3, 3, T>& ma, const Matrix<3, 3, T>& mb)
   {
      return Matrix<3, 3, T>(
         ma[0] + mb[0], ma[1] + mb[1], ma[2] + mb[2],
         ma[3] + mb[3], ma[4] + mb[4], ma[5] + mb[5],
         ma[6] + mb[6], ma[7] + mb[7], ma[8] + mb[8]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator-(const Matrix<3, 3, T>& ma, const Matrix<3, 3, T>& mb)
   {
      return Matrix<3, 3, T>(
         ma[0] - mb[0], ma[1] - mb[1], ma[2] - mb[2],
         ma[3] - mb[3], ma[4] - mb[4], ma[5] - mb[5],
         ma[6] - mb[6], ma[7] - mb[7], ma[8] - mb[8]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& ma, const Matrix<3, 3, T>& mb)
   {
      return Matrix<3, 3, T>(
         ma(0, 0) * mb(0, 0) + ma(0, 1) * mb(1, 0) + ma(0, 2) * mb(2, 0),
         ma(0, 0) * mb(0, 1) + ma(0, 1) * mb(1, 1) + ma(0, 2) * mb(2, 1),
         ma(0, 0) * mb(0, 2) + ma(0, 1) * mb(1, 2) + ma(0, 2) * mb(2, 2),
         ma(1, 0) * mb(0, 0) + ma(1, 1) * mb(1, 0) + ma(1, 2) * mb(2, 0),
         ma(1, 0) * mb(0, 1) + ma(1, 1) * mb(1, 1) + ma(1, 2) * mb(2, 1),
         ma(1, 0) * mb(0, 2) + ma(1, 1) * mb(1, 2) + ma(1, 2) * mb(2, 2),
         ma(2, 0) * mb(0, 0) + ma(2, 1) * mb(1, 0) + ma(2, 2) * mb(2, 0),
         ma(2, 0) * mb(0, 1) + ma(2, 1) * mb(1, 1) + ma(2, 2) * mb(2, 1),
         ma(2, 0) * mb(0, 2) + ma(2, 1) * mb(1, 2) + ma(2, 2) * mb(2, 2)
         );
   }

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator*(T scalar, const Matrix<3, 3, T>& m)
   {
      return Matrix<3, 3, T>(
         scalar * m[0], scalar * m[1], scalar * m[2],
         scalar * m[3], scalar * m[4], scalar * m[5],
         scalar * m[6], scalar * m[7], scalar * m[8]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& m, T scalar)
   {
      return scalar * m;
   }

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(const Matrix<3, 3, T>& m, const Vector<3, T>& v)
   {
      return Vector<3, T>(
         m[0] * v[0] + m[1] * v[1] + m[2] * v[2],
         m[3] * v[0] + m[4] * v[1] + m[5] * v[2], 
         m[6] * v[0] + m[7] * v[1] + m[8] * v[2]
         );
   }
}