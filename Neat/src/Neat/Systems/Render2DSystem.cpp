#include "NeatPCH.hpp"

#include "Render2DSystem.hpp"

#include "Neat/ECS/EntityManager.hpp"
#include "Neat/Graphics/RenderCommand.hpp"
#include "Neat/Graphics/Renderer2D.hpp"
#include "Neat/Components/RenderableSpriteComponent.hpp"
#include "Neat/Components/TransformComponent.hpp"
#include "Neat/Components/CameraComponent.hpp"
#include "Neat/Components/ActiveCameraTagComponent.hpp"

namespace Neat {
void Render2DSystem::onUpdate(
    Ref<EntityManager> &entityManager,
    [[maybe_unused]] Ref<EventDispatcher> &eventDispatcher,
    [[maybe_unused]] double deltaTimeSeconds) {
  NT_PROFILE_FUNCTION();

  Renderer2D::resetStats();
  RenderCommand::clearWithColor(Color::lightSlateGray);

  for (auto entity :
       entityManager->entitiesWithComponents<
           ActiveCameraTagComponent, CameraComponent, TransformComponent>()) {
    auto camera = entity.getComponent<CameraComponent>();
    auto cameraTransform = entity.getComponent<TransformComponent>();
    Renderer2D::beginScene(*camera, *cameraTransform);

    ComponentHandle<RenderableSpriteComponent> renderableSprite;
    ComponentHandle<TransformComponent> transform;
    for ([[maybe_unused]] auto entity :
         entityManager->entitiesWithComponents(renderableSprite, transform)) {
      Renderer2D::drawSprite(*transform, *renderableSprite);
    }
    Renderer2D::endScene();
    break;
  }
}
}  // namespace Neat