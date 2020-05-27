#include "Neat/Graphics/GraphicsContext.h"
#include "Neat/Core/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Neat
{
   GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
      : m_window(windowHandle)
   {
      NT_CORE_ASSERT(m_window, "Window is null!");
   }

   void GraphicsContext::init()
   {
      glfwMakeContextCurrent(m_window);

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
      glfwSwapBuffers(m_window);
   }
}