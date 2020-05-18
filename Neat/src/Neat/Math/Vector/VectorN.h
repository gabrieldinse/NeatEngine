#pragma once

#include <type_traits>
#include <iostream>
#include <numeric>
#include <algorithm>

#include "Neat/Core/Types.h"
#include "Neat/Core/Exceptions.h"


namespace Neat
{
   // Vector class template
   template <UInt N, typename T>
   struct Vector;


   // Relational operators
   template <typename T, UInt N>
   inline constexpr
   bool operator>(const Vector<N, T>& va, const Vector<N, T>& vb);

   template <typename T, UInt N>
   inline constexpr
   bool operator<(const Vector<N, T>& va, const Vector<N, T>& vb);

   template <typename T, UInt N>
   inline constexpr
   bool operator==(const Vector<N, T>& va, const Vector<N, T>& vb);

   template <typename T, UInt N>
   inline constexpr
   bool operator!=(const Vector<N, T>& va, const Vector<N, T>& vb);

   template <typename T, UInt N>
   inline constexpr
   bool operator>=(const Vector<N, T>& va, const Vector<N, T>& vb);

   template <typename T, UInt N>
   inline constexpr
   bool operator<=(const Vector<N, T>& va, const Vector<N, T>& vb);


   template <typename T, UInt N>
   std::ostream& operator<<(std::ostream& os, const Vector<N, T>& v);
}

#include "Neat/Math/Vector/VectorN.inl"