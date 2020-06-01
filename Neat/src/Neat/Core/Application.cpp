#include <chrono>
#include <thread>

#include "Neat/Core/Application.h"
#include "Neat/Core/Input.h"
#include "Neat/Core/Log.h"
#include "Neat/Core/Timer.h"
#include "Neat/Events/Event.h"
#include "Neat/ImGui/ImGuiRender.h"
#include "Neat/Graphics/Renderer.h"
#include "Neat/Helper/FPSCounter.h"


namespace Neat
{
   Application* Application::s_instance = nullptr;

   Application::Application()
   {
      // Check of there's another application running
      NT_CORE_ASSERT(!s_instance, "Application already exists!");
      s_instance = this;

      m_window = std::make_unique<Window>(m_events);

      m_events.subscribe<WindowCloseEvent>(
         *this, EventPriority::Highest, true);
      m_events.subscribe<WindowResizeEvent>(
         *this, EventPriority::Highest, true);

      Renderer::init();
      ImGuiRender::init();
      Input::setWindow(m_window->getNativeWindow());
   }

   Application::~Application()
   {
      Renderer::shutdown();
      ImGuiRender::shutdown();
   }

   void Application::stop()
   {
      m_running = false;
   }

   void Application::run()
   {
      FPSCounter fps_counter;
      Timer timer;
      double accumulator = 0.0f;

      m_running = true;

      timer.start();
      fps_counter.start();

      while (m_running)
      {
         fps_counter.addFrame();
         update(timer.restart());

      #ifdef NT_IMGUI
         ImGuiRender::begin();
         imGuiRender();
         ImGuiRender::end();
      #endif

         m_window->swapBuffers();
         m_window->pollEvents();
      }
   }

   void Application::pushLayer(std::unique_ptr<Layer>&& layer)
   {
      m_layerGroup.pushLayer(std::move(layer));
   }

   void Application::pushOverlay(std::unique_ptr<Layer>&& layer)
   {
      m_layerGroup.pushOverlay(std::move(layer));
   }

   std::unique_ptr<Layer> Application::popLayer(Int position)
   {
      return m_layerGroup.popLayer(position);
   }

   std::unique_ptr<Layer> Application::popOverlay(Int position)
   {
      return m_layerGroup.popOverlay(position);
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