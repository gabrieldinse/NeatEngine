#pragma once

#include <type_traits>
#include <string>
#include <iostream>
#include <algorithm>

#include "Neat/Core/Types.h"
#include "Neat/Core/Exceptions.h"


namespace Neat
{
   template <std::size_t M, std::size_t N, typename T>
   struct Mat;

   template <std::size_t M, std::size_t N, typename T>
   std::ostream& operator<<(std::ostream& os, const Mat<M, N, T>& m);
}

#include "Neat/Math/Matrix/MatrixMxN.inl"