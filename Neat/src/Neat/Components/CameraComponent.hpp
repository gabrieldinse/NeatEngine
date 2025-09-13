#pragma once

#include <type_traits>

#include "OrthographicProperties.hpp"
#include "PerspectiveProperties.hpp"

#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Projection.hpp"
#include "Neat/Math/Projection.hpp"

namespace Neat {
enum class CameraType { Orthographic = 0, Perspective = 1 };

class CameraComponent {
 public:
  CameraComponent() = default;
  CameraComponent(const OrthographicProperties &orthographicProperties);
  CameraComponent(const PerspectiveProperties &perspectiveProperties);

  const Matrix4F &getProjection() const { return m_projectionMatrix; }

  CameraType getType() const { return m_type; }
  void setType(CameraType type) { m_type = type; }

  void setOrthographic(const OrthographicProperties &orthographicProperties);
  void setPerspective(const PerspectiveProperties &perspectiveProperties);
  const OrthographicProperties &getOrthographicProperties() const {
    return m_orthographicProperties;
  }
  const PerspectiveProperties &getPerspectiveProperties() const {
    return m_perspectiveProperties;
  }

  void setOrthographicLeft(float left);
  void setOrthographicRight(float right);
  void setOrthographicBottom(float bottom);
  void setOrthographicTop(float top);
  void setOrthographicNear(float near);
  void setOrthographicFar(float far);
  void setOrthographicAspectRatio(float aspectRatio);
  template <typename T, typename U>
    requires std::is_integral_v<T> and std::is_integral_v<U>
  void setOrthographicAspectRatio(T width, U height) {
    m_orthographicProperties.setAspectRatio(width, height);
    updateProjection();
  }
  void setOrthographicSize(float size);
  float getOrthographicNear() const { return m_orthographicProperties.near; }
  float getOrthographicFar() const { return m_orthographicProperties.far; }
  float getOrthographicSize() const {
    return m_orthographicProperties.getSize();
  }
  float getOrthographicAspectRatio() const {
    return m_orthographicProperties.getAspectRatio();
  }

  void setPerspectiveFOV(float fov);
  void setPerspectiveAspectRatio(float aspectRatio);
  void setPerspectiveNear(float near);
  void setPerspectiveFar(float far);
  float getPerspectiveFOV() const { return m_perspectiveProperties.fov; }
  float getPerspectiveAspectRatio() const {
    return m_perspectiveProperties.aspectRatio;
  }
  float getPerspectiveNear() const { return m_perspectiveProperties.near; }
  float getPerspectiveFar() const { return m_perspectiveProperties.far; }

 private:
  void updateProjection();

 private:
  CameraType m_type = CameraType::Orthographic;
  OrthographicProperties m_orthographicProperties{};
  PerspectiveProperties m_perspectiveProperties{};
  Matrix4F m_projectionMatrix{1.0f};
};
}  // namespace Neat