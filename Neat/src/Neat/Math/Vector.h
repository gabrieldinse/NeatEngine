#pragma once

#include "Neat/Math/Types/Vector1.h"
#include "Neat/Math/Types/Vector2.h"
#include "Neat/Math/Types/Vector3.h"
#include "Neat/Math/Types/Vector4.h"


namespace Neat
{
   template <UInt32 N, typename T>
   Vector<N, T> reflect(const Vector<N, T>& v, const Vector<N, T>& normal);

   template <UInt32 N, typename T>
   Vector<N, T> refract(const Vector<N, T>& v, const Vector<N, T>& normal,
      const T& eta);
}

#include "Neat/Math/Vector.inl"