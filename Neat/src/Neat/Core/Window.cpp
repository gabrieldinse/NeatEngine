#include "NeatPCH.hpp"

#include "Neat/Core/Window.hpp"

#ifdef NT_PLATFORM_LINUX
#include "Platform/Linux/LinuxWindow.hpp"
#endif

namespace Neat {
Scope<Window> Window::create(const WindowProps &props) {
#ifdef NT_PLATFORM_LINUX
  return makeScope<LinuxWindow>(props);
#else
  NT_CORE_ASSET(false, "Unknown platform!");
  return nullptr;
#endif
}
}  // namespace Neat