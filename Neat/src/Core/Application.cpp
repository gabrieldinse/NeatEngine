#include "NeatPCH.hpp"

#include "Application.hpp"
#include "Input.hpp"
#include "Log.hpp"
#include "Timer.hpp"

#include "Graphics/Renderer.hpp"

#include "ImGui/ImGuiRender.hpp"

namespace Neat {
Application *Application::s_instance = nullptr;

Application::Application(const ApplicationProperties &appProperties,
                         const ApplicationCommandLineArguments &commandLineArgs)
    : m_commandLineArgs{commandLineArgs},
      m_eventDispatcher(makeRef<EventDispatcher>()),
      m_window(m_eventDispatcher, appProperties.windowProperties) {
  NT_PROFILE_FUNCTION();
  NT_CORE_ASSERT(not s_instance, "Application already exists!");
  s_instance = this;

  m_eventDispatcher->get<WindowCloseEvent>()
      .connect<&Application::onWindowClose>(*this, EventPriorityHighest);
  m_eventDispatcher->get<WindowResizeEvent>()
      .connect<&Application::onWindowResize>(*this, EventPriorityHighest);

  Renderer::initialize();
  Input::setWindow(m_window);
  ImGuiRender::initialize();
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
    update(deltaTimeSeconds);
    m_layerGroup.update(deltaTimeSeconds);
    ImGuiRender::end();

    m_window.update();
    m_eventDispatcher->update();
  }
  NT_CORE_INFO("Application stopped");
}

void Application::pushLayer(Scope<Layer> &&layer) {
  NT_PROFILE_FUNCTION();
  m_layerGroup.pushLayer(std::move(layer));
}

void Application::pushOverlay(Scope<Layer> &&layer) {
  NT_PROFILE_FUNCTION();
  m_layerGroup.pushOverlay(std::move(layer));
}

Scope<Layer> Application::popLayer(Int32 position) {
  NT_PROFILE_FUNCTION();
  return m_layerGroup.popLayer(position);
}

Scope<Layer> Application::popOverlay(Int32 position) {
  NT_PROFILE_FUNCTION();
  return m_layerGroup.popOverlay(position);
}

bool Application::onWindowClose(
    [[maybe_unused]] const WindowCloseEvent &event) {
  NT_PROFILE_FUNCTION();
  stop();
  return true;
}

bool Application::onWindowResize(const WindowResizeEvent &event) {
  NT_PROFILE_FUNCTION();
  if (not m_window.isMinimized())
    Renderer::onWindowResize(event.width, event.height);

  return false;
}
}  // namespace Neat