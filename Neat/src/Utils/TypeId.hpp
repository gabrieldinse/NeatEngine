#pragma once

#include "Core/Types.hpp"

namespace Neat {
template <typename T>
constexpr TypeId getTypeIDImpl() {
  static Byte type_id;
  return reinterpret_cast<TypeId>(&type_id);
}

template <typename T>
constexpr TypeId getTypeId() {
  using DecayedType = typename std::decay_t<T>;
  return getTypeIDImpl<DecayedType>();
}

template <auto method>
constexpr TypeId getMethodId() {
  return reinterpret_cast<TypeId>(&getMethodId<method>);
}
}  // namespace Neat