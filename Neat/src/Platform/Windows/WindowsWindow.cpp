#include "Neat/Core/Window.h"
#include "Neat/Core/Log.h"
#include "Neat/Core/Application.h"
#include "Neat/Events/Event.h"
#include "Neat/Renderer/GraphicsContext.h"
#include "Neat/Debug/Instrumentator.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Neat
{
   static void GLFWErrorCallback(Int error, const char* description)
   {
      NT_CORE_ERROR("GLFW Error ({0}); {1}", error, description);
   }

   // -------------------------------------------------------------------------
   // GLFW callbacks ----------------------------------------------------------
   // -------------------------------------------------------------------------
   void windowResizeCallback(GLFWwindow* window, Int width, Int height);
   void windowCloseCallback(GLFWwindow* window);
   void keyActionCallback(
      GLFWwindow* window, Int key, Int scancode, Int action, Int mods);
   void keyTypeCallback(GLFWwindow* window, UInt key);
   void mouseButtonActionCallback(
      GLFWwindow* window, Int button, Int action, Int mods);
   void mouseScrollCallback(
      GLFWwindow* window, double xOffset, double yOffset);
   void mouseMoveCallback(GLFWwindow* window, double xPos, double yPos);


   // Defines a personalized std::unique_ptr for GLFWwindow
   struct GLFWwindowDeleter
   {
      void operator()(GLFWwindow* ptr)
      {
         glfwDestroyWindow(ptr);
      }
   };

   using GLFWwindowUniquePtr = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>;

   // -------------------------------------------------------------------------
   // Window ------------------------------------------------------------------
   // -------------------------------------------------------------------------
   struct Window::WindowImpl
   {
      WindowProps props;
      GLFWwindowUniquePtr window;
      std::unique_ptr<GraphicsContext> context;

      EventManager& events;

      bool minimized = false;
      bool vSync = false;


      WindowImpl(EventManager& eventManager, const WindowProps& props)
         : events(eventManager), props(props)
      {
         static Int windowCount = 0;
         NT_PROFILE_FUNCTION();

         if (windowCount == 0)
         {
            NT_PROFILE_SCOPE("GLFW initialization");
            Int status = glfwInit();
            glfwSetErrorCallback(GLFWErrorCallback);
            NT_CORE_ASSERT(status, "Failed to initialize GLFW!");
         }

         {
            NT_PROFILE_SCOPE("GLFW initialization");

            window = GLFWwindowUniquePtr(glfwCreateWindow(
               (Int)props.width, (Int)props.height,
               props.title.c_str(), NULL, NULL));
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            windowCount++;
         }

         {
            NT_PROFILE_SCOPE("OpenGL context initialization");
            context = std::make_unique<GraphicsContext>(window.get());
         }
      }
   };


   Window::Window(EventManager& eventManager, const WindowProps& props)
      : m_data(std::make_unique<WindowImpl>(eventManager, props))
   {
      NT_PROFILE_FUNCTION();

      NT_CORE_INFO("Created window {0} ({1}, {2})",
         props.title,
         props.width,
         props.height);

      m_data->context->init();

      glfwSetWindowUserPointer(m_data->window.get(), m_data.get());
      setVSync(true);

      glfwSetWindowSizeCallback(m_data->window.get(), windowResizeCallback);
      glfwSetWindowCloseCallback(m_data->window.get(), windowCloseCallback);
      glfwSetKeyCallback(m_data->window.get(), keyActionCallback);
      glfwSetCharCallback(m_data->window.get(), keyTypeCallback);
      glfwSetMouseButtonCallback(m_data->window.get(), mouseButtonActionCallback);
      glfwSetScrollCallback(m_data->window.get(), mouseScrollCallback);
      glfwSetCursorPosCallback(m_data->window.get(), mouseMoveCallback);
   }

   Int Window::getWidth() const
   {
      return m_data->props.width;
   }

   Int Window::getHeight() const
   {
      return m_data->props.height;
   }

   void* Window::getNativeWindow() const
   {
      return m_data->window.get();
   }

   Window::~Window()
   {
   }

   void Window::onUpdate()
   {
      NT_PROFILE_FUNCTION();

      glfwPollEvents();
      m_data->context->swapBuffers();
   }

   bool Window::isMinimized() const
   {
      return m_data->minimized;
   }

   void Window::setVSync(bool enabled)
   {
      NT_PROFILE_FUNCTION();

      if (enabled)
         glfwSwapInterval(1);
      else
         glfwSwapInterval(0);
      m_data->vSync = enabled;
   }

   bool Window::isSync() const
   {
      return m_data->vSync;
   }

   // -------------------------------------------------------------------------
   // GLFW callbacks ----------------------------------------------------------
   // -------------------------------------------------------------------------
   void windowResizeCallback(GLFWwindow* window, Int width, Int height)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *static_cast<Window::WindowImpl*>(
         glfwGetWindowUserPointer(window));

      data.props.width = width;
      data.props.height = height;

      if (data.props.width == 0 || data.props.height == 0)
         data.minimized = true;
      else
         data.minimized = false;

      data.events.publish<WindowResizeEvent>(width, height);
   }

   void windowCloseCallback(GLFWwindow* window)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *static_cast<Window::WindowImpl*>(
         glfwGetWindowUserPointer(window));
      data.events.publish<WindowCloseEvent>();
   }

   void keyActionCallback(
      GLFWwindow* window, Int key, Int scancode, Int action, Int mods)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *(Window::WindowImpl*)glfwGetWindowUserPointer(window);

      switch (action)
      {
         case GLFW_PRESS:
         {
            data.events.publish<KeyPressedEvent>(static_cast<KeyCode>(key), 0);
            break;
         }
         case GLFW_RELEASE:
         {
            data.events.publish<KeyReleasedEvent>(static_cast<KeyCode>(key));
            break;
         }
         case GLFW_REPEAT:
         {
            data.events.publish<KeyPressedEvent>(static_cast<KeyCode>(key), 1);
            break;
         }
      }
   }

   void keyTypeCallback(GLFWwindow* window, UInt key)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *static_cast<Window::WindowImpl*>(
         glfwGetWindowUserPointer(window));
      data.events.publish<KeyTypedEvent>(static_cast<KeyCode>(key));
   }

   void mouseButtonActionCallback(
      GLFWwindow* window, Int button, Int action, Int mods)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *static_cast<Window::WindowImpl*>(
         glfwGetWindowUserPointer(window));

      switch (action)
      {
         case GLFW_PRESS:
         {
            MouseButtonPressedEvent event(static_cast<MouseCode>(button));
            data.events.publish<MouseButtonPressedEvent>(
               static_cast<MouseCode>(button));
            break;
         }
         case GLFW_RELEASE:
         {
            MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
            data.events.publish<MouseButtonReleasedEvent>(
               static_cast<MouseCode>(button));
            break;
         }
      }
   }

   void mouseScrollCallback(
      GLFWwindow* window, double xOffset, double yOffset)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *static_cast<Window::WindowImpl*>(glfwGetWindowUserPointer(window));

      MouseScrolledEvent event((float)xOffset, (float)yOffset);
      data.events.publish<MouseScrolledEvent>((float)xOffset, (float)yOffset);
   }

   void mouseMoveCallback(
      GLFWwindow* window, double xPos, double yPos)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *static_cast<Window::WindowImpl*>(glfwGetWindowUserPointer(window));

      MouseMovedEvent event((float)xPos, (float)yPos);
      data.events.publish<MouseMovedEvent>((float)xPos, (float)yPos);
   }
}