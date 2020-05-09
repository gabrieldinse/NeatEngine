#pragma once

#include "Neat/Renderer/OrthographicCamera.h"
#include "Neat/Core/Timestep.h"
#include "Neat/Events/ApplicationEvent.h"
#include "Neat/Events/MouseEvent.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class OrthographicCameraController
   {
   public:
      OrthographicCameraController(Float aspectRatio, Bool rotationEnabled = false);

      OrthographicCamera& getCamera() { return this->camera; }
      const OrthographicCamera& getCamera() const { return this->camera; }

      void onUpdate(Timestep dt);
      void onEvent(Event& event);

   private:
      Bool onMouseScrolled(MouseScrolledEvent& event);
      Bool onMouseMoved(MouseMovedEvent& event);
      Bool onWindowResized(WindowResizeEvent& event);

   private:
      Float aspectRatio;
      Float zoomLevel = 1.0f;

      OrthographicCamera camera;

      Vec3 cameraPosition = {0.0f, 0.0f, 0.0f};
      Vec2 lastMousePosition;
      Float cameraTranslationSpeed = 1.0f;
      Float cameraRotation = 0.0f;
      Float cameraRotationSpeed = 90.0f;

      Bool rotationEnabled;
   };
}