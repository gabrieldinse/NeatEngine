#pragma once

#include "Neat/Math/Types/TypeMatrixMxN.h"


namespace Neat
{
   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesX(const T& angleX);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesY(const T& angle);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesZ(const T& angleZ);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesXYZ(const T& angle1, const T& angle2,
      const T& angle3);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesYXZ(const T& yaw, const T& pitch,
      const T& roll);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesXZX(const T& angle1, const T& angle2,
      const T& angle3);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesXYX(const T& angle1, const T& angle2,
      const T& angle);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesYXY(const T& angle1, const T& angle2,
      const T& angle3);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesYZY(const T& angle1, const T& angle2,
      const T& angle3);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesZYZ(const T& angle1, const T& angle2,
      const T& angle3);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesZXZ(const T& angle1, const T& angle2,
      const T& angle3);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesXZY(const T& angle1, const T& angle2,
      const T& angle3);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesYZX(const T& angle1, const T& angle2,
      const T& angle3);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesZYX(const T& angle1, const T& angle2,
      const T& angle3);

   template <typename T>
   inline Matrix<4, 4, T> eulerAnglesZXY(const T& angle1, const T& angle2,
      const T& angle3);

   template <typename T>
   inline Matrix<4, 4, T> yawPitchRoll(const T& yaw, const T& pitch,
      const T& roll);
}

#include "Neat/Math/EulerAngles.inl"