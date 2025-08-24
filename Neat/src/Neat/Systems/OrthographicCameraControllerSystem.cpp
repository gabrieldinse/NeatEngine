#include "NeatPCH.hpp"

#include "Neat/Systems/OrthographicCameraControllerSystem.hpp"
#include "Neat/Core/Application.hpp"
#include "Neat/Core/Input.hpp"
#include "Neat/Math/Transform.hpp"
#include "Neat/ECS/Entity.hpp"

namespace Neat {
OrthographicCameraControllerSystem::OrthographicCameraControllerSystem(
    const Entity &camera, bool rotationEnabled)
    : m_camera(camera), m_rotationEnabled(rotationEnabled) {}

OrthographicCameraControllerSystem::~OrthographicCameraControllerSystem() {}

void OrthographicCameraControllerSystem::init(
    Ref<EntityManager> &entityManager, Ref<EventDispatcher> &eventDispatcher) {
  eventDispatcher->get<MouseScrolledEvent>()
      .connect<&OrthographicCameraControllerSystem::onMouseScrolled>(*this);
  eventDispatcher->get<WindowResizeEvent>()
      .connect<&OrthographicCameraControllerSystem::onWindowResize>(*this);
  m_entityManager = entityManager;
}

void OrthographicCameraControllerSystem::onUpdate(
    [[maybe_unused]] Ref<EntityManager> &entityManager,
    [[maybe_unused]] Ref<EventDispatcher> &eventDispatcher,
    double deltaTimeSeconds) {
  NT_PROFILE_FUNCTION();

  auto distance = static_cast<float>(m_translationSpeed * deltaTimeSeconds);
  auto camera = m_camera.getComponent<CameraComponent>();
  auto transform = m_camera.getComponent<TransformComponent>();

  if (Input::isKeyPressed(Key::W)) {
    moveUp(*transform, distance);
  }

  if (Input::isKeyPressed(Key::S)) {
    moveDown(*transform, distance);
  }

  if (Input::isKeyPressed(Key::D)) {
    moveRight(*transform, distance);
  }

  if (Input::isKeyPressed(Key::A)) {
    moveLeft(*transform, distance);
  }

  if (Input::isKeyPressed(Key::Up)) {
    incrementZoomLevel(*camera, m_zoomSpeed);
  }

  if (Input::isKeyPressed(Key::Down)) {
    incrementZoomLevel(*camera, -m_zoomSpeed);
  }

  if (m_rotationEnabled) {
    auto rotation = (float)(m_rotationSpeed * deltaTimeSeconds);
    if (Input::isKeyPressed(Key::Q)) {
      transform->incrementRotation(rotation);
    }

    if (Input::isKeyPressed(Key::E)) {
      transform->incrementRotation(-rotation);
    }
  }
}

void OrthographicCameraControllerSystem::updateCameraProjection(
    CameraComponent &camera) {
  float aspectRatio = m_right / m_top;
  m_bottom = -m_zoomLevel;
  m_top = m_zoomLevel;
  m_left = -aspectRatio * m_zoomLevel;
  m_right = aspectRatio * m_zoomLevel;
  camera.setOrthographic(m_left, m_right, m_bottom, m_top, m_near, m_far);
}

void OrthographicCameraControllerSystem::incrementZoomLevel(
    CameraComponent &camera, float offset, float zoomTranslationSpeed) {
  NT_PROFILE_FUNCTION();
  m_zoomLevel -= offset * zoomTranslationSpeed;
  m_zoomLevel = std::max(m_zoomLevel, m_maxZoomLevel);
  m_translationSpeed = m_initialTranslationSpeed * m_zoomLevel;
  updateCameraProjection(camera);
}

void OrthographicCameraControllerSystem::moveUp(TransformComponent &transform,
                                                float distance) {
  NT_PROFILE_FUNCTION();
  transform.incrementPosition(
      -sin(degreesToRadians(transform.getRotationZ())) * distance,
      cos(degreesToRadians(transform.getRotationZ())) * distance);
}

void OrthographicCameraControllerSystem::moveDown(TransformComponent &transform,
                                                  float distance) {
  NT_PROFILE_FUNCTION();
  transform.incrementPosition(
      sin(degreesToRadians(transform.getRotationZ())) * distance,
      -cos(degreesToRadians(transform.getRotationZ())) * distance);
}

void OrthographicCameraControllerSystem::moveRight(
    TransformComponent &transform, float distance) {
  NT_PROFILE_FUNCTION();
  transform.incrementPosition(cos(degreesToRadians(m_rotation)) * distance,
                              sin(degreesToRadians(m_rotation)) * distance);
}

void OrthographicCameraControllerSystem::moveLeft(TransformComponent &transform,
                                                  float distance) {
  NT_PROFILE_FUNCTION();
  transform.incrementPosition(-cos(degreesToRadians(m_rotation)) * distance,
                              -sin(degreesToRadians(m_rotation)) * distance);
}

void OrthographicCameraControllerSystem::setAspectRatio(CameraComponent &camera,
                                                        float aspectRatio) {
  NT_PROFILE_FUNCTION();
  m_zoomLevel = m_top;
  m_left = -aspectRatio * m_zoomLevel;
  m_right = aspectRatio * m_zoomLevel;
  camera.setOrthographic(m_left, m_right, m_bottom, m_top, m_near, m_far);
}

void OrthographicCameraControllerSystem::setAspectRatio(float aspectRatio) {
  NT_PROFILE_FUNCTION();
  auto camera = m_camera.getComponent<CameraComponent>();
  setAspectRatio(*camera, aspectRatio);
}

void OrthographicCameraControllerSystem::setAspectRatio(UInt32 width,
                                                        UInt32 height) {
  NT_PROFILE_FUNCTION();
  auto camera = m_camera.getComponent<CameraComponent>();
  setAspectRatio(*camera,
                 static_cast<float>(width) / static_cast<float>(height));
}

bool OrthographicCameraControllerSystem::onWindowResize(
    const WindowResizeEvent &event) {
  NT_PROFILE_FUNCTION();
  setAspectRatio(static_cast<float>(event.width) /
                 static_cast<float>(event.height));

  return false;
}

bool OrthographicCameraControllerSystem::onMouseScrolled(
    const MouseScrolledEvent &event) {
  NT_PROFILE_FUNCTION();
  auto camera = m_camera.getComponent<CameraComponent>();
  incrementZoomLevel(*camera, -event.yOffset);

  return false;
}

}  // namespace Neat