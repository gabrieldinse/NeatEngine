#include <functional>
#include <memory>
#include <list>

#include "Neat/Misc/SafeQueue.hpp"

namespace Neat {
class IEventConnections {
  public:
    virtual void update() = 0;
    virtual ~IEventConnections() = default;
};

template <typename EventType>
class EventConnections : public IEventConnections {
 public:
  using EventsQueue = SafeQueue<std::unique_ptr<EventType>>;
  using HandlerFunction = std::function<bool(const EventType&)>;

  struct Handler {
    HandlerFunction function;
    bool ignoreIfHandled;
  };

  template <auto method, typename Instance>
  void connect(Instance& instance, bool ignoreIfHandled = false) {
    m_handlers.emplace_back([&instance](const EventType& event) {
      return (instance.*method)(event);
    }, ignoreIfHandled);
  }

  //template <auto method, typename Instance>
  //void connect(Instance& instance, SizeType pos) {
  //  m_handlers.emplace(m_handlers.begin() + pos,
  //  [&instance](const EventType& event) {
  //    return (instance.*method)(event);
  //  });
  //}

  void update() {
    while (auto event = m_events.tryPop()) {
      bool handled = false;
      for (auto &handler : m_handlers) {
        if (not handled or handler.ignoreIfHandled)
          if (handler.function(*event.value())) {
            handled = true;
          }
      }
    }
  }

  template <typename... Args>
  void enqueue(Args&&... args) {
    m_events.push(std::make_unique<EventType>(std::forward<Args>(args)...));
  }

 private:
  EventsQueue m_events;
  std::list<Handler> m_handlers;
};
} // namespace Neat