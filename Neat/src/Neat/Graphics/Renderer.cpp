#include "Neat/Graphics/Renderer.h"
#include "Neat/Graphics/Renderer2D.h"


namespace Neat
{
   std::unique_ptr<Renderer::SceneData> Renderer::m_sceneData = std::make_unique<Renderer::SceneData>();

   void Renderer::init()
   {
      RenderCommand::init();
      Renderer2D::init();
   }
   
   void Renderer::shutdown()
   {
      Renderer2D::shutdown();
   }

   void Renderer::onWindowResize(UInt32 width, UInt32 height)
   {
      RenderCommand::setViewport(0, 0, width, height);
   }
}