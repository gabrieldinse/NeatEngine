#pragma once

#include <unordered_map>

#include "ComponentSerializationProperties.hpp"

#include <rfl/yaml.hpp>

namespace Neat {
class ComponentSerializationRegistry {
 public:
  using Registry =
      std::unordered_map<std::string, ComponentSerializationProperties>;
  using RegistryIt = Registry::iterator;
  using RegistryConstIt = Registry::const_iterator;

 public:
  ComponentSerializationRegistry();
  ~ComponentSerializationRegistry() = default;

  template <typename C>
  void registerComponent(const std::string &name) {
    NT_PROFILE_FUNCTION();

    ComponentSerializationProperties properties{
        [](const Entity &entity) -> std::optional<rfl::Generic> {
          if (not entity.hasComponent<C>()) {
            return std::nullopt;
          }

          const auto component = entity.getComponent<C>();
          return rfl::to_generic(*component);
        },
        [](Entity &entity, const std::string &componentName,
           const rfl::Generic &entityGeneric) {
          auto entityObjOpt = entityGeneric.to_object();
          if (not entityObjOpt) {
            NT_ERROR("Failed to deserialize entity.");
            return;
          }

          auto entityObj = entityObjOpt.value();
          if (entityObj.count(componentName) == 0) {
            return;
          }

          NT_TRACE("Reading {}.", componentName);
          auto componentObjOpt = entityObj[componentName].to_object();
          if (not componentObjOpt) {
            NT_ERROR("Failed to read component: {}.", componentName);
            return;
          }

          auto componentObj = componentObjOpt.value();
          auto reflComponent =
              rfl::yaml::read<C>(rfl::yaml::write(componentObj));
          if (reflComponent) {
            auto component = reflComponent.value();
            entity.addComponent<C>(std::move(component));
          }
        }};

    m_registry[name] = properties;
  }

  RegistryIt begin() { return m_registry.begin(); }
  RegistryIt end() { return m_registry.end(); }
  RegistryConstIt begin() const { return m_registry.begin(); }
  RegistryConstIt end() const { return m_registry.end(); }

 private:
  std::unordered_map<std::string, ComponentSerializationProperties> m_registry;
};
}  // namespace Neat