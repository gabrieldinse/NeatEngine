#include <algorithm>

#include "Neat/Core/Application.h"
#include "Neat/Core/OrthographicCameraController.h"
#include "Neat/Core/Input.h"
#include "Neat/Core/Log.h"
#include "Neat/Debug/Instrumentator.h"
#include "Neat/Math/Transforms.h"


namespace Neat
{
   OrthographicCameraController::OrthographicCameraController(Float aspectRatio, Bool rotationEnabled)
      : camera(-aspectRatio * this->zoomLevel, aspectRatio * this->zoomLevel,
         -this->zoomLevel, this->zoomLevel)
      , aspectRatio(aspectRatio)
      , rotationEnabled(rotationEnabled)
      , lastMousePosition(getMouseX(), getMouseY())
   {
   }

   void OrthographicCameraController::onUpdate(Timestep dt)
   {
      NT_PROFILE_FUNCTION();

      // Camera --------------------------------------
      if (!((isKeyPressed(KeyCode::LeftControl) ||
         isKeyPressed(KeyCode::RightControl)) &&
         isMouseButtonPressed(MouseCode::ButtonLeft)))
      {
         if (isKeyPressed(KeyCode::W))
         {
            this->cameraPosition.y += this->cameraTranslationSpeed * dt;
            this->camera.setPosition(this->cameraPosition);
         }

         if (isKeyPressed(KeyCode::S))
         {
            this->cameraPosition.y -= this->cameraTranslationSpeed * dt;
            this->camera.setPosition(this->cameraPosition);
         }

         if (isKeyPressed(KeyCode::D))
         {
            this->cameraPosition.x += this->cameraTranslationSpeed * dt;
            this->camera.setPosition(this->cameraPosition);
         }

         if (isKeyPressed(KeyCode::A))
         {
            this->cameraPosition.x -= this->cameraTranslationSpeed * dt;
            this->camera.setPosition(this->cameraPosition);
         }
      }

      if (this->rotationEnabled)
      {
         if (isKeyPressed(KeyCode::Q))
         {
            this->cameraRotation += this->cameraRotationSpeed * dt;
            if (this->cameraRotation >= 360.0f)
               this->cameraRotation -= 360.0f;
            this->camera.setRotation(this->cameraRotation);
         }

         if (isKeyPressed(KeyCode::E))
         {
            this->cameraRotation -= this->cameraRotationSpeed * dt;
            if (this->cameraRotation <= -360.0f)
               this->cameraRotation += 360.0f;
            this->camera.setRotation(this->cameraRotation);
         }
      }
   }

   void OrthographicCameraController::onEvent(Event& event)
   {
      NT_PROFILE_FUNCTION();

      event.dispatch<MouseScrolledEvent>(
         [this](MouseScrolledEvent& event) { return this->onMouseScrolled(event); });
      event.dispatch<MouseMovedEvent>(
         [this](MouseMovedEvent& event) { return this->onMouseMoved(event); });
      event.dispatch<WindowResizeEvent>(
         [this](WindowResizeEvent& event) { return this->onWindowResized(event); });
      
   }

   Bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& event)
   {
      NT_PROFILE_FUNCTION();

      if ((isKeyPressed(KeyCode::LeftControl) ||
         isKeyPressed(KeyCode::RightControl)))
      {
         this->zoomLevel -= event.getYOffset() * 0.2f;
         this->zoomLevel = std::max(zoomLevel, 0.25f);
         this->cameraTranslationSpeed = 2.0f * this->zoomLevel;
         this->camera.setProjection(
            -aspectRatio * this->zoomLevel,
             aspectRatio * this->zoomLevel,
            -this->zoomLevel, this->zoomLevel);
      }

      return false;
   }

   Bool OrthographicCameraController::onMouseMoved(MouseMovedEvent& event)
   {
      NT_PROFILE_FUNCTION();

      Vec2 current_mouse_position(event.getX(), event.getY());

      if ((isKeyPressed(KeyCode::LeftControl) ||
         isKeyPressed(KeyCode::RightControl)) &&
         isMouseButtonPressed(MouseCode::ButtonLeft))
      {
         const auto& window = Application::get().getWindow();
         const auto scale_factor = 
            2.0f * this->zoomLevel / (Float)window.getHeight();

         auto mouse_possition_offset =
            current_mouse_position - this->lastMousePosition;
         auto screen_position_offset = 
            rotate(degreesToRadians(this->cameraRotation), { 0, 0, 1 }) *
            scale(Vec3(-scale_factor, scale_factor, 1.0f)) *
            Vec4(mouse_possition_offset, 0.0f, 1.0f);

         this->cameraPosition = this->cameraPosition + Vec3(screen_position_offset);
         this->camera.setPosition(this->cameraPosition);
      }

      this->lastMousePosition = current_mouse_position;

      return false;
   }

   Bool OrthographicCameraController::onWindowResized(WindowResizeEvent& event)
   {
      NT_PROFILE_FUNCTION();

      this->aspectRatio = (Float)event.getWidth() / (Float)event.getHeight();
      this->camera.setProjection(
         -aspectRatio * this->zoomLevel,
          aspectRatio * this->zoomLevel,
         -this->zoomLevel, this->zoomLevel);

      return false;
   }
}