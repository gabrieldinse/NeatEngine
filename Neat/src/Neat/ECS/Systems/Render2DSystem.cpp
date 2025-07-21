#include "NeatPCH.hpp"

#include "Neat/ECS/Entity.hpp"
#include "Neat/Graphics/RenderCommand.hpp"
#include "Neat/Graphics/Renderer2D.hpp"
#include "Neat/ECS/Systems/Render2DSystem.hpp"
#include "Neat/ECS/Components/RenderableSpriteComponent.hpp"
#include "Neat/ECS/Components/TransformComponent.hpp"

namespace Neat {
void Render2DSystem::onUpdate(
    const Ref<EntityManager> &entityManager,
    [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
    [[maybe_unused]] double deltaTimeSeconds) {
  Neat::Renderer2D::resetStats();
  Neat::RenderCommand::clearWithColor({0.35f, 0.35f, 0.55f, 1.0f});

  Renderer2D::beginScene(m_camera);

  ComponentHandle<RenderableSpriteComponent> renderableSprite;
  ComponentHandle<TransformComponent> transform;
  for ([[maybe_unused]] auto &&entity :
       entityManager->entitiesWithComponents(renderableSprite, transform)) {
    Renderer2D::drawSprite(transform->getTransform(), *renderableSprite.get());
  }

  Renderer2D::endScene();
}
}  // namespace Neat