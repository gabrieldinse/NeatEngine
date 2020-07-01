#include "Neat/Core/Application.h"
#include "Neat/Core/Input.h"
#include "Neat/ECS/Systems/Camera2DControllerSystem.h"


namespace Neat
{
   Camera2DControllerSystem::Camera2DControllerSystem(float aspectRatio,
      bool rotationEnabled)
      : m_camera(Vector2F(0.0f), aspectRatio)
      , m_aspectRatio(aspectRatio)
      , m_rotationEnabled(rotationEnabled)
   {
   }

   Camera2DControllerSystem::~Camera2DControllerSystem()
   {
   }

   void Camera2DControllerSystem::init(EventManager& eventManager)
   {
      eventManager.addListener<MouseMovedEvent>(*this);
      eventManager.addListener<MouseScrolledEvent>(*this);
      eventManager.addListener<WindowResizeEvent>(*this);
   }

   void Camera2DControllerSystem::update(
      EntityManager& entityManager, EventManager& eventManager,
      DeltaTime deltaTime)
   {
      auto distance = (float)(m_translationSpeed * deltaTime);
      if (Input::isKeyPressed(KeyCode::W))
         m_camera.moveUp(distance);

      if (Input::isKeyPressed(KeyCode::S))
         m_camera.moveDown(distance);

      if (Input::isKeyPressed(KeyCode::D))
         m_camera.moveRight(distance);

      if (Input::isKeyPressed(KeyCode::A))
         m_camera.moveLeft(distance);

      if (m_rotationEnabled)
      {
         auto rotation = (float)(m_rotationSpeed * deltaTime);
         if (Input::isKeyPressed(KeyCode::Q))
            m_camera.setRotation(wrap360(m_camera.getRotation() + rotation));

         if (Input::isKeyPressed(KeyCode::E))
            m_camera.setRotation(wrap360(m_camera.getRotation() - rotation));
      }
   }

   bool Camera2DControllerSystem::listenEvent(
      const MouseScrolledEvent& event)
   {
      m_zoomLevel -= event.yOffset * 0.2f;
      m_zoomLevel = std::max(m_zoomLevel, 0.25f);
      m_translationSpeed = 2.0f * m_zoomLevel;
      m_camera.setZoomLevel(m_zoomLevel);

      return false;
   }

   bool Camera2DControllerSystem::listenEvent(
      const MouseMovedEvent& event)
   {
      if (m_firstMouse)
      {
         m_lastMousePosition = Vector2F(event.xPos, event.yPos);
         m_firstMouse = false;
      }

      Vector2F current_mouse_position(event.xPos, event.yPos);

      const auto& window = Application::get().getWindow();
      const auto scale_factor =
         2.0f * m_zoomLevel / (float)window.getHeight();

      auto mouse_possition_offset =
         current_mouse_position - m_lastMousePosition;
      auto screen_position_offset =
         rotateZ(radians(m_camera.getRotation())) *
         scale(Vector3F(-scale_factor, scale_factor, 1.0f)) *
         Vector4F(mouse_possition_offset, 0.0f, 1.0f);

      m_camera.move(Vector2F(screen_position_offset));
      m_lastMousePosition = current_mouse_position;

      return false;
   }

   bool Camera2DControllerSystem::listenEvent(
      const WindowResizeEvent& event)
   {
      m_aspectRatio = (float)event.width / (float)event.height;
      m_camera.setSize(m_aspectRatio);

      return false;
   }
}