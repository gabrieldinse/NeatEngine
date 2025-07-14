#include "NeatPCH.hpp"

#include "Neat/Graphics/RenderCommand.hpp"

namespace Neat {
Scope<RendererAPI> RenderCommand::s_rendererAPI = RendererAPI::create();
}  // namespace Neat