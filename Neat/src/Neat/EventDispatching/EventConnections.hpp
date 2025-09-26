#pragma once

#include <functional>
#include <memory>
#include <list>

#include "QueuedEvent.hpp"

#include "Neat/Utils/TypeId.hpp"
#include "Neat/Core/Limits.hpp"

namespace Neat {
constexpr UInt16 EventPriorityHighest = 0;
constexpr UInt16 EventPriorityLowest = Limits::Max<UInt16>;

class BaseEventConnections {
 public:
  virtual ~BaseEventConnections() = default;
  virtual void onUpdate(const BaseQueuedEvent &queuedEvent) = 0;
  virtual void disconnect(void *instance) = 0;
};

template <typename EventType>
class EventConnections : public BaseEventConnections {
 public:
  using HandlerFunction = std::function<bool(const EventType &)>;

  struct Handler {
    HandlerFunction function;
    void *instancePointer;
    TypeId instanceMethodId;
    bool ignoreIfHandled;
    UInt16 priority;
  };

  template <auto method, typename Instance>
  void connect(Instance &instance, UInt16 priority = EventPriorityLowest,
               bool ignoreIfHandled = false) {
    auto insert_it = std::find_if(m_handlers.begin(), m_handlers.end(),
                                  [priority](const Handler &handler) {
                                    return handler.priority > priority;
                                  });
    m_handlers.emplace(
        insert_it,
        [&instance](const EventType &event) {
          return (instance.*method)(event);
        },
        static_cast<void *>(&instance), getMethodId<method>(), ignoreIfHandled,
        priority);
  }

  template <auto method, typename Instance>
  void disconnect(Instance &instance) {
    TypeId methodId = getMethodId<method>();
    m_handlers.remove_if([&](const Handler &handler) {
      return handler.instancePointer == static_cast<void *>(&instance) and
             handler.instanceMethodId == methodId;
    });
  }

  void disconnect(void *instance) {
    m_handlers.remove_if([&](const Handler &handler) {
      return handler.instancePointer == instance;
    });
  }

  void onUpdate(const EventType &event) {
    bool handled = false;
    for (auto &handler : m_handlers) {
      if (not handled or handler.ignoreIfHandled) {
        if (handler.function(event)) {
          handled = true;
        }
      }
    }
  }

  void onUpdate(EventType &&event) { onUpdate(event); }

  void onUpdate(const BaseQueuedEvent &queuedEvent) {
    onUpdate(static_cast<const QueuedEvent<EventType> &>(queuedEvent).event);
  }

  template <typename... Args>
    requires(not std::same_as<std::tuple<std::decay_t<Args>...>,
                              std::tuple<EventType> >)
  void onUpdate(Args &&...args) {
    onUpdate(EventType(std::forward<Args>(args)...));
  }

 private:
  std::list<Handler> m_handlers;
};
}  // namespace Neat