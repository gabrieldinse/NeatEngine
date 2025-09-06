#include <memory>

#include "ExampleLayer.hpp"

#include <rfl/yaml.hpp>
#include <rfl.hpp>

struct Person {
  std::string first_name;
  std::string last_name;
  int age;
};

namespace rfl {
template <>
struct Reflector<Neat::Vector1F> {
  struct ReflType {
    float x;
  };

  static Neat::Vector1F to(const ReflType &v) noexcept {
    return Neat::Vector1F{v.x};
  }

  static ReflType from(const Neat::Vector1F &v) { return {v.x()}; }

  static Neat::Vector1F to_refl(const ReflType &v) noexcept {
    return Neat::Vector1F{v.x};
  }

  static ReflType from_refl(const Neat::Vector1F &v) { return {v.x()}; }
};
}  // namespace rfl

// namespace rfl {
// template <>
// struct Reflector<Neat::Vector3F> {
//   struct ReflType {
//     float x;
//     float y;
//     float z;
//   };
//
//   static Neat::Vector3F to(const ReflType &v) noexcept {
//     return {v.x, v.y, v.z};
//   }
//
//   static ReflType from(const Neat::Vector3F &v) { return {v.x, v.y, v.z}; }
//   static ReflType to_refl(const Neat::Vector3F &v) noexcept {
//     return {v.x, v.y, v.z};
//   }
//
//   static Neat::Vector3F from_refl(const ReflType &r) noexcept {
//     return {r.x, r.y, r.z};
//   }
// };
// }  // namespace rfl
//
// struct TransformDummy {
//   Neat::Vector2F position;
//   Neat::Vector2F rotation;
//   Neat::Vector2F scale;
// };

ExampleLayer::ExampleLayer(
    const Neat::Ref<Neat::EventDispatcher> &eventDispatcher)
    : m_checkerboardTexture(
          Neat::Texture2D::create("assets/textures/texture1.png")),
      m_spritesheetTexture(
          Neat::Texture2D::create("assets/textures/spritesheet1.png")),
      m_stairsTexture(Neat::SubTexture2D::createFromIndex(m_spritesheetTexture,
                                                          {7, 6}, {64, 64})),
      stairsTexture2(Neat::SubTexture2D::createFromIndex(m_spritesheetTexture,
                                                         {8, 6}, {64, 64})) {
  const auto homer =
      Person{.first_name = "Homer", .last_name = "Simpson", .age = 45};

  Neat::Vector1F v1{3.0f};
  std::cout << v1 << std::endl;

  // We can now write into and read from a JSON string.
  const std::string yaml_string = rfl::yaml::write(homer);
  std::cout << yaml_string << std::endl;
  auto homer2 = rfl::yaml::read<Person>(yaml_string).value();
  std::cout << homer2.age << homer2.first_name << homer2.last_name << std::endl;

  const std::string yaml_string2 = rfl::yaml::write(Neat::Vector1F{1.0f});

  std::cout << yaml_string2 << std::endl;

  // for (const auto &f : rfl::fields<Neat::Vector1F>()) {
  //   std::cout << "name: " << f.name() << ", type: " << f.type() << std::endl;
  // }

  m_entityManager = Neat::makeRef<Neat::EntityManager>(eventDispatcher);
  m_systems =
      Neat::makeRef<Neat::SystemManager>(m_entityManager, eventDispatcher);
  eventDispatcher->get<Neat::WindowResizeEvent>()
      .connect<&ExampleLayer::onWindowResize>(*this);
  eventDispatcher->get<Neat::MouseMovedEvent>()
      .connect<&ExampleLayer::onMouseMoved>(*this);

  auto cameraEntity = m_entityManager->createEntity();
  cameraEntity.addComponent<Neat::CameraComponent>(
      Neat::OrthographicProperties{1600, 900});
  cameraEntity.addComponent<Neat::TransformComponent>(
      Neat::Vector2F{0.0f, 0.0f});
  cameraEntity.addComponent<Neat::ActiveCameraTagComponent>();

  m_systems->addSystem<Neat::OrthographicCameraControllerSystem>();
  m_systems->addSystem<Neat::Render2DSystem>();
  m_systems->initialize();

  for (std::size_t i = 0; i < this->numberOfLines; ++i) {
    for (std::size_t j = 0; j < this->numberOfColumns; ++j) {
      auto flatColorQuad = m_entityManager->createEntity();
      flatColorQuad.addComponent<Neat::RenderableSpriteComponent>(
          Neat::Vector4F{float(i) / this->numberOfLines,
                         float(j) / this->numberOfColumns, 1.0f, 1.0f});
      flatColorQuad.addComponent<Neat::TransformComponent>(
          Neat::Vector3F{0.1f * j, 0.1f * i, 0.0f},
          Neat::Vector3F{0.1f, 0.1f, 1.0f});
    }
  }

  // Set values different from the default
  m_checkerboardTexture->setMinification(Neat::Texture2DFilter::Nearest);
  m_checkerboardTexture->setMagnification(Neat::Texture2DFilter::Nearest);
  m_checkerboardTexture->setWrapS(Neat::Texture2DWrapping::ClampToEdge);

  auto checkerboardQuad = m_entityManager->createEntity();
  checkerboardQuad.addComponent<Neat::RenderableSpriteComponent>(
      this->m_checkerboardTexture, Neat::Vector4F{0.8f, 0.4f, 0.3f, 0.75f},
      5.0f);
  checkerboardQuad.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, 0.0f, 0.5f}, Neat::Vector3F{1.0f, 1.0f, 1.0f},
      Neat::Vector3F{0.0f, 0.0f, 45.0f});

  Neat::Vector4B test{false, true, false, true};
  for (int i = 0; i < test.size(); ++i) {
    NT_TRACE("val: {}", test[i]);
  }
}

void ExampleLayer::onImGuiRender() {
  auto stats = Neat::Renderer2D::getStats();
  ImGui::Begin("Example Layer");
  ImGui::Text("Renderer2D stats:");
  ImGui::Text("Draw calls: %d", stats.drawCalls);
  ImGui::Text("Quads: %d", stats.quadCount);
  ImGui::Text("Indexes: %d", stats.getTotalIndexCount());
  ImGui::Text("Vertexes: %d\n", stats.getTotalVertexCount());
  // ImGui::SliderInt("Number of columns", &this->numberOfColumns, 0, 500);
  // ImGui::SliderInt("Number of lines", &this->numberOfLines, 0, 500);
  // ImGui::ColorEdit4("Square Color", this->tint.raw());
  ImGui::End();
}

void ExampleLayer::onUpdate(double deltaTimeSeconds) {
  m_systems->onUpdate<Neat::OrthographicCameraControllerSystem>(
      deltaTimeSeconds);
  m_systems->onUpdate<Neat::Render2DSystem>(deltaTimeSeconds);
  onImGuiRender();
}

bool ExampleLayer::onWindowResize(const Neat::WindowResizeEvent &event) {
  NT_CORE_INFO("Example handle window resize event.");
  for (auto cameraEntity :
       m_entityManager->entitiesWithComponents<Neat::ActiveCameraTagComponent,
                                               Neat::CameraComponent>()) {
    cameraEntity.getComponent<Neat::CameraComponent>()
        ->setOrthographicAspectRatio(event.width, event.height);
    return false;
  }

  return false;
}

bool ExampleLayer::onMouseMoved(
    [[maybe_unused]] const Neat::MouseMovedEvent &event) {
  // NT_CORE_TRACE("Mouse moved to ({0}, {1})", event.xPos, event.yPos);
  return false;
}
