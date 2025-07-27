#include "NeatPCH.hpp"

#include "Neat/Core/Application.hpp"
#include "Neat/Core/Input.hpp"
#include "Neat/Core/Log.hpp"
#include "Neat/Core/Timer.hpp"
#include "Neat/Graphics/Renderer.hpp"

namespace Neat {
Application *Application::s_instance = nullptr;

Application::Application() : m_eventDispatcher(makeRef<EventDispatcher>()) {
  NT_PROFILE_FUNCTION();
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
  NT_PROFILE_FUNCTION();
  ImGuiRender::shutdown();
  Renderer::shutdown();
}

void Application::stop() { m_running = false; }

void Application::run() {
  NT_PROFILE_FUNCTION();
  NT_CORE_INFO("Application started");
  Timer timer;
  m_running = true;
  timer.start();

  while (m_running) {
    NT_PROFILE_SCOPE("RunLoop");
    double deltaTimeSeconds = timer.restart();

    ImGuiRender::begin();
    onUpdate(deltaTimeSeconds);
    layersOnUpdate(deltaTimeSeconds);
    ImGuiRender::end();

    m_window->onUpdate();
    m_eventDispatcher->onUpdate();
  }
  NT_CORE_INFO("Application stopped");
}

void Application::pushLayer(Scope<Layer> &&layer) {
  m_layerGroup.pushLayer(std::move(layer));
}

void Application::pushOverlay(Scope<Layer> &&layer) {
  m_layerGroup.pushOverlay(std::move(layer));
}

Scope<Layer> Application::popLayer(Int32 position) {
  return m_layerGroup.popLayer(position);
}

Scope<Layer> Application::popOverlay(Int32 position) {
  return m_layerGroup.popOverlay(position);
}

void Application::layersOnUpdate(double deltaTimeSeconds) {
  NT_PROFILE_FUNCTION();
  for (auto &layer : m_layerGroup) {
    layer->onUpdate(deltaTimeSeconds);
  }
}

bool Application::onWindowClose(
    [[maybe_unused]] const WindowCloseEvent &event) {
  stop();
  return true;
}

bool Application::onWindowResize(const WindowResizeEvent &event) {
  if (not m_window->isMinimized())
    Renderer::onWindowResize(event.width, event.height);

  return false;
}
}  // namespace Neat