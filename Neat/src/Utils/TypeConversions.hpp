#pragma once

#include "Math/Vector.hpp"

struct ImVec4;
struct ImVec2;

namespace Neat {
template <typename E>
constexpr typename std::enable_if<std::is_enum<E>::value,
                                  std::underlying_type_t<E>>::type
enumToInt(E e) {
  return static_cast<std::underlying_type_t<E>>(e);
}

ImVec4 toImVec4(const Vector4F &vector);
ImVec2 toImVec2(const Vector2F &vector);
}  // namespace Neat