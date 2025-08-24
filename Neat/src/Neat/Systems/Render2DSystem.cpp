#include "NeatPCH.hpp"

#include "Neat/ECS/Entity.hpp"
#include "Neat/Graphics/RenderCommand.hpp"
#include "Neat/Graphics/Renderer2D.hpp"
#include "Neat/Systems/Render2DSystem.hpp"
#include "Neat/Components/RenderableSpriteComponent.hpp"
#include "Neat/Components/TransformComponent.hpp"
#include "Neat/Components/CameraComponent.hpp"
#include "Neat/Components/MainCameraTagComponent.hpp"

namespace Neat {
void Render2DSystem::onUpdate(
    Ref<EntityManager> &entityManager,
    [[maybe_unused]] Ref<EventDispatcher> &eventDispatcher,
    [[maybe_unused]] double deltaTimeSeconds) {
  NT_PROFILE_FUNCTION();
  Neat::Renderer2D::resetStats();
  Neat::RenderCommand::clearWithColor({0.35f, 0.35f, 0.55f, 1.0f});

  for (auto entity :
       entityManager->entitiesWithComponents<
           MainCameraTagComponent, CameraComponent, TransformComponent>()) {
    auto camera = entity.getComponent<CameraComponent>();
    auto cameraTransform = entity.getComponent<TransformComponent>();
    Renderer2D::beginScene(*camera, *cameraTransform);

    ComponentHandle<RenderableSpriteComponent> renderableSprite;
    ComponentHandle<TransformComponent> transform;
    for ([[maybe_unused]] auto entity :
         entityManager->entitiesWithComponents(renderableSprite, transform)) {
      Renderer2D::drawSprite(*transform, *renderableSprite);
      Renderer2D::endScene();
    }
  }
}
}  // namespace Neat