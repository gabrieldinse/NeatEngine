#pragma once

#include "Core/Types.hpp"
#include "ECS/System.hpp"

#include <box2d/box2d.h>

namespace Neat {
class Physics2DSystem : public System<Physics2DSystem> {
 public:
  Physics2DSystem() = default;
  ~Physics2DSystem();

  virtual void onInitialize(const Ref<EntityManager> &entityManager,
                            const Ref<EventDispatcher> &eventDispatcher,
                            LayerID layerID = NoLayer) override;
  virtual void onShutdown(const Ref<EntityManager> &entityManager,
                          const Ref<EventDispatcher> &eventDispatcher,
                          LayerID layerID = NoLayer) override;
  virtual void onUpdate(const Ref<EntityManager> &entityManager,
                        const Ref<EventDispatcher> &eventDispatcher,
                        double deltaTimeSeconds,
                        LayerID layerID = NoLayer) override;

 private:
  b2WorldId m_worldID;
  const float bounceThreshold = 0.5f;
};
}  // namespace Neat