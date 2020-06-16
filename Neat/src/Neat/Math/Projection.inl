#include "Neat/Math/VectorOperations.h"


namespace Neat
{
   template <typename T>
   Matrix<4, 4, T> orthographic(const T& left, const T& right,
      const T& bottom, const T& top, const T& near, const T& far)
   {
      Matrix<4, 4, T> result(static_cast<T>(1));

      result[0][0] = static_cast<T>(2) / (right - left);
      result[1][1] = static_cast<T>(2) / (top - bottom);
      result[2][2] = -static_cast<T>(2) / (far - near);
      result[0][3] = -(right + left) / (right - left);
      result[1][3] = -(top + bottom) / (top - bottom);
      result[2][3] = -(far + near) / (far - near);

      return result;
   }

   template <typename T>
   Matrix<4, 4, T> perspective(const T& fieldOfView, const T& aspectRatio,
      const T& near, const T& far)
   {  
      Matrix<4, 4, T> result(static_cast<T>(1));

      T tan_half_fov = std::tan(fieldOfView / static_cast<T>(2));
      result[0][0] = static_cast<T>(1) / (aspectRatio * tan_half_fov);
      result[1][1] = static_cast<T>(1) / tan_half_fov;
      result[2][2] = -(far + near) / (far - near);
      result[2][3] = -static_cast<T>(2) * far * near / (far - near);
      result[3][2] = -static_cast<T>(1);
      result[3][3] = static_cast<T>(0);

      return result;
   }


   template<typename T>
   Matrix<4, 4, T> lookAtRH(const Vector<3, T>& eye,
      const Vector<3, T>& target, const Vector<3, T>& upDirection)
   {
      Vector<3, T> front(normalize(target - eye));
      Vector<3, T> right(normalize(cross(front, upDirection)));
      Vector<3, T> up(cross(right, front));

      return Matrix<4, 4, T>(
          right.x,  right.y,  right.z, -dot(eye, right),
             up.x,     up.y,     up.z, -dot(eye, up),
         -front.x, -front.y, -front.z, dot(eye, front),
         0, 0, 0, 1
         );
   }

   template<typename T>
   Matrix<4, 4, T> lookAtLH(const Vector<3, T>& eye,
      const Vector<3, T>& target, const Vector<3, T>& upDirection)
   {
      Vector<3, T> front(normalize(target - eye));
      Vector<3, T> right(normalize(cross(upDirection, front)));
      Vector<3, T> up(cross(front, right));

      return Matrix<4, 4, T>(
         right.x, right.y, right.z, -dot(eye, right),
            up.x,    up.y,    up.z, -dot(eye, up),
         front.x, front.y, front.z, -dot(eye, front),
         0, 0, 0, 1
         );
   }
}