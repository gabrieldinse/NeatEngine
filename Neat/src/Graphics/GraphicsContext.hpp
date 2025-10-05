#pragma once

#include "GraphicsContext.hpp"

namespace Neat {
class GraphicsContext {
 public:
  virtual ~GraphicsContext() = default;

  virtual void initialize() = 0;
  virtual void onUpdate() = 0;

  static Scope<GraphicsContext> create(void *window);
};
}  // namespace Neat