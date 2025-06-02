#include <memory>

#include "Neat/Core/Layer.hpp"
#include "Neat/ImGui/ImGuiRender.hpp"

#include <ImGui/imgui.h>

class ExampleLayer : public Neat::Layer {
 public:
  ExampleLayer() = default;
  ~ExampleLayer() = default;

  virtual void onImGuiRender() override;
};