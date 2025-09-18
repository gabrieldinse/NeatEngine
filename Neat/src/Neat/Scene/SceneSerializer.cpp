#include "NeatPCH.hpp"

#include "SceneSerializer.hpp"

#include "Neat/Components/Components.hpp"

#include <rfl/yaml.hpp>
#include <rfl.hpp>

namespace Neat {
void SceneSerializer::serialize(const std::string &filepath) {
  NT_PROFILE_FUNCTION();

  NT_CORE_TRACE("Serializing scene to {}", filepath);
  auto entitiesArray = rfl::Generic::Array();
  for (Entity entity : m_scene->getEntityManager()->entities()) {
    auto entityObject = rfl::Generic::Object();
    entityObject["ID"] = entity.id().index();
    for (const auto &[name, componentProperties] : m_componentRegistry) {
      if (auto data = componentProperties.serialize(entity)) {
        auto componentObj = rfl::Generic::Object();
        entityObject[name] = *data;
      }
    }

    entitiesArray.push_back(entityObject);
  }

  auto sceneObject = rfl::Generic::Object();
  sceneObject["Name"] = "Scene";
  sceneObject["Entities"] = entitiesArray;

  NT_TRACE("Serialized Scene: \n{}", rfl::yaml::write(sceneObject));
  rfl::yaml::save(filepath, sceneObject);
}

bool SceneSerializer::deserialize(const std::string &filepath) {
  NT_PROFILE_FUNCTION();

  NT_CORE_TRACE("Deserializing scene from {}", filepath);
  auto sceneGeneric = rfl::yaml::load<rfl::Generic>(filepath);

  if (not sceneGeneric) {
    NT_ERROR("Error reading scene.");
    return false;
  }

  auto sceneObjOpt = sceneGeneric.value().to_object();
  if (not sceneObjOpt) {
    NT_ERROR("Error reading scene data.");
    return false;
  }

  auto sceneObject = sceneObjOpt.value();
  NT_TRACE("Deserialized Scene: \n{}", rfl::yaml::write(sceneObject));

  if (sceneObject.count("Entities") == 0) {
    NT_ERROR("No entities found in the scene.");
    return false;
  }

  auto entitiesArrayOpt = sceneObject["Entities"].to_array();
  if (not entitiesArrayOpt) {
    NT_ERROR("Error rading entities data.");
    return false;
  }

  auto entitiesArray = entitiesArrayOpt.value();
  for (const auto &entityArrayElem : entitiesArray) {
    auto entityObjOpt = entityArrayElem.to_object();
    if (not entityObjOpt) {
      NT_ERROR("Failed to read entity data.");
      return false;
    }

    auto entityObj = entityObjOpt.value();
    NT_TRACE("Reading entity {}.", entityObj["ID"].to_int().value_or(-1));
    auto entity = m_scene->getEntityManager()->createEntity();

    for (const auto &[name, componentProperties] : m_componentRegistry) {
      componentProperties.deserialize(entity, name, entityObj);
    }
  }

  return true;
}
}  // namespace Neat