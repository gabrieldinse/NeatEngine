#pragma once

#include <memory>
#include <unordered_map>
#include <utility>

#include "Neat/Events/BaseEvent.hpp"
#include "Neat/Events/EventPriority.hpp"
#include "Neat/Events/EventToListenersConnection.hpp"

namespace Neat {
class EventManager;

class BaseEventListener {
 public:
  using ConnectedEventsMap = std::unordered_map<
      BaseEvent::Family,
      std::pair<std::weak_ptr<EventToListenersConnection>, std::size_t>>;

 public:
  ~BaseEventListener() {
    for (auto &&[family, connection_pair] : m_connectedEvents) {
      auto &&[connection, connection_id] = connection_pair;
      if (not connection.expired())
        connection.lock()->removeListener(connection_id);
    }
  }

  UInt32 getNumberOfConnectedSignals() const {
    UInt32 count = 0;
    for (auto &&[family, connection_pair] : m_connectedEvents) {
      auto &&[connection, connection_id] = connection_pair;
      if (not connection.expired()) ++count;
    }

    return count;
  }

 private:
  friend class EventManager;

  ConnectedEventsMap m_connectedEvents;
};
}  // namespace Neat