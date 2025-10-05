#pragma once

#include <functional>

#include "Neat/Core/Constants.hpp"

namespace Neat {
template <typename EventType>
using HandlerFunction = std::function<bool(const EventType &)>;

template <typename EventType>
struct EventHandler {
  HandlerFunction<EventType> function;
  void *instancePointer;
  TypeId instanceMethodId;
  bool ignoreIfHandled;
  EventPriority priority;
  LayerID layerID = NoLayer;
  bool enabled = true;
};

}  // namespace Neat