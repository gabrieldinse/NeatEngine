#pragma once


namespace Neat
{
   template <typename T>
   inline constexpr
   Mat<3, 2, T> operator+(const Mat<3, 2, T>& ma, const Mat<3, 2, T>& mb)
   {
      return Mat<3, 2, T>(
         ma[0] + mb[0], ma[1] + mb[1],
         ma[2] + mb[2], ma[3] + mb[3],
         ma[4] + mb[4], ma[5] + mb[5]
         );
   }

   template <typename T>
   inline constexpr
   Mat<3, 2, T> operator-(const Mat<3, 2, T>& ma, const Mat<3, 2, T>& mb)
   {
      return Mat<3, 2, T>(
         ma[0] - mb[0], ma[1] - mb[1],
         ma[2] - mb[2], ma[3] - mb[3],
         ma[4] - mb[4], ma[5] - mb[5]
         );
   }
}