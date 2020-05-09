

namespace Neat
{
   // Determinant
   template <typename T>
   T determinant(const Mat<2, 2, T>& m)
   {
      return m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1);
   }

   template <typename T>
   T determinant(const Mat<3, 3, T>& m)
   {
      return
         + m(0, 0) * (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2))
         - m(1, 0) * (m(0, 1) * m(2, 2) - m(2, 1) * m(0, 2))
         + m(2, 0) * (m(0, 1) * m(1, 2) - m(1, 1) * m(0, 2));
   }

   template <typename T>
   T determinant(const Mat<4, 4, T>& m)
   {
      T sub1 = m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2);
      T sub2 = m(2, 3) * m(3, 1) - m(2, 1) * m(3, 3);
      T sub3 = m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1);
      T sub4 = m(2, 3) * m(3, 0) - m(2, 0) * m(3, 3);
      T sub5 = m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0);
      T sub6 = m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1);
      T sub7 = m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0);
      T sub8 = m(2, 2) * m(3, 0) - m(2, 0) * m(3, 2);

      T det1 = m(1, 1) * sub1 + m(1, 2) * sub2 + m(1, 3) * sub3;
      T det2 = m(1, 0) * sub1 + m(1, 2) * sub4 + m(1, 3) * sub5;
      T det3 = m(1, 0) * sub6 + m(1, 1) * sub4 + m(1, 3) * sub7;
      T det4 = m(1, 0) * sub3 + m(1, 1) * sub8 + m(1, 2) * sub7;

      return
         m(0, 0) * det1 - m(0, 1) * det2 + m(0, 2) * det3 - m(0, 3) * det4;
   }


   // Transpose
   template <typename T>
   Mat<2, 2, T> transpose(const Mat<2, 2, T>& m)
   {
      return Mat<2, 2, T>(
         m(0, 0), m(1, 0),
         m(0, 1), m(1, 1)
         );
   }

   template <typename T>
   Mat<3, 2, T> transpose(const Mat<2, 3, T>& m)
   {
      return Mat<3, 2, T>(
         m(0, 0), m(1, 0),
         m(0, 1), m(1, 1),
         m(0, 2), m(1, 2)
         );
   }

   template <typename T>
   Mat<2, 3, T> transpose(const Mat<3, 2, T>& m)
   {
      return Mat<2, 3, T>(
         m(0, 0), m(1, 0), m(2, 0),
         m(0, 1), m(1, 1), m(2, 1)
         );
   }

   template <typename T>
   Mat<3, 3, T> transpose(const Mat<3, 3, T>& m)
   {
      return Mat<3, 3, T>(
         m(0, 0), m(1, 0), m(2, 0),
         m(0, 1), m(1, 1), m(2, 1),
         m(0, 2), m(1, 2), m(2, 2)
         );
   }

   template <typename T>
   Mat<2, 4, T> transpose(const Mat<4, 2, T>& m)
   {
      return Mat<2, 4, T>(
         m(0, 0), m(1, 0), m(2, 0), m(3, 0),
         m(0, 1), m(1, 1), m(2, 1), m(3, 1)
         );
   }

   template <typename T>
   Mat<4, 2, T> transpose(const Mat<2, 4, T>& m)
   {
      return Mat<4, 2, T>(
         m(0, 0), m(1, 0),
         m(0, 1), m(1, 1),
         m(0, 2), m(1, 2),
         m(0, 3), m(1, 3)
         );
   }

   template <typename T>
   Mat<3, 4, T> transpose(const Mat<4, 3, T>& m)
   {
      return Mat<3, 4, T>(
         m(0, 0), m(1, 0), m(2, 0), m(3, 0),
         m(0, 1), m(1, 1), m(2, 1), m(3, 1),
         m(0, 2), m(1, 2), m(2, 2), m(3, 2)
         );
   }

   template <typename T>
   Mat<4, 3, T> transpose(const Mat<3, 4, T>& m)
   {
      return Mat<4, 3, T>(
         m(0, 0), m(1, 0), m(2, 0),
         m(0, 1), m(1, 1), m(2, 1),
         m(0, 2), m(1, 2), m(2, 2),
         m(0, 3), m(1, 3), m(2, 3)
         );
   }

   template <typename T>
   Mat<4, 4, T> transpose(const Mat<4, 4, T>& m)
   {
      return Mat<4, 4, T>(
         m(0, 0), m(1, 0), m(2, 0), m(3, 0),
         m(0, 1), m(1, 1), m(2, 1), m(3, 1),
         m(0, 2), m(1, 2), m(2, 2), m(3, 2),
         m(0, 3), m(1, 3), m(2, 3), m(3, 3)
         );
   }


   // Inverse
   template <typename T>
   Mat<2, 2, T> inverse(const Mat<2, 2, T>& m)
   {
      T one_over_determinant =
         static_cast<T>(1) / (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1));

      return Mat<2, 2, T>(
         m(1, 1) * one_over_determinant, -m(0, 1) * one_over_determinant,
         -m(1, 0) * one_over_determinant, m(0, 0) * one_over_determinant
         );
   }

   template <typename T>
   Mat<3, 3, T> inverse(const Mat<3, 3, T>& m)
   {
      T one_over_determinant = static_cast<T>(1) / determinant(m);

      return Mat<3, 3, T>(
          (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) * one_over_determinant,
         -(m(0, 1) * m(2, 2) - m(2, 1) * m(0, 2)) * one_over_determinant,
          (m(0, 1) * m(1, 2) - m(1, 1) * m(0, 2)) * one_over_determinant,
         -(m(1, 0) * m(2, 2) - m(2, 0) * m(1, 2)) * one_over_determinant,
          (m(0, 0) * m(2, 2) - m(2, 0) * m(0, 2)) * one_over_determinant,
         -(m(0, 0) * m(1, 2) - m(1, 0) * m(0, 2)) * one_over_determinant,
          (m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1)) * one_over_determinant,
         -(m(0, 0) * m(2, 1) - m(2, 0) * m(0, 1)) * one_over_determinant,
          (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1)) * one_over_determinant
         );
   }

   template <typename T>
   Mat<4, 4, T> inverse(const Mat<4, 4, T>& m)
   {
      T pre_inv0 =
         m[5] * m[10] * m[15] -
         m[5] * m[11] * m[14] -
         m[9] * m[6] * m[15] +
         m[9] * m[7] * m[14] +
         m[13] * m[6] * m[11] -
         m[13] * m[7] * m[10];

      T pre_inv1 =
         -m[1] * m[10] * m[15] +
         m[1] * m[11] * m[14] +
         m[9] * m[2] * m[15] -
         m[9] * m[3] * m[14] -
         m[13] * m[2] * m[11] +
         m[13] * m[3] * m[10];

      T pre_inv2 =
         m[1] * m[6] * m[15] -
         m[1] * m[7] * m[14] -
         m[5] * m[2] * m[15] +
         m[5] * m[3] * m[14] +
         m[13] * m[2] * m[7] -
         m[13] * m[3] * m[6];

      T pre_inv3 =
         -m[1] * m[6] * m[11] +
         m[1] * m[7] * m[10] +
         m[5] * m[2] * m[11] -
         m[5] * m[3] * m[10] -
         m[9] * m[2] * m[7] +
         m[9] * m[3] * m[6];

      T pre_inv4 =
         -m[4] * m[10] * m[15] +
         m[4] * m[11] * m[14] +
         m[8] * m[6] * m[15] -
         m[8] * m[7] * m[14] -
         m[12] * m[6] * m[11] +
         m[12] * m[7] * m[10];

      T pre_inv5 =
         m[0] * m[10] * m[15] -
         m[0] * m[11] * m[14] -
         m[8] * m[2] * m[15] +
         m[8] * m[3] * m[14] +
         m[12] * m[2] * m[11] -
         m[12] * m[3] * m[10];

      T pre_inv6 =
         -m[0] * m[6] * m[15] +
         m[0] * m[7] * m[14] +
         m[4] * m[2] * m[15] -
         m[4] * m[3] * m[14] -
         m[12] * m[2] * m[7] +
         m[12] * m[3] * m[6];

      T pre_inv7 =
         m[0] * m[6] * m[11] -
         m[0] * m[7] * m[10] -
         m[4] * m[2] * m[11] +
         m[4] * m[3] * m[10] +
         m[8] * m[2] * m[7] -
         m[8] * m[3] * m[6];

      T pre_inv8 =
         m[4] * m[9] * m[15] -
         m[4] * m[11] * m[13] -
         m[8] * m[5] * m[15] +
         m[8] * m[7] * m[13] +
         m[12] * m[5] * m[11] -
         m[12] * m[7] * m[9];

      T pre_inv9 =
         -m[0] * m[9] * m[15] +
         m[0] * m[11] * m[13] +
         m[8] * m[1] * m[15] -
         m[8] * m[3] * m[13] -
         m[12] * m[1] * m[11] +
         m[12] * m[3] * m[9];

      T pre_inv10 =
         m[0] * m[5] * m[15] -
         m[0] * m[7] * m[13] -
         m[4] * m[1] * m[15] +
         m[4] * m[3] * m[13] +
         m[12] * m[1] * m[7] -
         m[12] * m[3] * m[5];

      T pre_inv11 =
         -m[0] * m[5] * m[11] +
         m[0] * m[7] * m[9] +
         m[4] * m[1] * m[11] -
         m[4] * m[3] * m[9] -
         m[8] * m[1] * m[7] +
         m[8] * m[3] * m[5];

      T pre_inv12 =
         -m[4] * m[9] * m[14] +
         m[4] * m[10] * m[13] +
         m[8] * m[5] * m[14] -
         m[8] * m[6] * m[13] -
         m[12] * m[5] * m[10] +
         m[12] * m[6] * m[9];

      T pre_inv13 =
         m[0] * m[9] * m[14] -
         m[0] * m[10] * m[13] -
         m[8] * m[1] * m[14] +
         m[8] * m[2] * m[13] +
         m[12] * m[1] * m[10] -
         m[12] * m[2] * m[9];

      T pre_inv14 =
         -m[0] * m[5] * m[14] +
         m[0] * m[6] * m[13] +
         m[4] * m[1] * m[14] -
         m[4] * m[2] * m[13] -
         m[12] * m[1] * m[6] +
         m[12] * m[2] * m[5];

      T pre_inv15 =
         m[0] * m[5] * m[10] -
         m[0] * m[6] * m[9] -
         m[4] * m[1] * m[10] +
         m[4] * m[2] * m[9] +
         m[8] * m[1] * m[6] -
         m[8] * m[2] * m[5];

      T one_over_determinant = static_cast<T>(1) / (
           m[0] * pre_inv0 + m[1] * pre_inv4
         + m[2] * pre_inv8 + m[3] * pre_inv12);

      return Mat<4, 4, T>(
         pre_inv0 * one_over_determinant,
         pre_inv1 * one_over_determinant,
         pre_inv2 * one_over_determinant,
         pre_inv3 * one_over_determinant,
         pre_inv4 * one_over_determinant,
         pre_inv5 * one_over_determinant,
         pre_inv6 * one_over_determinant,
         pre_inv7 * one_over_determinant,
         pre_inv8 * one_over_determinant,
         pre_inv9 * one_over_determinant,
         pre_inv10 * one_over_determinant,
         pre_inv11 * one_over_determinant,
         pre_inv12 * one_over_determinant,
         pre_inv13 * one_over_determinant,
         pre_inv14 * one_over_determinant,
         pre_inv15 * one_over_determinant
         );
   }
}