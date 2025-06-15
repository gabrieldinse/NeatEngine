#include <functional>
#include <memory>
#include <list>
#include <any>

#include "Neat/Misc/TypeId.hpp"

namespace Neat {
class IEventConnections {
 public:
  virtual void update(const std::any &event) = 0;
  virtual ~IEventConnections() = default;
};

template <typename EventType>
class EventConnections : public IEventConnections {
 public:
  using HandlerFunction = std::function<bool(const EventType &)>;

  struct Handler {
    HandlerFunction function;
    void *instancePointer;
    std::size_t instanceMethodId;
    bool ignoreIfHandled;
  };

  template <auto method, typename Instance>
  void connect(Instance &instance, bool ignoreIfHandled = false) {
    m_handlers.emplace_back(
        [&instance](const EventType &event) {
          return (instance.*method)(event);
        },
        static_cast<void *>(&instance), Neat::getMethodId<method>(),
        ignoreIfHandled);
  }

  template <auto method, typename Instance>
  void disconnect(Instance &instance) {
    std::size_t methodId = getMethodId<method>();
    m_handlers.remove_if([&](const Handler &handler) {
      return handler.instancePointer == static_cast<void *>(&instance) and
             handler.instanceMethodId == methodId;
    });
  }

  void update(const EventType &event) {
    bool handled = false;
    for (auto &handler : m_handlers) {
      if (not handled or handler.ignoreIfHandled) {
        if (handler.function(event)) {
          handled = true;
        }
      }
    }
  }

  void update(EventType &&event) { update(event); }

  void update(const std::any &event) {
    update(std::any_cast<const EventType &>(event));
  }

  // Enable this template only if the Args is not EventType
  template <typename... Args,
            std::enable_if_t<!std::is_same_v<std::tuple<std::decay_t<Args>...>,
                                             std::tuple<EventType>>,
                             int> = 0>
  void update(Args &&...args) {
    update(EventType(std::forward<Args>(args)...));
  }

 private:
  std::list<Handler> m_handlers;
};
}  // namespace Neat