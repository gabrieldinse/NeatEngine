#pragma once

#include <Neat.h>

#include <ImGui/imgui.h>


class Sandbox2D : public Neat::Layer
{
public:
   Sandbox2D();

   void onAttach() override;
   void onDetach() override;
   void onUpdate(Neat::Timestep dt) override;
   void onRender() override;
   virtual void onImGuiRender() override;

private:
   Neat::OrthographicCameraController cameraController;

   std::shared_ptr<Neat::Texture2D> checkerboardTexture;
   std::shared_ptr<Neat::Texture2D> spritesheetTexture;
   std::shared_ptr<Neat::SubTexture2D> stairsTexture;
   std::shared_ptr<Neat::SubTexture2D> stairsTexture2;

   Neat::Vec4 tint = {0.8f, 0.3f, 0.2f, 1.0f};

   int numberOfColumns = 20;
   int numberOfLines = 20;
};