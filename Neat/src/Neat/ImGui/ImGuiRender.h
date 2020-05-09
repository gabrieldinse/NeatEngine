#pragma once

#include "Neat/Core/Layer.h"
#include "Neat/Events/ApplicationEvent.h"
#include "Neat/Events/MouseEvent.h"
#include "Neat/Events/KeyEvent.h"


namespace Neat
{
   namespace ImGuiRender
   {
      void init();
      void shutdown();
      void begin();
      void end();
   }
}