#pragma once

#include "Core/Types.hpp"

namespace Neat {
template <typename T>
constexpr TypeID getTypeID() {
  using DecayedType = typename std::decay_t<T>;
  return reinterpret_cast<TypeID>(&getTypeID<DecayedType>);
}

template <auto method>
constexpr TypeID getMethodID() {
  return reinterpret_cast<TypeID>(&getMethodID<method>);
}

template <typename T>
constexpr TypeID getMethodID() {
  return getTypeID<T>();
}

template <typename Instance>
constexpr InstanceID getInstanceID(const Instance &instance) {
  return reinterpret_cast<InstanceID>(&instance);
}
}  // namespace Neat