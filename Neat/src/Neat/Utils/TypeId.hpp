#pragma once

#include "Neat/Core/Types.hpp"

namespace Neat {
template <typename T>
constexpr std::size_t getTypeIDImpl() {
  static Byte type_id;
  return reinterpret_cast<std::size_t>(&type_id);
}

template <typename T>
constexpr std::size_t getTypeId() {
  using DecayedType = typename std::decay_t<T>;
  return getTypeIDImpl<DecayedType>();
}

template <auto method>
constexpr std::size_t getMethodId() {
  return reinterpret_cast<std::size_t>(&getMethodId<method>);
}
}  // namespace Neat