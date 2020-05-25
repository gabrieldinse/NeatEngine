#include <algorithm>

#include "Neat/Core/Application.h"
#include "Neat/Core/OrthographicCameraController.h"
#include "Neat/Core/Input.h"
#include "Neat/Core/Log.h"
#include "Neat/Math/Transforms.h"


namespace Neat
{
   OrthographicCameraController::OrthographicCameraController(
      float aspectRatio, EventManager& eventManager, bool rotationEnabled)
      : m_aspectRatio(aspectRatio)
      , m_camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio* m_zoomLevel,
         -m_zoomLevel, m_zoomLevel, -m_zoomLevel)
      , m_rotationEnabled(rotationEnabled)
      , m_events(eventManager)
      , m_lastMousePosition(Input::getMouseX(), Input::getMouseY())
   {
      m_events.subscribe<MouseMovedEvent>(*this);
      m_events.subscribe<MouseScrolledEvent>(*this);
      m_events.subscribe<WindowResizeEvent>(*this);
   }

   OrthographicCameraController::~OrthographicCameraController()
   {
      m_events.unsubscribe<MouseMovedEvent>(*this);
      m_events.unsubscribe<MouseScrolledEvent>(*this);
      m_events.unsubscribe<WindowResizeEvent>(*this);
   }

   void OrthographicCameraController::update(DeltaTime deltaTime)
   {
      if (!((Input::isKeyPressed(KeyCode::LeftControl) ||
         Input::isKeyPressed(KeyCode::RightControl)) &&
         Input::isMouseButtonPressed(MouseCode::ButtonLeft)))
      {
         if (Input::isKeyPressed(KeyCode::W))
         {
            m_cameraPosition.y += (float)(m_cameraTranslationSpeed * deltaTime);
            m_camera.setPosition(m_cameraPosition);
         }

         if (Input::isKeyPressed(KeyCode::S))
         {
            m_cameraPosition.y -= (float)(m_cameraTranslationSpeed * deltaTime);
            m_camera.setPosition(m_cameraPosition);
         }

         if (Input::isKeyPressed(KeyCode::D))
         {
            m_cameraPosition.x += (float)(m_cameraTranslationSpeed * deltaTime);
            m_camera.setPosition(m_cameraPosition);
         }

         if (Input::isKeyPressed(KeyCode::A))
         {
            m_cameraPosition.x -= (float)(m_cameraTranslationSpeed * deltaTime);
            m_camera.setPosition(m_cameraPosition);
         }
      }

      if (m_rotationEnabled)
      {
         if (Input::isKeyPressed(KeyCode::Q))
         {
            m_cameraRotation += (float)(m_cameraRotationSpeed * deltaTime);
            if (m_cameraRotation >= 360.0f)
               m_cameraRotation -= 360.0f;
            m_camera.setRotation(m_cameraRotation);
         }

         if (Input::isKeyPressed(KeyCode::E))
         {
            m_cameraRotation -= (float)(m_cameraRotationSpeed * deltaTime);
            if (m_cameraRotation <= -360.0f)
               m_cameraRotation += 360.0f;
            m_camera.setRotation(m_cameraRotation);
         }
      }
   }

   bool OrthographicCameraController::receive(const MouseScrolledEvent& event)
   {
      if ((Input::isKeyPressed(KeyCode::LeftControl) ||
         Input::isKeyPressed(KeyCode::RightControl)))
      {
         m_zoomLevel -= event.yOffset * 0.2f;
         m_zoomLevel = std::max(m_zoomLevel, 0.25f);
         m_cameraTranslationSpeed = 2.0f * m_zoomLevel;
         m_camera.setProjection(
            -m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel,
            -m_zoomLevel, m_zoomLevel,
            -m_zoomLevel);
      }

      return false;
   }

   bool OrthographicCameraController::receive(const MouseMovedEvent& event)
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
            rotate(degreesToRadians(m_cameraRotation), { 0, 0, 1 }) *
            scale(Vector3(-scale_factor, scale_factor, 1.0f)) *
            Vector4(mouse_possition_offset, 0.0f, 1.0f);

         m_cameraPosition = m_cameraPosition + Vector3(screen_position_offset);
         m_camera.setPosition(m_cameraPosition);
      }

      m_lastMousePosition = current_mouse_position;

      return false;
   }

   bool OrthographicCameraController::receive(const WindowResizeEvent& event)
   {
      m_aspectRatio = (float)event.width / (float)event.height;
      m_camera.setProjection(
         -m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel,
         -m_zoomLevel, m_zoomLevel,
         -m_zoomLevel);

      return false;
   }
}