#pragma once

#include "Neat/Core/Base.hpp"
#include "Neat/Core/LayerGroup.hpp"
#include "Neat/Core/Window.hpp"
#include "Neat/Events/Events/WindowCloseEvent.hpp"
#include "Neat/Events/Events/WindowResizeEvent.hpp"
#include "Neat/Events/EventManager.hpp"

namespace Neat {
class Application : public EventListener<Application> {
 public:
  Application();
  virtual ~Application();

  void run();
  void stop();
  virtual void update(DeltaTime deltaTime) {}

  template <typename T, typename... Args>
  void pushLayer(Args &&...args);
  template <typename T, typename... Args>
  void pushOverlay(Args &&...args);
  void pushLayer(std::unique_ptr<Layer> &&layer);
  void pushOverlay(std::unique_ptr<Layer> &&layer);
  std::unique_ptr<Layer> popLayer(Int32 position);
  std::unique_ptr<Layer> popOverlay(Int32 position);

  void setUpdateRate(double rate) { m_updatePeriod = 1.0f / rate; }

  static Application &get() { return *s_instance; }
  Window &getWindow() { return *m_window; }

  // Events receiving
  bool handleEvent(const WindowCloseEvent &event);
  bool handleEvent(const WindowResizeEvent &event);

  EventManager &events() { return m_events; }

 private:
  static Application *s_instance;

  std::unique_ptr<Window> m_window;
  EventManager m_events;
  LayerGroup m_layerGroup;
  double m_updatePeriod = 1.0f / 120.0f;

  bool m_running = false;
};

std::unique_ptr<Application> createApplication();

template <typename T, typename... Args>
void Application::pushLayer(Args &&...args) {
  m_layerGroup.pushLayer<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
void Application::pushOverlay(Args &&...args) {
  m_layerGroup.pushOverlay<T>(std::forward<Args>(args)...);
}
}  // namespace Neat
