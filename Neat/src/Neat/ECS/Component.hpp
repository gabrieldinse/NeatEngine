#pragma once

#include <bitset>

#include "Neat/ECS/BaseComponent.hpp"

namespace Neat {
constexpr std::size_t maxComponents = 64;
using ComponentMask = std::bitset<maxComponents>;

template <typename Derived>
struct Component : public BaseComponent {
 private:
  friend class EntityManager;

  static Family getFamily() {
    static Family family = s_familyCounter++;
    if (family >= maxComponents) throw MaximumNumberOfComponentsError();

    return family;
  }
};
}  // namespace Neat