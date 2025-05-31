#pragma once

#include "Neat/Math/Vector.hpp"

namespace Neat {
struct Direction2D {
  Direction2D(const Vector2F &direction) : direction(direction) {}

  Vector2F direction;
};
}  // namespace Neat