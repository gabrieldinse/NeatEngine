#include "Neat/Core/Window.hpp"
#include "Neat/Core/Log.hpp"
#include "Neat/Core/Application.hpp"
#include "Neat/Events/Event.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Neat
{
   static void GLFWErrorCallback(Int32 error, const char* description)
   {
      NT_CORE_ERROR("GLFW Error ({0}); {1}", error, description);
   }

   // ---------------------------------------------------------------------- //
   // GLFW callbacks ------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   void windowResizeCallback(GLFWwindow* window, Int32 width, Int32 height);
   void windowCloseCallback(GLFWwindow* window);
   void keyActionCallback(
      GLFWwindow* window, Int32 key, Int32 scancode, Int32 action, Int32 mods);
   void keyTypeCallback(GLFWwindow* window, UInt32 key);
   void mouseButtonActionCallback(
      GLFWwindow* window, Int32 button, Int32 action, Int32 mods);
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

   // ---------------------------------------------------------------------- //
   // Window --------------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   struct Window::WindowImpl
   {
      WindowProps props;
      GLFWwindowUniquePtr window;
      EventManager& events;
      bool minimized = false;
      bool vSync = false;


      WindowImpl(EventManager& eventManager, const WindowProps& props)
         : events(eventManager), props(props)
      {
         static Int32 windowCount = 0;
         

         if (windowCount == 0)
         {
            Int32 status = glfwInit();
            glfwSetErrorCallback(GLFWErrorCallback);
            NT_CORE_ASSERT(status, "Failed to initialize GLFW!");
         }

         window = GLFWwindowUniquePtr(glfwCreateWindow(
            (Int32)props.width, (Int32)props.height,
            props.title.c_str(), NULL, NULL));
         glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
         glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
         glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
         windowCount++;


         NT_CORE_ASSERT(window.get(), "Window is null!");

         glfwMakeContextCurrent(window.get());

         // Glad initialization (need to be after window creation)
         auto status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
         NT_CORE_ASSERT(status, "Failed to initialize Glad!");

         NT_CORE_INFO("OpenGL info:");
         NT_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
         NT_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
         NT_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
      }
   };


   Window::Window(EventManager& eventManager, const WindowProps& props)
      : m_impl(std::make_unique<WindowImpl>(eventManager, props))
   {
      NT_CORE_INFO("Created window {0} ({1}, {2})",
         props.title,
         props.width,
         props.height);

      glfwSetWindowUserPointer(m_impl->window.get(), m_impl.get());
      setVSync(m_impl->vSync);

      glfwSetWindowSizeCallback(m_impl->window.get(), windowResizeCallback);
      glfwSetWindowCloseCallback(m_impl->window.get(), windowCloseCallback);
      glfwSetKeyCallback(m_impl->window.get(), keyActionCallback);
      glfwSetCharCallback(m_impl->window.get(), keyTypeCallback);
      glfwSetMouseButtonCallback(m_impl->window.get(), mouseButtonActionCallback);
      glfwSetScrollCallback(m_impl->window.get(), mouseScrollCallback);
      glfwSetCursorPosCallback(m_impl->window.get(), mouseMoveCallback);
   }


   Int32 Window::getWidth() const
   {
      return m_impl->props.width;
   }

   Int32 Window::getHeight() const
   {
      return m_impl->props.height;
   }

   float Window::getAspectRatio() const
   {
      return (float)m_impl->props.width / (float)m_impl->props.height;
   }


   void* Window::getNativeWindow() const
   {
      return m_impl->window.get();
   }

   Window::~Window()
   {
   }

   void Window::swapBuffers()
   {
      glfwSwapBuffers(m_impl->window.get());
   }

   void Window::pollEvents()
   {
      glfwPollEvents();
   }

   bool Window::isMinimized() const
   {
      return m_impl->minimized;
   }

   void Window::setVSync(bool enabled)
   {
      if (enabled)
         glfwSwapInterval(1);
      else
         glfwSwapInterval(0);
      m_impl->vSync = enabled;
   }

   bool Window::isSync() const
   {
      return m_impl->vSync;
   }

   // ---------------------------------------------------------------------- //
   // GLFW callbacks ------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   void windowResizeCallback(GLFWwindow* window, Int32 width, Int32 height)
   {
      auto& impl = *static_cast<Window::WindowImpl*>(
         glfwGetWindowUserPointer(window));

      impl.props.width = width;
      impl.props.height = height;

      if (impl.props.width == 0 || impl.props.height == 0)
         impl.minimized = true;
      else
         impl.minimized = false;

      impl.events.publish<WindowResizeEvent>(width, height);
   }

   void windowCloseCallback(GLFWwindow* window)
   {
      auto& impl = *static_cast<Window::WindowImpl*>(
         glfwGetWindowUserPointer(window));
      impl.events.publish<WindowCloseEvent>();
   }

   void keyActionCallback(GLFWwindow* window, Int32 key, Int32 scancode,
      Int32 action, Int32 mods)
   {
      auto& impl = *static_cast<Window::WindowImpl*>(
         glfwGetWindowUserPointer(window));

      switch (action)
      {
         case GLFW_PRESS:
         {
            impl.events.publish<KeyPressedEvent>(static_cast<KeyCode>(key), 0);
            break;
         }
         case GLFW_RELEASE:
         {
            impl.events.publish<KeyReleasedEvent>(static_cast<KeyCode>(key));
            break;
         }
         case GLFW_REPEAT:
         {
            impl.events.publish<KeyPressedEvent>(static_cast<KeyCode>(key), 1);
            break;
         }
      }
   }

   void keyTypeCallback(GLFWwindow* window, UInt32 key)
   {
      auto& impl = *static_cast<Window::WindowImpl*>(
         glfwGetWindowUserPointer(window));
      impl.events.publish<KeyTypedEvent>(static_cast<KeyCode>(key));
   }

   void mouseButtonActionCallback(
      GLFWwindow* window, Int32 button, Int32 action, Int32 mods)
   {
      auto& impl = *static_cast<Window::WindowImpl*>(
         glfwGetWindowUserPointer(window));

      switch (action)
      {
         case GLFW_PRESS:
         {
            MouseButtonPressedEvent event(static_cast<MouseCode>(button));
            impl.events.publish<MouseButtonPressedEvent>(
               static_cast<MouseCode>(button));
            break;
         }
         case GLFW_RELEASE:
         {
            MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
            impl.events.publish<MouseButtonReleasedEvent>(
               static_cast<MouseCode>(button));
            break;
         }
      }
   }

   void mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
   {
      auto& impl = *static_cast<Window::WindowImpl*>(
         glfwGetWindowUserPointer(window));

      MouseScrolledEvent event((float)xOffset, (float)yOffset);
      impl.events.publish<MouseScrolledEvent>((float)xOffset, (float)yOffset);
   }

   void mouseMoveCallback(GLFWwindow* window, double xPos, double yPos)
   {
      auto& impl = *static_cast<Window::WindowImpl*>(
         glfwGetWindowUserPointer(window));

      MouseMovedEvent event((float)xPos, (float)yPos);
      impl.events.publish<MouseMovedEvent>((float)xPos, (float)yPos);
   }
}