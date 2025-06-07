#pragma once

#include "Neat/Events/BaseEventHandler.hpp"

namespace Neat {
template <typename Derived>
struct EventHandler : public BaseEventHandler {
  virtual ~EventHandler() {}
};
}  // namespace Neat