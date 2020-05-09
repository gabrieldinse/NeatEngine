#include "Neat/Renderer/GraphicsContext.h"
#include "Neat/Core/Log.h"
#include "Neat/Debug/Instrumentator.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Neat
{
   GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
      : window(windowHandle)
   {
      NT_CORE_ASSERT(this->window, "Window is null!");
   }

   void GraphicsContext::init()
   {
      NT_PROFILE_FUNCTION();

      glfwMakeContextCurrent(this->window);

      // Glad initialization (need to be after window creation)
      auto status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
      NT_CORE_ASSERT(status, "Failed to initialize Glad!");

      NT_CORE_INFO("OpenGL info:");
      NT_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
      NT_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
      NT_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
   }

   void GraphicsContext::swapBuffers()
   {
      NT_PROFILE_FUNCTION();

      glfwSwapBuffers(this->window);
   }
}