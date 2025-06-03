#include "Neat/Core/Window.hpp"
#include "Neat/Events/EventManager.hpp"

#ifdef NT_PLATFORM_LINUX
#include "Platform/Linux/LinuxWindow.hpp"
#endif

namespace Neat {
std::unique_ptr<Window> Window::create(const WindowProps &props) {
#ifdef NT_PLATFORM_LINUX
  return std::make_unique<LinuxWindow>(props);
#else
  NT_CORE_ASSET(false, "Unknown platform!");
  return nullptr;
#endif
}
}  // namespace Neat