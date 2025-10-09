#pragma once

#include "PlatformDetection.hpp"
#include "LayerGroup.hpp"
#include "Window.hpp"
#include "ApplicationProperties.hpp"
#include "ApplicationCommandLineArguments.hpp"

#include "Events/WindowCloseEvent.hpp"
#include "Events/WindowResizeEvent.hpp"
#include "EventDispatching/EventDispatcher.hpp"
#include "ImGui/ImGuiRender.hpp"

namespace Neat {
class Application {
 public:
  Application(
      const ApplicationProperties &appProperties = ApplicationProperties{},
      const ApplicationCommandLineArguments &commandLineArgs =
          ApplicationCommandLineArguments{});
  virtual ~Application();

  virtual void run();
  virtual void close() { stop(); }
  virtual void update([[maybe_unused]] double deltaTimeSeconds) {}

  template <typename T, typename... Args>
  void pushLayer(Args &&...args);
  template <typename T, typename... Args>
  void pushOverlay(Args &&...args);
  void pushLayer(Scope<Layer> &&layer);
  void pushOverlay(Scope<Layer> &&layer);
  Scope<Layer> popLayer(Int32 position);
  Scope<Layer> popOverlay(Int32 position);

  static Application &get() { return *s_instance; }
  Window &getWindow() { return *m_window; }

  const ApplicationCommandLineArguments &getCommandLineArgs() const {
    return m_commandLineArgs;
  }

 protected:
  Ref<EventDispatcher> &getEventDispatcher() { return m_eventDispatcher; }

 private:
  void stop();
  bool onWindowClose(const WindowCloseEvent &event);
  bool onWindowResize(const WindowResizeEvent &event);

 private:
  static Application *s_instance;

  ApplicationCommandLineArguments m_commandLineArgs;

  Scope<Window> m_window;
  Ref<EventDispatcher> m_eventDispatcher;
  LayerGroup m_layerGroup;

  bool m_running = false;
  bool m_initialized = false;
};

Scope<Application> createApplication(
    const ApplicationCommandLineArguments &commandLineArgs);

template <typename T, typename... Args>
void Application::pushLayer(Args &&...args) {
  m_layerGroup.pushLayer<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
void Application::pushOverlay(Args &&...args) {
  m_layerGroup.pushOverlay<T>(std::forward<Args>(args)...);
}
}  // namespace Neat
