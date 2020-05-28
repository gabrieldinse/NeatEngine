#pragma once

#include "Neat/Graphics/OrthographicCamera.h"
#include "Neat/Events/Event.h"
#include "Neat/Events/EventManager.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class OrthographicCameraController
      : public EventSubscriber<OrthographicCameraController>
   {
   public:
      OrthographicCameraController(float aspectRatio,
         EventManager& eventManager = Application::get().events(),
         bool rotationEnabled = true);

      ~OrthographicCameraController();

      OrthographicCamera& getCamera() { return m_camera; }
      const OrthographicCamera& getCamera() const { return m_camera; }

      void update(DeltaTime deltaTime);

      bool receive(const MouseScrolledEvent& event);
      bool receive(const MouseMovedEvent& event);
      bool receive(const WindowResizeEvent& event);

   private:
      float m_aspectRatio;
      float m_zoomLevel = 1.0f;

      OrthographicCamera m_camera;

      Vector3 m_cameraPosition = {0.0f, 0.0f, 0.0f};
      Vector2 m_lastMousePosition;
      float m_cameraTranslationSpeed = 1.0f;
      float m_cameraRotation = 0.0f;
      float m_cameraRotationSpeed = 90.0f;

      bool m_rotationEnabled;
   };
}