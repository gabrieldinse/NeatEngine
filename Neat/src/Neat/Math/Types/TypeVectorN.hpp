#pragma once

#include <iostream>

#include "Neat/Core/Exceptions.hpp"
#include "Neat/Core/Types.hpp"
#include "Neat/Math/Constants.hpp"

namespace Neat {
// Vector class template
template <UInt32 N, typename T> struct Vector {};

// Ostream operator
template <typename T, UInt32 N>
std::ostream &operator<<(std::ostream &os, const Vector<N, T> &v);
} // namespace Neat

#include "Neat/Math/Types/TypeVectorN.inl"
