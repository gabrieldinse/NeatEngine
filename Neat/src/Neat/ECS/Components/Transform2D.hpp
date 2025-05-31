#pragma once

#include "Neat/Math/Vector.hpp"

namespace Neat {
struct Transform2D {
  Transform2D(const Vector2F &position) : position(position) {}

  Vector2F position;
};
}  // namespace Neat