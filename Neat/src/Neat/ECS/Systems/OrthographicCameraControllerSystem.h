#pragma once

#include "Neat/ECS/System.h"
#include "Neat/ECS/Entity.h"
#include "Neat/ECS/Components.h"
#include "Neat/Graphics/OrthographicCamera.h"
#include "Neat/Events/Event.h"
#include "Neat/Events/EventManager.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class OrthographicCameraControllerSystem
      : public System<OrthographicCameraControllerSystem>
      , public EventListener<OrthographicCameraControllerSystem>
   {
   public:
      OrthographicCameraControllerSystem(float aspectRatio,
         bool rotationEnabled = true);

      ~OrthographicCameraControllerSystem();

      void init(EventManager& eventManager);

      OrthographicCamera& getCamera() { return m_camera; }
      const OrthographicCamera& getCamera() const { return m_camera; }

      void update(EntityManager& entityManager,
         EventManager& eventManager, DeltaTime deltaTime);

      bool listenEvent(const MouseScrolledEvent& event);
      bool listenEvent(const MouseMovedEvent& event);
      bool listenEvent(const WindowResizeEvent& event);

   private:
      float m_aspectRatio;
      float m_zoomLevel = 1.0f;

      OrthographicCamera m_camera;

      Vector3 m_cameraPosition = { 0.0f, 0.0f, 0.0f };
      Vector2 m_lastMousePosition;
      float m_cameraTranslationSpeed = 1.0f;
      float m_cameraRotation = 0.0f;
      float m_cameraRotationSpeed = 90.0f;

      bool m_rotationEnabled;
   };
}