#include "Neat/Core/Application.hpp"
#include "Neat/Core/Input.hpp"
#include "Neat/ECS/Systems/Camera3DControllerSystem.hpp"
#include "Neat/Math/Trigonometric.hpp"


namespace Neat
{
   Camera3DControllerSystem::Camera3DControllerSystem(float aspectRatio,
      bool rotationEnabled)
      : m_rotationEnabled(rotationEnabled)
   {
      m_camera.setPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
      m_translationSpeed = m_camera.getFieldOfView() * 0.5f;
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

   void Camera3DControllerSystem::update(EntityManager& entityManager,
      EventManager& eventManager, DeltaTime deltaTime)
   {
      auto distance = (float)(m_translationSpeed * deltaTime);
      if (Input::isKeyPressed(KeyCode::W))
         m_camera.moveForward(distance);

      if (Input::isKeyPressed(KeyCode::S))
         m_camera.moveBackward(distance );

      if (Input::isKeyPressed(KeyCode::D))
         m_camera.moveRight(distance);

      if (Input::isKeyPressed(KeyCode::A))
         m_camera.moveLeft(distance);

      if (Input::isKeyPressed(KeyCode::Z))
         m_camera.moveUp(distance);

      if (Input::isKeyPressed(KeyCode::X))
         m_camera.moveDown(distance);

      if (m_rotationEnabled)
      {
         auto rotation = (float)(m_rotationSpeed * deltaTime);
         if (Input::isKeyPressed(KeyCode::Q))
            m_camera.setRoll(wrap360(m_camera.getRoll() + rotation));

         if (Input::isKeyPressed(KeyCode::E))
            m_camera.setRoll(wrap360(m_camera.getRoll() - rotation));
      }
   }

   bool Camera3DControllerSystem::listenEvent(const MouseScrolledEvent& event)
   {
      auto fov = clamp(-event.yOffset + m_camera.getFieldOfView(), 1.0f, 60.0f);
      m_translationSpeed = fov * 0.5f;
      m_camera.setFieldOfView(fov);

      return false;
   }

   bool Camera3DControllerSystem::listenEvent(const MouseMovedEvent& event)
   {
      if (m_firstMouse)
      {
         m_lastMousePosition = Vector2F(event.xPos, event.yPos);
         m_firstMouse = false;
      }

      Vector2F current_mouse_position(event.xPos, event.yPos);
      auto mouse_position_offset = current_mouse_position - m_lastMousePosition;
      m_lastMousePosition = current_mouse_position;

      auto yaw_offset = -m_mouseSensitivity * mouse_position_offset.x;
      auto pitch_offset = -m_mouseSensitivity * mouse_position_offset.y;
      m_camera.setYaw(wrap360(yaw_offset + m_camera.getYaw()));
      m_camera.setPitch(wrap360(pitch_offset + m_camera.getPitch()));

      return false;
   }

   bool Camera3DControllerSystem::listenEvent(
      const WindowResizeEvent& event)
   {
      m_camera.setAspectRatio((float)event.width / (float)event.height);

      return false;
   }
}