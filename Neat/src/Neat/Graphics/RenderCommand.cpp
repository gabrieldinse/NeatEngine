#include "NeatPCH.hpp"

#include "RenderCommand.hpp"

namespace Neat {
Scope<RendererAPI> RenderCommand::s_rendererAPI = RendererAPI::create();
}  // namespace Neat