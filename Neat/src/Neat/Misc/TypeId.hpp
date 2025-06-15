#include "Neat/Core/Types.hpp"

namespace Neat {
template <typename T>
std::size_t getTypeId() {
  static Byte type_id;
  return reinterpret_cast<std::size_t>(&type_id);
}

template <auto method>
constexpr std::size_t getMethodId() {
  return reinterpret_cast<std::size_t>(&getMethodId<method>);
}
}  // namespace Neat