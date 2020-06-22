#include "Neat/Math/Constants.h"
#include "Neat/Math/Trigonometric.h"


namespace Neat
{
   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesX(const T& angleX)
   {
      T cos_x = cos(angleX);
      T sin_x = sin(angleX);

      return Matrix<4, 4, T>(
         one<T>, zero<T>, zero<T>, zero<T>,
         zero<T>, cos_x, sin_x, zero<T>,
         zero<T>, -sin_x, cos_x, zero<T>,
         zero<T>, zero<T>, zero<T>, one<T>);
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesY(const T& angle)
   {
      T cos_y = cos(angleY);
      T sin_y = sin(angleY);

      return Matrix<4, 4, T>(
         cos_y, zero<T>, -sin_y, zero<T>,
         zero<T>, one<T>, zero<T>, zero<T>,
         sin_y, zero<T>, cos_y, zero<T>,
         zero<T>, zero<T>, zero<T>, one<T>);
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesZ(const T& angleZ)
   {
      T cos_z = cos(angleZ);
      T sin_z = sin(angleZ);

      return Matrix<4, 4, T>(
         cos_z, sin_z, zero<T>, zero<T>,
         -sin_z, cos_z, zero<T>, zero<T>,
         zero<T>, zero<T>, one<T>, zero<T>,
         zero<T>, zero<T>, zero<T>, one<T>);
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesXYZ(const T& angle1, const T& angle2,
      const T& angle3 )
   {
      T c1 = cos(-angle1);
      T c2 = cos(-angle2);
      T c3 = cos(-angle3);
      T s1 = sin(-angle1);
      T s2 = sin(-angle2);
      T s3 = sin(-angle3);

      Matrix<4, 4, T> result;
      result[0][0] = c2 * c3;
      result[0][1] = -c1 * s3 + s1 * s2 * c3;
      result[0][2] = s1 * s3 + c1 * s2 * c3;
      result[1][0] = c2 * s3;
      result[1][1] = c1 * c3 + s1 * s2 * s3;
      result[1][2] = -s1 * c3 + c1 * s2 * s3;
      result[2][0] = -s2;
      result[2][1] = s1 * c2;
      result[2][2] = c1 * c2;

      return result;
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesYXZ(const T& yaw, const T& pitch,
      const T& roll)
   {
      T tmp_ch = cos(yaw);
      T tmp_sh = sin(yaw);
      T tmp_cp = cos(pitch);
      T tmp_sp = sin(pitch);
      T tmp_cb = cos(roll);
      T tmp_sb = sin(roll);

      Matrix<4, 4, T> result;
      result[0][0] = tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
      result[0][1] = tmp_sb * tmp_cp;
      result[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
      result[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
      result[1][1] = tmp_cb * tmp_cp;
      result[1][2] = tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
      result[2][0] = tmp_sh * tmp_cp;
      result[2][1] = -tmp_sp;
      result[2][2] = tmp_ch * tmp_cp;

      return result;
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesXZX(const T& angle1, const T& angle2,
      const T& angle3)
   {
      T c1 = cos(angle1);
      T s1 = sin(angle1);
      T c2 = cos(angle2);
      T s2 = sin(angle2);
      T c3 = cos(angle3);
      T s3 = sin(angle3);

      Matrix<4, 4, T> result;
      result[0][0] = c2;
      result[0][1] = c1 * s2;
      result[0][2] = s1 * s2;
      result[1][0] = -c3 * s2;
      result[1][1] = c1 * c2 * c3 - s1 * s3;
      result[1][2] = c1 * s3 + c2 * c3 * s1;
      result[2][0] = s2 * s3;
      result[2][1] = -c3 * s1 - c1 * c2 * s3;
      result[2][2] = c1 * c3 - c2 * s1 * s3;

      return result;
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesXYX(const T& angle1, const T& angle2,
      const T& angle)
   {
      T c1 = cos(angle1);
      T s1 = sin(angle1);
      T c2 = cos(angle2);
      T s2 = sin(angle2);
      T c3 = cos(angle3);
      T s3 = sin(angle3);

      Matrix<4, 4, T> result;
      result[0][0] = c2;
      result[0][1] = s1 * s2;
      result[0][2] = -c1 * s2;
      result[1][0] = s2 * s3;
      result[1][1] = c1 * c3 - c2 * s1 * s3;
      result[1][2] = c3 * s1 + c1 * c2 * s3;
      result[2][0] = c3 * s2;
      result[2][1] = -c1 * s3 - c2 * c3 * s1;
      result[2][2] = c1 * c2 * c3 - s1 * s3;

      return result;
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesYXY(const T& angle1, const T& angle2,
      const T& angle3)
   {
      T c1 = cos(angle1);
      T s1 = sin(angle1);
      T c2 = cos(angle2);
      T s2 = sin(angle2);
      T c3 = cos(angle3);
      T s3 = sin(angle3);

      Matrix<4, 4, T> result;
      result[0][0] = c1 * c3 - c2 * s1 * s3;
      result[0][1] = s2 * s3;
      result[0][2] = -c3 * s1 - c1 * c2 * s3;
      result[1][0] = s1 * s2;
      result[1][1] = c2;
      result[1][2] = c1 * s2;
      result[2][0] = c1 * s3 + c2 * c3 * s1;
      result[2][1] = -c3 * s2;
      result[2][2] = c1 * c2 * c3 - s1 * s3;

      return result;
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesYZY(const T& angle1, const T& angle2,
      const T& angle3)
   {
      T c1 = cos(angle1);
      T s1 = sin(angle1);
      T c2 = cos(angle2);
      T s2 = sin(angle2);
      T c3 = cos(angle3);
      T s3 = sin(angle3);

      Matrix<4, 4, T> result;
      result[0][0] = c1 * c2 * c3 - s1 * s3;
      result[0][1] = c3 * s2;
      result[0][2] = -c1 * s3 - c2 * c3 * s1;
      result[1][0] = -c1 * s2;
      result[1][1] = c2;
      result[1][2] = s1 * s2;
      result[2][0] = c3 * s1 + c1 * c2 * s3;
      result[2][1] = s2 * s3;
      result[2][2] = c1 * c3 - c2 * s1 * s3;

      return result;
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesZYZ(const T& angle1, const T& angle2,
      const T& angle3)
   {
      T c1 = cos(angle1);
      T s1 = sin(angle1);
      T c2 = cos(angle2);
      T s2 = sin(angle2);
      T c3 = cos(angle3);
      T s3 = sin(angle3);

      Matrix<4, 4, T> result;
      result[0][0] = c1 * c2 * c3 - s1 * s3;
      result[0][1] = c1 * s3 + c2 * c3 * s1;
      result[0][2] = -c3 * s2;
      result[1][0] = -c3 * s1 - c1 * c2 * s3;
      result[1][1] = c1 * c3 - c2 * s1 * s3;
      result[1][2] = s2 * s3;
      result[2][0] = c1 * s2;
      result[2][1] = s1 * s2;
      result[2][2] = c2;

      return result;
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesZXZ(const T& angle1, const T& angle2,
      const T& angle3)
   {
      T c1 = cos(angle1);
      T s1 = sin(angle1);
      T c2 = cos(angle2);
      T s2 = sin(angle2);
      T c3 = cos(angle3);
      T s3 = sin(angle3);

      Matrix<4, 4, T> result;
      result[0][0] = c1 * c3 - c2 * s1 * s3;
      result[0][1] = c3 * s1 + c1 * c2 * s3;
      result[0][2] = s2 * s3;
      result[1][0] = -c1 * s3 - c2 * c3 * s1;
      result[1][1] = c1 * c2 * c3 - s1 * s3;
      result[1][2] = c3 * s2;
      result[2][0] = s1 * s2;
      result[2][1] = -c1 * s2;
      result[2][2] = c2;

      return result;
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesXZY(const T& angle1, const T& angle2,
      const T& angle3)
   {
      T c1 = cos(angle1);
      T s1 = sin(angle1);
      T c2 = cos(angle2);
      T s2 = sin(angle2);
      T c3 = cos(angle3);
      T s3 = sin(angle3);

      Matrix<4, 4, T> result;
      result[0][0] = c2 * c3;
      result[0][1] = s1 * s3 + c1 * c3 * s2;
      result[0][2] = c3 * s1 * s2 - c1 * s3;
      result[1][0] = -s2;
      result[1][1] = c1 * c2;
      result[1][2] = c2 * s1;
      result[2][0] = c2 * s3;
      result[2][1] = c1 * s2 * s3 - c3 * s1;
      result[2][2] = c1 * c3 + s1 * s2 * s3;

      return result;
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesYZX(const T& angle1, const T& angle2,
      const T& angle3)
   {
      T c1 = cos(angle1);
      T s1 = sin(angle1);
      T c2 = cos(angle2);
      T s2 = sin(angle2);
      T c3 = cos(angle3);
      T s3 = sin(angle3);

      Matrix<4, 4, T> result;
      result[0][0] = c1 * c2;
      result[0][1] = s2;
      result[0][2] = -c2 * s1;
      result[1][0] = s1 * s3 - c1 * c3 * s2;
      result[1][1] = c2 * c3;
      result[1][2] = c1 * s3 + c3 * s1 * s2;
      result[2][0] = c3 * s1 + c1 * s2 * s3;
      result[2][1] = -c2 * s3;
      result[2][2] = c1 * c3 - s1 * s2 * s3;

      return result;
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesZYX(const T& angle1, const T& angle2,
      const T& angle3)
   {
      T c1 = cos(angle1);
      T s1 = sin(angle1);
      T c2 = cos(angle2);
      T s2 = sin(angle2);
      T c3 = cos(angle3);
      T s3 = sin(angle3);

      Matrix<4, 4, T> result;
      result[0][0] = c1 * c2;
      result[0][1] = c2 * s1;
      result[0][2] = -s2;
      result[1][0] = c1 * s2 * s3 - c3 * s1;
      result[1][1] = c1 * c3 + s1 * s2 * s3;
      result[1][2] = c2 * s3;
      result[2][0] = s1 * s3 + c1 * c3 * s2;
      result[2][1] = c3 * s1 * s2 - c1 * s3;
      result[2][2] = c2 * c3;

      return result;
   }

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesZXY(const T& angle1, const T& angle2,
      const T& angle3)
   {
      T c1 = cos(angle1);
      T s1 = sin(angle1);
      T c2 = cos(angle2);
      T s2 = sin(angle2);
      T c3 = cos(angle3);
      T s3 = sin(angle3);

      Matrix<4, 4, T> result;
      result[0][0] = c1 * c3 - s1 * s2 * s3;
      result[0][1] = c3 * s1 + c1 * s2 * s3;
      result[0][2] = -c2 * s3;
      result[1][0] = -c2 * s1;
      result[1][1] = c1 * c2;
      result[1][2] = s2;
      result[2][0] = c1 * s3 + c3 * s1 * s2;
      result[2][1] = s1 * s3 - c1 * c3 * s2;
      result[2][2] = c2 * c3;

      return result;
   }

   template <typename T>
   inline Matrix<4, 4, T> yawPitchRoll(const T& yaw, const T& pitch,
      const T& roll)
   {
      T cy = cos(yaw);
      T sy = sin(yaw);
      T cp = cos(pitch);
      T sp = sin(pitch);
      T cr = cos(roll);
      T sr = sin(roll);

      Matrix<4, 4, T> result;
      result[0][0] = cy * cr + sy * sp * sr;
      result[0][1] = sr * cp;
      result[0][2] = -sy * cr + cy * sp * sr;
      result[1][0] = -cy * sr + sy * sp * cr;
      result[1][1] = cr * cp;
      result[1][2] = sr * sy + cy * sp * cr;
      result[2][0] = sy * cp;
      result[2][1] = -sp;
      result[2][2] = cy * cp;

      return result;
   }
}