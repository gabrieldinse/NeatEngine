#pragma once

#include <functional>

#include "Core/Constants.hpp"

namespace Neat {

template <typename EventType>
struct EventHandler {
  using HandlerFunction = std::function<bool(const EventType &)>;

  HandlerFunction function = nullptr;
  InstanceID instanceID = NoneInstance;
  TypeID methodID = NoneType;
  bool ignoreIfHandled = false;
  EventPriority priority = EventPriorityLowest;
  LayerID layerID = NoneLayer;
  bool enabled = true;
};

}  // namespace Neat