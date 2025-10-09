#pragma once

#include <any>

#include "Math/Vector.hpp"

namespace Neat {
struct BoxCollider2DComponent {
  Vector2F offset{0.0f, 0.0f};
  Vector2F size{1.0f, 1.0f};
  float density = 1.0f;
  float friction = 0.5f;
  float bounceFactor = 0.0f;
};
};  // namespace Neat