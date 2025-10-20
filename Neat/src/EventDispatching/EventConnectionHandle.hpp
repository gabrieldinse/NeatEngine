#pragma once

#include "EventHandler.hpp"

namespace Neat {
template <typename EventType>
class EventConnections;

class BaseEventConnectionHandle {
 public:
  virtual ~BaseEventConnectionHandle() = default;
  virtual void disconnect() = 0;
};

template <typename EventType>
class EventConnectionHandle : public BaseEventConnectionHandle {
 public:
  EventConnectionHandle(EventConnections<EventType> &eventConnections,
                        const EventHandler<EventType> &eventHandler)
      : m_eventConnections{eventConnections}, m_eventHandler{eventHandler} {}
  ~EventConnectionHandle();
  virtual void disconnect() override;

  const EventHandler<EventType> &getEventHandler() const {
    return m_eventHandler;
  }

 private:
  EventConnections<EventType> &m_eventConnections;
  EventHandler<EventType> m_eventHandler;
};

template <typename EventType>
void EventConnectionHandle<EventType>::disconnect() {
  m_eventConnections.disconnectHandle(*this);
}

template <typename EventType>
EventConnectionHandle<EventType>::~EventConnectionHandle() {
  disconnect();
}
}  // namespace Neat