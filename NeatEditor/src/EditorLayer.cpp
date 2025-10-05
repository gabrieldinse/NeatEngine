#include <memory>

#include "EditorLayer.hpp"

#include "Neat/Scene/SceneSerializer.hpp"
#include "Neat/ImGui/ImGuiTools.hpp"

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

  FramebufferSpecification specification{
      1600,
      900,
      {FramebufferColorFormat::RGBA8, FramebufferColorFormat::OneUInt32},
      FramebufferDepthFormat::Depth24Stencil8};
  m_framebuffer = Framebuffer::create(specification);

  m_playIcon =
      Texture2D::create("./NeatEditorAssets/Resources/Icons/PlayButton.png");
  m_stopIcon =
      Texture2D::create("./NeatEditorAssets/Resources/Icons/StopButton.png");
}

EditorLayer::~EditorLayer() {}

void EditorLayer::startDockSpace() {
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
}

void EditorLayer::onImGuiRender() {
  startDockSpace();
  onMenuUpdate();
  m_sceneHierarchyPanel.onUpdate();
  m_contentBrowserPanel.onUpdate();
  ImGuiTools::onStatsUpdate(m_hoveredEntity);
  onViewportUpdate();
  onUIToolbarUpdate();
  endDockSpace();
}

void EditorLayer::endDockSpace() {
  ImGui::End();  // DockSpace
}

void EditorLayer::onMenuUpdate() {
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
}

void EditorLayer::onUpdate(double deltaTimeSeconds) {
  handleViewportResized();
  m_framebuffer->bind();
  m_framebuffer->clearUInt32ColorAttachment(1, Entity::ID::InvalidIndex);
  onSceneUpdate(deltaTimeSeconds);
  handleEntityHovered();
  onImGuiRender();
  m_framebuffer->unbind();
}

void EditorLayer::handleViewportResized() {
  if (m_viewportSize != m_newViewportSize) {
    NT_CORE_TRACE("Resizing framebuffer to ({}, {})", m_newViewportSize.x(),
                  m_newViewportSize.y());
    m_viewportSize = m_newViewportSize;
    m_scene->setViewport(m_viewportSize.x(), m_viewportSize.y());
    m_framebuffer->resize(m_viewportSize.x(), m_viewportSize.y());
    m_editorCamera.setViewport(m_viewportSize.x(), m_viewportSize.y());
  }
}

void EditorLayer::onSceneUpdate(double deltaTimeSeconds) {
  switch (m_sceneState) {
    case SceneState::Edit:
      m_editorCamera.onUpdate(deltaTimeSeconds);
      m_scene->onEditorUpdate(deltaTimeSeconds, m_editorCamera);
      break;
    case SceneState::Play:
      m_scene->onRuntimeUpdate(deltaTimeSeconds);
      break;
  }
}

void EditorLayer::onViewportUpdate() {
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
  ImGui::Begin("Viewport", nullptr,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                   ImGuiWindowFlags_NoScrollbar |
                   ImGuiWindowFlags_NoScrollWithMouse |
                   ImGuiWindowFlags_NoDecoration);
  if (ImGui::IsWindowDocked()) {
    ImGuiDockNode *node = ImGui::GetWindowDockNode();
    if (node) node->LocalFlags |= ImGuiDockNodeFlags_HiddenTabBar;
  }
  auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
  auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
  auto viewportOffset = ImGui::GetWindowPos();
  m_viewportBounds[0] = {viewportMinRegion.x + viewportOffset.x,
                         viewportMinRegion.y + viewportOffset.y};
  m_viewportBounds[1] = {viewportMaxRegion.x + viewportOffset.x,
                         viewportMaxRegion.y + viewportOffset.y};
  m_viewportFocused = ImGui::IsWindowFocused();
  m_viewportHovered = ImGui::IsWindowHovered();
  m_newViewportSize = m_viewportBounds[1] - m_viewportBounds[0];
  UInt32 textureID = m_framebuffer->getColorAttachmentID();
  ImGui::Image(static_cast<ImTextureID>(textureID),
               ImVec2{static_cast<float>(m_viewportSize.x()),
                      static_cast<float>(m_viewportSize.y())},
               ImVec2{0, 1}, ImVec2{1, 0});

  if (ImGui::BeginDragDropTarget()) {
    const ImGuiPayload *dragDropPayload =
        ImGui::AcceptDragDropPayload("Content Browser Item");
    if (dragDropPayload) {
      const char *relativePath =
          static_cast<const char *>(dragDropPayload->Data);
      std::filesystem::path sceneFilepath{
          (std::filesystem::path(ContentBrowserPanel::getAssetsPath()) /
           relativePath)};
      std::string sceneFilepathStr{sceneFilepath.string()};
      openScene(sceneFilepathStr);
    }
    ImGui::EndDragDropTarget();
  }

  handleGizmos();
  ImGui::PopStyleVar();
  ImGui::End();  // Viewport
}

