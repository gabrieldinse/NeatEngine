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
  Camera(const Vector3F &position = {0.0f, 0.0f, 1.0f});

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
  void setEulerAngles(float pitch, float yaw, float roll,
                      bool doWrapIn360Degrees = true);
  void setPitch(float pitch, bool doWrapIn360Degrees = true);
  void setYaw(float yaw, bool doWrapIn360Degrees = true);
  void setRoll(float roll, bool doWrapIn360Degrees = true);
  void setNear(float near) { m_near = near; }
  void setFar(float far) { m_far = far; }

  void incrementPitchYawRoll(float pitchIncrement, float yawIncrement,
                             float rollIncrement,
                             bool doWrapIn360Degrees = true);
  void incrementPitch(float pitchIncrement, bool doWrapIn360Degrees = true);
  void incrementYaw(float yawIncrement, bool doWrapIn360Degrees = true);
  void incrementRoll(float rollIncrement, bool doWrapIn360Degrees = true);

  void incrementPosition(const Vector3F &position);
  void incrementX(float distance);
  void incrementY(float distance);
  void incrementZ(float distance);
  void moveUp(float distance);
  void moveDown(float distance);
  void moveRight(float distance);
  void moveLeft(float distance);
  void moveForward(float distance);
  void moveBackward(float distance);

  const Matrix4F &getProjectionMatrix() const { return m_projectionMatrix; }
  const Matrix4F &getViewMatrix() const { return m_viewMatrix; }
  const Matrix4F &getCameraTransform() const { return m_cameraTransform; }

  bool isOrthographic() const {
    return m_cameraType == CameraType::Orthographic;
  }
  bool isPerspective() const { return m_cameraType == CameraType::Perspective; }

  // Perspective
  float getFieldOfView() const;
  float getAspectRatio() const;
  void setFieldOfView(float fieldOfView);
  void setAspectRatio(float aspectRatio);
  void setAspectRatio(UInt32 width, UInt32 height);

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

    if (m_cameraType != type) throw WrongCameraTypeError();
  }

  void updateViewMatrix();
  void updateCameraTransform();

 private:
  CameraType m_cameraType = CameraType::None;
  std::variant<OrthographicProps, PerspectiveProps> m_cameraData =
      OrthographicProps{};
  Vector3F m_position;
  Matrix4F m_viewMatrix{Matrix4F::identity()};
  Matrix4F m_projectionMatrix{Matrix4F::identity()};
  Matrix4F m_cameraTransform{Matrix4F::identity()};
  Vector3F m_forwardDirection{0.0f};
  Vector3F m_rightDirection{0.0f};
  Vector3F m_upDirection{0.0f};
  float m_yaw = 0.0f;
  float m_pitch = 0.0f;
  float m_roll = 0.0f;
  float m_near = -1.0f;
  float m_far = 1.0f;
};
}  // namespace Neat