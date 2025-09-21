#include <memory>

#include <string_view>

#include "ExampleLayer.hpp"

#include <rfl/yaml.hpp>
#include <rfl.hpp>

#include <ImGuizmo/ImGuizmo.h>

struct Person {
  std::string first_name;
  std::string last_name;
  int age;
};

struct Person2 {
  int age = 25;
  std::string name = "John";
  double height = 5.9;
};

namespace rfl {
template <Neat::UInt32 N, typename T>
struct Reflector<Neat::Vector<N, T>> {
  struct ReflType {
    std::array<T, N> elements;
  };

  static Neat::Vector<N, T> to(const ReflType &rv) noexcept {
    return Neat::Vector<N, T>{rv.elements};
  }

  static ReflType from(const Neat::Vector<N, T> &v) { return {v.elements}; }
};

template <>
struct Reflector<Neat::TransformComponent> {
  struct ReflType {
    Neat::Vector3F position;
    Neat::Vector3F scaling;
    Neat::Vector3F rotation;
  };

  static Neat::TransformComponent to(const ReflType &reflTransform) noexcept {
    return Neat::TransformComponent{
        reflTransform.position, reflTransform.scaling, reflTransform.rotation};
  }

  static ReflType from(const Neat::TransformComponent &transform) {
    return {transform.position, transform.scaling, transform.rotation};
  }
};
}  // namespace rfl

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
  Person2 person{30, "Alice", 5.7};

  Neat::TransformComponent transform;
  const std::string yaml_string3 = rfl::yaml::write(transform);
  NT_INFO(yaml_string3);

  auto refl2 =
      rfl::Reflector<Neat::TransformComponent>::from(Neat::TransformComponent{
          Neat::Vector3F{1.0f, 2.0f, 3.0f}, Neat::Vector3F{1.0f, 1.0f, 1.0f},
          Neat::Vector3F{45.0f, 0.0f, 90.0f}});
  const auto view2 = rfl::to_view(refl2);
  NT_INFO(*view2.get<0>());
  if constexpr (std::is_aggregate_v<Person>) {
    Person personTest{"John", "Doe", 30};
    const auto view3 = rfl::to_view(personTest);
    NT_INFO(*view3.get<0>());
    NT_TRACE("ReflType is an aggregate");
  } else {
    NT_TRACE("ReflType is NOT an aggregate");
  }

  Person personTest2{"John", "Doe", 30};
  auto generic = rfl::to_generic(personTest2);

  //////////////////////// IMPORTANT! ////////////////////////////
  /*********** Writing Scene to YAML *************/
  auto sceneWrite = rfl::Generic::Object();
  // Add scene
  sceneWrite["Name"] = "Scene";

  // Add entity1
  auto entity1 = rfl::Generic::Object();
  entity1["ID"] = 1;

  // Add component to entity1
  entity1["TransformComponent"] = rfl::to_generic(refl2);
  sceneWrite["entities"] = rfl::Generic::Array({entity1});
  NT_INFO(rfl::yaml::write(sceneWrite));

  // Save Scene to file
  rfl::yaml::save("./scene.yaml", sceneWrite);
  /*********** Writing Scene to YAML *************/

  /*********** Reading Scene from YAML *************/
  // As we were loading from a file
  auto sceneReadGeneric = rfl::yaml::load<rfl::Generic>("./scene.yaml");
  // auto sceneReadGeneric =
  //     rfl::yaml::read<rfl::Generic>(rfl::yaml::write(sceneWrite));
  NT_INFO("Debug YAML after read:");
  NT_INFO(rfl::yaml::write(sceneReadGeneric.value()));
  NT_INFO("Reading Scene");
  if (!sceneReadGeneric) {
    NT_ERROR("Error reading scene");
    return;
  }

  NT_INFO("Reading Scene object");
  if (!sceneReadGeneric.value().to_object()) {
    NT_ERROR("Error reading scene");
    return;
  }

  auto sceneObject = sceneReadGeneric.value().to_object().value();

  NT_INFO("Checking entities");
  if (sceneObject.count("entities") == 0) {
    NT_ERROR("No entities found in the scene");
    return;
  }

  NT_INFO("Reading entities");
  if (!sceneObject["entities"].to_array()) {
    NT_ERROR("Entities is not an array");
    return;
  }

  NT_INFO("Entities is an array");
  NT_INFO("Scene name: {0}",
          sceneObject["Name"].to_string().value_or("Unnamed Scene"));
  auto entitiesArray = sceneObject["entities"].to_array().value();

  for (const auto &entity : entitiesArray) {
    NT_INFO("Reading entity");
    if (!entity.to_object()) {
      NT_ERROR("Entity is not an object");
      continue;
    }

    NT_ERROR("Entity is an object");

    auto entityObj = entity.to_object().value();

    NT_INFO("Checking TransformComponent");
    if (entityObj.count("TransformComponent") == 0) {
      NT_ERROR("No TransformComponent found in the entity");
      continue;
    }

    NT_INFO("Reading TransformComponent");
    if (!entityObj["TransformComponent"].to_object()) {
      NT_ERROR("TransformComponent is not an object");
      continue;
    }

    auto transformObj = entityObj["TransformComponent"].to_object().value();
    auto reflTransformRead = rfl::yaml::read<Neat::TransformComponent>(
        rfl::yaml::write(transformObj));
    if (reflTransformRead) {
      auto transformComponent = reflTransformRead.value();
      NT_TRACE("TransformComponent read successfully");
      NT_TRACE("Entity ID: {0}", entityObj["ID"].to_int().value_or(-1));
      NT_TRACE("Position: {}", transformComponent.position);
      NT_TRACE("Scaling: {}", transformComponent.scaling);
      NT_TRACE("Rotation: {}", transformComponent.rotation);
    }
  }
  /*********** Reading Scene from YAML *************/
  //////////////////////// IMPORTANT! ////////////////////////////

  /* ImGuizmo */
  Neat::Matrix4F matrix{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  Neat::Vector3F matrixTranslation{};
  Neat::Vector3F matrixRotation{};
  Neat::Vector3F matrixScale{};
  ImGuizmo::DecomposeMatrixToComponents(matrix.data(), matrixTranslation.data(),
                                        matrixRotation.data(),
                                        matrixScale.data());
  NT_TRACE("Matrix: {}", matrix);
  NT_TRACE("Matrix Decomposed: Translation {}, Rotation {}, Scale {}",
           matrixTranslation, matrixRotation, matrixScale);
  /* ---------------------*/

  m_entityManager = Neat::makeRef<Neat::EntityManager>(eventDispatcher);
  m_systemManager =
      Neat::makeRef<Neat::SystemManager>(m_entityManager, eventDispatcher);
  eventDispatcher->get<Neat::WindowResizeEvent>()
      .connect<&ExampleLayer::onWindowResize>(*this);
  eventDispatcher->get<Neat::MouseMovedEvent>()
      .connect<&ExampleLayer::onMouseMoved>(*this);

  auto cameraEntity = m_entityManager->createEntity();
  cameraEntity.addComponent<Neat::CameraComponent>(
      Neat::OrthographicProperties{1600, 900});
  cameraEntity.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, 0.0f, -1.0f}, Neat::Vector3F{1.0f, 1.0f, 1.0f},
      Neat::Vector3F{0.0f, 0.0f, 0.0f});
  cameraEntity.addComponent<Neat::ActiveCameraTagComponent>();

  m_systemManager->addSystem<Neat::OrthographicCameraControllerSystem>();
  m_systemManager->addSystem<Neat::Render2DSystem>();
  m_systemManager->initialize();

  // for (std::size_t i = 0; i < this->numberOfLines; ++i) {
  //   for (std::size_t j = 0; j < this->numberOfColumns; ++j) {
  //     auto flatColorQuad = m_entityManager->createEntity();
  //     flatColorQuad.addComponent<Neat::RenderableSpriteComponent>(
  //         Neat::Vector4F{float(i) / this->numberOfLines,
  //                        float(j) / this->numberOfColumns, 1.0f, 1.0f});
  //     flatColorQuad.addComponent<Neat::TransformComponent>(
  //         Neat::Vector3F{0.1f * j, 0.1f * i, 0.0f},
  //         Neat::Vector3F{0.1f, 0.1f, 1.0f});
  //   }
  // }

  // Set values different from the default
  // m_checkerboardTexture->setMinification(Neat::Texture2DFilter::Nearest);
  // m_checkerboardTexture->setMagnification(Neat::Texture2DFilter::Nearest);
  // m_checkerboardTexture->setWrapS(Neat::Texture2DWrapping::ClampToEdge);

  // auto checkerboardQuad = m_entityManager->createEntity();
  // checkerboardQuad.addComponent<Neat::RenderableSpriteComponent>(
  //     this->m_checkerboardTexture, Neat::Vector4F{0.8f, 0.4f, 0.3f, 0.75f},
  //     5.0f);
  // checkerboardQuad.addComponent<Neat::TransformComponent>(
  //     Neat::Vector3F{0.0f, 0.0f, 0.5f}, Neat::Vector3F{1.0f, 1.0f, 1.0f},
  //     Neat::Vector3F{0.0f, 0.0f, 45.0f});
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

  // ImGui::ShowDemoWindow();

  ImGuiIO &io = ImGui::GetIO();
  // float windowWidth = (float)ImGui::GetWindowWidth();
  // float windowHeight = (float)ImGui::GetWindowHeight();
  //  if (!useWindow)
  //{
  //     ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
  //  }
  //  else
  //   ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y,
  //                     windowWidth, windowHeight);

  // ImGuizmo::SetDrawlist(ImGui::GetWindowDrawList());

  ImGuizmo::SetOrthographic(true);
  ImGuizmo::Enable(true);
  ImGuizmo::SetDrawlist();
  ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
  Neat::Matrix4F cameraView = Neat::Matrix4F::identity();
  Neat::Matrix4F cameraProjection = Neat::Matrix4F::identity();
  Neat::Matrix4F model = Neat::Matrix4F::identity();

  ImGuizmo::Manipulate(cameraView.data(), cameraProjection.data(),
                       ImGuizmo::ROTATE, ImGuizmo::WORLD, model.data(), NULL,
                       NULL);

  ImGui::End();
}

void ExampleLayer::onUpdate(double deltaTimeSeconds) {
  m_systemManager->onUpdate<Neat::OrthographicCameraControllerSystem>(
      deltaTimeSeconds);
  m_systemManager->onUpdate<Neat::Render2DSystem>(deltaTimeSeconds);
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
  // NT_TRACE("Mouse moved to ({0}, {1})", event.xPos, event.yPos);
  return false;
}
