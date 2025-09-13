#include "NeatPCH.hpp"

#include "CameraComponent.hpp"

namespace Neat {
CameraComponent::CameraComponent(
    const OrthographicProperties &orthographicProperties)
    : m_type(CameraType::Orthographic),
      m_orthographicProperties{orthographicProperties} {
  updateProjection();
}

CameraComponent::CameraComponent(
    const PerspectiveProperties &perspectiveProperties)
    : m_type(CameraType::Perspective),
      m_perspectiveProperties{perspectiveProperties} {
  updateProjection();
}

void CameraComponent::setOrthographic(
    const OrthographicProperties &orthographicProperties) {
  NT_PROFILE_FUNCTION();
  m_type = CameraType::Orthographic;
  m_orthographicProperties = orthographicProperties;
  updateProjection();
}

void CameraComponent::setPerspective(
    const PerspectiveProperties &perspectiveProperties) {
  NT_PROFILE_FUNCTION();
  m_type = CameraType::Perspective;
  m_perspectiveProperties = perspectiveProperties;
  updateProjection();
}

void CameraComponent::setOrthographicLeft(float left) {
  NT_PROFILE_FUNCTION();
  m_orthographicProperties.left = left;
  updateProjection();
}

void CameraComponent::setOrthographicRight(float right) {
  NT_PROFILE_FUNCTION();
  m_orthographicProperties.right = right;
  updateProjection();
}

void CameraComponent::setOrthographicBottom(float bottom) {
  NT_PROFILE_FUNCTION();
  m_orthographicProperties.bottom = bottom;
  updateProjection();
}

void CameraComponent::setOrthographicTop(float top) {
  NT_PROFILE_FUNCTION();
  m_orthographicProperties.top = top;
  updateProjection();
}

void CameraComponent::setOrthographicNear(float near) {
  NT_PROFILE_FUNCTION();
  m_orthographicProperties.near = near;
  updateProjection();
}

void CameraComponent::setOrthographicFar(float far) {
  NT_PROFILE_FUNCTION();
  m_orthographicProperties.far = far;
  updateProjection();
}

void CameraComponent::setOrthographicAspectRatio(float aspectRatio) {
  NT_PROFILE_FUNCTION();
  m_orthographicProperties.setAspectRatio(aspectRatio);
  updateProjection();
}

void CameraComponent::setOrthographicSize(float size) {
  NT_PROFILE_FUNCTION();
  m_orthographicProperties.setSize(size);
  updateProjection();
}

void CameraComponent::setPerspectiveFOV(float fov) {
  NT_PROFILE_FUNCTION();
  m_perspectiveProperties.fov = fov;
  updateProjection();
}

void CameraComponent::setPerspectiveAspectRatio(float aspectRatio) {
  NT_PROFILE_FUNCTION();
  m_perspectiveProperties.aspectRatio = aspectRatio;
  updateProjection();
}

void CameraComponent::setPerspectiveNear(float near) {
  NT_PROFILE_FUNCTION();
  m_perspectiveProperties.near = near;
  updateProjection();
}

void CameraComponent::setPerspectiveFar(float far) {
  NT_PROFILE_FUNCTION();
  m_perspectiveProperties.far = far;
  updateProjection();
}

void CameraComponent::updateProjection() {
  NT_PROFILE_FUNCTION();
  switch (m_type) {
    case CameraType::Orthographic:
      m_projectionMatrix = orthographicProjection(
          m_orthographicProperties.left, m_orthographicProperties.right,
          m_orthographicProperties.bottom, m_orthographicProperties.top,
          m_orthographicProperties.near, m_orthographicProperties.far);
      break;
    case CameraType::Perspective:
      m_projectionMatrix = perspectiveProjection(
          m_perspectiveProperties.fov, m_perspectiveProperties.aspectRatio,
          m_perspectiveProperties.near, m_perspectiveProperties.far);
      break;
  }
}
}  // namespace Neat