#pragma once

#include <algorithm>
#include <functional>
#include <list>
#include <memory>

#include "Neat/Events/EventPriority.hpp"

namespace Neat {
using EventCallbackFunction = std::function<bool(const void *)>;

class EventCallbacksList {
 public:
  // EventCallback -------------------------------------------------
  struct EventCallback {
    EventCallback(
        const std::shared_ptr<EventCallbackFunction> &eventCallbackFunction,
        EventPriority priority, bool ignoreIfHandled)
        : eventCallbackFunction(eventCallbackFunction),
          priority(priority),
          ignoreIfHandled(ignoreIfHandled) {}

    std::shared_ptr<EventCallbackFunction> eventCallbackFunction;
    EventPriority priority;
    bool ignoreIfHandled;
  };
  // ----------------------------------------------------------------------

 public:
  EventCallbacksList() = default;

  template <typename E, typename Handler>
  std::size_t addHandler(Handler &listener, EventPriority priority,
                         bool ignoreIfHandled) {
    bool (Handler::*handleEvent)(const E &) = &Handler::handleEvent;

    auto eventCallbackFunction = EventCallbackWrapper<E>(
        std::bind(handleEvent, &listener, std::placeholders::_1));

    auto callback_element = EventCallback(
        std::make_shared<EventCallbackFunction>(eventCallbackFunction),
        priority, ignoreIfHandled);

    m_eventCallbacks.insert(
        std::lower_bound(
            m_eventCallbacks.begin(), m_eventCallbacks.end(), priority,
            [](const EventCallback &element, EventPriority priority) {
              return element.priority >= priority;
            }),
        callback_element);

    return (std::size_t)m_eventCallbacks.back().eventCallbackFunction.get();
  }

  void removeEventCallback(std::size_t id) {
    m_eventCallbacks.remove_if([id](const EventCallback &eventCallback) {
      return (std::size_t)eventCallback.eventCallbackFunction.get() == id;
    });
  }

  template <typename E>
  void generateEvent(const E &event) {
    executeCallbacks(&event);
  }

  template <typename E>
  void generateEvent(std::unique_ptr<E> event) {
    executeCallbacks(event.get());
  }

  template <typename E, typename... Args>
  void generateEvent(Args &&...args) {
    E event(std::forward<Args>(args)...);
    executeCallbacks(&event);
  }

  std::size_t size() const { return m_eventCallbacks.size(); }

 private:
  template <typename E>
  struct EventCallbackWrapper {
    std::function<bool(const E &)> eventCallbackFunction;

    EventCallbackWrapper(std::function<bool(const E &)> eventCallbackFunction)
        : eventCallbackFunction(eventCallbackFunction) {}

    bool operator()(const void *event) {
      return eventCallbackFunction(*(static_cast<const E *>(event)));
    }
  };

  void executeCallbacks(const void *event) {
    bool eventHandled = false;
    for (auto &callback_element : m_eventCallbacks)
      if (callback_element.eventCallbackFunction != nullptr and
          (callback_element.ignoreIfHandled or !eventHandled)) {
        eventHandled |= (*callback_element.eventCallbackFunction)(event);
      }
  }

 private:
  std::list<EventCallback> m_eventCallbacks;
};
}  // namespace Neat