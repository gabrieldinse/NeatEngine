#include "Sandbox2D.h"


Sandbox2D::Sandbox2D()
   : Layer("Example Layer")
   , cameraController(
      (float)Neat::Application::get().getWindow().getWidth() /
      (float)Neat::Application::get().getWindow().getHeight())
{
}

void Sandbox2D::onAttach()
{
   this->checkerboardTexture = std::make_shared<Neat::Texture2D>(
      "assets/textures/texture1.png");
   this->spritesheetTexture = std::make_shared<Neat::Texture2D>(
      "assets/textures/spritesheet1.png");
   this->stairsTexture = Neat::SubTexture2D::createFromIndex(
      *this->spritesheetTexture, { 7, 6 }, { 64, 64 });
   this->stairsTexture2 = Neat::SubTexture2D::createFromIndex(
      *this->spritesheetTexture, { 8, 6 }, { 64, 64 });
}

void Sandbox2D::onDetach()
{
}

void Sandbox2D::onUpdate(Neat::Timestep dt)
{
   NT_PROFILE_FUNCTION();
   this->cameraController.onUpdate(dt);
}

void Sandbox2D::onRender()
{
   NT_PROFILE_FUNCTION();

   Neat::Renderer2D::resetStats();

   {
      NT_PROFILE_SCOPE("Renderer setup");

      Neat::RenderCommand::setClearColor({0.35f, 0.35f, 0.55f, 1.0f});
      Neat::RenderCommand::clear();
   }

   {
      NT_PROFILE_SCOPE("Renderer");

      Neat::Renderer2D::beginScene(this->cameraController.getCamera());

      Neat::Renderer2D::drawQuad(
         {1.0f, 0.0f}, {0.5f, 0.5f}, {0.7f, 0.5f, 0.3f, 1.0f});
      Neat::Renderer2D::drawQuad(
         {-1.2f, 0.0f}, {0.5f, 0.5f}, {0.35f, 0.3f, 0.9f, 1.0f});
      Neat::Renderer2D::drawRotatedQuad(
         { 0.0f, 0.75f }, { 0.5f, 0.5f }, 45.0f, { 0.65f, 0.78f, 0.2f, 1.0f });
      Neat::Renderer2D::drawQuad(
         {0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, this->checkerboardTexture, this->tint, 5.0f);

      for (std::size_t i = 0; i < this->numberOfLines; ++i)
         for (std::size_t j = 0; j < this->numberOfColumns; ++j)
            Neat::Renderer2D::drawQuad(
               { 0.1f * j, 0.1f * i},
               { 0.1f, 0.1f },
               { float(i) / this->numberOfLines, float(j) / this->numberOfColumns, 1.0f, 1.0f });

      Neat::Renderer2D::drawQuad(
         { 0.0f, -0.7f, 0.5f }, { 1.0f, 1.0f }, this->stairsTexture);
      Neat::Renderer2D::drawQuad(
         { 1.0f, -0.7f, 0.5f }, { 1.0f, 1.0f }, this->stairsTexture2);

      Neat::Renderer2D::endScene();
   }
}

void Sandbox2D::onImGuiRender()
{
   NT_PROFILE_FUNCTION();

   ImGui::Begin("Settings");

   auto stats = Neat::Renderer2D::getStats();
   ImGui::Text("Renderer2D stats:");
   ImGui::Text("Draw calls: %d", stats.drawCalls);
   ImGui::Text("Quads: %d", stats.quadCount);
   ImGui::Text("Indexes: %d", stats.getTotalIndexCount());
   ImGui::Text("Vertexes: %d\n", stats.getTotalVertexCount());

   ImGui::SliderInt("Number of columns", &this->numberOfColumns, 0, 500);
   ImGui::SliderInt("Number of lines", &this->numberOfLines, 0, 500);

   ImGui::ColorEdit4("Square Color", this->tint.dataPointer());

   ImGui::End();
}