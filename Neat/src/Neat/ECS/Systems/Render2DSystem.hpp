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
  Render2DSystem(Camera &camera) : m_camera(camera) {}

  virtual void onUpdate(const std::shared_ptr<EntityManager> &entityManager,
                        const std::shared_ptr<EventDispatcher> &eventDispatcher,
                        double deltaTimeSeconds);

 private:
  Camera &m_camera;
};
}  // namespace Neat