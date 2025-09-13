#pragma once

#include <string>

#include "PlatformDetection.hpp"
#include "Types.hpp"

namespace Neat {
class Layer {
 public:
  Layer() = default;
  virtual ~Layer() = 0;

  virtual void onAttach() {}
  virtual void onDetach() {}
  virtual void onUpdate([[maybe_unused]] double deltaTimeSeconds) {}
  virtual void onRender() {}
};
}  // namespace Neat