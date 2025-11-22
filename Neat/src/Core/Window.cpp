#include "NeatPCH.hpp"

#include "Window.hpp"

#include "Core/Log.hpp"
#include "Events/KeyPressedEvent.hpp"
#include "Events/KeyReleasedEvent.hpp"
#include "Events/KeyTypedEvent.hpp"
#include "Events/MouseButtonPressedEvent.hpp"
#include "Events/MouseButtonReleasedEvent.hpp"
#include "Events/MouseMovedEvent.hpp"
#include "Events/MouseScrolledEvent.hpp"
#include "Events/WindowResizeEvent.hpp"
#include "Events/WindowCloseEvent.hpp"
#include "EventDispatching/EventDispatcher.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Neat {

static void GLFWErrorCallback(Int32 error, const char *description) {
  NT_CORE_ERROR("GLFW Error ({0}); {1}", error, description);
}

// ---------------------------------------------------------------------- //
// GLFW callbacks ------------------------------------------------------- //
// ---------------------------------------------------------------------- //
void windowResizeCallback(GLFWwindow *window, Int32 width, Int32 height);
void windowCloseCallback(GLFWwindow *window);
void keyActionCallback(GLFWwindow *window, Int32 key, Int32 scancode,
                       Int32 action, Int32 mods);
void keyTypeCallback(GLFWwindow *window, UInt32 key);
void mouseButtonActionCallback(GLFWwindow *window, Int32 button, Int32 action,
                               Int32 mods);
void mouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset);
void mouseMoveCallback(GLFWwindow *window, double xPos, double yPos);

Int32 Window::s_windowCount = 0;

