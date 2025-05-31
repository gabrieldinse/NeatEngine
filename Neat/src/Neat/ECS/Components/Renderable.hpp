#pragma once

#include <memory>

#include "Neat/Graphics/Shape2D/Quad.hpp"

namespace Neat {
struct Renderable {
  Renderable(std::unique_ptr<Shape> &&shape) : shape(std::move(shape)) {}

  std::unique_ptr<Shape> shape;
};
}  // namespace Neat