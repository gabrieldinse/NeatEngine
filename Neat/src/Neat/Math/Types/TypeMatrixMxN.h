#pragma once

#include <type_traits>
#include <string>
#include <iostream>
#include <algorithm>

#include "Neat/Core/Types.h"
#include "Neat/Core/Exceptions.h"


namespace Neat
{
   template <UInt32 M, UInt32 N, typename T>
   struct Matrix {};

   template <UInt32 M, UInt32 N, typename T>
   std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& m);
}

#include "Neat/Math/Types/TypeMatrixMxN.inl"
