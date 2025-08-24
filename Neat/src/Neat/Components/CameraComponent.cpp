#include "NeatPCH.hpp"

#include "Neat/Components/CameraComponent.hpp"

namespace Neat {
CameraComponent::CameraComponent(const Matrix4F &projection)
    : m_projectionMatrix{projection} {}

CameraComponent::CameraComponent(float left, float right, float bottom,
                                 float top, float near, float far)
    : m_projectionMatrix{
          orthographicProjection(left, right, bottom, top, near, far)} {}

CameraComponent::CameraComponent(float aspectRatio, float zoomLevel) {
  setOrthographic(aspectRatio, zoomLevel);
}

CameraComponent::CameraComponent(UInt32 width, UInt32 height, float zoomLevel) {
  setOrthographic(width, height, zoomLevel);
}

void CameraComponent::setOrthographic(UInt32 width, UInt32 height,
                                      float zoomLevel) {
  setOrthographic(static_cast<float>(width) / static_cast<float>(height),
                  zoomLevel);
}

CameraComponent CameraComponent::createOrthographic(float left, float right,
                                                    float bottom, float top,
                                                    float near, float far) {
  return CameraComponent(left, right, bottom, top, near, far);
}

CameraComponent CameraComponent::createOrthographic(float aspectRatio,
                                                    float zoomLevel) {
  return CameraComponent(aspectRatio, zoomLevel);
}

CameraComponent CameraComponent::createOrthographic(UInt32 width, UInt32 height,
                                                    float zoomLevel) {
  return CameraComponent(width, height, zoomLevel);
}

void CameraComponent::setOrthographic(float aspectRatio, float zoomLevel) {
  NT_PROFILE_FUNCTION();
  float left = -aspectRatio * zoomLevel;
  float right = aspectRatio * zoomLevel;
  float bottom = -zoomLevel;
  float top = zoomLevel;
  setOrthographic(left, right, bottom, top);
}

void CameraComponent::setOrthographic(float left, float right, float bottom,
                                      float top, float near, float far) {
  NT_PROFILE_FUNCTION();
  m_projectionMatrix =
      orthographicProjection(left, right, bottom, top, near, far);
}
}  // namespace Neat