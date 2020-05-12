#include <chrono>
#include <thread>

#include "Neat/Core/Application.h"
#include "Neat/Core/Log.h"
#include "Neat/Core/Timer.h"
#include "Neat/Events/Event.h"
#include "Neat/ImGui/ImGuiRender.h"
#include "Neat/Renderer/Renderer.h"
#include "Neat/Debug/Instrumentator.h"



namespace Neat
{
   Application* Application::instance = nullptr;

   Application::Application()
   {
      NT_PROFILE_FUNCTION();

      // Check of there's another application running
      NT_CORE_ASSERT(!instance, "Application already exists!");
      instance = this;

      this->window.setEventCallback(
         [this](Event& event) { this->onEvent(event); });

      Renderer::init();
      ImGuiRender::init();
   }

   Application::~Application()
   {
      NT_PROFILE_FUNCTION();

      Renderer::shutdown();
      ImGuiRender::shutdown();
   }

   void Application::run()
   {
      NT_PROFILE_FUNCTION();

      this->running = true;
      std::thread update_loop(&Application::updateLoop, this);
      renderLoop();
      update_loop.join();
   }

   void Application::updateLoop()
   {
      Timer timer;
      Float accumulator = 0.0f;

      timer.start();

      while (this->running)
      {
         NT_PROFILE_SCOPE("Update loop");

         timer.reset();
         accumulator += timer.getDeltaTime();

         while (accumulator >= this->deltaTime)
         {
            NT_PROFILE_SCOPE("LayerGroup onUpdate");

            for (auto& layer : this->layerGroup)
               layer->onUpdate(this->deltaTime);
            accumulator -= this->deltaTime;
         }
      }
   }

   void Application::renderLoop()
   {
      while (this->running)
      {
         NT_PROFILE_SCOPE("Render loop");

         if (!this->window.isMinimized())
         {
            NT_PROFILE_SCOPE("LayerGroup onRender");

            for (auto& layer : this->layerGroup)
               layer->onRender();
         }

      #ifdef NT_IMGUI
         ImGuiRender::begin();
         {
            NT_PROFILE_SCOPE("LayerGroup onImGuiRender");

            for (auto& layer : this->layerGroup)
               layer->onImGuiRender();
         }
         ImGuiRender::end();
      #endif

         this->window.onUpdate();
      }
   }

   void Application::onEvent(Event& event)
   {
      NT_PROFILE_FUNCTION();

      event.dispatch<WindowCloseEvent>(
         [this](WindowCloseEvent& event) { return this->onWindowClose(event); });
      event.dispatch<WindowResizeEvent>(
         [this](WindowResizeEvent& event) { return this->onWindowResize(event); });

      // Do stuff with the event until its handled (function returns true)
      for (auto& layer : this->layerGroup)
      {
         layer->onEvent(event);
         if (event.isHandled())
            break;
      }
   }

   void Application::pushLayer(std::unique_ptr<Layer>&& layer)
   {
      NT_PROFILE_FUNCTION();

      this->layerGroup.pushLayer(std::move(layer));
   }

   void Application::pushOverlay(std::unique_ptr<Layer>&& layer)
   {
      NT_PROFILE_FUNCTION();

      this->layerGroup.pushOverlay(std::move(layer));
   }

   std::unique_ptr<Layer> Application::popLayer(Int position)
   {
      NT_PROFILE_FUNCTION();

      return this->layerGroup.popLayer(position);
   }

   std::unique_ptr<Layer> Application::popLayer(const std::string& name)
   {
      NT_PROFILE_FUNCTION();

      return this->layerGroup.popLayer(name);
   }


   std::unique_ptr<Layer> Application::popOverlay(Int position)
   {
      NT_PROFILE_FUNCTION();

      return this->layerGroup.popOverlay(position);
   }

   std::unique_ptr<Layer> Application::popOverlay(const std::string& name)
   {
      NT_PROFILE_FUNCTION();

      return this->layerGroup.popOverlay(name);
   }

   Bool Application::onWindowClose(WindowCloseEvent& event)
   {
      this->running = false;
      return true;
   }

   Bool Application::onWindowResize(WindowResizeEvent& event)
   {
      NT_PROFILE_FUNCTION();

      if (this->window.isMinimized())
         return false;

      Renderer::onWindowResize(event.getWidth(), event.getHeight());

      return false;
   }
}