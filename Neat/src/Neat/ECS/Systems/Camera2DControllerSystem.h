#pragma once

#include "Neat/ECS/System.h"
#include "Neat/ECS/Entity.h"
#include "Neat/ECS/Components.h"
#include "Neat/Graphics/Cameras/Camera2D.h"
#include "Neat/Events/Event.h"
#include "Neat/Events/EventManager.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class Camera2DControllerSystem
      : public System<Camera2DControllerSystem>
      , public EventListener<Camera2DControllerSystem>
   {
   public:
      Camera2DControllerSystem(float aspectRatio, bool rotationEnabled = true);

      ~Camera2DControllerSystem();

      void init(EventManager& eventManager);

      Camera& getCamera() { return m_camera.getCamera(); }
      const Camera& getCamera() const { return m_camera.getCamera(); }
      Camera2D& getCamera2D() { return m_camera; }
      const Camera2D& getCamera2D() const { return m_camera; }

      void update(EntityManager& entityManager,
         EventManager& eventManager, DeltaTime deltaTime);

      bool listenEvent(const MouseScrolledEvent& event);
      bool listenEvent(const MouseMovedEvent& event);
      bool listenEvent(const WindowResizeEvent& event);

   private:
      Camera2D m_camera;
      float m_zoomLevel = 1.0f;
      float m_translationSpeed = 1.0f;
      float m_rotationSpeed = 90.0f;
      float m_aspectRatio;
      Vector2F m_lastMousePosition{ 0.0f };
      bool m_firstMouse = true;
      bool m_rotationEnabled;
   };
}