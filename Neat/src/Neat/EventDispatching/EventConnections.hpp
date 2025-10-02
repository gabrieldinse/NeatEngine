#pragma once

#include <functional>
#include <memory>
#include <list>

#include "QueuedEvent.hpp"

#include "Neat/Utils/TypeId.hpp"
#include "Neat/Core/Limits.hpp"
#include "Neat/Core/Types.hpp"
#include "Neat/Core/Constants.hpp"

namespace Neat {
class BaseEventConnections {
 public:
  virtual ~BaseEventConnections() = default;
  virtual void onUpdate(const BaseQueuedEvent &queuedEvent) = 0;
  virtual void disconnect(void *instance) = 0;
  virtual void enable(LayerID layerID) = 0;
  virtual void disable(LayerID layerID) = 0;
};

template <typename EventType>
class EventConnections : public BaseEventConnections {
 public:
  using HandlerFunction = std::function<bool(const EventType &)>;

  struct EventHandler {
    HandlerFunction function;
    void *instancePointer;
    TypeId instanceMethodId;
    bool ignoreIfHandled;
    EventPriority priority;
    LayerID layerID = NoLayer;
    bool enabled = true;
  };

  template <auto method, typename Instance>
  void connect(Instance &instance, EventPriority priority = EventPriorityLowest,
               LayerID layerID = NoLayer, bool ignoreIfHandled = false) {
    auto insert_it =
        std::find_if(m_eventHandlers.begin(), m_eventHandlers.end(),
                     [priority](const EventHandler &eventHandler) {
                       return eventHandler.priority > priority;
                     });
    m_eventHandlers.emplace(
        insert_it,
        [&instance](const EventType &event) {
          return (instance.*method)(event);
        },
        static_cast<void *>(&instance), getMethodId<method>(), ignoreIfHandled,
        priority, layerID);
  }

  template <auto method, typename Instance>
  void disconnect(Instance &instance) {
    TypeId methodId = getMethodId<method>();
    m_eventHandlers.remove_if([&](const EventHandler &eventHandler) {
      return eventHandler.instancePointer == static_cast<void *>(&instance) and
             eventHandler.instanceMethodId == methodId;
    });
  }

  void disconnect(void *instance) override {
    m_eventHandlers.remove_if([&](const EventHandler &eventHandler) {
      return eventHandler.instancePointer == instance;
    });
  }

  void disconnect(LayerID &layerID) {
    m_eventHandlers.remove_if([&](const EventHandler &eventHandler) {
      return eventHandler.layerID == layerID;
    });
  }

  void enable(LayerID layerID) override {
    auto enableIt = findEventHandler(layerID);
    if (enableIt != m_eventHandlers.end()) {
      enableIt->enabled = true;
    }
  }

  void disable(LayerID layerID) override {
    auto disableIt = findEventHandler(layerID);
    if (disableIt != m_eventHandlers.end()) {
      disableIt->enabled = false;
    }
  }

  void onUpdate(const EventType &event) {
    bool handled = false;
    for (auto &eventHandler : m_eventHandlers) {
      if ((not eventHandler.enabled) or
          (handled and not eventHandler.ignoreIfHandled)) {
        continue;
      }

      if (eventHandler.function(event)) {
        handled = true;
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
  auto findEventHandler(LayerID &layerID) {
    return std::find_if(m_eventHandlers.begin(), m_eventHandlers.end(),
                        [layerID](const EventHandler &eventHandler) {
                          return eventHandler.layerID == layerID;
                        });
  }

 private:
  std::list<EventHandler> m_eventHandlers;
};
}  // namespace Neat