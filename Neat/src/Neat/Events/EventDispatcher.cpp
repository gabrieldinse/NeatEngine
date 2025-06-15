#include "Neat/Events/EventDispatcher.hpp"

namespace Neat {
void EventDispatcher::update() {
  while (auto queuedEvent = m_eventsQueue.tryPop()) {
    auto &&[eventId, event] = *queuedEvent.value();
    if (m_eventConnectionsMap.contains(eventId)) {
      m_eventConnectionsMap[eventId]->update(event);
    }
  }
}
}  // namespace Neat