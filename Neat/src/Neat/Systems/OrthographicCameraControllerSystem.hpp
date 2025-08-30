#pragma once

#include "Neat/Debug/Debug.hpp"
#include "Neat/ECS/System.hpp"
#include "Neat/ECS/EntityManager.hpp"
#include "Neat/Events/MouseScrolledEvent.hpp"
#include "Neat/Events/MouseMovedEvent.hpp"
#include "Neat/Events/WindowResizeEvent.hpp"
#include "Neat/EventDispatching/EventDispatcher.hpp"
#include "Neat/Math/Vector.hpp"
#include "Neat/Components/CameraComponent.hpp"
#include "Neat/Components/TransformComponent.hpp"

namespace Neat {
class OrthographicCameraControllerSystem
    : public System<OrthographicCameraControllerSystem> {
 public:
  OrthographicCameraControllerSystem(const Entity &camera,
                                     bool rotationEnabled = true);
  ~OrthographicCameraControllerSystem();

  virtual void initialize(Ref<EntityManager> &entityManager,
                          Ref<EventDispatcher> &eventDispatcher) override;
  virtual void onUpdate(Ref<EntityManager> &entityManager,
                        Ref<EventDispatcher> &eventDispatcher,
                        double deltaTimeSeconds) override;

  void moveUp(TransformComponent &transform, float distance);
  void moveDown(TransformComponent &transform, float distance);
  void moveRight(TransformComponent &transform, float distance);
  void moveLeft(TransformComponent &transform, float distance);
  void incrementZoomLevel(CameraComponent &camera, float offset,
                          float translationSpeed = 0.2f);
  void setAspectRatio(CameraComponent &camera, float aspectRatio);
  void setAspectRatio(float aspectRatio);
  template <typename T, typename U>
    requires std::is_integral_v<T> and std::is_integral_v<U>
  void setAspectRatio(T width, U height) {
    NT_PROFILE_FUNCTION();
    auto camera = m_camera.getComponent<CameraComponent>();
    camera->setOrthographicAspectRatio(width, height);
  }

 private:
  bool onMouseScrolled(const MouseScrolledEvent &event);
  bool onWindowResize(const WindowResizeEvent &event);

 private:
  Ref<EntityManager> m_entityManager;
  Entity m_camera;

  float m_maxZoomLevel = 0.25f;
  float m_zoomSpeed = 0.1f;
  float m_initialTranslationSpeed = 2.0f;
  float m_translationSpeed = m_initialTranslationSpeed;
  float m_rotationSpeed = 90.0f;
  Vector2F m_lastMousePosition{0.0f};
  bool m_rotationEnabled;
};
}  // namespace Neat