#pragma once

#include "Neat/ECS/Components/Renderable.hpp"
#include "Neat/ECS/Entity.hpp"
#include "Neat/ECS/System.hpp"
#include "Neat/Graphics/Cameras/Camera.hpp"
#include "Neat/Graphics/RenderCommand.hpp"
#include "Neat/Graphics/Renderer2D.hpp"

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