#pragma once

#include <optional>

#include "BaseComponent.hpp"

#include "Core/Constants.hpp"

namespace Neat {
template <typename Derived>
struct Component : public BaseComponent {
 private:
  friend class EntityManager;

  static std::optional<Family> getFamily() {
    static const Family family = s_familyCounter++;
    if (family >= MaxComponents) {
      return std::nullopt;
    }

    return family;
  }
};
}  // namespace Neat