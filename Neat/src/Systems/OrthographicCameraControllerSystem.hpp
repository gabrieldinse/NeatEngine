#pragma once

#include "Debug/Debug.hpp"
#include "ECS/System.hpp"
#include "ECS/EntityManager.hpp"
#include "Events/MouseScrolledEvent.hpp"
#include "Events/MouseMovedEvent.hpp"
#include "EventDispatching/EventDispatcher.hpp"
#include "Math/Vector.hpp"
#include "Components/CameraComponent.hpp"
#include "Components/TransformComponent.hpp"

namespace Neat {
class OrthographicCameraControllerSystem
    : public System<OrthographicCameraControllerSystem> {
 public:
  OrthographicCameraControllerSystem(bool rotationEnabled = true);
  ~OrthographicCameraControllerSystem();

  virtual void onInitialize(const Ref<EntityManager> &entityManager,
                            const Ref<EventDispatcher> &eventDispatcher,
                            LayerID layerID = NoneLayer) override;
  virtual void onUpdate(const Ref<EntityManager> &entityManager,
                        const Ref<EventDispatcher> &eventDispatcher,
                        double deltaTimeSeconds,
                        LayerID layerID = NoneLayer) override;

 private:
  void moveUp(TransformComponent &transform, float distance);
  void moveDown(TransformComponent &transform, float distance);
  void moveRight(TransformComponent &transform, float distance);
  void moveLeft(TransformComponent &transform, float distance);
  void incrementZoomLevel(CameraComponent &camera, float offset,
                          float translationSpeed = 0.2f);
  bool onMouseScrolled(const MouseScrolledEvent &event);
  std::optional<Entity> getCamera();

 private:
  Ref<EntityManager> m_entityManager;

  float m_maxSize = 0.5f;
  float m_sizeIncreaseSpeed = 0.2f;
  float m_initialTranslationSpeed = 2.0f;
  float m_translationSpeed = m_initialTranslationSpeed;
  float m_rotationSpeed = 90.0f;
  Vector2F m_lastMousePosition{0.0f};
  bool m_rotationEnabled;
};
}  // namespace Neat