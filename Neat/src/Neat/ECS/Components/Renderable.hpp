#pragma once

#include <memory>

#include "Neat/Graphics/Shape2D/Quad.hpp"

namespace Neat {
struct Renderable {
  Renderable(Scope<Shape> &&shape) : shape(std::move(shape)) {}

  Scope<Shape> shape;
};
}  // namespace Neat