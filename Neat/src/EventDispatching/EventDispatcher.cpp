#include "NeatPCH.hpp"

#include "EventDispatcher.hpp"

namespace Neat {
void EventDispatcher::update() {
  while (auto queuedEventOpt = m_eventsQueue.tryPop()) {
    auto &queuedEvent = queuedEventOpt.value();
    if (m_eventConnectionsMap.contains(queuedEvent->eventId)) {
      m_eventConnectionsMap[queuedEvent->eventId]->update(*queuedEvent);
    }
  }
}
}  // namespace Neat