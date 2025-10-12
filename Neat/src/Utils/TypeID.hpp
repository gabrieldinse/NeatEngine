#pragma once

#include "Core/Types.hpp"

namespace Neat {
template <typename T>
constexpr TypeID getTypeIDImpl() {
  static Byte type_id;
  return reinterpret_cast<TypeID>(&type_id);
}

template <typename T>
constexpr TypeID getTypeId() {
  using DecayedType = typename std::decay_t<T>;
  return getTypeIDImpl<DecayedType>();
}

template <auto method>
constexpr TypeID getMethodId() {
  return reinterpret_cast<TypeID>(&getMethodId<method>);
}

template <typename Instance>
constexpr InstanceID getInstanceID(const Instance &instance) {
  return reinterpret_cast<InstanceID>(&instance);
}
}  // namespace Neat