#pragma once

#include "Neat/Events/BaseEventListener.hpp"

namespace Neat {
template <typename Derived>
struct EventListener : public BaseEventListener {
  virtual ~EventListener() {}
};
}  // namespace Neat