#pragma once

#include "QueuedEvent.hpp"
#include "EventConnections.hpp"

#include "Neat/Utils/SafeQueue.hpp"

namespace Neat {
class EventDispatcher {
 public:
  template <typename EventType>
  EventConnections<EventType>& get() {
    TypeId eventId = getTypeId<EventType>();
    if (not m_eventConnectionsMap.contains(eventId)) {
      m_eventConnectionsMap[eventId] = makeScope<EventConnections<EventType>>();
    }

    return *static_cast<EventConnections<EventType>*>(
        m_eventConnectionsMap[eventId].get());
  }

  template <typename EventType>
  void enqueue(const EventType& event) {
    m_eventsQueue.push(
        makeScope<QueuedEvent<EventType>>(getTypeId<EventType>(), event));
  }

  template <typename EventType>
  void enqueue(EventType&& event) {
    using DecayedEventType = std::remove_reference_t<EventType>;
    m_eventsQueue.push(makeScope<QueuedEvent<DecayedEventType>>(
        getTypeId<DecayedEventType>(), event));
  }

  template <typename EventType, typename... Args,
            std::enable_if_t<!std::is_same_v<std::tuple<std::decay_t<Args>...>,
                                             std::tuple<EventType>>,
                             int> = 0>
  void enqueue(Args&&... args) {
    m_eventsQueue.push(makeScope<QueuedEvent<EventType>>(
        getTypeId<EventType>(), EventType(std::forward<Args>(args)...)));
  }

  template <typename EventType>
  void trigger(const EventType& event) {
    get<EventType>().onUpdate(event);
  }

  template <typename EventType>
  void trigger(EventType&& event) {
    using DecayedEventType = std::remove_reference_t<EventType>;
    get<DecayedEventType>().onUpdate(std::forward<EventType>(event));
  }

  template <typename EventType, typename... Args,
            std::enable_if_t<!std::is_same_v<std::tuple<std::decay_t<Args>...>,
                                             std::tuple<EventType>>,
                             int> = 0>
  void trigger(Args&&... args) {
    get<EventType>().onUpdate(std::forward<Args>(args)...);
  }

  template <typename Instance>
  void disconnect(Instance& instance) {
    for (auto& [_, connections] : m_eventConnectionsMap) {
      connections->disconnect(static_cast<void*>(&instance));
    }
  }

  void onUpdate();

 private:
  using EventConnectionsMap =
      std::unordered_map<TypeId, Scope<BaseEventConnections>>;
  using EventsQueue = SafeQueue<Scope<BaseQueuedEvent>>;

 private:
  EventConnectionsMap m_eventConnectionsMap;
  EventsQueue m_eventsQueue;
};
}  // namespace Neat
