#pragma once

#include "Neat/ECS/Entity.hpp"
#include "Neat/Events/Events/EntityEvent.hpp"

namespace Neat {
struct EntityDestroyedEvent : public EntityEvent {
  explicit EntityDestroyedEvent(const Entity &entity) : EntityEvent(entity) {}
  virtual ~EntityDestroyedEvent() {}
};
}  // namespace Neat