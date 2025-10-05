#pragma once

#include "Core/Exceptions.hpp"
#include "Core/Types.hpp"

namespace Neat {
struct BaseComponent {
  using Family = UInt32;

  void operator delete(void *) = delete;
  void operator delete[](void *) = delete;

 protected:
  static Family s_familyCounter;
};
}  // namespace Neat