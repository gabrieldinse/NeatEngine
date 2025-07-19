#pragma once

#include "Neat/Graphics/GraphicsContext.hpp"

namespace Neat {
class GraphicsContext {
 public:
  virtual ~GraphicsContext() = default;

  virtual void init() = 0;
  virtual void onUpdate() = 0;

  static Scope<GraphicsContext> create(void *window);
};
}  // namespace Neat