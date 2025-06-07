#pragma once

#include <memory>
#include <unordered_map>
#include <utility>

#include "Neat/Events/BaseEvent.hpp"
#include "Neat/Events/EventPriority.hpp"
#include "Neat/Events/EventCallbacksList.hpp"

namespace Neat {
class EventManager;

class BaseEventHandler {
 public:
  using EventsToHandleMap = std::unordered_map<
      BaseEvent::Family,
      std::pair<std::weak_ptr<EventCallbacksList>, std::size_t>>;

 public:
  ~BaseEventHandler() {
    for (auto &&[family, connection_pair] : m_eventsToHandleMap) {
      auto &&[eventCallbackList, connection_id] = connection_pair;
      if (not eventCallbackList.expired()) {
        eventCallbackList.lock()->removeEventCallback(connection_id);
      }
    }
  }

  UInt32 getNumberOfConnectedSignals() const {
    UInt32 count = 0;
    for (auto &&[family, connection_pair] : m_eventsToHandleMap) {
      auto &&[eventCallbackList, connection_id] = connection_pair;
      if (not eventCallbackList.expired()) {
        ++count;
      }
    }

    return count;
  }

 private:
  friend class EventManager;

  EventsToHandleMap m_eventsToHandleMap;
};
}  // namespace Neat