void EditorLayer::onUIToolbarUpdate() {
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 2});
  ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2{0, 0});

  const auto &imGuiColors = ImGui::GetStyle().Colors;
  const auto &buttonHoveredColor = imGuiColors[ImGuiCol_ButtonHovered];
  const auto &buttonActiveColor = imGuiColors[ImGuiCol_ButtonActive];

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0, 0, 0, 0});
  ImGui::PushStyleColor(
      ImGuiCol_ButtonHovered,
      ImVec4{buttonHoveredColor.x, buttonHoveredColor.y, buttonHoveredColor.z,
             buttonHoveredColor.w * 0.5f});
  ImGui::PushStyleColor(
      ImGuiCol_ButtonActive,
      ImVec4{buttonActiveColor.x, buttonActiveColor.y, buttonActiveColor.z,
             buttonActiveColor.w * 0.5f});

  ImGui::Begin("Toolbar", nullptr,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                   ImGuiWindowFlags_NoScrollbar |
                   ImGuiWindowFlags_NoScrollWithMouse |
                   ImGuiWindowFlags_NoDecoration);
  if (ImGui::IsWindowDocked()) {
    ImGuiDockNode *node = ImGui::GetWindowDockNode();
    if (node) node->LocalFlags |= ImGuiDockNodeFlags_HiddenTabBar;
  }
  float size = ImGui::GetWindowHeight() - 4.0f;

  Ref<Texture2D> icon =
      m_sceneState == SceneState::Edit ? m_playIcon : m_stopIcon;
  ImGui::SetCursorPosX((ImGui::GetWindowWidth() * 0.5f) - (size * 0.5f));

  if (ImGui::ImageButton("ToolbarPlayButton",
                         static_cast<ImTextureID>(icon->getRendererID()),
                         ImVec2{size, size}, ImVec2{0, 0}, ImVec2{1, 1})) {
    if (m_sceneState == SceneState::Edit) {
      m_sceneState = SceneState::Play;
    } else if (m_sceneState == SceneState::Play) {
      m_sceneState = SceneState::Edit;
    }
  }

  ImGui::PopStyleColor(3);
  ImGui::PopStyleVar(2);
  ImGui::End();  // Toolbar
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

void EditorLayer::handleEntityHovered() {
  auto [mx, my] = ImGui::GetMousePos();
  mx -= static_cast<float>(m_viewportBounds[0].x());
  my -= static_cast<float>(m_viewportBounds[0].y());
  int mouseX = static_cast<int>(mx);
  int mouseY = static_cast<int>(my);

  if (mouseX >= 0 and mouseY >= 0 and
      mouseX < static_cast<int>(m_viewportSize.x()) and
      mouseY < static_cast<int>(m_viewportSize.y())) {
    UInt32 entityIndex = m_framebuffer->getUInt32Pixel(
        1, Vector2U{static_cast<UInt32>(mouseX), static_cast<UInt32>(mouseY)});

    if (entityIndex != Entity::ID::InvalidIndex) {
      m_hoveredEntity = m_scene->getEntityManager()->getEntity(entityIndex);
    } else {
      m_hoveredEntity = Entity{};
    }
  }
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
    openScene(ImGuiFileDialog::Instance()->GetFilePathName());
  }
  ImGuiFileDialog::Instance()->Close();
}

void EditorLayer::handleSaveFileAsDialog() {
  if (ImGuiFileDialog::Instance()->IsOk()) {
    saveScene(ImGuiFileDialog::Instance()->GetFilePathName());
  }
  ImGuiFileDialog::Instance()->Close();
}

void EditorLayer::openScene(const std::string &filepath) {
  m_scene = makeRef<Scene>(m_eventDispatcher);
  m_scene->setViewport(m_viewportSize.x(), m_viewportSize.y());
  m_sceneHierarchyPanel.setScene(m_scene);
  SceneSerializer serializer{m_scene};
  serializer.deserialize(filepath);
  m_openedFilepath = filepath;
}

void EditorLayer::saveScene(const std::string &filepath) {
  SceneSerializer serializer(m_scene);
  serializer.serialize(filepath);
  m_openedFilepath = filepath;
}
}  // namespace Neat