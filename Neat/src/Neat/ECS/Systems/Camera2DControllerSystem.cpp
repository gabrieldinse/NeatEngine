#include "NeatPCH.hpp"

#include "Neat/ECS/Systems/Camera2DControllerSystem.hpp"
#include "Neat/Core/Application.hpp"
#include "Neat/Core/Input.hpp"
#include "Neat/Math/Transform.hpp"

namespace Neat {
Camera2DControllerSystem::Camera2DControllerSystem(float aspectRatio,
                                                   bool rotationEnabled)
    : m_camera(Vector2F(0.0f), aspectRatio),
      m_aspectRatio(aspectRatio),
      m_rotationEnabled(rotationEnabled) {}

Camera2DControllerSystem::~Camera2DControllerSystem() {}

void Camera2DControllerSystem::init(
    const std::shared_ptr<EventDispatcher> &eventDispatcher) {
  eventDispatcher->get<MouseMovedEvent>()
      .connect<&Camera2DControllerSystem::onMouseMoved>(*this);
  eventDispatcher->get<MouseScrolledEvent>()
      .connect<&Camera2DControllerSystem::onMouseScrolled>(*this);
  eventDispatcher->get<WindowResizeEvent>()
      .connect<&Camera2DControllerSystem::onWindowResize>(*this);
}

void Camera2DControllerSystem::onUpdate(
    [[maybe_unused]] const std::shared_ptr<EntityManager> &entityManager,
    [[maybe_unused]] const std::shared_ptr<EventDispatcher> &eventDispatcher,
    double deltaTimeSeconds) {
  auto distance = (float)(m_translationSpeed * deltaTimeSeconds);
  if (Input::isKeyPressed(Key::W)) m_camera.moveUp(distance);

  if (Input::isKeyPressed(Key::S)) m_camera.moveDown(distance);

  if (Input::isKeyPressed(Key::D)) m_camera.moveRight(distance);

  if (Input::isKeyPressed(Key::A)) m_camera.moveLeft(distance);

  if (m_rotationEnabled) {
    auto rotation = (float)(m_rotationSpeed * deltaTimeSeconds);
    if (Input::isKeyPressed(Key::Q))
      m_camera.setRotation(wrap360(m_camera.getRotation() + rotation));

    if (Input::isKeyPressed(Key::E))
      m_camera.setRotation(wrap360(m_camera.getRotation() - rotation));
  }
}

bool Camera2DControllerSystem::onMouseScrolled(
    const MouseScrolledEvent &event) {
  m_zoomLevel -= event.yOffset * 0.2f;
  m_zoomLevel = std::max(m_zoomLevel, 0.25f);
  m_translationSpeed = 2.0f * m_zoomLevel;
  m_camera.setZoomLevel(m_zoomLevel);

  return false;
}

bool Camera2DControllerSystem::onMouseMoved(const MouseMovedEvent &event) {
  if (m_firstMouse) {
    m_lastMousePosition = Vector2F(event.xPos, event.yPos);
    m_firstMouse = false;
  }

  Vector2F current_mouse_position(event.xPos, event.yPos);

  const auto &window = Application::get().getWindow();
  const auto scale_factor = 2.0f * m_zoomLevel / (float)window.getHeight();

  auto mouse_possition_offset = current_mouse_position - m_lastMousePosition;
  auto screen_position_offset =
      rotateZ(radians(m_camera.getRotation())) *
      scale(Vector3F(-scale_factor, scale_factor, 1.0f)) *
      Vector4F(mouse_possition_offset, 0.0f, 1.0f);

  m_camera.move(Vector2F(screen_position_offset));
  m_lastMousePosition = current_mouse_position;

  return false;
}

bool Camera2DControllerSystem::onWindowResize(const WindowResizeEvent &event) {
  m_aspectRatio = (float)event.width / (float)event.height;
  m_camera.setSize(m_aspectRatio);

  return false;
}
}  // namespace Neat