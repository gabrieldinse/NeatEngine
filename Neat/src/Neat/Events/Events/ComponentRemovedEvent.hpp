#pragma once

#include "Neat/Events/Events/ComponentEvent.hpp"

namespace Neat {
template <typename C>
struct ComponentRemovedEvent : public ComponentEvent {
  ComponentRemovedEvent(const Entity &entity,
                        const ComponentHandle<C> &component)
      : entity(entity), ComponentEvent(component) {}
  virtual ~ComponentRemovedEvent() = default;
};
}  // namespace Neat