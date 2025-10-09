#pragma once

#include "Events/MouseScrolledEvent.hpp"
#include "EventDispatching/EventDispatcher.hpp"
#include "Components/CameraComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
#include "Math/Quaternion.hpp"

namespace Neat {

class EditorCamera {
 public:
  EditorCamera() = default;
  EditorCamera(const PerspectiveProperties& perspectiveProperties,
               const Ref<EventDispatcher>& eventDispatcher,
               LayerID layerID = NoLayer);

  const CameraComponent& getCamera() const { return m_camera; }
  const TransformComponent& getTransform() const { return m_transform; }

  void update(double deltaTimeSeconds);

  Matrix4F getProjection() const { return m_camera.getProjection(); }
  Matrix4F getViewMatrix() const { return inverse(m_transform.getTransform()); }

  void setViewport(UInt32 width, UInt32 height) {
    m_viewportWidth = width;
    m_viewportHeight = height;
    m_camera.setAspectRatio(width, height);
  }

  Vector3F getUpDirection() const;
  Vector3F getRightDirection() const;
  Vector3F getForwardDirection() const;

 private:
  void updateView();
  bool onMouseScrolled(const MouseScrolledEvent& e);

  void mousePan(const Vector2F& delta);
  void mouseRotate(const Vector2F& delta);
  void mouseZoom(float delta);

  Vector3F calculatePosition() const;

  Vector2F getPanSpeed() const;
  float getRotationSpeed() const;
  float getZoomSpeed() const;

 private:
  CameraComponent m_camera{PerspectiveProperties{}};
  TransformComponent m_transform;
  Vector3F m_focalPoint{0.0f, 0.0f, 0.0f};

  Vector2F m_initialMousePosition{0.0f, 0.0f};

  float m_distance = 10.0f;

  float m_viewportWidth = 1280;
  float m_viewportHeight = 720;
};
}  // namespace Neat