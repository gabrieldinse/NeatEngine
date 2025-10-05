#pragma once

#include <memory>

#include <Neat.hpp>
#include "ImGui/ImGuiRender.hpp"

#include <ImGui/imgui.h>

class ExampleLayer : public Neat::Layer {
 public:
  ExampleLayer(const Neat::Ref<Neat::EventDispatcher> &eventManager);
  ~ExampleLayer() = default;

  void onImGuiRender();
  virtual void onUpdate(double deltaTimeSeconds) override;
  bool onWindowResize(const Neat::WindowResizeEvent &event);
  bool onMouseMoved(const Neat::MouseMovedEvent &event);

 private:
  Neat::Ref<Neat::SystemManager> m_systemManager;
  Neat::Ref<Neat::EntityManager> m_entityManager;
  Neat::Ref<Neat::EventDispatcher> m_eventDispatcher;

  Neat::Ref<Neat::Texture2D> m_checkerboardTexture;
  Neat::Ref<Neat::Texture2D> m_spritesheetTexture;
  Neat::Ref<Neat::SubTexture2D> m_stairsTexture;
  Neat::Ref<Neat::SubTexture2D> stairsTexture2;

  Neat::Vector4F tint = {0.8f, 0.3f, 0.2f, 1.0f};

  int numberOfColumns = 20;
  int numberOfLines = 20;
};