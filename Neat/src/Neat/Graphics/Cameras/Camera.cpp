#include "NeatPCH.hpp"

#include "Neat/Core/Log.hpp"
#include "Neat/Graphics/Cameras/Camera.hpp"
#include "Neat/Math/EulerAngles.hpp"
#include "Neat/Math/Projection.hpp"
#include "Neat/Math/Quaternion.hpp"
#include "Neat/Math/Transform.hpp"

namespace Neat {
Camera::Camera(const Vector3F &position, const Vector3F &upDirection)
    : m_position(position), m_worldUpDirection(normalize(upDirection)) {
  updateOrientationVectors();
}

Camera &Camera::setOrthographic(float left, float right, float bottom,
                                float top, float near, float far) {
  m_cameraData = OrthographicProps(left, right, bottom, top);
  m_near = near;
  m_far = far;
  m_cameraType = CameraType::Orthographic;

  return *this;
}

Camera &Camera::setOrthographic(float left, float right, float bottom,
                                float top) {
  m_cameraData = OrthographicProps(left, right, bottom, top);
  m_cameraType = CameraType::Orthographic;

  return *this;
}

Camera &Camera::setPerspective(float fov, float aspectRatio, float near,
                               float far) {
  m_cameraData = PerspectiveProps(fov, aspectRatio);
  m_near = near;
  m_far = far;
  m_cameraType = CameraType::Perspective;

  return *this;
}

void Camera::setEulerAngles(float pitch, float yaw, float roll,
                            bool doWrapIn360Degrees) {
  if (doWrapIn360Degrees) {
    pitch = wrapIn360Degrees(pitch);
    yaw = wrapIn360Degrees(yaw);
    roll = wrapIn360Degrees(roll);
  }
  m_pitch = pitch;
  m_yaw = yaw;
  m_roll = roll;
  updateOrientationVectors();
}

void Camera::setPitch(float pitch, bool doWrapIn360Degrees) {
  if (doWrapIn360Degrees) {
    pitch = wrapIn360Degrees(pitch);
  }
  m_pitch = pitch;
  updateOrientationVectors();
}

void Camera::setYaw(float yaw, bool doWrapIn360Degrees) {
  if (doWrapIn360Degrees) {
    yaw = wrapIn360Degrees(yaw);
  }
  m_yaw = yaw;
  updateOrientationVectors();
}

void Camera::setRoll(float roll, bool doWrapIn360Degrees) {
  if (doWrapIn360Degrees) {
    roll = wrapIn360Degrees(roll);
  }
  m_roll = roll;
  updateOrientationVectors();
}

void Camera::incrementPitchYawRoll(float pitchIncrement, float yawIncrement,
                                   float rollIncrement, bool doWrapIn360Degrees) {
  m_pitch += pitchIncrement;
  m_yaw += yawIncrement;
  m_roll += rollIncrement;

  if (doWrapIn360Degrees) {
    m_pitch = wrapIn360Degrees(m_pitch);
    m_yaw = wrapIn360Degrees(m_yaw);
    m_roll = wrapIn360Degrees(m_roll);
  }

  updateOrientationVectors();
}

void Camera::incrementPitch(float pitchIncrement, bool doWrapIn360Degrees) {
  setPitch(m_pitch + pitchIncrement, doWrapIn360Degrees);
}

void Camera::incrementYaw(float yawIncrement, bool doWrapIn360Degrees) {
  setYaw(m_yaw + yawIncrement, doWrapIn360Degrees);
}

void Camera::incrementRoll(float rollIncrement, bool doWrapIn360Degrees) {
  setRoll(m_roll + rollIncrement, doWrapIn360Degrees);
}

Matrix4F Camera::getProjectionMatrix() const {
  switch (m_cameraType) {
    case CameraType::Orthographic: {
      auto &camera_data = getOrthographicData();
      return orthographic(camera_data.left, camera_data.right,
                          camera_data.bottom, camera_data.top, m_near, m_far);
    }

    case CameraType::Perspective: {
      auto &camera_data = getPerspectiveData();
      return perspective(degreesToRadians(camera_data.fieldOfView),
                         camera_data.aspectRatio, m_near, m_far);
    }

    default:
      throw CameraTypeHasNotBeenSettedError();
  }
}

Matrix4F Camera::getViewMatrix() const {
  return lookAtRH(m_position, m_position + m_forwardDirection, m_upDirection);
}

Matrix4F Camera::getCameraTransform() const {
  return getProjectionMatrix() * getViewMatrix();
}

// Perspective
float Camera::getFieldOfView() const {
  checkIsType(CameraType::Perspective);

  return getPerspectiveData().fieldOfView;
}

float Camera::getAspectRatio() const {
  checkIsType(CameraType::Perspective);

  return getPerspectiveData().aspectRatio;
}

void Camera::setFieldOfView(float fieldOfView) {
  checkIsType(CameraType::Perspective);

  getPerspectiveData().fieldOfView = fieldOfView;
}

void Camera::setAspectRatio(float aspectRatio) {
  checkIsType(CameraType::Perspective);

  getPerspectiveData().aspectRatio = aspectRatio;
}

void Camera::setAspectRatio(UInt32 width, UInt32 height) {
  setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
}

// Orthographic
float Camera::getLeft() const {
  checkIsType(CameraType::Orthographic);

  return getOrthographicData().left;
}

float Camera::getRight() const {
  checkIsType(CameraType::Orthographic);

  return getOrthographicData().right;
}

float Camera::getBottom() const {
  checkIsType(CameraType::Orthographic);

  return getOrthographicData().bottom;
}

float Camera::getTop() const {
  checkIsType(CameraType::Orthographic);

  return getOrthographicData().top;
}

void Camera::setLeft(float left) {
  checkIsType(CameraType::Orthographic);

  getOrthographicData().left = left;
}

void Camera::setRight(float right) {
  checkIsType(CameraType::Orthographic);

  getOrthographicData().right = right;
}

void Camera::setBottom(float bottom) {
  checkIsType(CameraType::Orthographic);

  getOrthographicData().bottom = bottom;
}

void Camera::setTop(float top) {
  checkIsType(CameraType::Orthographic);

  getOrthographicData().top = top;
}

void Camera::updateOrientationVectors() {
  auto orientation = QuaternionF::fromEulerAngles(degreesToRadians(m_pitch),
                                                  degreesToRadians(m_yaw),
                                                  degreesToRadians(m_roll));

  m_forwardDirection = rotate(orientation, Vector3F(0, 0, -1));
  m_rightDirection = rotate(orientation, Vector3F(1, 0, 0));
  m_upDirection = rotate(orientation, Vector3F(0, 1, 0));
}
}  // namespace Neat