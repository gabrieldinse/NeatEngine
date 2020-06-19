#pragma once

#include <iostream>

#include "Neat/Core/Types.h"
#include "Neat/Core/Exceptions.h"


namespace Neat
{
   // Vector class template
   template <UInt32 N, typename T>
   struct Vector {};

   template <typename T, UInt32 N>
   std::ostream& operator<<(std::ostream& os, const Vector<N, T>& v);
}

#include "Neat/Math/Types/TypeVectorN.inl"
