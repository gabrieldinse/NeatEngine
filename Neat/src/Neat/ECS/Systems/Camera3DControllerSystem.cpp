#include "NeatPCH.hpp"

#include "Neat/ECS/Systems/Camera3DControllerSystem.hpp"
#include "Neat/Core/Application.hpp"
#include "Neat/Core/Input.hpp"
#include "Neat/Math/Trigonometric.hpp"

namespace Neat {
Camera3DControllerSystem::Camera3DControllerSystem(float aspectRatio,
                                                   bool rotationEnabled)
    : m_rotationEnabled(rotationEnabled) {
  m_camera.setPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
  m_translationSpeed = m_camera.getFieldOfView() * 0.5f;
}

Camera3DControllerSystem::~Camera3DControllerSystem() {}

void Camera3DControllerSystem::init(
    const std::shared_ptr<EventDispatcher> &eventDispatcher) {
  eventDispatcher->get<MouseMovedEvent>()
      .connect<&Camera3DControllerSystem::onMouseMoved>(*this);
  eventDispatcher->get<MouseScrolledEvent>()
      .connect<&Camera3DControllerSystem::onMouseScrolled>(*this);
  eventDispatcher->get<WindowResizeEvent>()
      .connect<&Camera3DControllerSystem::onWindowResize>(*this);
}

void Camera3DControllerSystem::onUpdate(
    [[maybe_unused]] const std::shared_ptr<EntityManager> &entityManager,
    [[maybe_unused]] const std::shared_ptr<EventDispatcher> &eventDispatcher,
    double deltaTimeSeconds) {
  auto distance = (float)(m_translationSpeed * deltaTimeSeconds);
  if (Input::isKeyPressed(Key::W)) m_camera.moveForward(distance);

  if (Input::isKeyPressed(Key::S)) m_camera.moveBackward(distance);

  if (Input::isKeyPressed(Key::D)) m_camera.moveRight(distance);

  if (Input::isKeyPressed(Key::A)) m_camera.moveLeft(distance);

  if (Input::isKeyPressed(Key::Z)) m_camera.moveUp(distance);

  if (Input::isKeyPressed(Key::X)) m_camera.moveDown(distance);

  if (m_rotationEnabled) {
    auto rotation = (float)(m_rotationSpeed * deltaTimeSeconds);
    if (Input::isKeyPressed(Key::Q))
      m_camera.setRoll(wrap360(m_camera.getRoll() + rotation));

    if (Input::isKeyPressed(Key::E))
      m_camera.setRoll(wrap360(m_camera.getRoll() - rotation));
  }
}

bool Camera3DControllerSystem::onMouseScrolled(
    const MouseScrolledEvent &event) {
  auto fov = clamp(-event.yOffset + m_camera.getFieldOfView(), 1.0f, 60.0f);
  m_translationSpeed = fov * 0.5f;
  m_camera.setFieldOfView(fov);

  return false;
}

bool Camera3DControllerSystem::onMouseMoved(const MouseMovedEvent &event) {
  if (m_firstMouse) {
    m_lastMousePosition = Vector2F(event.xPos, event.yPos);
    m_firstMouse = false;
  }

  Vector2F current_mouse_position(event.xPos, event.yPos);
  auto mouse_position_offset = current_mouse_position - m_lastMousePosition;
  m_lastMousePosition = current_mouse_position;

  auto yaw_offset = -m_mouseSensitivity * mouse_position_offset.x;
  auto pitch_offset = -m_mouseSensitivity * mouse_position_offset.y;
  m_camera.setYaw(wrap360(yaw_offset + m_camera.getYaw()));
  m_camera.setPitch(wrap360(pitch_offset + m_camera.getPitch()));

  return false;
}

bool Camera3DControllerSystem::onWindowResize(const WindowResizeEvent &event) {
  m_camera.setAspectRatio((float)event.width / (float)event.height);

  return false;
}
}  // namespace Neat