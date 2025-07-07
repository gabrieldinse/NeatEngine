#include "NeatPCH.hpp"

#include "Neat/Graphics/RenderCommand.hpp"

namespace Neat {
std::unique_ptr<RendererAPI> RenderCommand::s_rendererAPI =
    RendererAPI::create();
}  // namespace Neat