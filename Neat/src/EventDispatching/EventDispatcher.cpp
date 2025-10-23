#include "NeatPCH.hpp"

#include "EventDispatcher.hpp"

namespace Neat {
void EventDispatcher::update() {
  while (auto queuedEventOpt = m_eventsQueue.tryPop()) {
    auto &queuedEvent = queuedEventOpt.value();
    auto it = m_eventConnectionsMap.find(queuedEvent.eventId);
    if (it != m_eventConnectionsMap.end()) {
      it->second->update(queuedEvent);
    }
  }
}
}  // namespace Neat