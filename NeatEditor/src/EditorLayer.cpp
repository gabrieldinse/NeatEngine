#include <memory>

#include "EditorLayer.hpp"
#include "Neat/Scene/SceneSerializer.hpp"

#include <ImGuiFileDialog/ImGuiFileDialog.h>
#include <ImGuizmo/ImGuizmo.h>

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
  eventDispatcher->get<MouseButtonPressedEvent>()
      .connect<&EditorLayer::onMouseButtonPressed>(*this, EventPriorityHighest);

  // TODO support this on the UI
  // m_checkerboardTexture->setMinification(Texture2DFilter::Nearest);
  // m_checkerboardTexture->setMagnification(Texture2DFilter::Nearest);
  // m_checkerboardTexture->setWrapS(Texture2DWrapping::ClampToEdge);

  FramebufferSpecification specification{
      1600,
      900,
      {FramebufferColorFormat::RGBA8, FramebufferColorFormat::OneUInt32},
      FramebufferDepthFormat::Depth24Stencil8};
  m_framebuffer = Framebuffer::create(specification);
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

      if (ImGui::MenuItem("Save", "Ctrl + S")) {
        saveFile();
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
  ImGui::Begin("Stats");
  std::string entityLabel{"None"};
  if (m_hoveredEntity) {
    if (m_hoveredEntity.hasComponent<LabelComponent>()) {
      entityLabel = m_hoveredEntity.getComponent<LabelComponent>()->label;
    } else {
      entityLabel = "Unnamed Entity";
    }
  }
  ImGui::Text("Hovered Entity: %s", entityLabel.c_str());
  ImGui::Text("Number of draw calls: %d", stats.drawCalls);
  ImGui::Text("Number of quads: %d", stats.quadCount);
  ImGui::Text("Number of indexes: %d", stats.getTotalIndexCount());
  ImGui::Text("Number of vertexes: %d\n", stats.getTotalVertexCount());
  ImGui::End();

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
  ImGui::Begin("Viewport");
  auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
  auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
  auto viewportOffset = ImGui::GetWindowPos();
  m_viewportBounds[0] = {viewportMinRegion.x + viewportOffset.x,
                         viewportMinRegion.y + viewportOffset.y};
  m_viewportBounds[1] = {viewportMaxRegion.x + viewportOffset.x,
                         viewportMaxRegion.y + viewportOffset.y};
  m_viewportFocused = ImGui::IsWindowFocused();
  m_viewportHovered = ImGui::IsWindowHovered();
  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  m_newViewportSize = Vector2U{static_cast<UInt32>(viewportPanelSize.x),
                               static_cast<UInt32>(viewportPanelSize.y)};
  UInt32 textureID = m_framebuffer->getColorAttachmentID();
  ImGui::Image(static_cast<ImTextureID>(textureID),
               ImVec2{static_cast<float>(m_viewportSize.x()),
                      static_cast<float>(m_viewportSize.y())},
               ImVec2{0, 1}, ImVec2{1, 0});
  handleGizmos();
  ImGui::End();
  ImGui::PopStyleVar();

  ImGui::End();
}

void EditorLayer::onUpdate(double deltaTimeSeconds) {
  if (m_viewportSize != m_newViewportSize) {
    NT_CORE_TRACE("Resizing framebuffer to ({}, {})", m_newViewportSize.x(),
                  m_newViewportSize.y());
    m_viewportSize = m_newViewportSize;
    m_scene->setViewport(m_viewportSize.x(), m_viewportSize.y());
    m_framebuffer->resize(m_viewportSize.x(), m_viewportSize.y());
    m_editorCamera.setViewport(m_viewportSize.x(), m_viewportSize.y());
  }

  m_editorCamera.onUpdate(deltaTimeSeconds);

  m_framebuffer->bind();
  m_framebuffer->clearUInt32ColorAttachment(1, Entity::ID::InvalidIndex);
  m_scene->onEditorUpdate(deltaTimeSeconds, m_editorCamera);

  //auto [mx, my] = ImGui::GetMousePos();
  //mx -= static_cast<float>(m_viewportBounds[0].x());
  //my -= static_cast<float>(m_viewportBounds[0].y());
  //Vector2I viewportSize{m_viewportBounds[1] - m_viewportBounds[0]};
  //my = static_cast<float>(viewportSize.y()) - my;
  //int mouseX = static_cast<int>(mx);
  //int mouseY = static_cast<int>(my);

  //if (mouseX >= 0 and mouseY >= 0 and mouseX < viewportSize.x() and
  //    mouseY < viewportSize.y()) {
  //  NT_CORE_TRACE("Mouse coordinates: ({}, {})", mouseX, mouseY);
  //  NT_CORE_TRACE("Viewport size: ({}, {})", viewportSize.x(),
  //                viewportSize.y());
  //  UInt32 entityIndex = m_framebuffer->getUInt32Pixel(
  //      1, Vector2U{static_cast<UInt32>(mouseX), static_cast<UInt32>(mouseY)});
  //  NT_CORE_TRACE("Hovered entity index: {}", entityIndex);
  //  m_hoveredEntity = m_scene->getEntityManager()->getEntity(entityIndex);
  //}

  onImGuiRender();
  m_framebuffer->unbind();
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
      if (controlPressed) {
        if (shiftPressed) {
          openSaveFileAsDialog();
        } else {
          saveFile();
        }
        return true;
      }
      break;
    case Key::Q:
      if (not ImGuizmo::IsUsing()) {
        m_gizmoType = -1;
        return true;
      }
      break;
    case Key::W:
      if (not ImGuizmo::IsUsing()) {
        m_gizmoType = ImGuizmo::OPERATION::TRANSLATE;
        return true;
      }
      break;
    case Key::E:
      if (not ImGuizmo::IsUsing()) {
        m_gizmoType = ImGuizmo::OPERATION::ROTATE;
        return true;
      }
      break;
    case Key::R:
      if (not ImGuizmo::IsUsing()) {
        m_gizmoType = ImGuizmo::OPERATION::SCALE;
        return true;
      }
      break;
    default:
      return false;
  }

  return false;
}

