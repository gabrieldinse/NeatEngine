
#pragma once

#include "Utils/TypeID.hpp"
#include "Core/Types.hpp"

namespace Neat {
struct BaseQueuedEvent {
  TypeID eventId;

  BaseQueuedEvent(TypeID eventId) : eventId{eventId} {}
  virtual ~BaseQueuedEvent() = default;
};

template <typename EventType>
struct QueuedEvent : BaseQueuedEvent {
  EventType event;

  QueuedEvent(TypeID eventId, EventType event)
      : BaseQueuedEvent{eventId}, event{event} {}
};
}  // namespace Neat