#include "Neat/Core/Window.h"
#include "Neat/Core/Log.h"
#include "Neat/Events/MouseEvent.h"
#include "Neat/Events/KeyEvent.h"
#include "Neat/Events/ApplicationEvent.h"
#include "Neat/Renderer/GraphicsContext.h"
#include "Neat/Debug/Instrumentator.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Neat
{
   static void GLFWErrorCallback(Int error, const Char* description)
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
      GLFWwindow* window, Double xOffset, Double yOffset);
   void mouseMoveCallback(GLFWwindow* window, Double xPos, Double yPos);


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
   struct WindowImpl
   {
      WindowProps props;
      GLFWwindowUniquePtr window;
      std::unique_ptr<GraphicsContext> context;
      Bool minimized = false;
      Bool vSync = false;
      eventCallbackFunction eventCallback;

      WindowImpl(const WindowProps& props)
         : props(props)
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

            this->window = GLFWwindowUniquePtr(glfwCreateWindow(
               (Int)this->props.width, (Int)this->props.height,
               props.title.c_str(), NULL, NULL));
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            windowCount++;
         }

         {
            NT_PROFILE_SCOPE("OpenGL context initialization");
            this->context = std::make_unique<GraphicsContext>(this->window.get());
         }
      }
   };


   Window::Window(const WindowProps& props)
      : data(std::make_unique<WindowImpl>(props))
   {
      NT_PROFILE_FUNCTION();

      NT_CORE_INFO("Created window {0} ({1}, {2})",
         props.title,
         props.width,
         props.height);

      this->data->context->init();

      glfwSetWindowUserPointer(this->data->window.get(), this->data.get());
      this->setVSync(true);

      glfwSetWindowSizeCallback(this->data->window.get(), windowResizeCallback);
      glfwSetWindowCloseCallback(this->data->window.get(), windowCloseCallback);
      glfwSetKeyCallback(this->data->window.get(), keyActionCallback);
      glfwSetCharCallback(this->data->window.get(), keyTypeCallback);
      glfwSetMouseButtonCallback(this->data->window.get(), mouseButtonActionCallback);
      glfwSetScrollCallback(this->data->window.get(), mouseScrollCallback);
      glfwSetCursorPosCallback(this->data->window.get(), mouseMoveCallback);
   }

   Int Window::getWidth() const
   {
      return this->data->props.width;
   }

   Int Window::getHeight() const
   {
      return this->data->props.height;
   }

   void* Window::getNativeWindow() const
   {
      return this->data->window.get();
   }

   void Window::setEventCallback(const eventCallbackFunction& callback)
   {
      this->data->eventCallback = callback;
   }

   Window::~Window()
   {
   }

   void Window::onUpdate()
   {
      NT_PROFILE_FUNCTION();

      glfwPollEvents();
      this->data->context->swapBuffers();
   }

   Bool Window::isMinimized() const
   {
      return this->data->minimized;
   }

   void Window::setVSync(Bool enabled)
   {
      NT_PROFILE_FUNCTION();

      if (enabled)
         glfwSwapInterval(1);
      else
         glfwSwapInterval(0);
      this->data->vSync = enabled;
   }

   Bool Window::isSync() const
   {
      return this->data->vSync;
   }

   // -------------------------------------------------------------------------
   // GLFW callbacks ----------------------------------------------------------
   // -------------------------------------------------------------------------
   void windowResizeCallback(GLFWwindow* window, Int width, Int height)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
      data.props.width = width;
      data.props.height = height;

      if (data.props.width == 0 || data.props.height == 0)
         data.minimized = true;
      else
         data.minimized = false;

      WindowResizeEvent event(width, height);
      data.eventCallback(event);
   }

   void windowCloseCallback(GLFWwindow* window)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
      WindowCloseEvent event;
      data.eventCallback(event);
   }

   void keyActionCallback(
      GLFWwindow* window, Int key, Int scancode, Int action, Int mods)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *(WindowImpl*)glfwGetWindowUserPointer(window);

      switch (action)
      {
         case GLFW_PRESS:
         {
            KeyPressedEvent event(static_cast<KeyCode>(key), 0);
            data.eventCallback(event);
            break;
         }
         case GLFW_RELEASE:
         {
            KeyReleasedEvent event(static_cast<KeyCode>(key));
            data.eventCallback(event);
            break;
         }
         case GLFW_REPEAT:
         {
            KeyPressedEvent event(static_cast<KeyCode>(key), 1);
            data.eventCallback(event);
            break;
         }
      }
   }

   void keyTypeCallback(GLFWwindow* window, UInt key)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
      KeyTypedEvent event(static_cast<KeyCode>(key));
      data.eventCallback(event);
   }

   void mouseButtonActionCallback(
      GLFWwindow* window, Int button, Int action, Int mods)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));

      switch (action)
      {
         case GLFW_PRESS:
         {
            MouseButtonPressedEvent event(static_cast<MouseCode>(button));
            data.eventCallback(event);
            break;
         }
         case GLFW_RELEASE:
         {
            MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
            data.eventCallback(event);
            break;
         }
      }
   }

   void mouseScrollCallback(
      GLFWwindow* window, Double xOffset, Double yOffset)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
      MouseScrolledEvent event((Float)xOffset, (Float)yOffset);
      data.eventCallback(event);
   }

   void mouseMoveCallback(
      GLFWwindow* window, Double xPos, Double yPos)
   {
      NT_PROFILE_FUNCTION();

      auto& data = *static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
      MouseMovedEvent event((Float)xPos, (Float)yPos);
      data.eventCallback(event);
   }
}