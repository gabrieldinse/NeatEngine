#include "NeatPCH.hpp"

#include "Neat/Systems/OrthographicCameraControllerSystem.hpp"
#include "Neat/Core/Application.hpp"
#include "Neat/Core/Input.hpp"
#include "Neat/Math/Transform.hpp"

namespace Neat {
OrthographicCameraControllerSystem::OrthographicCameraControllerSystem(
    const Ref<OrthographicCamera> &camera, bool rotationEnabled)
    : m_camera(camera),
      m_zoomLevel(camera->getZoomLevel()),
      m_rotationEnabled(rotationEnabled) {}

OrthographicCameraControllerSystem::~OrthographicCameraControllerSystem() {}

void OrthographicCameraControllerSystem::init(
    const Ref<EventDispatcher> &eventDispatcher) {
  eventDispatcher->get<MouseScrolledEvent>()
      .connect<&OrthographicCameraControllerSystem::onMouseScrolled>(*this);
  eventDispatcher->get<WindowResizeEvent>()
      .connect<&OrthographicCameraControllerSystem::onWindowResize>(*this);
}

void OrthographicCameraControllerSystem::onUpdate(
    [[maybe_unused]] const Ref<EntityManager> &entityManager,
    [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
    double deltaTimeSeconds) {
  NT_PROFILE_FUNCTION();
  auto distance = (float)(m_translationSpeed * deltaTimeSeconds);
  if (Input::isKeyPressed(Key::W)) {
    m_camera->moveUp(distance);
  }

  if (Input::isKeyPressed(Key::S)) {
    m_camera->moveDown(distance);
  }

  if (Input::isKeyPressed(Key::D)) {
    m_camera->moveRight(distance);
  }

  if (Input::isKeyPressed(Key::A)) {
    m_camera->moveLeft(distance);
  }

  if (Input::isKeyPressed(Key::Up)) {
    setZoomLevel(m_zoomSpeed);
  }

  if (Input::isKeyPressed(Key::Down)) {
    setZoomLevel(-m_zoomSpeed);
  }

  if (m_rotationEnabled) {
    auto rotation = (float)(m_rotationSpeed * deltaTimeSeconds);
    if (Input::isKeyPressed(Key::Q)) {
      m_camera->incrementRotation(rotation);
    }

    if (Input::isKeyPressed(Key::E)) {
      m_camera->incrementRotation(-rotation);
    }
  }
}

void OrthographicCameraControllerSystem::setZoomLevel(
    float offset, float zoomTranslationSpeed) {
  m_zoomLevel -= offset * zoomTranslationSpeed;
  m_zoomLevel = std::max(m_zoomLevel, m_maxZoomLevel);
  m_translationSpeed = m_initialTranslationSpeed * m_zoomLevel;
  m_camera->setZoomLevel(m_zoomLevel);
}

bool OrthographicCameraControllerSystem::onMouseScrolled(
    const MouseScrolledEvent &event) {
  NT_PROFILE_FUNCTION();
  setZoomLevel(-event.yOffset);

  return false;
}

bool OrthographicCameraControllerSystem::onWindowResize(
    const WindowResizeEvent &event) {
  NT_PROFILE_FUNCTION();
  m_camera->setAspectRatio(event.width, event.height);

  return false;
}
}  // namespace Neat