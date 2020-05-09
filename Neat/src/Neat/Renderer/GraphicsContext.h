#pragma once

#include <memory>

#include "Neat/Core/Core.h"


struct GLFWwindow;


namespace Neat
{
   class GraphicsContext
   {
   public:
      GraphicsContext(GLFWwindow* windowHandle);

      void init();
      void swapBuffers();

   private:
      GLFWwindow* window;
   };
}