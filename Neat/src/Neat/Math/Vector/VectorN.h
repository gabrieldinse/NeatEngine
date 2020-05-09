#pragma once

#include <type_traits>
#include <iostream>
#include <numeric>
#include <algorithm>

#include "Neat/Core/Types.h"
#include "Neat/Math/Exceptions.h"


namespace Neat
{
   // Vec class template
   template <SizeType N, typename T>
   struct Vec;


   // Relational operators
   template <typename T, SizeType N>
   inline constexpr
   Bool operator>(const Vec<N, T>& va, const Vec<N, T>& vb);

   template <typename T, SizeType N>
   inline constexpr
   Bool operator<(const Vec<N, T>& va, const Vec<N, T>& vb);

   template <typename T, SizeType N>
   inline constexpr
   Bool operator==(const Vec<N, T>& va, const Vec<N, T>& vb);

   template <typename T, SizeType N>
   inline constexpr
   Bool operator!=(const Vec<N, T>& va, const Vec<N, T>& vb);

   template <typename T, SizeType N>
   inline constexpr
   Bool operator>=(const Vec<N, T>& va, const Vec<N, T>& vb);

   template <typename T, SizeType N>
   inline constexpr
   Bool operator<=(const Vec<N, T>& va, const Vec<N, T>& vb);


   template <typename T, SizeType N>
   std::ostream& operator<<(std::ostream& os, const Vec<N, T>& v);
}

#include "Neat/Math/Vector/VectorN.inl"