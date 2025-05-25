#include <memory>

#include <Neat.hpp>
#include <Neat/Core/Main.hpp>

#include <ImGui/imgui.h>

//#include "Sandbox2D.hpp"



class Sandbox : public Neat::Application
{
public:
   Sandbox()
      : entities(events())
      , systems(entities, events())
      , checkerboardTexture(std::make_shared<Neat::Texture2D>(
         "assets/textures/texture1.png"))
      , spritesheetTexture(std::make_shared<Neat::Texture2D>(
         "assets/textures/spritesheet1.png"))
      , stairsTexture(Neat::SubTexture2D::createFromIndex(
         *spritesheetTexture, { 7, 6 }, { 64, 64 }))
      , stairsTexture2(Neat::SubTexture2D::createFromIndex(
         *spritesheetTexture, { 8, 6 }, { 64, 64 }))
   {
      //auto q = Neat::Quaternion::fromAngleAxis(Neat::radians(45.0f), Neat::Vector3F(1, 0, 0));
      //auto q2 = glm::angleAxis(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
      //NT_TRACE(q);
      //NT_TRACE(Neat::log(q));
      //NT_TRACE(Neat::pow(q, 0.5f));
      //NT_TRACE("");
      //NT_TRACE(glm::to_string(q2));
      //NT_TRACE(glm::to_string(glm::log(q2)));
      //NT_TRACE(glm::to_string(glm::pow(q2, 0.5f)));
      //NT_ASSERT(false, "");

      auto camera_controller_system =
         systems.addSystem<Neat::Camera3DControllerSystem>(
            getWindow().getAspectRatio());
      systems.addSystem<Neat::Render2DSystem>(
         camera_controller_system->getCamera());
      systems.init();

      for (std::size_t i = 0; i < this->numberOfLines; ++i)
      {
         for (std::size_t j = 0; j < this->numberOfColumns; ++j)
         {
            auto entity = entities.createEntity();
            entity.addComponent<Neat::Renderable>(
               std::make_unique<Neat::Quad>(
                  Neat::Vector3F{ 0.1f * j, 0.1f * i, 0.0f },
                  Neat::Vector2F{ 0.1f, 0.1f },
                  Neat::Vector4F{
                     float(i) / this->numberOfLines,
                     float(j) / this->numberOfColumns,
                     1.0f, 1.0f }
                     )
               );
         }
      }
   } 

   ~Sandbox()
   {
   }

   virtual void update(Neat::DeltaTime deltaTime) override
   {
      systems.update<Neat::Camera3DControllerSystem>(deltaTime);
      systems.update<Neat::Render2DSystem>(deltaTime);
   }

   virtual void imGuiRender() override
   {
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

private:
   Neat::SystemManager systems;
   Neat::EntityManager entities;

   std::shared_ptr<Neat::Texture2D> checkerboardTexture;
   std::shared_ptr<Neat::Texture2D> spritesheetTexture;
   std::shared_ptr<Neat::SubTexture2D> stairsTexture;
   std::shared_ptr<Neat::SubTexture2D> stairsTexture2;

   Neat::Vector4F tint = { 0.8f, 0.3f, 0.2f, 1.0f };

   int numberOfColumns = 20;
   int numberOfLines = 20;
};


std::unique_ptr<Neat::Application> Neat::createApplication()
{
   return std::make_unique<Sandbox>();
}