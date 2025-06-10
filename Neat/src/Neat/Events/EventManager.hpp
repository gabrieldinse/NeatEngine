#pragma once

#include <vector>

#include "Neat/Core/Exceptions.hpp"
#include "Neat/Core/Log.hpp"
#include "Neat/Events/EventHandler.hpp"
#include "Neat/Events/Event.hpp"
#include "Neat/Misc/SafeQueue.hpp"

namespace Neat {
class EventManager {
 public:
  using EventCallbacksListsVector =
      std::vector<std::shared_ptr<EventCallbacksList>>;

 public:
  EventManager() = default;
  virtual ~EventManager() = default;

  EventManager(const EventManager &) = delete;
  EventManager &operator=(const EventManager &) = delete;

  template <typename E, typename Handler>
  void addHandler(Handler &eventHandler,
                  EventPriority priority = EventPriority::Lowest,
                  bool ignoreIfHandled = false) {
    auto event_callbacks_list = getEventCallbacksList<E>();
    auto event_callback_id = event_callbacks_list->template addHandler<E>(
        eventHandler, priority, ignoreIfHandled);

    BaseEventHandler &base_event_handler = eventHandler;
    base_event_handler.m_eventsToHandleMap.insert(std::make_pair(
        Event<E>::getFamily(),
        std::make_pair(std::weak_ptr<EventCallbacksList>(event_callbacks_list),
                       event_callback_id)));
  }

  template <typename E, typename Handler>
  void removeHandler(Handler &eventHandler) {
    BaseEventHandler &base_event_handler = eventHandler;
    auto family = Event<E>::getFamily();

    if (base_event_handler.m_eventsToHandleMap.find(family) ==
        base_event_handler.m_eventsToHandleMap.end()) {
      throw EventListenerError();
    }

    auto &[event_callbacks_list, event_callback_id] =
        base_event_handler.m_eventsToHandleMap[family];

    if (not event_callbacks_list.expired()) {
      event_callbacks_list.lock()->removeHandler(event_callback_id);
    }

    base_event_handler.m_eventsToHandleMap.erase(family);
  }

  template <typename E>
  void generateEvent(const E &event) {
    auto event_callbacks_list = getEventCallbacksList<E>();
    event_callbacks_list->template generateEvent<E>(event);
  }

  template <typename E>
  void generateEvent(std::unique_ptr<E> event) {
    auto event_callbacks_list = getEventCallbacksList<E>();
    event_callbacks_list->template generateEvent<E>(event);
  }

  template <typename E, typename... Args>
  void generateEvent(Args &&...args) {
    auto event_callbacks_list = getEventCallbacksList<E>();
    event_callbacks_list->template generateEvent<E>(
        std::forward<Args>(args)...);
  }

  std::size_t getNumberOfHandlers() const {
    std::size_t count = 0;
    for (auto &event_callbacks_list : m_eventCallbacksLists) {
      if (event_callbacks_list) {
        count += event_callbacks_list->size();
      }
    }

    return count;
  }

 private:
  template <typename E>
  std::shared_ptr<EventCallbacksList> &getEventCallbacksList() {
    auto family = Event<E>::getFamily();

    if (family >= m_eventCallbacksLists.size()) {
      m_eventCallbacksLists.resize(family + 1);
    }

    if (not m_eventCallbacksLists[family]) {
      m_eventCallbacksLists[family] = std::make_shared<EventCallbacksList>();
    }

    return m_eventCallbacksLists[family];
  }

 private:
  EventCallbacksListsVector m_eventCallbacksLists;
};

}  // namespace Neat