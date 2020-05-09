#include "Neat/Renderer/Renderer.h"
#include "Neat/Renderer/Renderer2D.h"
#include "Neat/Debug/Instrumentator.h"


namespace Neat
{
   std::unique_ptr<Renderer::SceneData> Renderer::sceneData = std::make_unique<Renderer::SceneData>();

   void Renderer::init()
   {
      NT_PROFILE_FUNCTION();

      RenderCommand::init();
      Renderer2D::init();
   }
   
   void Renderer::shutdown()
   {
      NT_PROFILE_FUNCTION();

      Renderer2D::shutdown();
   }

   void Renderer::onWindowResize(UInt width, UInt height)
   {
      NT_PROFILE_FUNCTION();

      RenderCommand::setViewport(0, 0, width, height);
   }
}