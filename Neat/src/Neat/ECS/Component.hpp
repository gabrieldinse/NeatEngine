#pragma once

#include "BaseComponent.hpp"

#include "Neat/Core/Constants.hpp"

namespace Neat {
template <typename Derived>
struct Component : public BaseComponent {
 private:
  friend class EntityManager;

  static Family getFamily() {
    static Family family = s_familyCounter++;
    if (family >= MaxComponents) throw MaximumNumberOfComponentsError();

    return family;
  }
};
}  // namespace Neat