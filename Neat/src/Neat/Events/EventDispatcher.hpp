#include "Neat/Events/EventConnections.hpp"
#include "Neat/Misc/SafeQueue.hpp"
#include <iostream>

namespace Neat {
class EventDispatcher {
 public:
  template <typename EventType>
  EventConnections<EventType>& get() {
    std::size_t eventId = getTypeId<EventType>();
    if (not m_eventConnectionsMap.contains(eventId)) {
      m_eventConnectionsMap[eventId] =
          std::make_unique<EventConnections<EventType>>();
    }

    return *static_cast<EventConnections<EventType>*>(
        m_eventConnectionsMap[eventId].get());
  }

  template <typename EventType>
  void enqueue(const EventType& event) {
    m_eventsQueue.push(
        std::make_unique<QueuedEvent>(getTypeId<EventType>(), event));
  }

  template <typename EventType>
  void enqueue(EventType&& event) {
    using DecayedEventType = std::remove_reference_t<EventType>;
    m_eventsQueue.push(
        std::make_unique<QueuedEvent>(getTypeId<DecayedEventType>(), event));
  }

  template <typename EventType, typename... Args,
            std::enable_if_t<!std::is_same_v<std::tuple<std::decay_t<Args>...>,
                                             std::tuple<EventType>>,
                             int> = 0>
  void enqueue(Args&&... args) {
    m_eventsQueue.push(std::make_unique<QueuedEvent>(
        getTypeId<EventType>(), EventType(std::forward<Args>(args)...)));
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

  void update();

 private:
  struct QueuedEvent {
    std::size_t eventId;
    std::any event;
  };

  using EventConnectionsMap =
      std::unordered_map<std::size_t, std::unique_ptr<IEventConnections>>;
  using EventsQueue = SafeQueue<std::unique_ptr<QueuedEvent>>;

 private:
  EventConnectionsMap m_eventConnectionsMap;
  EventsQueue m_eventsQueue;
};
}  // namespace Neat