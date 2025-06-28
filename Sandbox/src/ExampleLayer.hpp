#include <memory>

#include <Neat.hpp>
#include "Neat/ImGui/ImGuiRender.hpp"

#include <ImGui/imgui.h>

class ExampleLayer : public Neat::Layer {
 public:
  ExampleLayer(const std::shared_ptr<Neat::EventDispatcher> &eventManager);
  ~ExampleLayer() = default;

  void onImGuiRender();
  virtual void onUpdate(Neat::DeltaTime deltaTime) override;
  bool onWindowResize(const Neat::WindowResizeEvent &event);
  bool onMouseMoved(const Neat::MouseMovedEvent &event);

 private:
  std::shared_ptr<Neat::SystemManager> systems;
  std::shared_ptr<Neat::EntityManager> entities;

  std::shared_ptr<Neat::Texture2D> checkerboardTexture;
  std::shared_ptr<Neat::Texture2D> spritesheetTexture;
  std::shared_ptr<Neat::SubTexture2D> stairsTexture;
  std::shared_ptr<Neat::SubTexture2D> stairsTexture2;

  Neat::Vector4F tint = {0.8f, 0.3f, 0.2f, 1.0f};

  int numberOfColumns = 20;
  int numberOfLines = 20;
};