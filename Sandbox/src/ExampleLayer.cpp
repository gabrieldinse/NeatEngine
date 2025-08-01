#include <memory>

#include "ExampleLayer.hpp"

ExampleLayer::ExampleLayer(
    const Neat::Ref<Neat::EventDispatcher> &eventDispatcher)
    : checkerboardTexture(
          Neat::Texture2D::create("assets/textures/texture1.png")),
      spritesheetTexture(
          Neat::Texture2D::create("assets/textures/spritesheet1.png")),
      stairsTexture(Neat::SubTexture2D::createFromIndex(spritesheetTexture,
                                                        {7, 6}, {64, 64})),
      stairsTexture2(Neat::SubTexture2D::createFromIndex(spritesheetTexture,
                                                         {8, 6}, {64, 64})) {
  entities = Neat::makeRef<Neat::EntityManager>(eventDispatcher);
  systems = Neat::makeRef<Neat::SystemManager>(entities, eventDispatcher);
  eventDispatcher->get<Neat::WindowResizeEvent>()
      .connect<&ExampleLayer::onWindowResize>(*this);
  eventDispatcher->get<Neat::MouseMovedEvent>()
      .connect<&ExampleLayer::onMouseMoved>(*this);
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
      systems->addSystem<Neat::OrthographicCameraControllerSystem>(1280.0f /
                                                                   720.0f);
  systems->addSystem<Neat::Render2DSystem>(
      camera_controller_system->getCamera());
  systems->init();

  for (std::size_t i = 0; i < this->numberOfLines; ++i) {
    for (std::size_t j = 0; j < this->numberOfColumns; ++j) {
      auto flatColorQuad = entities->createEntity();
      flatColorQuad.addComponent<Neat::RenderableSpriteComponent>(
          Neat::Vector4F{float(i) / this->numberOfLines,
                         float(j) / this->numberOfColumns, 1.0f, 1.0f});
      flatColorQuad.addComponent<Neat::TransformComponent>(

          Neat::Vector3F{0.1f * j, 0.1f * i, 0.0f},
          Neat::Vector3F{0.0f, 0.0f, 0.0f}, Neat::Vector3F{0.1f, 0.1f, 1.0f});
    }
  }

  auto checkerboardQuad = entities->createEntity();
  checkerboardQuad.addComponent<Neat::RenderableSpriteComponent>(
      this->checkerboardTexture, Neat::Vector4F{0.8f, 0.4f, 0.3f, 0.75f}, 5.0f);
  checkerboardQuad.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, 0.0f, 0.5f}, Neat::Vector3F{0.0f, 0.0f, 45.0f},
      Neat::Vector3F{1.0f, 1.0f, 1.0f});
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

void ExampleLayer::onUpdate(double deltaTimeSeconds) {
  systems->onUpdate<Neat::OrthographicCameraControllerSystem>(deltaTimeSeconds);
  systems->onUpdate<Neat::Render2DSystem>(deltaTimeSeconds);
  onImGuiRender();
}

bool ExampleLayer::onWindowResize(const Neat::WindowResizeEvent &event) {
  NT_CORE_INFO("Example handle window resize event.");
  return false;
}

bool ExampleLayer::onMouseMoved(
    [[maybe_unused]] const Neat::MouseMovedEvent &event) {
  // NT_CORE_TRACE("Mouse moved to ({0}, {1})", event.xPos, event.yPos);
  return false;
}