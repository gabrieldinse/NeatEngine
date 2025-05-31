#include "Neat/Core/Application.hpp"
#include "Neat/Core/Input.hpp"
#include "Neat/Core/Log.hpp"
#include "Neat/Core/Timer.hpp"
#include "Neat/Graphics/Renderer.hpp"

namespace Neat {
Application *Application::s_instance = nullptr;

Application::Application() {
  // Check of there's another application running
  NT_CORE_ASSERT(not s_instance, "Application already exists!");
  s_instance = this;

  m_window = std::make_unique<Window>(m_events);

  m_events.addListener<WindowCloseEvent>(*this, EventPriority::Highest, true);
  m_events.addListener<WindowResizeEvent>(*this, EventPriority::Highest, true);

  Renderer::init();
  Input::setWindow(*m_window);
}

Application::~Application() { Renderer::shutdown(); }

void Application::stop() { m_running = false; }

void Application::run() {
  Timer timer;
  m_running = true;
  timer.start();

  while (m_running) {
    update(timer.restart());
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

bool Application::handleEvent(const WindowCloseEvent &event) {
  stop();
  return true;
}

bool Application::handleEvent(const WindowResizeEvent &event) {
  if (not m_window->isMinimized())
    Renderer::onWindowResize(event.width, event.height);

  return false;
}
}  // namespace Neat