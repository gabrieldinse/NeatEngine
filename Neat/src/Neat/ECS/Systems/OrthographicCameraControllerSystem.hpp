#pragma once

#include "Neat/ECS/System.hpp"
#include "Neat/Events/Events/MouseScrolledEvent.hpp"
#include "Neat/Events/Events/MouseMovedEvent.hpp"
#include "Neat/Events/Events/WindowResizeEvent.hpp"
#include "Neat/Events/EventDispatcher.hpp"
#include "Neat/Graphics/Cameras/OrthographicCamera.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
class OrthographicCameraControllerSystem
    : public System<OrthographicCameraControllerSystem> {
 public:
  OrthographicCameraControllerSystem(const Ref<OrthographicCamera> &camera,
                                     bool rotationEnabled = true);
  ~OrthographicCameraControllerSystem();

  virtual void init(const Ref<EventDispatcher> &eventDispatcher) override;
  virtual void onUpdate(const Ref<EntityManager> &entityManager,
                        const Ref<EventDispatcher> &eventDispatcher,
                        double deltaTimeSeconds) override;

  Ref<OrthographicCamera> &getCamera() { return m_camera; }
  const Ref<OrthographicCamera> &getCamera() const { return m_camera; }
  void setCamera(const Ref<OrthographicCamera> &camera) { m_camera = camera; }

  bool onMouseScrolled(const MouseScrolledEvent &event);
  bool onMouseMoved(const MouseMovedEvent &event);
  bool onWindowResize(const WindowResizeEvent &event);

 private:
  void setZoomLevel(float offset, float translationSpeed = 0.2f);

 private:
  Ref<OrthographicCamera> m_camera;
  float m_maxZoomLevel = 0.25f;
  float m_zoomLevel = 1.0f;
  float m_zoomSpeed = 0.1f;
  float m_initialTranslationSpeed = 2.0f;
  float m_translationSpeed = m_initialTranslationSpeed;
  float m_rotationSpeed = 90.0f;
  float m_aspectRatio;
  Vector2F m_lastMousePosition{0.0f};
  bool m_firstMouse = true;
  bool m_rotationEnabled;
};
}  // namespace Neat