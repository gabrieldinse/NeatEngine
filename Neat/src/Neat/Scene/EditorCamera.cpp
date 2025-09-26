#include "NeatPCH.hpp"

#include "EditorCamera.hpp"

#include "Neat/Core/Input.hpp"
#include "Neat/Core/KeyCodes.hpp"
#include "Neat/Core/MouseButtonCodes.hpp"
#include "Neat/Math/Projection.hpp"
#include "Neat/Math/Trigonometric.hpp"
#include "Neat/Math/Transform.hpp"

namespace Neat {
EditorCamera::EditorCamera(const PerspectiveProperties& perspectiveProperties,
                           const Ref<EventDispatcher>& eventDispatcher)
    : m_camera{perspectiveProperties} {
  eventDispatcher->get<MouseScrolledEvent>()
      .connect<&EditorCamera::onMouseScrolled>(*this);
  updateView();
}

void EditorCamera::onUpdate([[maybe_unused]] double deltaTimeSeconds) {
  if (Input::isKeyPressed(Key::LeftAlt)) {
    const Vector2F& mousePosition{Input::getMouseX(), Input::getMouseY()};
    Vector2F deltaPos{(mousePosition - m_initialMousePosition) * 0.003f};
    m_initialMousePosition = mousePosition;

    if (Input::isMouseButtonPressed(MouseButton::Middle)) {
      mousePan(deltaPos);
    } else if (Input::isMouseButtonPressed(MouseButton::Left)) {
      mouseRotate(deltaPos);
    } else if (Input::isMouseButtonPressed(MouseButton::Right)) {
      mouseZoom(deltaPos.y());
    }
  }
  updateView();
}

Vector3F EditorCamera::getUpDirection() const {
  return rotate(m_transform.getOrientation(), Vector3F(0.0f, 1.0f, 0.0f));
}

Vector3F EditorCamera::getRightDirection() const {
  return rotate(m_transform.getOrientation(), Vector3F(1.0f, 0.0f, 0.0f));
}

Vector3F EditorCamera::getForwardDirection() const {
  return rotate(m_transform.getOrientation(), Vector3F(0.0f, 0.0f, -1.0f));
}

void EditorCamera::updateView() {
  m_transform.setPosition(calculatePosition());
}

Vector2F EditorCamera::getPanSpeed() const {
  float x = std::min(m_viewportWidth / 1000.0f, 2.4f);  // max = 2.4f
  float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

  float y = std::min(m_viewportHeight / 1000.0f, 2.4f);  // max = 2.4f
  float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

  return Vector2F{xFactor, yFactor};
}

float EditorCamera::getRotationSpeed() const { return radiansToDegrees(0.8f); }

float EditorCamera::getZoomSpeed() const {
  float distance = m_distance * 0.2f;
  distance = std::max(distance, 0.0f);
  float speed = distance * distance;
  speed = std::min(speed, 100.0f);  // max speed = 100
  return speed;
}

bool EditorCamera::onMouseScrolled(const MouseScrolledEvent& event) {
  float deltaPos = event.yOffset * 0.1f;
  mouseZoom(deltaPos);
  updateView();
  return false;
}

void EditorCamera::mousePan(const Vector2F& deltaPos) {
  Vector2F panSpeed = getPanSpeed();
  m_focalPoint +=
      -getRightDirection() * deltaPos.x() * panSpeed.x() * m_distance;
  m_focalPoint += getUpDirection() * deltaPos.y() * panSpeed.y() * m_distance;
}

void EditorCamera::mouseRotate(const Vector2F& deltaPos) {
  float yawSign = getUpDirection().y() < 0 ? -1.0f : 1.0f;
  m_transform.incrementYaw(yawSign * -deltaPos.x() * getRotationSpeed());
  m_transform.incrementPitch(-deltaPos.y() * getRotationSpeed());
}

void EditorCamera::mouseZoom(float deltaPos) {
  m_distance -= deltaPos * getZoomSpeed();
  if (m_distance < 1.0f) {
    m_focalPoint += getForwardDirection();
    m_distance = 1.0f;
  }
}

Vector3F EditorCamera::calculatePosition() const {
  return m_focalPoint - getForwardDirection() * m_distance;
}
}  // namespace Neat