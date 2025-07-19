#include "NeatPCH.hpp"

#include "Neat/Graphics/Cameras/OrthographicCamera.hpp"
#include "Neat/Math/EulerAngles.hpp"
#include "Neat/Math/Projection.hpp"
#include "Neat/Math/Quaternion.hpp"
#include "Neat/Math/Transform.hpp"

namespace Neat {
OrthographicCamera::OrthographicCamera(const Vector2F &position, float size,
                                       KeepAspect keepAspect)
    : m_position(Vector3F(position, m_zPos)),
      m_aspectRatio(size),
      m_keepAspect(keepAspect) {
  setAspectRatio(m_aspectRatio);
}

void OrthographicCamera::setPosition(const Vector2F &position) {
  m_position.x = position.x;
  m_position.y = position.y;
  updateCameraTransform();
}

void OrthographicCamera::setRotation(float rotation) {
  m_rotation = rotation;
  updateCameraTransform();
}

void OrthographicCamera::incrementPosition(const Vector2F &position) {
  m_position.x += position.x;
  m_position.y += position.y;
  updateCameraTransform();
}

void OrthographicCamera::incrementRotation(float rotation) {
  m_rotation += rotation;
  updateCameraTransform();
}

void OrthographicCamera::moveUp(float distance) {
  m_position.x += -sin(degreesToRadians(m_rotation)) * distance;
  m_position.y += cos(degreesToRadians(m_rotation)) * distance;
  updateCameraTransform();
}

void OrthographicCamera::moveDown(float distance) {
  m_position.x -= -sin(degreesToRadians(m_rotation)) * distance;
  m_position.y -= cos(degreesToRadians(m_rotation)) * distance;
  updateCameraTransform();
}

void OrthographicCamera::moveRight(float distance) {
  m_position.x += cos(degreesToRadians(m_rotation)) * distance;
  m_position.y += sin(degreesToRadians(m_rotation)) * distance;
  updateCameraTransform();
}

void OrthographicCamera::moveLeft(float distance) {
  m_position.x -= cos(degreesToRadians(m_rotation)) * distance;
  m_position.y -= sin(degreesToRadians(m_rotation)) * distance;
  updateCameraTransform();
}

void OrthographicCamera::updateViewMatrix() {
  Matrix4F rotation{rotateZ(degreesToRadians(m_rotation))};
  Matrix4F translation{translate(m_position)};
  m_viewMatrix = inverse(translation * rotation);
}

void OrthographicCamera::updateCameraTransform() {
  updateViewMatrix();
  m_cameraTransform = m_projectionMatrix * m_viewMatrix;
}

void OrthographicCamera::setAspectRatio(float aspectRatio,
                                        KeepAspect keepAspect) {
  m_keepAspect = keepAspect;
  m_aspectRatio = aspectRatio;
  updateProjection();
  updateCameraTransform();
}

void OrthographicCamera::setAspectRatio(float aspectRatio) {
  m_aspectRatio = aspectRatio;
  updateProjection();
  updateCameraTransform();
}

void OrthographicCamera::setZoomLevel(float zoomLevel) {
  m_zoomLevel = zoomLevel;
  updateProjection();
  updateCameraTransform();
}

void OrthographicCamera::updateProjection() {
  switch (m_keepAspect) {
    case KeepAspect::Height:
      m_projectionMatrix = orthographicProjection(
          -m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel,
          -m_zoomLevel, m_zoomLevel, -1.0f, 1.0f);
      break;

    case KeepAspect::Width:
      m_projectionMatrix = orthographicProjection(
          -m_zoomLevel, m_zoomLevel, -m_aspectRatio * m_zoomLevel,
          m_aspectRatio * m_zoomLevel, -1.0f, 1.0f);
      break;
  }
}
}  // namespace Neat