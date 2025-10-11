#include "NeatPCH.hpp"

#include "OrthographicCameraControllerSystem.hpp"

#include "Core/Application.hpp"
#include "Core/Input.hpp"
#include "Math/Transform.hpp"
#include "ECS/EntityManager.hpp"
#include "Components/ActiveCameraTagComponent.hpp"

namespace Neat {
OrthographicCameraControllerSystem::OrthographicCameraControllerSystem(
    bool rotationEnabled)
    : m_rotationEnabled(rotationEnabled) {}

OrthographicCameraControllerSystem::~OrthographicCameraControllerSystem() {}

void OrthographicCameraControllerSystem::onInitialize(
    const Ref<EntityManager> &entityManager,
    const Ref<EventDispatcher> &eventDispatcher,
    [[maybe_unused]] LayerID layerID) {
  eventDispatcher->get<MouseScrolledEvent>()
      .connect<&OrthographicCameraControllerSystem::onMouseScrolled>(*this);
  m_entityManager = entityManager;
}

void OrthographicCameraControllerSystem::onUpdate(
    [[maybe_unused]] const Ref<EntityManager> &entityManager,
    [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
    double deltaTimeSeconds, [[maybe_unused]] LayerID layerID) {
  NT_PROFILE_FUNCTION();

  auto mainCamera = getCamera();
  if (not mainCamera) {
    return;
  }

  Entity cameraEntity = *mainCamera;
  auto cameraOpt = cameraEntity.getComponent<CameraComponent>();
  if (not cameraOpt) {
    return;
  }

  auto camera = *cameraOpt;
  if (camera->getType() != CameraType::Orthographic) {
    return;
  }

  auto distance = static_cast<float>(m_translationSpeed * deltaTimeSeconds);
  auto transformOpt = cameraEntity.getComponent<TransformComponent>();
  if (not transformOpt) {
    return;
  }

  auto transform = *transformOpt;

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
  auto mainCamera = getCamera();
  if (not mainCamera) {
    return false;
  }

  Entity cameraEntity = *mainCamera;
  auto cameraOpt = cameraEntity.getComponent<CameraComponent>();
  if (not cameraOpt) {
    return false;
  }
  auto camera = *cameraOpt;
  incrementZoomLevel(*camera, -event.yOffset);

  return false;
}

std::optional<Entity> OrthographicCameraControllerSystem::getCamera() {
  for (auto entity :
       m_entityManager->entitiesWithComponents<
           ActiveCameraTagComponent, CameraComponent, TransformComponent>()) {
    return entity;
  }
  return std::nullopt;
}

}  // namespace Neat