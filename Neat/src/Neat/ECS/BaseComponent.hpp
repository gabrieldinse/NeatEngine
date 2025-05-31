#pragma once

#include "Neat/Core/Exceptions.hpp"
#include "Neat/Core/Types.hpp"

namespace Neat {
struct BaseComponent {
  using Family = UInt32;

  void operator delete(void *ptr) { fail(); }
  void operator delete[](void *ptr) { fail(); }

 protected:
  static void fail() { throw BadComponentAllocationError(); }

  static Family s_familyCounter;
};
}  // namespace Neat