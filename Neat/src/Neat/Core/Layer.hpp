#pragma once

#include <string>

#include "Neat/Core/Base.hpp"
#include "Neat/Core/Types.hpp"

namespace Neat {
class Layer {
 public:
  Layer() = default;
  virtual ~Layer() = default;

  virtual void onAttach() {}
  virtual void onDetach() {}
  virtual void onUpdate(DeltaTime deltaTime) {}
  virtual void onRender() {}
};
}  // namespace Neat