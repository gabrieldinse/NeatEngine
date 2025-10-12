#pragma once

#include <functional>
#include <memory>
#include <list>

#include "QueuedEvent.hpp"
#include "EventHandler.hpp"
#include "EventConnectionHandle.hpp"

#include "Utils/TypeID.hpp"
#include "Core/Limits.hpp"
#include "Core/Types.hpp"
#include "Core/Constants.hpp"

namespace Neat {
class BaseEventConnections {
 public:
  virtual ~BaseEventConnections() = default;
  virtual void update(const BaseQueuedEvent &queuedEvent) = 0;
  virtual void disconnect(InstanceID instanceID) = 0;
  virtual void enable(LayerID layerID) = 0;
  virtual void disable(LayerID layerID) = 0;
};

template <typename EventType>
class EventConnections : public BaseEventConnections {
 public:
  template <auto method, typename Instance>
  void connect(Instance &instance, EventPriority priority = EventPriorityLowest,
               LayerID layerID = NoLayer, bool ignoreIfHandled = false) {
    insertEventHandler<method>(instance, priority, layerID, ignoreIfHandled);
  }

  template <auto method, typename Instance>
  [[nodiscard]] Ref<BaseEventConnectionHandle> connectScoped(
      Instance &instance, EventPriority priority = EventPriorityLowest,
      LayerID layerID = NoLayer, bool ignoreIfHandled = false) {
    auto &eventHandler = insertEventHandler<method>(instance, priority, layerID,
                                                    ignoreIfHandled);
    return makeRef<EventConnectionHandle<EventType>>(*this, eventHandler);
  }

  template <auto method, typename Instance>
  void disconnect(Instance &instance) {
    TypeID methodId = getMethodID<method>();
    m_eventHandlers.remove_if([&](const EventHandler<EventType> &eventHandler) {
      return eventHandler.instanceID == getInstanceID(instance) and
             eventHandler.instanceMethodId == methodId;
    });
  }

  void disconnect(InstanceID instanceID) override {
    m_eventHandlers.remove_if([&](const EventHandler<EventType> &eventHandler) {
      return eventHandler.instanceID == instanceID;
    });
  }

  void disconnect(LayerID &layerID) {
    m_eventHandlers.remove_if([&](const EventHandler<EventType> &eventHandler) {
      return eventHandler.layerID == layerID;
    });
  }

  void disconnect(
      const EventConnectionHandle<EventType> &eventConnectionHandle) {
    m_eventHandlers.remove_if([&](const EventHandler<EventType> &eventHandler) {
      return eventHandler.instanceID ==
                 eventConnectionHandle.getEventHandler().instanceID and
             eventHandler.instanceMethodId ==
                 eventConnectionHandle.getEventHandler().instanceMethodId;
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

  void update(const EventType &event) {
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

  void update(EventType &&event) { update(event); }

  void update(const BaseQueuedEvent &queuedEvent) {
    update(static_cast<const QueuedEvent<EventType> &>(queuedEvent).event);
  }

  template <typename... Args>
    requires(not std::same_as<std::tuple<std::decay_t<Args>...>,
                              std::tuple<EventType>>)
  void update(Args &&...args) {
    update(EventType(std::forward<Args>(args)...));
  }

 private:
  auto findEventHandler(LayerID &layerID) {
    return std::find_if(m_eventHandlers.begin(), m_eventHandlers.end(),
                        [layerID](const EventHandler<EventType> &eventHandler) {
                          return eventHandler.layerID == layerID;
                        });
  }

  template <auto method, typename Instance>
  EventHandler<EventType> &insertEventHandler(Instance &instance,
                                              EventPriority priority,
                                              LayerID layerID,
                                              bool ignoreIfHandled) {
    auto insert_it =
        std::find_if(m_eventHandlers.begin(), m_eventHandlers.end(),
                     [priority](const EventHandler<EventType> &eventHandler) {
                       return eventHandler.priority > priority;
                     });
    EventHandler<EventType> eventHandler{[&instance](const EventType &event) {
                                           return (instance.*method)(event);
                                         },
                                         getInstanceID(instance),
                                         getMethodID<method>(),
                                         ignoreIfHandled,
                                         priority,
                                         layerID};
    auto it = m_eventHandlers.insert(insert_it, std::move(eventHandler));
    return *it;
  }

 private:
  std::list<EventHandler<EventType>> m_eventHandlers;
};
}  // namespace Neat