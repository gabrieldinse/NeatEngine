#pragma once

#include "Neat/Core/PlatformDetection.hpp"
#include "Neat/Core/LayerGroup.hpp"
#include "Neat/Core/Window.hpp"
#include "Neat/Events/Events/WindowCloseEvent.hpp"
#include "Neat/Events/Events/WindowResizeEvent.hpp"
#include "Neat/Events/EventDispatcher.hpp"
#include "Neat/ImGui/ImGuiRender.hpp"

namespace Neat {
class Application {
 public:
  Application();
  virtual ~Application();

  void run();
  void stop();
  virtual void onUpdate([[maybe_unused]] double deltaTimeSeconds) {}

  template <typename T, typename... Args>
  void pushLayer(Args &&...args);
  template <typename T, typename... Args>
  void pushOverlay(Args &&...args);
  void pushLayer(Scope<Layer> &&layer);
  void pushOverlay(Scope<Layer> &&layer);
  Scope<Layer> popLayer(Int32 position);
  Scope<Layer> popOverlay(Int32 position);

  void layersOnUpdate(double deltaTimeSeconds);

  static Application &get() { return *s_instance; }
  Window &getWindow() { return *m_window; }

  bool onWindowClose(const WindowCloseEvent &event);
  bool onWindowResize(const WindowResizeEvent &event);

 protected:
  Ref<EventDispatcher> &getEventDispatcher() { return m_eventDispatcher; }

 private:
  static Application *s_instance;

  Scope<Window> m_window;
  Ref<EventDispatcher> m_eventDispatcher;
  LayerGroup m_layerGroup;

  bool m_running = false;
};

Scope<Application> createApplication();

template <typename T, typename... Args>
void Application::pushLayer(Args &&...args) {
  m_layerGroup.pushLayer<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
void Application::pushOverlay(Args &&...args) {
  m_layerGroup.pushOverlay<T>(std::forward<Args>(args)...);
}
}  // namespace Neat
