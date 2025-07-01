#pragma once

#include <Neat.hpp>

#include <ImGui/imgui.h>

class Sandbox2D : public Neat::Layer {
 public:
  Sandbox2D();

  void attach() override;
  void detach() override;
  void onUpdate(double deltaTimeSeconds) override;
  void onRender() override;

 private:
  std::shared_ptr<Neat::Texture2D> checkerboardTexture;
  std::shared_ptr<Neat::Texture2D> spritesheetTexture;
  std::shared_ptr<Neat::SubTexture2D> stairsTexture;
  std::shared_ptr<Neat::SubTexture2D> stairsTexture2;

  Neat::Vector4F tint = {0.8f, 0.3f, 0.2f, 1.0f};

  int numberOfColumns = 20;
  int numberOfLines = 20;
};