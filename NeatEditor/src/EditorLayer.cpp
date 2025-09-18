#include <memory>

#include "EditorLayer.hpp"
#include "Neat/Scene/SceneSerializer.hpp"

#include <ImGuiFileDialog/ImGuiFileDialog.h>

namespace Neat {
EditorLayer::EditorLayer(const Ref<EventDispatcher> &eventDispatcher)
    : m_scene{makeRef<Scene>(eventDispatcher)},
      m_sceneHierarchyPanel{m_scene},
      m_eventDispatcher{eventDispatcher},
      m_editorCamera{PerspectiveProperties{30.0f}, eventDispatcher} {
  eventDispatcher->get<MouseScrolledEvent>()
      .connect<&EditorLayer::onMouseScrolled>(*this, EventPriorityHighest);
  eventDispatcher->get<KeyPressedEvent>().connect<&EditorLayer::onKeyPressed>(
      *this, EventPriorityHighest);

  // TODO support this on the UI
  // m_checkerboardTexture->setMinification(Texture2DFilter::Nearest);
  // m_checkerboardTexture->setMagnification(Texture2DFilter::Nearest);
  // m_checkerboardTexture->setWrapS(Texture2DWrapping::ClampToEdge);

  FrameBufferSpecification specification{1600, 900};
  m_frameBuffer = FrameBuffer::create(specification);
}

EditorLayer::~EditorLayer() {}

void EditorLayer::onImGuiRender() {
  bool open = true;
  bool *p_open = &open;
  // READ THIS !!!
  // TL;DR; this demo is more complicated than what most users you would
  // normally use. If we remove all options we are showcasing, this demo would
  // become:
  //     void ShowExampleAppDockSpace()
  //     {
  //         ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
  //     }
  // In most cases you should be able to just call DockSpaceOverViewport() and
  // ignore all the code below! In this specific demo, we are not using
  // DockSpaceOverViewport() because:
  // - (1) we allow the host window to be floating/moveable instead of filling
  // the viewport (when opt_fullscreen == false)
  // - (2) we allow the host window to have padding (when opt_padding == true)
  // - (3) we expose many flags and need a way to have them visible.
  // - (4) we have a local menu bar in the host window (vs. you could use
  // BeginMainMenuBar() + DockSpaceOverViewport()
  //      in your code, but we don't here because we allow the window to be
  //      floating)

  static bool opt_fullscreen = true;
  static bool opt_padding = false;
  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

  // We are using the ImGuiWindowFlags_NoDocking flag to make the parent
  // window not dockable into, because it would be confusing to have two
  // docking targets within each others.
  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
  if (opt_fullscreen) {
    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |=
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
  } else {
    dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
  }

  // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will
  // render our background and handle the pass-thru hole, so we ask Begin() to
  // not render a background.
  if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
    window_flags |= ImGuiWindowFlags_NoBackground;

  // Important: note that we proceed even if Begin() returns false (aka window
  // is collapsed). This is because we want to keep our DockSpace() active. If
  // a DockSpace() is inactive, all active windows docked into it will lose
  // their parent and become undocked. We cannot preserve the docking
  // relationship between an active window and an inactive docking, otherwise
  // any change of dockspace/settings would lead to windows being stuck in
  // limbo and never being visible.
  if (!opt_padding)
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("DockSpace Demo", p_open, window_flags);
  if (!opt_padding) ImGui::PopStyleVar();

  if (opt_fullscreen) ImGui::PopStyleVar(2);

  // Submit the DockSpace
  ImGuiIO &io = ImGui::GetIO();
  ImGuiStyle &style = ImGui::GetStyle();
  float minWinSizeX = style.WindowMinSize.x;
  style.WindowMinSize.x = 370.0f;

  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
  }

