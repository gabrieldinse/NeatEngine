#include <memory>

#include <string_view>

#include "ExampleLayer.hpp"

#include <rfl/yaml.hpp>
#include <rfl.hpp>

#include <glaze/glaze.hpp>

// struct Person {
//   std::string first_name;
//   std::string last_name;
//   int age;
// };

struct Person {
  int age = 25;
  std::string name = "John";
  double height = 5.9;
};

namespace rfl {
// template <typename T>
// struct Reflector<Neat::Vector<1, T>> {
//   struct ReflType {
//     T x;
//   };
//
//   static Neat::Vector<1, T> to(const ReflType &v) noexcept {
//     return Neat::Vector<1, T>{v.x};
//   }
//
//   static ReflType from(const Neat::Vector<1, T> &v) { return {v.x()}; }
//
//   static Neat::Vector<1, T> to_refl(const ReflType &v) noexcept {
//     return Neat::Vector<1, T>{v.x};
//   }
//
//   static ReflType from_refl(const Neat::Vector<1, T> &v) { return {v.x()}; }
// };
//
// template <typename T>
// struct Reflector<Neat::Vector<2, T>> {
//   struct ReflType {
//     T x;
//     T y;
//   };
//
//   static Neat::Vector<2, T> to(const ReflType &v) noexcept {
//     return Neat::Vector<2, T>{v.x, v.y};
//   }
//
//   static ReflType from(const Neat::Vector<2, T> &v) { return {v.x(), v.y()};
//   }
//
//   static Neat::Vector<2, T> to_refl(const ReflType &v) noexcept {
//     return Neat::Vector<2, T>{v.x, v.y};
//   }
//
//   static ReflType from_refl(const Neat::Vector<2, T> &v) {
//     return {v.x(), v.y()};
//   }
// };
//
// template <typename T>
// struct Reflector<Neat::Vector<3, T>> {
//   struct ReflType {
//     T x;
//     T y;
//     T z;
//   };
//
//   static Neat::Vector<3, T> to(const ReflType &v) noexcept {
//     return Neat::Vector<3, T>{v.x, v.y, v.z};
//   }
//
//   static ReflType from(const Neat::Vector<3, T> &v) {
//     return {v.x(), v.y(), v.z()};
//   }
//
//   static Neat::Vector<3, T> to_refl(const ReflType &v) noexcept {
//     return Neat::Vector<3, T>{v.x, v.y, v.z};
//   }
//
//   static ReflType from_refl(const Neat::Vector<3, T> &v) {
//     return {v.x(), v.y(), v.z()};
//   }
// };
//

template <typename T>
struct Reflector<Neat::Vector<4, T>> {
  struct ReflType {
    T x;
    T y;
    T z;
    T w;
  };

  static Neat::Vector<4, T> to(const ReflType &refl) noexcept {
    return Neat::Vector<4, T>{refl.x, refl.y, refl.z, refl.w};
  }

  static ReflType from(const Neat::Vector<4, T> &v) {
    return {v.x(), v.y(), v.z(), v.w()};
  }

  static Neat::Vector<4, T> to_refl(const ReflType &refl) noexcept {
    return Neat::Vector<4, T>{refl.x, refl.y, refl.z, refl.w};
  }

  static ReflType from_refl(const Neat::Vector<4, T> &v) {
    return {v.x(), v.y(), v.z(), v.w()};
  }
};

// template <Neat::UInt32 N, typename T>
// struct Reflector<Neat::Vector<N, T>> {
//   struct ReflType {
//     std::array<T, N> elements;
//   };
//
//   static Neat::Vector<N, T> to(const ReflType &rv) noexcept {
//     return Neat::Vector<N, T>{rv.elements};
//   }
//
//   static ReflType from(const Neat::Vector<N, T> &v) { return {v.elements}; }
//
//   static Neat::Vector<N, T> to_refl(const ReflType &rv) noexcept {
//     return Neat::Vector<N, T>{rv.elements};
//   }
//
//   static ReflType from_refl(const Neat::Vector<N, T> &v) {
//     return {v.elements};
//   }
// };

// template <>
// struct Reflector<Neat::Vector<4, float>> {
//   struct ReflType {
//     float x;
//     float y;
//     float z;
//     float w;
//   };
//
//   static Neat::Vector<4, float> to(const ReflType &v) noexcept {
//     return Neat::Vector<4, float>{v.x, v.y, v.z, v.w};
//   }
//
//   static ReflType from(const Neat::Vector<4, float> &v) {
//     return {v.x(), v.y(), v.z(), v.w()};
//   }
//
//   static Neat::Vector<4, float> to_refl(const ReflType &v) noexcept {
//     return Neat::Vector<4, float>{v.x, v.y, v.z, v.w};
//   }
//
//   static ReflType from_refl(const Neat::Vector<4, float> &v) {
//     return {v.x(), v.y(), v.z(), v.w()};
//   }
// };
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

template <Neat::UInt32 N, typename T>
struct glz::meta<Neat::Vector<N, T>> {
  using Type = Neat::Vector<N, T>;
  static constexpr auto value = glz::object(&Type::elements);
  // static_assert(glz::reflect<Type>::size == 1);  // Number of fields
};

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
  Person person{30, "Alice", 5.7};

