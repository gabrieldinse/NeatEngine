
#pragma once

#include "Neat/Utils/TypeId.hpp"
#include "Neat/Core/Types.hpp"

namespace Neat {
struct BaseQueuedEvent {
  TypeId eventId;

  BaseQueuedEvent(TypeId eventId) : eventId{eventId} {}
  virtual ~BaseQueuedEvent() = default;
};

template <typename EventType>
struct QueuedEvent : BaseQueuedEvent {
  EventType event;

  QueuedEvent(TypeId eventId, EventType event)
      : BaseQueuedEvent{eventId}, event{event} {}
};
}  // namespace Neat