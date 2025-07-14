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
  Neat::Ref<Neat::Texture2D> checkerboardTexture;
  Neat::Ref<Neat::Texture2D> spritesheetTexture;
  Neat::Ref<Neat::SubTexture2D> stairsTexture;
  Neat::Ref<Neat::SubTexture2D> stairsTexture2;

  Neat::Vector4F tint = {0.8f, 0.3f, 0.2f, 1.0f};

  int numberOfColumns = 20;
  int numberOfLines = 20;
};