  /* GLAZE */
  // Write to JSON
  NT_TRACE("GLAZE TEST");
  std::string json = glz::write_json(person).value_or("error");
  std::cout << json << std::endl;
  // Result: {"age":30,"name":"Alice","height":5.7}

  // Read from JSON
  std::string input = R"({"age":25,"name":"Bob","height":6.1})";
  Person new_person{};
  auto error = glz::read_json(new_person, input);
  if (error) {
    std::string error_msg = glz::format_error(error, input);
    std::cout << error_msg << std::endl;
  } else {
    // Success! new_person is now populated
    std::cout << new_person.name << " is " << new_person.age << " years old\n";
  }

  Neat::Vector4F vec4{1.0f, 2.0f, 3.0f, 4.0f};
  std::string jsonVector4f = glz::write_json(vec4).value_or("error");
  std::cout << jsonVector4f << std::endl;

  Neat::Vector3F vec3{1.0f, 2.0f, 3.0f};
  std::string jsonVector3f = glz::write_json(vec3).value_or("error");
  std::cout << jsonVector3f << std::endl;
  Neat::Vector2F vec2{1.0f, 2.0f};
  std::string jsonVector2f = glz::write_json(vec2).value_or("error");
  std::cout << jsonVector2f << std::endl;
  Neat::Vector1F vec1{1.0f};
  std::string jsonVector1f = glz::write_json(vec1).value_or("error");
  std::cout << jsonVector1f << std::endl;

  constexpr auto meta = glz::reflect<Neat::Vector4F>();
  int i = 0;
  glz::for_each_field(Neat::Vector4F{5.0f, 6.0f, 7.0f, 8.0f}, [&](auto &field) {
    std::string_view field_name = meta.keys[i];
    std::cout << field_name << " = ";
    for (auto elem : field) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
    i++;
  });

  /* REFLECT-CPP */
  // NT_TRACE("REFLECT-CPP TEST");
  // const auto homer =
  //     Person{.first_name = "Homer", .last_name = "Simpson", .age = 45};

  // Neat::Vector1F v1{3.0f};
  // std::cout << v1 << std::endl;

  ////// We can now write into and read from a JSON string.
  // const std::string yaml_string = rfl::yaml::write(homer);
  // std::cout << yaml_string << std::endl;
  // auto homer2 = rfl::yaml::read<Person>(yaml_string).value();
  // std::cout << homer2.age << homer2.first_name << homer2.last_name <<
  // std::endl;

  //// Vector1F
  // const std::string yaml_string2 = rfl::yaml::write(Neat::Vector1F{1.0f});

  // std::cout << yaml_string2 << std::endl;

  // for (const auto &f : rfl::fields<Neat::Vector1F>()) {
  //   std::cout << "name: " << f.name() << ", type: " << f.type() << std::endl;
  // }

  // Neat::Vector4F vec4{1.0f, 2.0f, 3.0f, 4.0f};
  // const std::string yaml_string3 = rfl::yaml::write(vec4);

  // std::cout << yaml_string3 << std::endl;
  // const auto view = rfl::to_view(vec4);
  // std::cout << *view.get<0>() << std::endl;

  // for (const auto &f : rfl::fields<Neat::Vector2F>()) {
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
  // NT_TRACE("Mouse moved to ({0}, {1})", event.xPos, event.yPos);
  return false;
}
