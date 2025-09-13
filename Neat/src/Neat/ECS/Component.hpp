#pragma once

#include "BaseComponent.hpp"

namespace Neat {
constexpr std::size_t maxComponents = 64;

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