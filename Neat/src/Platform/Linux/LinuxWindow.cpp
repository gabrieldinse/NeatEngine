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
#include "Neat/Events/EventManager.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Neat {
void GLFWwindowDeleter::operator()(GLFWwindow *ptr) { glfwDestroyWindow(ptr); }

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

// Defines a customized std::unique_ptr for GLFWwindow

LinuxWindow::LinuxWindow(const WindowProps &props) : m_windowProps(props) {
  static Int32 windowCount = 0;

  if (windowCount == 0) {
    Int32 status = glfwInit();
    glfwSetErrorCallback(GLFWErrorCallback);
    NT_CORE_ASSERT(status, "Failed to initialize GLFW!");
  }

  m_glfwWindow = GLFWwindowUniquePtr(
      glfwCreateWindow((Int32)m_windowProps.width, (Int32)m_windowProps.height,
                       m_windowProps.title.c_str(), NULL, NULL));
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  windowCount++;

  NT_CORE_ASSERT(m_glfwWindow.get(), "Window is null!");

  glfwMakeContextCurrent(m_glfwWindow.get());

  // Glad initialization (need to be after window creation)
  auto status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  NT_CORE_ASSERT(status, "Failed to initialize Glad!");

  NT_CORE_INFO("OpenGL info:");
  NT_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
  NT_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
  NT_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
  NT_CORE_INFO("Created window {0} ({1}, {2})", m_windowProps.title,
               m_windowProps.width, m_windowProps.height);

  glfwSetWindowUserPointer(m_glfwWindow.get(), &m_windowProps);
  setVSync(m_windowProps.vSync);

  glfwSetWindowSizeCallback(m_glfwWindow.get(), windowResizeCallback);
  glfwSetWindowCloseCallback(m_glfwWindow.get(), windowCloseCallback);
  glfwSetKeyCallback(m_glfwWindow.get(), keyActionCallback);
  glfwSetCharCallback(m_glfwWindow.get(), keyTypeCallback);
  glfwSetMouseButtonCallback(m_glfwWindow.get(), mouseButtonActionCallback);
  glfwSetScrollCallback(m_glfwWindow.get(), mouseScrollCallback);
  glfwSetCursorPosCallback(m_glfwWindow.get(), mouseMoveCallback);
}

Int32 LinuxWindow::getWidth() const { return m_windowProps.width; }

Int32 LinuxWindow::getHeight() const { return m_windowProps.height; }

float LinuxWindow::getAspectRatio() const {
  return (float)m_windowProps.width / (float)m_windowProps.height;
}

void *LinuxWindow::getNativeWindow() const { return m_glfwWindow.get(); }

void LinuxWindow::onUpdate() {
  glfwSwapBuffers(m_glfwWindow.get());
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

bool LinuxWindow::isSync() const { return m_windowProps.vSync; }

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

  windowProps.eventManager->generateEvent<WindowResizeEvent>(width, height);
}

void windowCloseCallback(GLFWwindow *window) {
  auto &windowProps =
      *static_cast<WindowProps *>(glfwGetWindowUserPointer(window));
  windowProps.eventManager->generateEvent<WindowCloseEvent>();
}

void keyActionCallback(GLFWwindow *window, Int32 key, Int32 scancode,
                       Int32 action, Int32 mods) {
  auto &windowProps =
      *static_cast<WindowProps *>(glfwGetWindowUserPointer(window));

  switch (action) {
    case GLFW_PRESS: {
      windowProps.eventManager->generateEvent<KeyPressedEvent>(
          static_cast<Key>(key), 0);
      break;
    }
    case GLFW_RELEASE: {
      windowProps.eventManager->generateEvent<KeyReleasedEvent>(
          static_cast<Key>(key));
      break;
    }
    case GLFW_REPEAT: {
      windowProps.eventManager->generateEvent<KeyPressedEvent>(
          static_cast<Key>(key), 1);
      break;
    }
  }
}

void keyTypeCallback(GLFWwindow *window, UInt32 key) {
  auto &windowProps =
      *static_cast<WindowProps *>(glfwGetWindowUserPointer(window));
  windowProps.eventManager->generateEvent<KeyTypedEvent>(static_cast<Key>(key));
}

void mouseButtonActionCallback(GLFWwindow *window, Int32 button, Int32 action,
                               Int32 mods) {
  auto &windowProps =
      *static_cast<WindowProps *>(glfwGetWindowUserPointer(window));

  switch (action) {
    case GLFW_PRESS: {
      MouseButtonPressedEvent event(static_cast<Mouse>(button));
      windowProps.eventManager->generateEvent<MouseButtonPressedEvent>(
          static_cast<Mouse>(button));
      break;
    }
    case GLFW_RELEASE: {
      MouseButtonReleasedEvent event(static_cast<Mouse>(button));
      windowProps.eventManager->generateEvent<MouseButtonReleasedEvent>(
          static_cast<Mouse>(button));
      break;
    }
  }
}

void mouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
  auto &windowProps =
      *static_cast<WindowProps *>(glfwGetWindowUserPointer(window));

  MouseScrolledEvent event((float)xOffset, (float)yOffset);
  windowProps.eventManager->generateEvent<MouseScrolledEvent>((float)xOffset,
                                                              (float)yOffset);
}

void mouseMoveCallback(GLFWwindow *window, double xPos, double yPos) {
  auto &windowProps =
      *static_cast<WindowProps *>(glfwGetWindowUserPointer(window));

  MouseMovedEvent event((float)xPos, (float)yPos);
  windowProps.eventManager->generateEvent<MouseMovedEvent>((float)xPos,
                                                           (float)yPos);
}
}  // namespace Neat