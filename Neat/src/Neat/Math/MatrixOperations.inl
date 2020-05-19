

namespace Neat
{
   // Determinant
   template <typename T>
   T determinant(const Matrix<2, 2, T>& m)
   {
      return m[0][0] * m[1][1] - m[1][0] * m[0][1];
   }

   template <typename T>
   T determinant(const Matrix<3, 3, T>& m)
   {
      return
         + m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
         - m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
         + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
   }

   template <typename T>
   T determinant(const Matrix<4, 4, T>& m)
   {
      T sub1 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
      T sub2 = m[2][3] * m[3][1] - m[2][1] * m[3][3];
      T sub3 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
      T sub4 = m[2][3] * m[3][0] - m[2][0] * m[3][3];
      T sub5 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
      T sub6 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
      T sub7 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
      T sub8 = m[2][2] * m[3][0] - m[2][0] * m[3][2];

      T det1 = m[1][1] * sub1 + m[1][2] * sub2 + m[1][3] * sub3;
      T det2 = m[1][0] * sub1 + m[1][2] * sub4 + m[1][3] * sub5;
      T det3 = m[1][0] * sub6 + m[1][1] * sub4 + m[1][3] * sub7;
      T det4 = m[1][0] * sub3 + m[1][1] * sub8 + m[1][2] * sub7;

      return
         m[0][0] * det1 - m[0][1] * det2 + m[0][2] * det3 - m[0][3] * det4;
   }


   // Transpose
   template <typename T>
   Matrix<2, 2, T> transpose(const Matrix<2, 2, T>& m)
   {
      return Matrix<2, 2, T>(
         m[0][0], m[1][0],
         m[0][1], m[1][1]
         );
   }

   template <typename T>
   Matrix<3, 3, T> transpose(const Matrix<3, 3, T>& m)
   {
      return Matrix<3, 3, T>(
         m[0][0], m[1][0], m[2][0],
         m[0][1], m[1][1], m[2][1],
         m[0][2], m[1][2], m[2][2]
         );
   }

   template <typename T>
   Matrix<4, 4, T> transpose(const Matrix<4, 4, T>& m)
   {
      return Matrix<4, 4, T>(
         m[0][0], m[1][0], m[2][0], m[3][0],
         m[0][1], m[1][1], m[2][1], m[3][1],
         m[0][2], m[1][2], m[2][2], m[3][2],
         m[0][3], m[1][3], m[2][3], m[3][3]
         );
   }


   // Inverse
   template <typename T>
   Matrix<2, 2, T> inverse(const Matrix<2, 2, T>& m)
   {
      T one_over_determinant =
         static_cast<T>(1) / (m[0][0] * m[1][1] - m[1][0] * m[0][1]);

      return Matrix<2, 2, T>(
          m[1][1] * one_over_determinant, -m[0][1] * one_over_determinant,
         -m[1][0] * one_over_determinant,  m[0][0] * one_over_determinant
         );
   }

   template <typename T>
   Matrix<3, 3, T> inverse(const Matrix<3, 3, T>& m)
   {
      T inverse_determinant = static_cast<T>(1) / determinant(m);

      return Matrix<3, 3, T>(
          (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * inverse_determinant,
         -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * inverse_determinant,
          (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * inverse_determinant,
         -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * inverse_determinant,
          (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * inverse_determinant,
         -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * inverse_determinant,
          (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * inverse_determinant,
         -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * inverse_determinant,
          (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * inverse_determinant
         );
   }

   template <typename T>
   Matrix<4, 4, T> inverse(const Matrix<4, 4, T>& m)
   {
      T s0 = m[0][0] * m[1][1] - m[1][0] * m[0][1];
      T s1 = m[0][0] * m[1][2] - m[1][0] * m[0][2];
      T s2 = m[0][0] * m[1][3] - m[1][0] * m[0][3];
      T s3 = m[0][1] * m[1][2] - m[1][1] * m[0][2];
      T s4 = m[0][1] * m[1][3] - m[1][1] * m[0][3];
      T s5 = m[0][2] * m[1][3] - m[1][2] * m[0][3];

      T c5 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
      T c4 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
      T c3 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
      T c2 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
      T c1 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
      T c0 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

      T inverse_determinant = static_cast<T>(1) /
         (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

      return Matrix<4, 4, T>(
         ( m[1][1] * c5 - m[1][2] * c4 + m[1][3] * c3) * inverse_determinant,
         (-m[0][1] * c5 + m[0][2] * c4 - m[0][3] * c3) * inverse_determinant,
         ( m[3][1] * s5 - m[3][2] * s4 + m[3][3] * s3) * inverse_determinant,
         (-m[2][1] * s5 + m[2][2] * s4 - m[2][3] * s3) * inverse_determinant,
         (-m[1][0] * c5 + m[1][2] * c2 - m[1][3] * c1) * inverse_determinant,
         ( m[0][0] * c5 - m[0][2] * c2 + m[0][3] * c1) * inverse_determinant,
         (-m[3][0] * s5 + m[3][2] * s2 - m[3][3] * s1) * inverse_determinant,
         ( m[2][0] * s5 - m[2][2] * s2 + m[2][3] * s1) * inverse_determinant,
         ( m[1][0] * c4 - m[1][1] * c2 + m[1][3] * c0) * inverse_determinant,
         (-m[0][0] * c4 + m[0][1] * c2 - m[0][3] * c0) * inverse_determinant,
         ( m[3][0] * s4 - m[3][1] * s2 + m[3][3] * s0) * inverse_determinant,
         (-m[2][0] * s4 + m[2][1] * s2 - m[2][3] * s0) * inverse_determinant,
         (-m[1][0] * c3 + m[1][1] * c1 - m[1][2] * c0) * inverse_determinant,
         ( m[0][0] * c3 - m[0][1] * c1 + m[0][2] * c0) * inverse_determinant,
         (-m[3][0] * s3 + m[3][1] * s1 - m[3][2] * s0) * inverse_determinant,
         ( m[2][0] * s3 - m[2][1] * s1 + m[2][2] * s0) * inverse_determinant
         );
   }
}