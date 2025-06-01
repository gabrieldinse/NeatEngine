#pragma once

#include "Neat/Events/Events/EntityEvent.hpp"

namespace Neat {
struct EntityCreatedEvent : public EntityEvent {
  explicit EntityCreatedEvent(const Entity &entity) : EntityEvent(entity) {}
  virtual ~EntityCreatedEvent() {}
};
}  // namespace Neat