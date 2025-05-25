#pragma once

#include <memory>

#include "Neat/Core/Input.hpp"
#include "Neat/Graphics/Shape2D/Quad.hpp"
#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Transform.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
struct Transform2D {
  Transform2D(const Vector2F &position) : position(position) {}

  Vector2F position;
};

struct Direction2D {
  Direction2D(const Vector2F &direction) : direction(direction) {}

  Vector2F direction;
};

struct Renderable {
  Renderable(std::unique_ptr<Shape> &&shape) : shape(std::move(shape)) {}

  std::unique_ptr<Shape> shape;
};
} // namespace Neat