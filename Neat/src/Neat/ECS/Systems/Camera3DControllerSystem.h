#pragma once

#include "Neat/ECS/System.h"
#include "Neat/ECS/Entity.h"
#include "Neat/ECS/Components.h"
#include "Neat/Graphics/Camera.h"
#include "Neat/Events/Event.h"
#include "Neat/Events/EventManager.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class Camera3DControllerSystem
      : public System<Camera3DControllerSystem>
      , public EventListener<Camera3DControllerSystem>
   {
   public:
      Camera3DControllerSystem(float aspectRatio, bool rotationEnabled = true);

      ~Camera3DControllerSystem();

      void init(EventManager& eventManager);

      Camera& getCamera() { return m_camera; }
      const Camera& getCamera() const { return m_camera; }

      void update(EntityManager& entityManager,
         EventManager& eventManager, DeltaTime deltaTime);

      bool listenEvent(const MouseScrolledEvent& event);
      bool listenEvent(const MouseMovedEvent& event);
      bool listenEvent(const WindowResizeEvent& event);

   private:
      float m_fov = 45.0f;
      Camera m_camera;
      Vector3 m_position;
      float m_rotation;
      float m_rotationy{ 0.0f };
      float m_rotationx{ 0.0f };
      float m_zoomLevel = 1.0f;
      float m_translationSpeed = 1.0f;
      float m_rotationSpeed = 90.0f;
      float m_aspectRatio;
      Vector2 m_lastMousePosition;
      bool m_rotationEnabled;
   };
}