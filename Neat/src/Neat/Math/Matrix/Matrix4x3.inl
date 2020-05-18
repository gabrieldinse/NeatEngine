#pragma once


namespace Neat
{
   template <typename T>
   inline constexpr
   Matrix<4, 3, T> operator+(const Matrix<4, 3, T>& ma, const Matrix<4, 3, T>& mb)
   {
      return Matrix<4, 3, T>(
         ma[0] + mb[0], ma[1] + mb[1], ma[2] + mb[2],
         ma[3] + mb[3], ma[4] + mb[4], ma[5] + mb[5],
         ma[6] + mb[6], ma[7] + mb[7], ma[8] + mb[8],
         ma[9] + mb[9], ma[10] + mb[10], ma[11] + mb[11]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<4, 3, T> operator-(const Matrix<4, 3, T>& ma, const Matrix<4, 3, T>& mb)
   {
      return Matrix<4, 3, T>(
         ma[0] - mb[0], ma[1] - mb[1], ma[2] - mb[2],
         ma[3] - mb[3], ma[4] - mb[4], ma[5] - mb[5],
         ma[6] - mb[6], ma[7] - mb[7], ma[8] - mb[8],
         ma[9] - mb[9], ma[10] - mb[10], ma[11] - mb[11]
         );
   }
}