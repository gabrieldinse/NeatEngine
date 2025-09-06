#include "NeatPCH.hpp"

#include "Neat/Utils/TypeConversions.hpp"

#include <imgui.h>

namespace Neat {
ImVec4 toImVec4(const Vector4F &vector) {
  return ImVec4{vector.x(), vector.y(), vector.z(), vector.w()};
}

ImVec2 toImVec2(const Vector2F &vector) {
  return ImVec2{vector.x(), vector.y()};
}
}  // namespace Neat