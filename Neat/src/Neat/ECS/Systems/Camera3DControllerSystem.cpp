#include "Neat/Core/Application.h"
#include "Neat/Core/Input.h"
#include "Neat/ECS/Systems/Camera3DControllerSystem.h"


namespace Neat
{
   Camera3DControllerSystem::Camera3DControllerSystem(float aspectRatio,
      bool rotationEnabled)
      : m_aspectRatio(aspectRatio)
      , m_position(m_camera.getPosition())
      , m_rotation(m_camera.getRoll())
      , m_rotationEnabled(rotationEnabled)
      , m_lastMousePosition(Input::getMouseX(), Input::getMouseY())
   {
      m_rotationy = m_camera.getYaw();
      m_rotationx = m_camera.getPitch();
      m_camera.setPerspective(radians(m_fov), m_aspectRatio, 0.1f, 100.0f);
      m_translationSpeed = m_fov;
   }

   Camera3DControllerSystem::~Camera3DControllerSystem()
   {
   }

   void Camera3DControllerSystem::init(EventManager& eventManager)
   {
      eventManager.addListener<MouseMovedEvent>(*this);
      eventManager.addListener<MouseScrolledEvent>(*this);
      eventManager.addListener<WindowResizeEvent>(*this);
   }

   void Camera3DControllerSystem::update(
      EntityManager& entityManager, EventManager& eventManager,
      DeltaTime deltaTime)
   {
      if (!((Input::isKeyPressed(KeyCode::LeftControl) ||
         Input::isKeyPressed(KeyCode::RightControl)) &&
         Input::isMouseButtonPressed(MouseCode::ButtonLeft)))
      {
         if (Input::isKeyPressed(KeyCode::W))
         {
            m_position.y += (float)(m_translationSpeed * deltaTime);
         }

         if (Input::isKeyPressed(KeyCode::S))
         {
            m_position.y -= (float)(m_translationSpeed * deltaTime);
         }

         if (Input::isKeyPressed(KeyCode::D))
         {
            m_position.x += (float)(m_translationSpeed * deltaTime);
         }

         if (Input::isKeyPressed(KeyCode::A))
         {
            m_position.x -= (float)(m_translationSpeed * deltaTime);
         }

         m_camera.setPosition(m_position);
      }

      if (m_rotationEnabled)
      {
         if (Input::isKeyPressed(KeyCode::Q))
         {
            m_rotation += (float)(m_rotationSpeed * deltaTime);
            if (m_rotation >= 360.0f)
               m_rotation -= 360.0f;
            m_camera.setRoll(m_rotation);
         }

         if (Input::isKeyPressed(KeyCode::E))
         {
            m_rotation -= (float)(m_rotationSpeed * deltaTime);
            if (m_rotation <= -360.0f)
               m_rotation += 360.0f;
            m_camera.setRoll(m_rotation);
         }

         if (Input::isKeyPressed(KeyCode::R))
         {
            m_rotationy += (float)(m_rotationSpeed * deltaTime);
            if (m_rotationy >= 360.0f)
               m_rotationy -= 360.0f;
            m_camera.setYaw(m_rotationy);
         }


         if (Input::isKeyPressed(KeyCode::T))
         {
            m_rotationy -= (float)(m_rotationSpeed * deltaTime);
            if (m_rotationy <= -360.0f)
               m_rotationy += 360.0f;
            m_camera.setYaw(m_rotationy);
         }

         if (Input::isKeyPressed(KeyCode::F))
         {
            m_rotationx += (float)(m_rotationSpeed * deltaTime);
            if (m_rotationx >= 89.0f)
               m_rotationx = 89.0f;
            m_camera.setPitch(m_rotationx);
         }


         if (Input::isKeyPressed(KeyCode::G))
         {
            m_rotationx -= (float)(m_rotationSpeed * deltaTime);
            if (m_rotationx <= -89.0f)
               m_rotationx = -89.0f;
            
            m_camera.setPitch(m_rotationx);
         }
      }
   }

   bool Camera3DControllerSystem::listenEvent(
      const MouseScrolledEvent& event)
   {
      if ((Input::isKeyPressed(KeyCode::LeftControl) ||
         Input::isKeyPressed(KeyCode::RightControl)))
      {
         m_fov -= event.yOffset;
         m_fov = std::max(m_fov, 1.0f);
         m_fov = std::min(m_fov, 60.0f);
         m_translationSpeed = m_fov;
         m_camera.setPerspective(radians(m_fov), m_aspectRatio, 0.1f, 100.0f);
      }

      return false;
   }

   bool Camera3DControllerSystem::listenEvent(
      const MouseMovedEvent& event)
   {
      Vector2 current_mouse_position(event.xPos, event.yPos);

      if ((Input::isKeyPressed(KeyCode::LeftControl) ||
         Input::isKeyPressed(KeyCode::RightControl)) &&
         Input::isMouseButtonPressed(MouseCode::ButtonLeft))
      {
         const auto& window = Application::get().getWindow();
         const auto scale_factor =
            2.0f * m_zoomLevel / (float)window.getHeight();

         auto mouse_possition_offset =
            current_mouse_position - m_lastMousePosition;
         auto screen_position_offset =
            rotate(radians(m_rotation), { 0, 0, 1 }) *
            scale(Vector3(-scale_factor, scale_factor, 1.0f)) *
            Vector4(mouse_possition_offset, 0.0f, 1.0f);

         m_position = m_position + Vector3(screen_position_offset);
         m_camera.setPosition(m_position);
      }

      m_lastMousePosition = current_mouse_position;

      return false;
   }

   bool Camera3DControllerSystem::listenEvent(
      const WindowResizeEvent& event)
   {
      m_aspectRatio = (float)event.width / (float)event.height;
      m_camera.setOrthographic(
         -m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel,
         -m_zoomLevel, m_zoomLevel);

      return false;
   }
}