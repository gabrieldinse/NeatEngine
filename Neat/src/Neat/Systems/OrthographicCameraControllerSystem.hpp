#pragma once

#include "Neat/Debug/Debug.hpp"
#include "Neat/ECS/System.hpp"
#include "Neat/ECS/EntityManager.hpp"
#include "Neat/Events/MouseScrolledEvent.hpp"
#include "Neat/Events/MouseMovedEvent.hpp"
#include "Neat/EventDispatching/EventDispatcher.hpp"
#include "Neat/Math/Vector.hpp"
#include "Neat/Components/CameraComponent.hpp"
#include "Neat/Components/TransformComponent.hpp"

namespace Neat {
class OrthographicCameraControllerSystem
    : public System<OrthographicCameraControllerSystem> {
 public:
  OrthographicCameraControllerSystem(bool rotationEnabled = true);
  ~OrthographicCameraControllerSystem();

  virtual void initialize(const Ref<EntityManager> &entityManager,
                          const Ref<EventDispatcher> &eventDispatcher) override;
  virtual void onUpdate(const Ref<EntityManager> &entityManager,
                        const Ref<EventDispatcher> &eventDispatcher,
                        double deltaTimeSeconds) override;

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