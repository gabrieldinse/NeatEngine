#pragma once

#include "Neat/Core/Core.h"
#include "Neat/Core/Window.h"
#include "Neat/Core/LayerGroup.h"
#include "Neat/Events/ApplicationEvent.h"
#include "Neat/Core/Timestep.h"


namespace Neat
{
   class Event;


   class  Application
   {
   public:
      Application();
      virtual ~Application();

      void run();
      void onEvent(Event& e);

      template <typename T, typename... Args>
      void pushLayer(Args&&... args)
      {
         this->pushLayer(std::make_unique<T>(std::forward<Args>(args)...));
      }

      template <typename T, typename... Args>
      void pushOverlay(Args&&... args)
      {
         this->pushOverlay(std::make_unique<T>(std::forward<Args>(args)...));
      }

      void pushLayer(std::unique_ptr<Layer>&& layer);
      void pushOverlay(std::unique_ptr<Layer>&& layer);
      std::unique_ptr<Layer> popLayer(Int position);
      std::unique_ptr<Layer> popLayer(const std::string& name);
      std::unique_ptr<Layer> popOverlay(Int position);
      std::unique_ptr<Layer> popOverlay(const std::string& name);

      void setUpdateRate(Float rate) { this->dt = 1.0f / rate; }

      static Application& get() { return *instance; }
      Window& getWindow() { return this->window; }

   private:
      void updateLoop();
      void renderLoop();

      // Callbacks
      Bool onWindowClose(WindowCloseEvent& event);
      Bool onWindowResize(WindowResizeEvent& event);

   private:
      static Application* instance;

      Window window;
      LayerGroup layerGroup;
      Float dt = 1.0f / 120.0f;

      Bool running = false;
   };

   std::unique_ptr<Application> createApplication();
}


