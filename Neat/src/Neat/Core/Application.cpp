#include <chrono>
#include <thread>

#include "Neat/Core/Application.hpp"
#include "Neat/Core/Input.hpp"
#include "Neat/Core/Log.hpp"
#include "Neat/Core/Timer.hpp"
#include "Neat/Events/Event.hpp"
#include "Neat/Graphics/Renderer.hpp"
#include "Neat/Helper/FPSCounter.hpp"
#include "Neat/ImGui/ImGuiRender.hpp"

namespace Neat {
Application *Application::s_instance = nullptr;

Application::Application() {
  // Check of there's another application running
  NT_CORE_ASSERT(!s_instance, "Application already exists!");
  s_instance = this;

  m_window = std::make_unique<Window>(m_events);

  m_events.addListener<WindowCloseEvent>(*this, EventPriority::Highest, true);
  m_events.addListener<WindowResizeEvent>(*this, EventPriority::Highest, true);

  Renderer::init();
  ImGuiRender::init();
  Input::setWindow(*m_window);
}

Application::~Application() {
  Renderer::shutdown();
  ImGuiRender::shutdown();
}

void Application::stop() { m_running = false; }

void Application::run() {
  FPSCounter fps_counter;
  Timer timer;

  m_running = true;

  timer.start();
  fps_counter.start();

  while (m_running) {
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

void Application::pushLayer(std::unique_ptr<Layer> &&layer) {
  m_layerGroup.pushLayer(std::move(layer));
}

void Application::pushOverlay(std::unique_ptr<Layer> &&layer) {
  m_layerGroup.pushOverlay(std::move(layer));
}

std::unique_ptr<Layer> Application::popLayer(Int32 position) {
  return m_layerGroup.popLayer(position);
}

std::unique_ptr<Layer> Application::popOverlay(Int32 position) {
  return m_layerGroup.popOverlay(position);
}

// Events receiving
bool Application::listenEvent(const WindowCloseEvent &event) {
  stop();
  return true;
}

bool Application::listenEvent(const WindowResizeEvent &event) {
  if (!m_window->isMinimized())
    Renderer::onWindowResize(event.width, event.height);

  return false;
}
} // namespace Neat