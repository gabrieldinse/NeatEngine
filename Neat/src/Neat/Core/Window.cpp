#include "NeatPCH.hpp"

#include "Neat/Core/Window.hpp"

#ifdef NT_PLATFORM_LINUX
#include "Platform/Linux/LinuxWindow.hpp"
#endif

namespace Neat {
Scope<Window> Window::create(const Ref<EventDispatcher> &eventDispatcher,
                             const WindowProperties &windowProperties) {
#ifdef NT_PLATFORM_LINUX
  return makeScope<LinuxWindow>(eventDispatcher, windowProperties);
#else
  NT_CORE_ASSET(false, "Unknown platform!");
  return nullptr;
#endif
}
}  // namespace Neat