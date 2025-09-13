#pragma once

#include <unordered_map>

#include "ComponentSerializationProperties.hpp"

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
    ComponentSerializationProperties properties{
        [](const Entity &entity) -> std::optional<rfl::Generic> {
          if (not entity.hasComponent<C>()) {
            return std::nullopt;
          }

          const auto component = entity.getComponent<C>();
          return rfl::to_generic(*component);
        },
        []([[maybe_unused]] Entity &entity,
           [[maybe_unused]] const rfl::Generic &data) {}};

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