bool EditorLayer::onMouseButtonPressed(const MouseButtonPressedEvent &event) {
  if (event.button == MouseButton::Left) {
    if (m_hoveredEntity and m_viewportHovered and not ImGuizmo::IsOver() &&
        not Input::isKeyPressed(Key::LeftAlt)) {
      m_sceneHierarchyPanel.setSelectedEntity(m_hoveredEntity);
    }
  }

  return false;
}

void EditorLayer::newScene() {
  m_scene = makeRef<Scene>(m_eventDispatcher);
  m_scene->setViewport(m_viewportSize.x(), m_viewportSize.y());
  m_sceneHierarchyPanel.setScene(m_scene);
}

void EditorLayer::handleGizmos() {
  Entity &selectedEntity = m_sceneHierarchyPanel.getSelectedEntity();
  if (selectedEntity.isValid() and
      selectedEntity.hasComponent<TransformComponent>() and m_gizmoType != -1) {
    ImGuizmo::SetOrthographic(false);
    ImGuizmo::Enable(true);
    ImGuizmo::SetDrawlist();
    ImGuizmo::SetRect(m_viewportBounds[0].x(), m_viewportBounds[0].y(),
                      m_viewportBounds[1].x() - m_viewportBounds[0].x(),
                      m_viewportBounds[1].y() - m_viewportBounds[0].y());

    Matrix4F transposeCameraView{transpose(m_editorCamera.getViewMatrix())};
    Matrix4F transposeCameraProjection{
        transpose(m_editorCamera.getProjection())};

    auto entityTransform = selectedEntity.getComponent<TransformComponent>();
    Matrix4F transposeEntityModel{transpose(entityTransform->getTransform())};

    // Snapping
    bool snap = Input::isKeyPressed(Key::LeftControl);
    float snapValue = 0.5f;  // Snap to 0.5m for translation/scale
    // Snap to 45 degrees for rotation
    if (m_gizmoType == ImGuizmo::OPERATION::ROTATE) {
      snapValue = 45.0f;
    }

    std::array<float, 3> snapValues{snapValue, snapValue, snapValue};

    bool manipulate = ImGuizmo::Manipulate(
        transposeCameraView.data(), transposeCameraProjection.data(),
        static_cast<ImGuizmo::OPERATION>(m_gizmoType), ImGuizmo::LOCAL,
        transposeEntityModel.data(), nullptr,
        snap ? snapValues.data() : nullptr);

    if (manipulate && ImGuizmo::IsUsing()) {
      Vector3F position, rotation, scaling;
      ImGuizmo::DecomposeMatrixToComponents(transposeEntityModel.data(),
                                            position.data(), rotation.data(),
                                            scaling.data());

      Vector3F deltaRotation = rotation - entityTransform->rotation;
      entityTransform->position = position;
      entityTransform->rotation += deltaRotation;
      entityTransform->scaling = scaling;
    }
  }
}

void EditorLayer::saveFile() {
  if (m_openedFilepath.empty()) {
    openSaveFileAsDialog();
  } else {
    SceneSerializer serializer(m_scene);
    serializer.serialize(m_openedFilepath);
  }
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
    m_openedFilepath = ImGuiFileDialog::Instance()->GetFilePathName();
    m_scene = makeRef<Scene>(m_eventDispatcher);
    m_scene->setViewport(m_viewportSize.x(), m_viewportSize.y());
    m_sceneHierarchyPanel.setScene(m_scene);
    SceneSerializer serializer{m_scene};
    serializer.deserialize(m_openedFilepath);
  }
  ImGuiFileDialog::Instance()->Close();
}

void EditorLayer::handleSaveFileAsDialog() {
  if (ImGuiFileDialog::Instance()->IsOk()) {
    m_openedFilepath = ImGuiFileDialog::Instance()->GetFilePathName();
    SceneSerializer serializer(m_scene);
    serializer.serialize(m_openedFilepath);
  }
  ImGuiFileDialog::Instance()->Close();
}
}  // namespace Neat