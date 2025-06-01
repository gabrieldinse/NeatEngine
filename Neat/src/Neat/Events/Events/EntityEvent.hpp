#pragma once

#include "Neat/Events/Events/ECSEvent.hpp"
#include "Neat/ECS/Entity.hpp"

namespace Neat {
struct EntityEvent : public ECSEvent {
  explicit EntityEvent(const Entity &entity) : entity(entity) {}
  virtual ~EntityEvent() {}

  Entity entity;
};
}  // namespace Neat