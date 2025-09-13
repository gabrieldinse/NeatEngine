#include "NeatPCH.hpp"

#include "SceneSerializer.hpp"
#include "Neat/Components/Components.hpp"

#include <rfl/yaml.hpp>
#include <rfl.hpp>

namespace Neat {
void SceneSerializer::serialize(const std::string &filepath) {
  auto entitiesArray = rfl::Generic::Array();
  for (Entity entity : m_scene->getEntityManager()->entities()) {
    auto componentsArray = rfl::Generic::Array();
    for (const auto &[name, componentProperties] : m_componentRegistry) {
      if (auto data = componentProperties.serialize(entity)) {
        auto componentObj = rfl::Generic::Object();
        componentObj[name] = *data;
        componentsArray.push_back(componentObj);
      }
    }

    auto entityObject = rfl::Generic::Object();
    entityObject["ID"] = entity.id().index();
    entityObject["Components"] = componentsArray;
    entitiesArray.push_back(entityObject);
  }

  auto sceneObject = rfl::Generic::Object();
  sceneObject["Name"] = "Scene";
  sceneObject["Entities"] = entitiesArray;

  NT_TRACE("Serialized Scene: \n{}", rfl::yaml::write(sceneObject));
  rfl::yaml::save(filepath, sceneObject);
}

// bool SceneSerializer::deserialize(const std::string &filepath) {}
}  // namespace Neat