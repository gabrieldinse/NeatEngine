#pragma once

#include "Neat/Core/Core.h"
#include "Neat/Core/Window.h"
#include "Neat/Core/LayerGroup.h"
#include "Neat/Events/EventManager.h"
#include "Neat/Events/Event.h"


namespace Neat
{
   class Application : public EventSubscriber<Application>
   {
   public:
      Application();
      virtual ~Application();

      void run();
      void stop();

      template <typename T, typename... Args>
      void pushLayer(Args&&... args)
      {
         pushLayer(std::make_unique<T>(std::forward<Args>(args)...));
      }

      template <typename T, typename... Args>
      void pushOverlay(Args&&... args)
      {
         pushOverlay(std::make_unique<T>(std::forward<Args>(args)...));
      }

      void pushLayer(std::unique_ptr<Layer>&& layer);
      void pushOverlay(std::unique_ptr<Layer>&& layer);
      std::unique_ptr<Layer> popLayer(Int position);
      std::unique_ptr<Layer> popLayer(const std::string& name);
      std::unique_ptr<Layer> popOverlay(Int position);
      std::unique_ptr<Layer> popOverlay(const std::string& name);

      void setUpdateRate(Timestep rate) { m_deltaTime = 1.0f / rate; }

      static Application& get() { return *s_instance; }
      Window& getWindow() { return *m_window; }

      // Events receiving
      bool receive(const WindowCloseEvent& event);
      bool receive(const WindowResizeEvent& event);

      EventManager events;

   private:
      void updateLoop();
      void renderLoop();

   private:
      static Application* s_instance;

      std::unique_ptr<Window> m_window;
      LayerGroup m_layerGroup;
      Timestep m_deltaTime = 1.0f / 120.0f;

      bool m_running = false;
   };

   std::unique_ptr<Application> createApplication();
}


