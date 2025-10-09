#include "NeatPCH.hpp"

#include "EventDispatcher.hpp"

namespace Neat {
void EventDispatcher::update() {
  while (auto queuedEvent = m_eventsQueue.tryPop()) {
    auto &baseQueuedEvent = queuedEvent.value();
    if (m_eventConnectionsMap.contains(baseQueuedEvent->eventId)) {
      m_eventConnectionsMap[baseQueuedEvent->eventId]->update(*baseQueuedEvent);
    }
  }
}
}  // namespace Neat