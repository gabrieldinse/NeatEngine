#include <chrono>
#include <thread>

#include "Neat/Core/Application.h"
#include "Neat/Core/Input.h"
#include "Neat/Core/Log.h"
#include "Neat/Core/Stopwatch.h"
#include "Neat/Events/Event.h"
#include "Neat/ImGui/ImGuiRender.h"
#include "Neat/Renderer/Renderer.h"
#include "Neat/Helper/FPSCounter.h"


namespace Neat
{
   Application* Application::s_instance = nullptr;

   Application::Application()
   {
      // Check of there's another application running
      NT_CORE_ASSERT(!s_instance, "Application already exists!");
      s_instance = this;

      m_window = std::make_unique<Window>(events());

      events().subscribe<WindowCloseEvent>(*this);
      events().subscribe<WindowResizeEvent>(*this);

      Renderer::init();
      ImGuiRender::init();
      Input::init(m_window->getNativeWindow());
   }

   Application::~Application()
   {
      events().unsubscribe<WindowCloseEvent>(*this);
      events().unsubscribe<WindowResizeEvent>(*this);

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
      Stopwatch stopwatch;
      double accumulator = 0.0f;

      m_running = true;

      stopwatch.start();
      fps_counter.start();

      while (m_running)
      {
         accumulator += stopwatch.restart();
         fps_counter.addFrame();

         while (accumulator >= m_updatePeriod)
         {
            for (auto& layer : m_layerGroup)
               layer->update(m_updatePeriod);
            accumulator -= m_updatePeriod;
         }

         if (!m_window->isMinimized())
         {
            for (auto& layer : m_layerGroup)
               layer->render();
         }

      #ifdef NT_IMGUI
         ImGuiRender::begin();

         for (auto& layer : m_layerGroup)
            layer->onImGuiRender();

         ImGuiRender::end();
      #endif

         m_window->update();
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

   std::unique_ptr<Layer> Application::popLayer(const std::string& name)
   {
      return m_layerGroup.popLayer(name);
   }


   std::unique_ptr<Layer> Application::popOverlay(Int position)
   {
      return m_layerGroup.popOverlay(position);
   }

   std::unique_ptr<Layer> Application::popOverlay(const std::string& name)
   {
      return m_layerGroup.popOverlay(name);
   }

   template <typename T, typename... Args>
   void Application::pushLayer(Args&&... args)
   {
      pushLayer(std::make_unique<T>(std::forward<Args>(args)...));
   }

   template <typename T, typename... Args>
   void Application::pushOverlay(Args&&... args)
   {
      pushOverlay(std::make_unique<T>(std::forward<Args>(args)...));
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