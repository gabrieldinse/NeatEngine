#include <memory>

#include "ExampleLayer.hpp"

ExampleLayer::ExampleLayer(
    const std::shared_ptr<Neat::EventManager> &eventManager)
    : checkerboardTexture(
          std::make_shared<Neat::Texture2D>("assets/textures/texture1.png")),
      spritesheetTexture(std::make_shared<Neat::Texture2D>(
          "assets/textures/spritesheet1.png")),
      stairsTexture(Neat::SubTexture2D::createFromIndex(*spritesheetTexture,
                                                        {7, 6}, {64, 64})),
      stairsTexture2(Neat::SubTexture2D::createFromIndex(*spritesheetTexture,
                                                         {8, 6}, {64, 64})) {
  entities = std::make_shared<Neat::EntityManager>(eventManager);
  systems = std::make_shared<Neat::SystemManager>(entities, eventManager);
  eventManager->addListener<Neat::WindowResizeEvent>(*this);
  // auto q = Neat::Quaternion::fromAngleAxis(Neat::radians(45.0f),
  // Neat::Vector3F(1, 0, 0)); auto q2 = glm::angleAxis(glm::radians(45.0f),
  // glm::vec3(1.0f, 0.0f, 0.0f)); NT_TRACE(q); NT_TRACE(Neat::log(q));
  // NT_TRACE(Neat::pow(q, 0.5f));
  // NT_TRACE("");
  // NT_TRACE(glm::to_string(q2));
  // NT_TRACE(glm::to_string(glm::log(q2)));
  // NT_TRACE(glm::to_string(glm::pow(q2, 0.5f)));
  // NT_ASSERT(false, "");

  auto camera_controller_system =
      systems->addSystem<Neat::Camera3DControllerSystem>(1280.0f / 720.0f);
  systems->addSystem<Neat::Render2DSystem>(
      camera_controller_system->getCamera());
  systems->init();

  for (std::size_t i = 0; i < this->numberOfLines; ++i) {
    for (std::size_t j = 0; j < this->numberOfColumns; ++j) {
      auto entity = entities->createEntity();
      entity.addComponent<Neat::Renderable>(std::make_unique<Neat::Quad>(
          Neat::Vector3F{0.1f * j, 0.1f * i, 0.0f}, Neat::Vector2F{0.1f, 0.1f},
          Neat::Vector4F{float(i) / this->numberOfLines,
                         float(j) / this->numberOfColumns, 1.0f, 1.0f}));
    }
  }
}

void ExampleLayer::onImGuiRender() {
  auto stats = Neat::Renderer2D::getStats();
  ImGui::Text("Renderer2D stats:");
  ImGui::Text("Draw calls: %d", stats.drawCalls);
  ImGui::Text("Quads: %d", stats.quadCount);
  ImGui::Text("Indexes: %d", stats.getTotalIndexCount());
  ImGui::Text("Vertexes: %d\n", stats.getTotalVertexCount());

  // ImGui::SliderInt("Number of columns", &this->numberOfColumns, 0, 500);
  // ImGui::SliderInt("Number of lines", &this->numberOfLines, 0, 500);

  // ImGui::ColorEdit4("Square Color", this->tint.dataPointer());
}

void ExampleLayer::onUpdate(Neat::DeltaTime deltaTime) {
  systems->onUpdate<Neat::Camera3DControllerSystem>(deltaTime);
  systems->onUpdate<Neat::Render2DSystem>(deltaTime);
  onImGuiRender();
}

bool ExampleLayer::handleEvent(const Neat::WindowResizeEvent &event) {
  NT_CORE_INFO("Example handle window resize event.");
  return false;
}