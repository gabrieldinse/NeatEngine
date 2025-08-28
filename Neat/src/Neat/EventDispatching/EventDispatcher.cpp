#include "NeatPCH.hpp"

#include "Neat/EventDispatching/EventDispatcher.hpp"

namespace Neat {
void EventDispatcher::onUpdate() {
  while (auto queuedEvent = m_eventsQueue.tryPop()) {
    auto &baseQueuedEvent = queuedEvent.value();
    if (m_eventConnectionsMap.contains(baseQueuedEvent->eventId)) {
      m_eventConnectionsMap[baseQueuedEvent->eventId]->onUpdate(
          *baseQueuedEvent);
    }
  }
}
}  // namespace Neat