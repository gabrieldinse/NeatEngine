#include "NeatPCH.hpp"

#include "Neat/Graphics/Cameras/OrthographicCamera.hpp"
#include "Neat/Math/EulerAngles.hpp"
#include "Neat/Math/Projection.hpp"
#include "Neat/Math/Quaternion.hpp"
#include "Neat/Math/Transform.hpp"

namespace Neat {
OrthographicCamera::OrthographicCamera(const Vector2F &position,
                                       float aspectRatio, float zoomLevel)
    : m_position(Vector3F{position, 0.0f}) {
  NT_PROFILE_FUNCTION();
  setProperties(aspectRatio, zoomLevel);
}

OrthographicCamera::OrthographicCamera(const Vector2F &position, UInt32 width,
                                       UInt32 height, float zoomLevel)
    : m_position(Vector3F{position, 0.0f}) {
  NT_PROFILE_FUNCTION();
  setProperties(static_cast<float>(width) / static_cast<float>(height),
                zoomLevel);
}

void OrthographicCamera::setProperties(float aspectRatio, float zoomLevel) {
  NT_PROFILE_FUNCTION();
  m_left = -aspectRatio * zoomLevel;
  m_right = aspectRatio * zoomLevel;
  m_bottom = -zoomLevel;
  m_top = zoomLevel;
  updateProjection();
  updateCameraTransform();
}

void OrthographicCamera::setProperties(float left, float right, float bottom,
                                       float top, float near, float far) {
  NT_PROFILE_FUNCTION();
  m_left = left;
  m_right = right;
  m_bottom = bottom;
  m_top = top;
  m_near = near;
  m_far = far;
  updateProjection();
  updateCameraTransform();
}

void OrthographicCamera::setPosition(const Vector2F &position) {
  NT_PROFILE_FUNCTION();
  m_position.x = position.x;
  m_position.y = position.y;
  updateCameraTransform();
}

void OrthographicCamera::setRotation(float rotation) {
  NT_PROFILE_FUNCTION();
  m_rotation = rotation;
  updateCameraTransform();
}

void OrthographicCamera::incrementPosition(const Vector2F &position) {
  NT_PROFILE_FUNCTION();
  m_position.x += position.x;
  m_position.y += position.y;
  updateCameraTransform();
}

void OrthographicCamera::incrementRotation(float rotation) {
  NT_PROFILE_FUNCTION();
  m_rotation += rotation;
  updateCameraTransform();
}

void OrthographicCamera::moveUp(float distance) {
  NT_PROFILE_FUNCTION();
  m_position.x += -sin(degreesToRadians(m_rotation)) * distance;
  m_position.y += cos(degreesToRadians(m_rotation)) * distance;
  updateCameraTransform();
}

void OrthographicCamera::moveDown(float distance) {
  NT_PROFILE_FUNCTION();
  m_position.x -= -sin(degreesToRadians(m_rotation)) * distance;
  m_position.y -= cos(degreesToRadians(m_rotation)) * distance;
  updateCameraTransform();
}

void OrthographicCamera::moveRight(float distance) {
  NT_PROFILE_FUNCTION();
  m_position.x += cos(degreesToRadians(m_rotation)) * distance;
  m_position.y += sin(degreesToRadians(m_rotation)) * distance;
  updateCameraTransform();
}

void OrthographicCamera::moveLeft(float distance) {
  NT_PROFILE_FUNCTION();
  m_position.x -= cos(degreesToRadians(m_rotation)) * distance;
  m_position.y -= sin(degreesToRadians(m_rotation)) * distance;
  updateCameraTransform();
}

void OrthographicCamera::updateViewMatrix() {
  NT_PROFILE_FUNCTION();
  Matrix4F rotation{rotateZ(degreesToRadians(m_rotation))};
  Matrix4F translation{translate(m_position)};
  m_viewMatrix = inverse(translation * rotation);
}

void OrthographicCamera::updateCameraTransform() {
  NT_PROFILE_FUNCTION();
  updateViewMatrix();
  m_cameraTransform = m_projectionMatrix * m_viewMatrix;
}

void OrthographicCamera::setAspectRatio(float aspectRatio) {
  NT_PROFILE_FUNCTION();
  float zoomLevel = m_top;
  m_left = -aspectRatio * zoomLevel;
  m_right = aspectRatio * zoomLevel;
  updateProjection();
  updateCameraTransform();
}

void OrthographicCamera::setZoomLevel(float zoomLevel) {
  NT_PROFILE_FUNCTION();
  float aspectRatio = m_right / m_top;
  m_bottom = -zoomLevel;
  m_top = zoomLevel;
  m_left = -aspectRatio * zoomLevel;
  m_right = aspectRatio * zoomLevel;
  updateProjection();
  updateCameraTransform();
}

void OrthographicCamera::setX(float x) {
  NT_PROFILE_FUNCTION();
  m_position.x = x;
  updateCameraTransform();
}

void OrthographicCamera::setY(float y) {
  NT_PROFILE_FUNCTION();
  m_position.y = y;
  updateCameraTransform();
}

void OrthographicCamera::incrementX(float x) {
  NT_PROFILE_FUNCTION();
  m_position.x += x;
  updateCameraTransform();
}

void OrthographicCamera::incrementY(float y) {
  NT_PROFILE_FUNCTION();
  m_position.y += y;
  updateCameraTransform();
}

void OrthographicCamera::updateProjection() {
  NT_PROFILE_FUNCTION();
  m_projectionMatrix =
      orthographicProjection(m_left, m_right, m_bottom, m_top, m_near, m_far);
}
}  // namespace Neat