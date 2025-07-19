#include "NeatPCH.hpp"

#include "Neat/ECS/Systems/Camera2DControllerSystem.hpp"
#include "Neat/Core/Application.hpp"
#include "Neat/Core/Input.hpp"
#include "Neat/Math/Transform.hpp"

namespace Neat {
Camera2DControllerSystem::Camera2DControllerSystem(float aspectRatio,
                                                   bool rotationEnabled)
    : m_camera(makeRef<OrthographicCamera>(Vector2F(0.0f), aspectRatio)),
      m_aspectRatio(aspectRatio),
      m_rotationEnabled(rotationEnabled) {}

Camera2DControllerSystem::~Camera2DControllerSystem() {}

void Camera2DControllerSystem::init(
    const Ref<EventDispatcher> &eventDispatcher) {
  eventDispatcher->get<MouseScrolledEvent>()
      .connect<&Camera2DControllerSystem::onMouseScrolled>(*this);
  eventDispatcher->get<WindowResizeEvent>()
      .connect<&Camera2DControllerSystem::onWindowResize>(*this);
}

void Camera2DControllerSystem::onUpdate(
    [[maybe_unused]] const Ref<EntityManager> &entityManager,
    [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
    double deltaTimeSeconds) {
  auto distance = (float)(m_translationSpeed * deltaTimeSeconds);
  if (Input::isKeyPressed(Key::W)) m_camera->moveUp(distance);

  if (Input::isKeyPressed(Key::S)) m_camera->moveDown(distance);

  if (Input::isKeyPressed(Key::D)) m_camera->moveRight(distance);

  if (Input::isKeyPressed(Key::A)) m_camera->moveLeft(distance);

  if (m_rotationEnabled) {
    auto rotation = (float)(m_rotationSpeed * deltaTimeSeconds);
    if (Input::isKeyPressed(Key::Q)) m_camera->incrementRotation(rotation);

    if (Input::isKeyPressed(Key::E)) m_camera->incrementRotation(-rotation);
  }
}

bool Camera2DControllerSystem::onMouseScrolled(
    const MouseScrolledEvent &event) {
  m_zoomLevel -= event.yOffset * 0.2f;
  m_zoomLevel = std::max(m_zoomLevel, 0.25f);
  m_translationSpeed = 2.0f * m_zoomLevel;
  m_camera->setZoomLevel(m_zoomLevel);

  return false;
}

bool Camera2DControllerSystem::onWindowResize(const WindowResizeEvent &event) {
  m_aspectRatio = (float)event.width / (float)event.height;
  m_camera->setAspectRatio(m_aspectRatio);

  return false;
}
}  // namespace Neat