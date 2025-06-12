#include <functional>
#include <memory>
#include <list>
#include <any>

#include "Neat/Misc/SafeQueue.hpp"
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

  void update(const std::any &event) {
    bool handled = false;
    int i = 0;
    for (auto &handler : m_handlers) {
      if (not handled or handler.ignoreIfHandled) {
        if (handler.function(std::any_cast<const EventType &>(event))) {
          handled = true;
        }
      }
      i++;
    }
  }

 private:
  std::list<Handler> m_handlers;
};
}  // namespace Neat