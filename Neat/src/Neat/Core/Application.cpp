#include "NeatPCH.hpp"

#include "Neat/Core/Application.hpp"
#include "Neat/Core/Input.hpp"
#include "Neat/Core/Log.hpp"
#include "Neat/Core/Timer.hpp"
#include "Neat/Graphics/Renderer.hpp"

namespace Neat {
Application *Application::s_instance = nullptr;

Application::Application()
    : m_eventDispatcher(std::make_shared<EventDispatcher>()) {
  // Check of there's another application running
  NT_CORE_ASSERT(not s_instance, "Application already exists!");
  s_instance = this;

  m_window = Window::create(WindowProps(m_eventDispatcher));
  m_eventDispatcher->get<WindowCloseEvent>()
      .connect<&Application::onWindowClose>(*this, EventPriorityHighest);
  m_eventDispatcher->get<WindowResizeEvent>()
      .connect<&Application::onWindowResize>(*this, EventPriorityHighest);

  Renderer::init();
  Input::setWindow(*m_window);
  ImGuiRender::init();
}

Application::~Application() {
  ImGuiRender::shutdown();
  Renderer::shutdown();
}

void Application::stop() { m_running = false; }

void Application::run() {
  NT_CORE_INFO("Application started");
  Timer timer;
  m_running = true;
  timer.start();

  while (m_running) {
    double deltaTimeSeconds = timer.restart();
    ImGuiRender::begin();
    onUpdate(deltaTimeSeconds);
    for (auto &layer : m_layerGroup) {
      layer->onUpdate(deltaTimeSeconds);
    }
    ImGuiRender::end();
    m_window->onUpdate();
    m_eventDispatcher->onUpdate();
  }
  NT_CORE_INFO("Application stopped");
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

bool Application::onWindowClose(const WindowCloseEvent &event) {
  stop();
  return true;
}

bool Application::onWindowResize(const WindowResizeEvent &event) {
  if (not m_window->isMinimized())
    Renderer::onWindowResize(event.width, event.height);

  return false;
}
}  // namespace Neat