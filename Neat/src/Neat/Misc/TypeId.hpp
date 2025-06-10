#include "Neat/Core/Types.hpp"

namespace Neat {
template<typename T>
void* typeId() {
  static Byte type_id;
  return &type_id;
}
}