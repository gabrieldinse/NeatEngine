#include <cmath>

#include "Neat/Math/Constants.h"
#include "Neat/Math/Trigonometric.h"


namespace Neat
{
   template <typename T>
   Matrix<4, 4, T> translate(const Vector<3, T>& v)
   {
      return Matrix<4, 4, T>(
          one<T>, zero<T>, zero<T>, v.x,
         zero<T>,  one<T>, zero<T>, v.y,
         zero<T>, zero<T>,  one<T>, v.z,
         zero<T>, zero<T>, zero<T>, one<T>
         );
   }

   template <typename T>
   Matrix<4, 4, T> translate(const Matrix<4, 4, T>& m, const Vector<3, T>& v)
   {
      Matrix<4, 4, T> result(m);
      result[0][3] = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + m[0][3];
      result[1][3] = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + m[1][3];
      result[2][3] = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + m[2][3];
      result[3][3] = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + m[3][3];

      return result;
   }

   template <typename T>
   Matrix<4, 4, T> rotate(const T& angleRadians, const Vector<3, T>& v)
   {
      T c = cos(angleRadians);
      T s = sin(angleRadians);
      Vector<3, T> axis(normalize(v));

      T one_minus_c_x = (one<T> - c) * axis.x;
      T one_minus_c_y = (one<T> - c) * axis.y;
      T one_minus_c_z = (one<T> - c) * axis.z;

      T x2c = one_minus_c_x * axis.x;
      T xyc = one_minus_c_x * axis.y;
      T xzc = one_minus_c_x * axis.z;
      T y2c = one_minus_c_y * axis.y;
      T yzc = one_minus_c_y * axis.z;
      T z2c = one_minus_c_z * axis.z;

      T r00 = x2c + c;
      T r10 = xyc + axis.z * s;
      T r20 = xzc - axis.y * s;
      T r01 = xyc - axis.z * s;
      T r11 = y2c + c;
      T r21 = yzc + axis.x * s;
      T r02 = xzc + axis.y * s;
      T r12 = yzc - axis.x * s;
      T r22 = z2c + c;

      return Matrix<4, 4, T>(
         r00, r01, r02, zero<T>,
         r10, r11, r12, zero<T>,
         r20, r21, r22, zero<T>,
         zero<T>, zero<T>, zero<T>, one<T>
         );
   }

   template <typename T>
   Matrix<4, 4, T> rotate(const Matrix<4, 4, T>& m, const T& angleRadians,
      const Vector<3, T>& v)
   {
      T c = cos(angleRadians);
      T s = sin(angleRadians);
      Vector<3, T> axis(normalize(v));

      T one_minus_c_x = (one<T> - c) * axis.x;
      T one_minus_c_y = (one<T> - c) * axis.y;
      T one_minus_c_z = (one<T> - c) * axis.z;

      T x2c = one_minus_c_x * axis.x;
      T xyc = one_minus_c_x * axis.y;
      T xzc = one_minus_c_x * axis.z;
      T y2c = one_minus_c_y * axis.y;
      T yzc = one_minus_c_y * axis.z;
      T z2c = one_minus_c_z * axis.z;

      T r00 = x2c + c;
      T r10 = xyc + axis.z * s;
      T r20 = xzc - axis.y * s;
      T r01 = xyc - axis.z * s;
      T r11 = y2c + c;
      T r21 = yzc + axis.x * s;
      T r02 = xzc + axis.y * s;
      T r12 = yzc - axis.x * s;
      T r22 = z2c + c;

      return Matrix<4, 4, T>(
         r00 * m[0][0] + r01 * m[1][0] + r02 * m[2][0],
         r00 * m[0][1] + r01 * m[1][1] + r02 * m[2][1],
         r00 * m[0][2] + r01 * m[1][2] + r02 * m[2][2],
         r00 * m[0][3] + r01 * m[1][3] + r02 * m[2][3],
         r10 * m[0][0] + r11 * m[1][0] + r12 * m[2][0],
         r10 * m[0][1] + r11 * m[1][1] + r12 * m[2][1],
         r10 * m[0][2] + r11 * m[1][2] + r12 * m[2][2],
         r10 * m[0][3] + r11 * m[1][3] + r12 * m[2][3],
         r20 * m[0][0] + r21 * m[1][0] + r22 * m[2][0],
         r20 * m[0][1] + r21 * m[1][1] + r22 * m[2][1],
         r20 * m[0][2] + r21 * m[1][2] + r22 * m[2][2],
         r20 * m[0][3] + r21 * m[1][3] + r22 * m[2][3],
         zero<T>,
         zero<T>,
         zero<T>,
         m(3, 3)
         );
   }

   template <typename T>
   Matrix<4, 4, T> scale(const Vector<3, T>& v)
   {
      return Matrix<4, 4, T>(
             v.x, zero<T>, zero<T>, zero<T>,
         zero<T>,     v.y, zero<T>, zero<T>,
         zero<T>, zero<T>,     v.z, zero<T>,
         zero<T>, zero<T>, zero<T>, one<T>
         );
   }

   template <typename T>
   Matrix<4, 4, T> scale(const Matrix<4, 4, T>& m, const Vector<3, T>& v)
   {
      return Matrix<4, 4, T>(
         m[0][0] * v.x, m[0][1] * v.y, m[0][2] * v.z, m[0][3],
         m[1][0] * v.x, m[1][1] * v.y, m[1][2] * v.z, m[1][3],
         m[2][0] * v.x, m[2][1] * v.y, m[2][2] * v.z, m[2][3],
         m[3][0] * v.x, m[3][1] * v.y, m[3][2] * v.z, m[3][3]
         );
   }
}