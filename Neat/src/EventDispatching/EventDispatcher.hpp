#pragma once

#include "QueuedEvent.hpp"
#include "EventConnections.hpp"

#include "Utils/SafeQueue.hpp"
#include "Core/Types.hpp"

namespace Neat {
class EventDispatcher {
 public:
  template <typename EventType>
  EventConnections<EventType>& get() {
    TypeID eventId = getTypeID<EventType>();
    if (not m_eventConnectionsMap.contains(eventId)) {
      m_eventConnectionsMap[eventId] = makeScope<EventConnections<EventType>>();
    }

    return *static_cast<EventConnections<EventType>*>(
        m_eventConnectionsMap[eventId].get());
  }

  template <typename EventType>
  void enqueue(const EventType& event) {
    m_eventsQueue.push(
        makeScope<QueuedEvent<EventType>>(getTypeID<EventType>(), event));
  }

  template <typename EventType>
  void enqueue(EventType&& event) {
    using DecayedEventType = std::remove_reference_t<EventType>;
    m_eventsQueue.push(makeScope<QueuedEvent<DecayedEventType>>(
        getTypeID<DecayedEventType>(), event));
  }

  template <typename EventType, typename... Args,
            std::enable_if_t<!std::is_same_v<std::tuple<std::decay_t<Args>...>,
                                             std::tuple<EventType>>,
                             int> = 0>
  void enqueue(Args&&... args) {
    m_eventsQueue.push(makeScope<QueuedEvent<EventType>>(
        getTypeID<EventType>(), EventType(std::forward<Args>(args)...)));
  }

  template <typename EventType>
  void trigger(const EventType& event) {
    get<EventType>().update(event);
  }

  template <typename EventType>
  void trigger(EventType&& event) {
    using DecayedEventType = std::remove_reference_t<EventType>;
    get<DecayedEventType>().update(std::forward<EventType>(event));
  }

  template <typename EventType, typename... Args,
            std::enable_if_t<!std::is_same_v<std::tuple<std::decay_t<Args>...>,
                                             std::tuple<EventType>>,
                             int> = 0>
  void trigger(Args&&... args) {
    get<EventType>().update(std::forward<Args>(args)...);
  }

  template <typename Instance>
  void disconnect(Instance& instance) {
    for (auto& [_, connections] : m_eventConnectionsMap) {
      connections->disconnect(getInstanceID(instance));
    }
  }

  void enable(LayerID layerID) {
    for (auto& [_, connections] : m_eventConnectionsMap) {
      connections->enable(layerID);
    }
  }
  void disable(LayerID layerID) {
    for (auto& [_, connections] : m_eventConnectionsMap) {
      connections->disable(layerID);
    }
  }

  void update();

 private:
  using EventConnectionsMap =
      std::unordered_map<TypeID, Scope<BaseEventConnections>>;
  using EventsQueue = SafeQueue<Scope<BaseQueuedEvent>>;

 private:
  EventConnectionsMap m_eventConnectionsMap;
  EventsQueue m_eventsQueue;
};
}  // namespace Neat
