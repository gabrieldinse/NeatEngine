#pragma once

#include "Neat/Events/Events/ECSEvent.hpp"
#include "Neat/ECS/ComponentHandle.hpp"

namespace Neat {
template <typename C>
struct ComponentEvent : public ECSEvent {
  ComponentEvent(const Entity &entity, const ComponentHandle<C> &component)
      : entity(entity), component(component) {}
  virtual ~ComponentEvent() = default;

  Entity entity;
  ComponentHandle<C> component;
};
}  // namespace Neat