Window::Window(const Ref<EventDispatcher> &eventDispatcher,
               const WindowProperties &windowProperties)
    : m_windowData{windowProperties, eventDispatcher} {
  NT_PROFILE_FUNCTION();
  if (s_windowCount == 0) {
    Int32 status = glfwInit();
    glfwSetErrorCallback(GLFWErrorCallback);
    NT_CORE_ASSERT(status, "Failed to initialize GLFW!");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_glfwWindow =
      glfwCreateWindow(static_cast<Int32>(m_windowData.windowProperties.width),
                       static_cast<Int32>(m_windowData.windowProperties.height),
                       m_windowData.windowProperties.title.c_str(), NULL, NULL);
  NT_CORE_ASSERT(m_glfwWindow, "Window is null!");
  s_windowCount++;

  m_graphicsContext = GraphicsContext::create(m_glfwWindow);
  m_graphicsContext->initialize();

  NT_CORE_INFO("Created window {0} ({1}, {2})",
               m_windowData.windowProperties.title,
               m_windowData.windowProperties.width,
               m_windowData.windowProperties.height);

  glfwSetWindowUserPointer(m_glfwWindow, &m_windowData);
  setVSync(m_windowData.windowProperties.vSync);

  glfwSetWindowSizeCallback(m_glfwWindow, windowResizeCallback);
  glfwSetWindowCloseCallback(m_glfwWindow, windowCloseCallback);
  glfwSetKeyCallback(m_glfwWindow, keyActionCallback);
  glfwSetCharCallback(m_glfwWindow, keyTypeCallback);
  glfwSetMouseButtonCallback(m_glfwWindow, mouseButtonActionCallback);
  glfwSetScrollCallback(m_glfwWindow, mouseScrollCallback);
  glfwSetCursorPosCallback(m_glfwWindow, mouseMoveCallback);
}

Window::~Window() {
  NT_PROFILE_FUNCTION();
  s_windowCount--;
  glfwDestroyWindow(m_glfwWindow);
  if (s_windowCount == 0) {
    glfwTerminate();
  }
}

Int32 Window::getWidth() const { return m_windowData.windowProperties.width; }

Int32 Window::getHeight() const { return m_windowData.windowProperties.height; }

float Window::getAspectRatio() const {
  return static_cast<float>(m_windowData.windowProperties.width) /
         static_cast<float>(m_windowData.windowProperties.height);
}

GLFWwindow *Window::getNativeWindow() const { return m_glfwWindow; }

void Window::update() {
  NT_PROFILE_FUNCTION();
  m_graphicsContext->update();
  glfwPollEvents();
}

bool Window::isMinimized() const {
  return m_windowData.windowProperties.minimized;
}

void Window::setVSync(bool enabled) {
  if (enabled) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  m_windowData.windowProperties.vSync = enabled;
}

bool Window::isVSync() const { return m_windowData.windowProperties.vSync; }

// ---------------------------------------------------------------------- //
// GLFW callbacks ------------------------------------------------------- //
// ---------------------------------------------------------------------- //
void windowResizeCallback(GLFWwindow *window, Int32 width, Int32 height) {
  auto &windowData =
      *static_cast<WindowData *>(glfwGetWindowUserPointer(window));

  windowData.windowProperties.width = width;
  windowData.windowProperties.height = height;

  if (windowData.windowProperties.width == 0 or
      windowData.windowProperties.height == 0)
    windowData.windowProperties.minimized = true;
  else
    windowData.windowProperties.minimized = false;

  windowData.eventDispatcher->enqueue<WindowResizeEvent>(width, height);
}

void windowCloseCallback(GLFWwindow *window) {
  auto &windowData =
      *static_cast<WindowData *>(glfwGetWindowUserPointer(window));
  windowData.eventDispatcher->enqueue<WindowCloseEvent>();
}

void keyActionCallback(GLFWwindow *window, Int32 key,
                       [[maybe_unused]] Int32 scancode, Int32 action,
                       [[maybe_unused]] Int32 mods) {
  auto &windowData =
      *static_cast<WindowData *>(glfwGetWindowUserPointer(window));

  switch (action) {
    case GLFW_PRESS: {
      windowData.eventDispatcher->enqueue<KeyPressedEvent>(
          static_cast<Key>(key), 0);
      break;
    }
    case GLFW_RELEASE: {
      windowData.eventDispatcher->enqueue<KeyReleasedEvent>(
          static_cast<Key>(key));
      break;
    }
    case GLFW_REPEAT: {
      windowData.eventDispatcher->enqueue<KeyPressedEvent>(
          static_cast<Key>(key), 1);
      break;
    }
  }
}

void keyTypeCallback(GLFWwindow *window, UInt32 key) {
  auto &windowData =
      *static_cast<WindowData *>(glfwGetWindowUserPointer(window));
  windowData.eventDispatcher->enqueue<KeyTypedEvent>(static_cast<Key>(key));
}

void mouseButtonActionCallback(GLFWwindow *window, Int32 button, Int32 action,
                               [[maybe_unused]] Int32 mods) {
  auto &windowData =
      *static_cast<WindowData *>(glfwGetWindowUserPointer(window));

  switch (action) {
    case GLFW_PRESS: {
      windowData.eventDispatcher->enqueue<MouseButtonPressedEvent>(
          static_cast<MouseButton>(button));
      break;
    }
    case GLFW_RELEASE: {
      windowData.eventDispatcher->enqueue<MouseButtonReleasedEvent>(
          static_cast<MouseButton>(button));
      break;
    }
  }
}

void mouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
  auto &windowData =
      *static_cast<WindowData *>(glfwGetWindowUserPointer(window));

  windowData.eventDispatcher->enqueue<MouseScrolledEvent>((float)xOffset,
                                                          (float)yOffset);
}

void mouseMoveCallback(GLFWwindow *window, double xPos, double yPos) {
  auto &windowData =
      *static_cast<WindowData *>(glfwGetWindowUserPointer(window));

  windowData.eventDispatcher->enqueue<MouseMovedEvent>((float)xPos,
                                                       (float)yPos);
}
}  // namespace Neat
