#pragma once

#include "Neat/Events/Events/ComponentEvent.hpp"

namespace Neat {
template <typename C>
struct ComponentAddedEvent : public ComponentEvent {
  ComponentAddedEvent(const Entity &entity, const ComponentHandle<C> &component)
      : entity(entity), ComponentEvent(component) {}
  virtual ~ComponentAddedEvent() = default;
};
}  // namespace Neat