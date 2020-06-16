#include "Neat/Core/Application.h"
#include "Neat/Core/Input.h"
#include "Neat/ECS/Systems/Camera3DControllerSystem.h"


namespace Neat
{
   Camera3DControllerSystem::Camera3DControllerSystem(float aspectRatio,
      bool rotationEnabled)
      : m_rotationEnabled(rotationEnabled)
      , m_lastMousePosition(Input::getMouseX(), Input::getMouseY())
   {
      m_camera.setPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
      m_translationSpeed = m_camera.getFieldOfView() * 0.2f;
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
         auto shift = (float)(m_translationSpeed * deltaTime);
         if (Input::isKeyPressed(KeyCode::W))
         {
            m_camera.incrementPosition(shift * m_camera.getFrontDirection());
         }

         if (Input::isKeyPressed(KeyCode::S))
         {
            m_camera.incrementPosition(-shift * m_camera.getFrontDirection());
         }

         if (Input::isKeyPressed(KeyCode::D))
         {
            m_camera.incrementPosition(shift * m_camera.getRightDirection());
         }

         if (Input::isKeyPressed(KeyCode::A))
         {
            m_camera.incrementPosition(-shift * m_camera.getRightDirection());
         }

         if (Input::isKeyPressed(KeyCode::Z))
         {
            m_camera.incrementPosition(shift * m_camera.getUpDirection());
         }

         if (Input::isKeyPressed(KeyCode::X))
         {
            m_camera.incrementPosition(-shift * m_camera.getUpDirection());
         }
      }

      if (m_rotationEnabled)
      {
         if (Input::isKeyPressed(KeyCode::Q))
         {
            auto rotation = (float)(m_rotationSpeed * deltaTime);
            if (m_camera.getRoll() + rotation >= 360.0f)
               rotation -= 360.0f;
            m_camera.incrementRoll(rotation);
         }

         if (Input::isKeyPressed(KeyCode::E))
         {
            auto rotation = -(float)(m_rotationSpeed * deltaTime);
            if (m_camera.getRoll() + rotation <= -360.0f)
               rotation += 360.0f;
            m_camera.incrementRoll(rotation);
         }
      }
   }

   bool Camera3DControllerSystem::listenEvent(
      const MouseScrolledEvent& event)
   {
      auto fov = std::max(-event.yOffset + m_camera.getFieldOfView(), 1.0f);
      fov = std::min(fov, 60.0f);
      m_translationSpeed = fov * 0.5f;
      m_camera.setFieldOfView(fov);

      return false;
   }

   bool Camera3DControllerSystem::listenEvent(
      const MouseMovedEvent& event)
   {
      Vector2 current_mouse_position(event.xPos, event.yPos);

      auto mouse_position_offset = current_mouse_position - m_lastMousePosition;
      auto yaw_offset = m_mouseSensitivity * mouse_position_offset.x;
      auto pitch_offset = m_mouseSensitivity * -mouse_position_offset.y;

      if (yaw_offset + m_camera.getYaw() >= 360.0f)
         yaw_offset -= 360.0f;
      if (yaw_offset + m_camera.getYaw() <= -360.0f)
         yaw_offset += 360.0f;
      if (pitch_offset + m_camera.getPitch() >= 360.0f)
         pitch_offset -= 360.0f;
      if (pitch_offset + m_camera.getPitch() <= -360.0f)
         pitch_offset += 360.0f;

      m_camera.incrementYaw(yaw_offset);
      m_camera.incrementPitch(pitch_offset);

      m_lastMousePosition = current_mouse_position;

      return false;
   }

   bool Camera3DControllerSystem::listenEvent(
      const WindowResizeEvent& event)
   {
      m_camera.setAspectRatio((float)event.width / (float)event.height);

      return false;
   }
}