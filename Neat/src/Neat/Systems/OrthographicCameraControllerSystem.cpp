#include "NeatPCH.hpp"

#include "Neat/Systems/OrthographicCameraControllerSystem.hpp"
#include "Neat/Core/Application.hpp"
#include "Neat/Core/Input.hpp"
#include "Neat/Math/Transform.hpp"
#include "Neat/ECS/EntityManager.hpp"

namespace Neat {
OrthographicCameraControllerSystem::OrthographicCameraControllerSystem(
    const Entity &camera, bool rotationEnabled)
    : m_camera(camera), m_rotationEnabled(rotationEnabled) {}

OrthographicCameraControllerSystem::~OrthographicCameraControllerSystem() {}

void OrthographicCameraControllerSystem::initialize(
    Ref<EntityManager> &entityManager, Ref<EventDispatcher> &eventDispatcher) {
  eventDispatcher->get<MouseScrolledEvent>()
      .connect<&OrthographicCameraControllerSystem::onMouseScrolled>(*this);
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
    incrementZoomLevel(*camera, m_sizeIncreaseSpeed);
  }

  if (Input::isKeyPressed(Key::Down)) {
    incrementZoomLevel(*camera, -m_sizeIncreaseSpeed);
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

void OrthographicCameraControllerSystem::incrementZoomLevel(
    CameraComponent &camera, float offset, float zoomTranslationSpeed) {
  NT_PROFILE_FUNCTION();
  float size = camera.getOrthographicSize();
  size -= offset * zoomTranslationSpeed;
  size = std::max(size, m_maxSize);
  m_translationSpeed = m_initialTranslationSpeed * size;
  camera.setOrthographicSize(size);
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
  transform.incrementPosition(
      cos(degreesToRadians(transform.getRotationZ())) * distance,
      sin(degreesToRadians(transform.getRotationZ())) * distance);
}

void OrthographicCameraControllerSystem::moveLeft(TransformComponent &transform,
                                                  float distance) {
  NT_PROFILE_FUNCTION();
  transform.incrementPosition(
      -cos(degreesToRadians(transform.getRotationZ())) * distance,
      -sin(degreesToRadians(transform.getRotationZ())) * distance);
}

bool OrthographicCameraControllerSystem::onMouseScrolled(
    const MouseScrolledEvent &event) {
  NT_PROFILE_FUNCTION();
  auto camera = m_camera.getComponent<CameraComponent>();
  incrementZoomLevel(*camera, -event.yOffset);

  return false;
}

}  // namespace Neat