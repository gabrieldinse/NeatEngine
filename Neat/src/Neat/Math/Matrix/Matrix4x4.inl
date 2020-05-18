#pragma once


namespace Neat
{
   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator+(const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb)
   {
      return Matrix<4, 4, T>(
         ma[0] + mb[0], ma[1] + mb[1], ma[2] + mb[2], ma[3] + mb[3],
         ma[4] + mb[4], ma[5] + mb[5], ma[6] + mb[6], ma[7] + mb[7],
         ma[8] + mb[8], ma[9] + mb[9], ma[10] + mb[10], ma[11] + mb[11],
         ma[12] + mb[12], ma[13] + mb[13], ma[14] + mb[14], ma[15] + mb[15]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator-(const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb)
   {
      return Matrix<4, 4, T>(
         ma[0] - mb[0], ma[1] - mb[1], ma[2] - mb[2], ma[3] - mb[3],
         ma[4] - mb[4], ma[5] - mb[5], ma[6] - mb[6], ma[7] - mb[7],
         ma[8] - mb[8], ma[9] - mb[9], ma[10] - mb[10], ma[11] - mb[11],
         ma[12] - mb[12], ma[13] - mb[13], ma[14] - mb[14], ma[15] - mb[15]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator*(const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb)
   {
      return Matrix<4, 4, T>(
         ma(0, 0) * mb(0, 0) + ma(0, 1) * mb(1, 0) + ma(0, 2) * mb(2, 0) + ma(0, 3) * mb(3, 0),
         ma(0, 0) * mb(0, 1) + ma(0, 1) * mb(1, 1) + ma(0, 2) * mb(2, 1) + ma(0, 3) * mb(3, 1),
         ma(0, 0) * mb(0, 2) + ma(0, 1) * mb(1, 2) + ma(0, 2) * mb(2, 2) + ma(0, 3) * mb(3, 2),
         ma(0, 0) * mb(0, 3) + ma(0, 1) * mb(1, 3) + ma(0, 2) * mb(2, 3) + ma(0, 3) * mb(3, 3),
         ma(1, 0) * mb(0, 0) + ma(1, 1) * mb(1, 0) + ma(1, 2) * mb(2, 0) + ma(1, 3) * mb(3, 0),
         ma(1, 0) * mb(0, 1) + ma(1, 1) * mb(1, 1) + ma(1, 2) * mb(2, 1) + ma(1, 3) * mb(3, 1),
         ma(1, 0) * mb(0, 2) + ma(1, 1) * mb(1, 2) + ma(1, 2) * mb(2, 2) + ma(1, 3) * mb(3, 2),
         ma(1, 0) * mb(0, 3) + ma(1, 1) * mb(1, 3) + ma(1, 2) * mb(2, 3) + ma(1, 3) * mb(3, 3),
         ma(2, 0) * mb(0, 0) + ma(2, 1) * mb(1, 0) + ma(2, 2) * mb(2, 0) + ma(2, 3) * mb(3, 0),
         ma(2, 0) * mb(0, 1) + ma(2, 1) * mb(1, 1) + ma(2, 2) * mb(2, 1) + ma(2, 3) * mb(3, 1),
         ma(2, 0) * mb(0, 2) + ma(2, 1) * mb(1, 2) + ma(2, 2) * mb(2, 2) + ma(2, 3) * mb(3, 2),
         ma(2, 0) * mb(0, 3) + ma(2, 1) * mb(1, 3) + ma(2, 2) * mb(2, 3) + ma(2, 3) * mb(3, 3),
         ma(3, 0) * mb(0, 0) + ma(3, 1) * mb(1, 0) + ma(3, 2) * mb(2, 0) + ma(3, 3) * mb(3, 0),
         ma(3, 0) * mb(0, 1) + ma(3, 1) * mb(1, 1) + ma(3, 2) * mb(2, 1) + ma(3, 3) * mb(3, 1),
         ma(3, 0) * mb(0, 2) + ma(3, 1) * mb(1, 2) + ma(3, 2) * mb(2, 2) + ma(3, 3) * mb(3, 2),
         ma(3, 0) * mb(0, 3) + ma(3, 1) * mb(1, 3) + ma(3, 2) * mb(2, 3) + ma(3, 3) * mb(3, 3)
         );
   }

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator*(T scalar, const Matrix<4, 4, T>& m)
   {
      return Matrix<4, 4, T>(
         scalar * m[0],  scalar * m[1],  scalar * m[2],  scalar * m[3],
         scalar * m[4],  scalar * m[5],  scalar * m[6],  scalar * m[7],
         scalar * m[8],  scalar * m[9],  scalar * m[10], scalar * m[11],
         scalar * m[12], scalar * m[13], scalar * m[14], scalar * m[15]
         );
   }

   template <typename T>
   inline constexpr
      Matrix<4, 4, T> operator*(const Matrix<4, 4, T>& m, T scalar)
   {
      return scalar * m;
   }



   template <typename T>
   inline constexpr
   Vector<4, T> operator*(const Matrix<4, 4, T>& m, const Vector<4, T>& v)
   {
      return Vector<4, T>(
         m[0]  * v[0] + m[1]  * v[1] + m[2]  * v[2] + m[3]  * v[3],
         m[4]  * v[0] + m[5]  * v[1] + m[6]  * v[2] + m[7]  * v[3],
         m[8]  * v[0] + m[9]  * v[1] + m[10] * v[2] + m[11] * v[3],
         m[12] * v[0] + m[13] * v[1] + m[14] * v[2] + m[15] * v[3]
         );
   }
}