#pragma once

#include <type_traits>
#include <iostream>
#include <numeric>
#include <algorithm>

#include "Neat/Core/Types.h"
#include "Neat/Core/Exceptions.h"


namespace Neat
{
   // Vec class template
   template <std::size_t N, typename T>
   struct Vec;


   // Relational operators
   template <typename T, std::size_t N>
   inline constexpr
   bool operator>(const Vec<N, T>& va, const Vec<N, T>& vb);

   template <typename T, std::size_t N>
   inline constexpr
   bool operator<(const Vec<N, T>& va, const Vec<N, T>& vb);

   template <typename T, std::size_t N>
   inline constexpr
   bool operator==(const Vec<N, T>& va, const Vec<N, T>& vb);

   template <typename T, std::size_t N>
   inline constexpr
   bool operator!=(const Vec<N, T>& va, const Vec<N, T>& vb);

   template <typename T, std::size_t N>
   inline constexpr
   bool operator>=(const Vec<N, T>& va, const Vec<N, T>& vb);

   template <typename T, std::size_t N>
   inline constexpr
   bool operator<=(const Vec<N, T>& va, const Vec<N, T>& vb);


   template <typename T, std::size_t N>
   std::ostream& operator<<(std::ostream& os, const Vec<N, T>& v);
}

#include "Neat/Math/Vector/VectorN.inl"