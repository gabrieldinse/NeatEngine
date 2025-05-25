#pragma once

#include <variant>

#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Projection.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
class Camera {
public:
  enum class CameraType { None, Orthographic, Perspective };

  struct OrthographicProps {
    OrthographicProps(float left = 0.0f, float right = 0.0f,
                      float bottom = 0.0f, float top = 0.0f)
        : left(left), right(right), bottom(bottom), top(top) {}

    float left = 0.0f;
    float right = 0.0f;
    float bottom = 0.0f;
    float top = 0.0f;
  };

  struct PerspectiveProps {
    PerspectiveProps(float fieldOfView = 0.0f, float aspectRatio = 0.0f)
        : fieldOfView(fieldOfView), aspectRatio(aspectRatio) {}

    float fieldOfView = 0.0f;
    float aspectRatio = 0.0f;
  };

public:
  Camera(const Vector3F &position = {0.0f, 0.0f, 1.0f},
         const Vector3F &upDirection = {0.0f, 1.0f, 0.0f});

  Camera &setOrthographic(float left, float right, float bottom, float top,
                          float near, float far);
  Camera &setOrthographic(float left, float right, float bottom, float top);
  Camera &setPerspective(float fov, float aspectRatio, float near, float far);

  const Vector3F &getPosition() const { return m_position; }
  float getPitch() const { return m_pitch; }
  float getYaw() const { return m_yaw; }
  float getRoll() const { return m_roll; }
  const Vector3F &getForwardDirection() const { return m_forwardDirection; }
  const Vector3F &getUpDirection() const { return m_upDirection; }
  const Vector3F &getRightDirection() const { return m_rightDirection; }
  float getNear() const { return m_near; }
  float getFar() const { return m_far; }

  void setPosition(const Vector3F &position) { m_position = position; }
  void setX(float x) { m_position.x = x; }
  void setY(float y) { m_position.y = y; }
  void setZ(float z) { m_position.z = z; }
  void setRotation(float pitch, float yaw, float roll);
  void setPitch(float pitch);
  void setYaw(float yaw);
  void setRoll(float roll);
  void setWorldUp(const Vector3F &worldUp) { m_worldUpDirection = worldUp; }
  void setNear(float near) { m_near = near; }
  void setFar(float far) { m_far = far; }

  void rotate(float pitch, float yaw, float roll);
  void rotatePitch(float pitch);
  void rotateYaw(float yaw);
  void rotateRoll(float roll);

  void move(const Vector3F &position) { m_position += position; }
  void moveX(float distance) { m_position.x += distance; }
  void moveY(float distance) { m_position.y += distance; }
  void moveZ(float distance) { m_position.z += distance; }
  void moveUp(float distance) { m_position += m_upDirection * distance; }
  void moveDown(float distance) { m_position -= m_upDirection * distance; }
  void moveRight(float distance) { m_position += m_rightDirection * distance; }
  void moveLeft(float distance) { m_position -= m_rightDirection * distance; }
  void moveForward(float distance) {
    m_position += m_forwardDirection * distance;
  }
  void moveBackward(float distance) {
    m_position -= m_forwardDirection * distance;
  }

  Matrix4F getProjectionMatrix() const;
  Matrix4F getViewMatrix() const;
  Matrix4F getCameraTransform() const;

  bool isOrthographic() const {
    return m_cameraType == CameraType::Orthographic;
  }
  bool isPerspective() const { return m_cameraType == CameraType::Perspective; }

  // Perspective
  float getFieldOfView() const;
  float getAspectRatio() const;
  void setFieldOfView(float fieldOfView);
  void setAspectRatio(float aspectRatio);

  // Orthographic
  float getLeft() const;
  float getRight() const;
  float getBottom() const;
  float getTop() const;
  void setLeft(float left);
  void setRight(float right);
  void setBottom(float bottom);
  void setTop(float top);

private:
  const OrthographicProps &getOrthographicData() const {
    return std::get<OrthographicProps>(m_cameraData);
  }

  OrthographicProps &getOrthographicData() {
    return std::get<OrthographicProps>(m_cameraData);
  }

  const PerspectiveProps &getPerspectiveData() const {
    return std::get<PerspectiveProps>(m_cameraData);
  }

  PerspectiveProps &getPerspectiveData() {
    return std::get<PerspectiveProps>(m_cameraData);
  }

  void checkIsType(CameraType type) const {
    if (m_cameraType == CameraType::None)
      throw CameraTypeHasNotBeenSettedError();

    if (m_cameraType != type)
      throw WrongCameraTypeError();
  }

  void updateOrientationVectors();

private:
  CameraType m_cameraType = CameraType::None;
  std::variant<OrthographicProps, PerspectiveProps> m_cameraData =
      OrthographicProps{};
  Vector3F m_position;
  Vector3F m_worldUpDirection;
  Vector3F m_forwardDirection{0.0f};
  Vector3F m_rightDirection{0.0f};
  Vector3F m_upDirection{0.0f};
  float m_yaw = 0.0f;
  float m_pitch = 0.0f;
  float m_roll = 0.0f;
  float m_near = -1.0f;
  float m_far = 1.0f;
};
} // namespace Neat