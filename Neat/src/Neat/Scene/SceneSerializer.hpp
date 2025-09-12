#pragma once

#include "Scene.hpp"
#include "ComponentSerializationRegistry.hpp"

namespace Neat {
class SceneSerializer {
 public:
  SceneSerializer(const Ref<Scene> &scene) : m_scene(scene) {}
  ~SceneSerializer() = default;

  void serialize(const std::string &filepath);
  // bool deserialize(const std::string &filepath);

  ComponentSerializationRegistry &getComponentRegistry() {
    return m_componentRegistry;
  }
  const ComponentSerializationRegistry &getComponentRegistry() const {
    return m_componentRegistry;
  }

 private:
  Ref<Scene> m_scene;
  ComponentSerializationRegistry m_componentRegistry;
};
}  // namespace Neat