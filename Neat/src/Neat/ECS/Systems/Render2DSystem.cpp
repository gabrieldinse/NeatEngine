#include "Neat/ECS/Systems/Render2DSystem.hpp"

namespace Neat {
void Render2DSystem::onUpdate(
    const std::shared_ptr<EntityManager> &entityManager,
    const std::shared_ptr<EventDispatcher> &eventDispatcher,
    double deltaTimeSeconds) {
  Neat::Renderer2D::resetStats();
  Neat::RenderCommand::clearWithColor({0.35f, 0.35f, 0.55f, 1.0f});

  Renderer2D::beginScene(m_camera);

  ComponentHandle<Renderable> renderable;
  for (auto &&entity : entityManager->entitiesWithComponents(renderable)) {
    renderable->shape->draw();
  }

  Renderer2D::endScene();
}
}  // namespace Neat