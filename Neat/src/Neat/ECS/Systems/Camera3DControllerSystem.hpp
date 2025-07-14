#pragma once

#include "Neat/ECS/System.hpp"
#include "Neat/Events/Events/MouseScrolledEvent.hpp"
#include "Neat/Events/Events/MouseMovedEvent.hpp"
#include "Neat/Events/Events/WindowResizeEvent.hpp"
#include "Neat/Events/EventDispatcher.hpp"
#include "Neat/Graphics/Cameras/Camera.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
class Camera3DControllerSystem : public System<Camera3DControllerSystem> {
 public:
  Camera3DControllerSystem(float aspectRatio, bool rotationEnabled = true);

  ~Camera3DControllerSystem();

  virtual void init(const Ref<EventDispatcher> &eventDispatcher) override;
  virtual void onUpdate(const Ref<EntityManager> &entityManager,
                        const Ref<EventDispatcher> &eventDispatcher,
                        double deltaTimeSeconds) override;

  Camera &getCamera() { return m_camera; }
  const Camera &getCamera() const { return m_camera; }

  bool onMouseScrolled(const MouseScrolledEvent &event);
  bool onMouseMoved(const MouseMovedEvent &event);
  bool onWindowResize(const WindowResizeEvent &event);

 private:
  Camera m_camera;
  float m_translationSpeed = 0.0f;
  float m_rotationSpeed = 90.0f;
  float m_mouseSensitivity = 0.2f;
  Vector2F m_lastMousePosition;
  bool m_firstMouse = true;
  bool m_rotationEnabled;
};
}  // namespace Neat