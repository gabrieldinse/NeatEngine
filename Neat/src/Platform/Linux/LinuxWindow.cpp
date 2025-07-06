#include "NeatPCH.hpp"

#include "Neat/Core/Application.hpp"
#include "Neat/Core/Log.hpp"
#include "Platform/Linux/LinuxWindow.hpp"
#include "Neat/Events/Events/KeyPressedEvent.hpp"
#include "Neat/Events/Events/KeyReleasedEvent.hpp"
#include "Neat/Events/Events/KeyTypedEvent.hpp"
#include "Neat/Events/Events/MouseButtonPressedEvent.hpp"
#include "Neat/Events/Events/MouseButtonReleasedEvent.hpp"
#include "Neat/Events/Events/MouseMovedEvent.hpp"
#include "Neat/Events/Events/MouseScrolledEvent.hpp"
#include "Neat/Events/EventDispatcher.hpp"

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

Int32 LinuxWindow::s_windowCount = 0;

LinuxWindow::LinuxWindow(const WindowProps &props) : m_windowProps(props) {
  if (s_windowCount == 0) {
    Int32 status = glfwInit();
    glfwSetErrorCallback(GLFWErrorCallback);
    NT_CORE_ASSERT(status, "Failed to initialize GLFW!");
  }

  m_glfwWindow =
      glfwCreateWindow((Int32)m_windowProps.width, (Int32)m_windowProps.height,
                       m_windowProps.title.c_str(), NULL, NULL);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  NT_CORE_ASSERT(m_glfwWindow, "Window is null!");
  s_windowCount++;

  glfwMakeContextCurrent(m_glfwWindow);

  // Glad initialization (need to be after window creation)
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  NT_CORE_ASSERT(status, "Failed to initialize Glad!");

  NT_CORE_INFO("OpenGL info:");
  NT_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
  NT_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
  NT_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
  NT_CORE_INFO("Created window {0} ({1}, {2})", m_windowProps.title,
               m_windowProps.width, m_windowProps.height);

  glfwSetWindowUserPointer(m_glfwWindow, &m_windowProps);
  setVSync(m_windowProps.vSync);

  glfwSetWindowSizeCallback(m_glfwWindow, windowResizeCallback);
  glfwSetWindowCloseCallback(m_glfwWindow, windowCloseCallback);
  glfwSetKeyCallback(m_glfwWindow, keyActionCallback);
  glfwSetCharCallback(m_glfwWindow, keyTypeCallback);
  glfwSetMouseButtonCallback(m_glfwWindow, mouseButtonActionCallback);
  glfwSetScrollCallback(m_glfwWindow, mouseScrollCallback);
  glfwSetCursorPosCallback(m_glfwWindow, mouseMoveCallback);
}

LinuxWindow::~LinuxWindow() {
  s_windowCount--;
  glfwDestroyWindow(m_glfwWindow);
  if (s_windowCount == 0) {
    glfwTerminate();
  }
}

Int32 LinuxWindow::getWidth() const { return m_windowProps.width; }

Int32 LinuxWindow::getHeight() const { return m_windowProps.height; }

float LinuxWindow::getAspectRatio() const {
  return (float)m_windowProps.width / (float)m_windowProps.height;
}

void *LinuxWindow::getNativeWindow() const { return m_glfwWindow; }

void LinuxWindow::onUpdate() {
  glfwSwapBuffers(m_glfwWindow);
  glfwPollEvents();
}

bool LinuxWindow::isMinimized() const { return m_windowProps.minimized; }

void LinuxWindow::setVSync(bool enabled) {
  if (enabled) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  m_windowProps.vSync = enabled;
}

bool LinuxWindow::isVSync() const { return m_windowProps.vSync; }

// ---------------------------------------------------------------------- //
// GLFW callbacks ------------------------------------------------------- //
// ---------------------------------------------------------------------- //
void windowResizeCallback(GLFWwindow *window, Int32 width, Int32 height) {
  auto &windowProps =
      *static_cast<WindowProps *>(glfwGetWindowUserPointer(window));

  windowProps.width = width;
  windowProps.height = height;

  if (windowProps.width == 0 or windowProps.height == 0)
    windowProps.minimized = true;
  else
    windowProps.minimized = false;

  windowProps.eventDispatcher->enqueue<WindowResizeEvent>(width, height);
}

void windowCloseCallback(GLFWwindow *window) {
  auto &windowProps =
      *static_cast<WindowProps *>(glfwGetWindowUserPointer(window));
  windowProps.eventDispatcher->enqueue<WindowCloseEvent>();
}

void keyActionCallback(GLFWwindow *window, Int32 key, Int32 scancode,
                       Int32 action, Int32 mods) {
  auto &windowProps =
      *static_cast<WindowProps *>(glfwGetWindowUserPointer(window));

  switch (action) {
    case GLFW_PRESS: {
      windowProps.eventDispatcher->enqueue<KeyPressedEvent>(
          static_cast<Key>(key), 0);
      break;
    }
    case GLFW_RELEASE: {
      windowProps.eventDispatcher->enqueue<KeyReleasedEvent>(
          static_cast<Key>(key));
      break;
    }
    case GLFW_REPEAT: {
      windowProps.eventDispatcher->enqueue<KeyPressedEvent>(
          static_cast<Key>(key), 1);
      break;
    }
  }
}

void keyTypeCallback(GLFWwindow *window, UInt32 key) {
  auto &windowProps =
      *static_cast<WindowProps *>(glfwGetWindowUserPointer(window));
  windowProps.eventDispatcher->enqueue<KeyTypedEvent>(static_cast<Key>(key));
}

void mouseButtonActionCallback(GLFWwindow *window, Int32 button, Int32 action,
                               Int32 mods) {
  auto &windowProps =
      *static_cast<WindowProps *>(glfwGetWindowUserPointer(window));

  switch (action) {
    case GLFW_PRESS: {
      MouseButtonPressedEvent event(static_cast<MouseButton>(button));
      windowProps.eventDispatcher->enqueue<MouseButtonPressedEvent>(
          static_cast<MouseButton>(button));
      break;
    }
    case GLFW_RELEASE: {
      MouseButtonReleasedEvent event(static_cast<MouseButton>(button));
      windowProps.eventDispatcher->enqueue<MouseButtonReleasedEvent>(
          static_cast<MouseButton>(button));
      break;
    }
  }
}

void mouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
  auto &windowProps =
      *static_cast<WindowProps *>(glfwGetWindowUserPointer(window));

  MouseScrolledEvent event((float)xOffset, (float)yOffset);
  windowProps.eventDispatcher->enqueue<MouseScrolledEvent>((float)xOffset,
                                                           (float)yOffset);
}

void mouseMoveCallback(GLFWwindow *window, double xPos, double yPos) {
  auto &windowProps =
      *static_cast<WindowProps *>(glfwGetWindowUserPointer(window));

  MouseMovedEvent event((float)xPos, (float)yPos);
  windowProps.eventDispatcher->enqueue<MouseMovedEvent>((float)xPos,
                                                        (float)yPos);
}
}  // namespace Neat