#pragma once

#include "Neat/ECS/System.hpp"

namespace Neat {
class Render2DSystem : public System<Render2DSystem> {
 public:
  Render2DSystem() = default;

  virtual void onUpdate(const Ref<EntityManager> &entityManager,
                        const Ref<EventDispatcher> &eventDispatcher,
                        double deltaTimeSeconds) override;
};
}  // namespace Neat