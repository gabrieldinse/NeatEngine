#include "NeatPCH.hpp"

#include "Neat/ECS/Systems/Render2DSystem.hpp"

namespace Neat {
void Render2DSystem::onUpdate(
    const Ref<EntityManager> &entityManager,
    [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
    [[maybe_unused]] double deltaTimeSeconds) {
  Neat::Renderer2D::resetStats();
  Neat::RenderCommand::clearWithColor({0.35f, 0.35f, 0.55f, 1.0f});

  Renderer2D::beginScene(m_camera);

  ComponentHandle<Renderable> renderable;
  for ([[maybe_unused]] auto &&entity :
       entityManager->entitiesWithComponents(renderable)) {
    renderable->shape->draw();
  }

  Renderer2D::endScene();
}
}  // namespace Neat