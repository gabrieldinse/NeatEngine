#pragma once

#include <algorithm>
#include <functional>
#include <list>
#include <memory>

#include "Neat/Events/EventPriority.hpp"

namespace Neat {
using EventCallback = std::function<bool(const void *)>;

class EventToListenersConnection {
 public:
  // EventCallbackElement -------------------------------------------------
  struct EventCallbackElement {
    EventCallbackElement(const std::shared_ptr<EventCallback> &callback,
                         EventPriority priority, bool ignoreIfHandled)
        : callback(callback),
          priority(priority),
          ignoreIfHandled(ignoreIfHandled) {}

    std::shared_ptr<EventCallback> callback;
    EventPriority priority;
    bool ignoreIfHandled;
  };
  // ----------------------------------------------------------------------

 public:
  EventToListenersConnection() = default;

  template <typename E, typename Listener>
  std::size_t addListener(Listener &listener, EventPriority priority,
                          bool ignoreIfHandled) {
    bool (Listener::*handleEvent)(const E &) = &Listener::handleEvent;

    auto callback = EventCallbackWrapper<E>(
        std::bind(handleEvent, &listener, std::placeholders::_1));

    auto callback_element = EventCallbackElement(
        std::make_shared<EventCallback>(callback), priority, ignoreIfHandled);

    m_connectedListenersCallbacks.insert(
        std::lower_bound(
            m_connectedListenersCallbacks.begin(),
            m_connectedListenersCallbacks.end(), priority,
            [](const EventCallbackElement &element, EventPriority priority) {
              return not(element.priority < priority);
            }),
        callback_element);

    return (std::size_t)m_connectedListenersCallbacks.back().callback.get();
  }

  void removeListener(std::size_t id) {
    m_connectedListenersCallbacks.remove_if(
        [id](const EventCallbackElement &callbackElement) {
          return (std::size_t)callbackElement.callback.get() == id;
        });
  }

  template <typename E>
  void publishEvent(const E &event) {
    executeCallbacks(&event);
  }

  template <typename E>
  void publishEvent(std::unique_ptr<E> event) {
    executeCallbacks(event.get());
  }

  template <typename E, typename... Args>
  void publishEvent(Args &&...args) {
    E event(std::forward<Args>(args)...);
    executeCallbacks(&event);
  }

  std::size_t size() const { return m_connectedListenersCallbacks.size(); }

 private:
  template <typename E>
  struct EventCallbackWrapper {
    std::function<bool(const E &)> callback;

    EventCallbackWrapper(std::function<bool(const E &)> callback)
        : callback(callback) {}

    bool operator()(const void *event) {
      return callback(*(static_cast<const E *>(event)));
    }
  };

  void executeCallbacks(const void *event) {
    bool handled = false;
    for (auto &callback_element : m_connectedListenersCallbacks)
      if (callback_element.callback != nullptr and
          (callback_element.ignoreIfHandled or !handled)) {
        handled |= (*callback_element.callback)(event);
      }
  }

 private:
  std::list<EventCallbackElement> m_connectedListenersCallbacks;
};
}  // namespace Neat