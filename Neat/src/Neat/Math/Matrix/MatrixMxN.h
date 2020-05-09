#pragma once

#include <type_traits>
#include <string>
#include <iostream>
#include <algorithm>

#include "Neat/Core/Types.h"
#include "Neat/Math/Exceptions.h"


namespace Neat
{
   template <SizeType M, SizeType N, typename T>
   struct Mat;

   template <SizeType M, SizeType N, typename T>
   std::ostream& operator<<(std::ostream& os, const Mat<M, N, T>& m);
}

#include "Neat/Math/Matrix/MatrixMxN.inl"