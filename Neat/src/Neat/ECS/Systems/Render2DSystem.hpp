#pragma once

#include "Neat/ECS/System.hpp"
#include "Neat/Graphics/Cameras/Camera.hpp"

namespace Neat {
class Render2DSystem : public System<Render2DSystem> {
 public:
  Render2DSystem(const Ref<Camera> &camera) : m_camera(camera) {}

  virtual void onUpdate(const Ref<EntityManager> &entityManager,
                        const Ref<EventDispatcher> &eventDispatcher,
                        double deltaTimeSeconds) override;

 private:
  Ref<Camera> m_camera;
};
}  // namespace Neat