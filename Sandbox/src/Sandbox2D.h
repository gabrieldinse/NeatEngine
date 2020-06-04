#pragma once

#include <Neat.h>

#include <ImGui/imgui.h>


class Sandbox2D : public Neat::Layer
{
public:
   Sandbox2D();

   void attach() override;
   void detach() override;
   void update(Neat::DeltaTime deltaTime) override;
   void render() override;

private:
   std::shared_ptr<Neat::Texture2D> checkerboardTexture;
   std::shared_ptr<Neat::Texture2D> spritesheetTexture;
   std::shared_ptr<Neat::SubTexture2D> stairsTexture;
   std::shared_ptr<Neat::SubTexture2D> stairsTexture2;

   Neat::Vector4 tint = {0.8f, 0.3f, 0.2f, 1.0f};

   int numberOfColumns = 20;
   int numberOfLines = 20;
};