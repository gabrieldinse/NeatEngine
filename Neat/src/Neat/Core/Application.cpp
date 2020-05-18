#include <chrono>
#include <thread>

#include "Neat/Core/Application.h"
#include "Neat/Core/Input.h"
#include "Neat/Core/Log.h"
#include "Neat/Core/Timer.h"
#include "Neat/Events/Event.h"
#include "Neat/ImGui/ImGuiRender.h"
#include "Neat/Renderer/Renderer.h"
#include "Neat/Debug/Instrumentator.h"


namespace Neat
{
   Application* Application::s_instance = nullptr;

   Application::Application()
   {
      NT_PROFILE_FUNCTION();

      // Check of there's another application running
      NT_CORE_ASSERT(!s_instance, "Application already exists!");
      s_instance = this;

      m_window = std::make_unique<Window>(this->events);

      events.subscribe<WindowCloseEvent>(*this);
      events.subscribe<WindowResizeEvent>(*this);

      Renderer::init();
      ImGuiRender::init();
      Input::init(m_window->getNativeWindow());
   }

   Application::~Application()
   {
      NT_PROFILE_FUNCTION();

      events.unsubscribe<WindowCloseEvent>(*this);
      events.unsubscribe<WindowResizeEvent>(*this);

      Renderer::shutdown();
      ImGuiRender::shutdown();
   }

   void Application::run()
   {
      NT_PROFILE_FUNCTION();

      m_running = true;
      std::thread update_loop(&Application::updateLoop, this);
      renderLoop();
      update_loop.join();
   }

   void Application::stop()
   {
      m_running = false;
   }

   void Application::updateLoop()
   {
      Timer timer;
      Timestep accumulator = 0.0f;

      timer.start();

      while (m_running)
      {
         NT_PROFILE_SCOPE("Update loop");

         timer.reset();
         accumulator += timer.getDeltaTime();

         while (accumulator >= m_deltaTime)
         {
            NT_PROFILE_SCOPE("LayerGroup onUpdate");

            for (auto& layer : m_layerGroup)
               layer->onUpdate(m_deltaTime);
            accumulator -= m_deltaTime;
         }
      }
   }

   void Application::renderLoop()
   {
      while (m_running)
      {
         NT_PROFILE_SCOPE("Render loop");

         if (!m_window->isMinimized())
         {
            NT_PROFILE_SCOPE("LayerGroup onRender");

            for (auto& layer : m_layerGroup)
               layer->onRender();
         }

      #ifdef NT_IMGUI
         ImGuiRender::begin();
         {
            NT_PROFILE_SCOPE("LayerGroup onImGuiRender");

            for (auto& layer : m_layerGroup)
               layer->onImGuiRender();
         }
         ImGuiRender::end();
      #endif

         m_window->onUpdate();
      }
   }

   void Application::pushLayer(std::unique_ptr<Layer>&& layer)
   {
      NT_PROFILE_FUNCTION();

      m_layerGroup.pushLayer(std::move(layer));
   }

   void Application::pushOverlay(std::unique_ptr<Layer>&& layer)
   {
      NT_PROFILE_FUNCTION();

      m_layerGroup.pushOverlay(std::move(layer));
   }

   std::unique_ptr<Layer> Application::popLayer(Int position)
   {
      NT_PROFILE_FUNCTION();

      return m_layerGroup.popLayer(position);
   }

   std::unique_ptr<Layer> Application::popLayer(const std::string& name)
   {
      NT_PROFILE_FUNCTION();

      return m_layerGroup.popLayer(name);
   }


   std::unique_ptr<Layer> Application::popOverlay(Int position)
   {
      NT_PROFILE_FUNCTION();

      return m_layerGroup.popOverlay(position);
   }

   std::unique_ptr<Layer> Application::popOverlay(const std::string& name)
   {
      NT_PROFILE_FUNCTION();

      return m_layerGroup.popOverlay(name);
   }


   // Events receiving
   bool Application::receive(const WindowCloseEvent& event)
   {
      stop();
      return true;
   }

   bool Application::receive(const WindowResizeEvent& event)
   {
      if (!m_window->isMinimized())
         Renderer::onWindowResize(event.width, event.height);

      return false;
   }
}