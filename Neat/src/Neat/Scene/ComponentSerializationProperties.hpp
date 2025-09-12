#pragma once

#include <functional>
#include <optional>

#include "Neat/ECS/EntityManager.hpp"

#include <rfl.hpp>

namespace Neat {
struct ComponentSerializationProperties {
  using SerializeFunction =
      std::function<std::optional<rfl::Generic>(const Entity &)>;
  using DeserializeFunction =
      std::function<void(Entity &, const rfl::Generic &)>;

  SerializeFunction serialize;
  DeserializeFunction deserialize;
};
}  // namespace Neat