  style.WindowMinSize.x = minWinSizeX;

  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Exit")) {
        Application::get().close();
      }

      if (ImGui::MenuItem("New", "Ctrl + N")) {
        newScene();
      }

      if (ImGui::MenuItem("Save As...", "Ctrl + Shift + S")) {
        openSaveFileAsDialog();
      }

      if (ImGui::MenuItem("Open File...", "Ctrl + O")) {
        openOpenFileDialog();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }

  if (ImGuiFileDialog::Instance()->Display("OpenFileDialog")) {
    handleOpenFileDialog();
  }

  if (ImGuiFileDialog::Instance()->Display("SaveFileAsDialog")) {
    handleSaveFileAsDialog();
  }

  m_sceneHierarchyPanel.onUpdate();

  auto stats = Renderer2D::getStats();
  ImGui::Begin("Example Layer");
  ImGui::Text("Renderer2D stats:");
  ImGui::Text("Draw calls: %d", stats.drawCalls);
  ImGui::Text("Quads: %d", stats.quadCount);
  ImGui::Text("Indexes: %d", stats.getTotalIndexCount());
  ImGui::Text("Vertexes: %d\n", stats.getTotalVertexCount());
  ImGui::End();

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
  ImGui::Begin("Viewport");
  m_viewportFocused = ImGui::IsWindowFocused();
  m_viewportHovered = ImGui::IsWindowHovered();
  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  m_newViewportSize = Vector2U{static_cast<UInt32>(viewportPanelSize.x),
                               static_cast<UInt32>(viewportPanelSize.y)};
  UInt32 textureID = m_frameBuffer->getColorAttachmentID();
  ImGui::Image(static_cast<ImTextureID>(textureID),
               ImVec2{static_cast<float>(m_viewportSize.x()),
                      static_cast<float>(m_viewportSize.y())},
               ImVec2{0, 1}, ImVec2{1, 0});
  ImGui::PopStyleVar();
  ImGui::End();

  ImGui::End();
}

void EditorLayer::onUpdate(double deltaTimeSeconds) {
  if (m_viewportSize != m_newViewportSize) {
    NT_CORE_TRACE("Resizing framebuffer to ({}, {})", m_newViewportSize.x(),
                  m_newViewportSize.y());
    m_viewportSize = m_newViewportSize;
    m_scene->setViewport(m_viewportSize.x(), m_viewportSize.y());
    m_frameBuffer->resize(m_viewportSize.x(), m_viewportSize.y());
    m_editorCamera.setViewportSize(m_viewportSize.x(), m_viewportSize.y());
  }

  if (m_viewportFocused) {
    m_scene->getSystemManager()->onUpdate<OrthographicCameraControllerSystem>(
        deltaTimeSeconds);
  }

  m_editorCamera.onUpdate(deltaTimeSeconds);

  m_frameBuffer->bind();
  m_scene->onEditorUpdate(deltaTimeSeconds, m_editorCamera);
  m_frameBuffer->unbind();

  onImGuiRender();
}

bool EditorLayer::onKeyPressed(const KeyPressedEvent &event) {
  if (event.repeatCount > 0) {
    return false;
  }

  bool controlPressed = Input::isKeyPressed(Key::LeftControl) or
                        Input::isKeyPressed(Key::RightControl);
  bool shiftPressed = Input::isKeyPressed(Key::LeftShift) or
                      Input::isKeyPressed(Key::RightShift);

  switch (event.key) {
    case Key::N:
      if (controlPressed) {
        newScene();
        return true;
      }
      break;
    case Key::O:
      if (controlPressed) {
        openOpenFileDialog();
        return true;
      }
      break;
    case Key::S:
      if (controlPressed and shiftPressed) {
        openSaveFileAsDialog();
        return true;
      }
      break;
    default:
      return false;
  }

  return false;
}

void EditorLayer::newScene() {
  m_scene = makeRef<Scene>(m_eventDispatcher);
  m_scene->setViewport(m_viewportSize.x(), m_viewportSize.y());
  m_sceneHierarchyPanel.setScene(m_scene);
}

void EditorLayer::openSaveFileAsDialog() {
  IGFD::FileDialogConfig config;
  config.path = ".";
  ImGuiFileDialog::Instance()->OpenDialog("SaveFileAsDialog", "Choose File",
                                          ".neat", config);
}

void EditorLayer::openOpenFileDialog() {
  IGFD::FileDialogConfig config;
  config.path = ".";
  ImGuiFileDialog::Instance()->OpenDialog("OpenFileDialog", "Choose File",
                                          ".neat", config);
}

void EditorLayer::handleOpenFileDialog() {
  if (ImGuiFileDialog::Instance()->IsOk()) {
    std::string filepath = ImGuiFileDialog::Instance()->GetFilePathName();
    m_scene = makeRef<Scene>(m_eventDispatcher);
    m_scene->setViewport(m_viewportSize.x(), m_viewportSize.y());
    m_sceneHierarchyPanel.setScene(m_scene);
    SceneSerializer serializer{m_scene};
    serializer.deserialize(filepath);
  }
  ImGuiFileDialog::Instance()->Close();
}

void EditorLayer::handleSaveFileAsDialog() {
  if (ImGuiFileDialog::Instance()->IsOk()) {
    std::string filepath = ImGuiFileDialog::Instance()->GetFilePathName();
    SceneSerializer serializer(m_scene);
    serializer.serialize(filepath);
  }
  ImGuiFileDialog::Instance()->Close();
}
}  // namespace Neat