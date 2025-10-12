#pragma once

#include <functional>

#include "Core/Constants.hpp"

namespace Neat {

template <typename EventType>
struct EventHandler {
  using HandlerFunction = std::function<bool(const EventType &)>;

  HandlerFunction function;
  InstanceID instanceID;
  TypeID instanceMethodId;
  bool ignoreIfHandled;
  EventPriority priority;
  LayerID layerID = NoLayer;
  bool enabled = true;
};

}  // namespace Neat