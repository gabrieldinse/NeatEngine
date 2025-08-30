#include <memory>

#include "EditorLayer.hpp"

namespace Neat {
EditorLayer::EditorLayer(const Ref<EventDispatcher> &eventDispatcher)
    : m_scene(makeRef<Scene>(eventDispatcher)),
      m_checkerboardTexture{Texture2D::create("assets/textures/texture1.png")},
      m_spritesheetTexture{
          Texture2D::create("assets/textures/spritesheet1.png")} {
  eventDispatcher->get<MouseScrolledEvent>()
      .connect<&EditorLayer::onMouseScrolled>(*this, EventPriorityHighest);

  m_sceneHierarchyPanel.setScene(m_scene);

  // Set values different from the default
  m_checkerboardTexture->setMinification(Texture2DFilter::Nearest);
  m_checkerboardTexture->setMagnification(Texture2DFilter::Nearest);
  m_checkerboardTexture->setWrapS(Texture2DWrapping::ClampToEdge);

  auto checkerboardQuad = m_scene->createEntity();
  checkerboardQuad.addComponent<RenderableSpriteComponent>(
      this->m_checkerboardTexture, Vector4F{0.8f, 0.4f, 0.3f, 0.75f}, 5.0f);
  checkerboardQuad.addComponent<TransformComponent>(
      Vector3F{0.0f, 0.0f, 0.5f}, Vector3F{1.0f, 1.0f, 1.0f},
      Vector3F{0.0f, 0.0f, 45.0f});
  checkerboardQuad.addComponent<LabelComponent>("Checkerboard Quad");

  FrameBufferSpecification specification{1280, 720};
  m_frameBuffer = FrameBuffer::create(specification);
}

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
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
  }

  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Exit")) {
        Application::get().close();
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Options")) {
      if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "",
                          (dockspace_flags &
                           ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) {
        dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode;
      }
      if (ImGui::MenuItem(
              "Flag: NoDockingSplit", "",
              (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0)) {
        dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit;
      }
      if (ImGui::MenuItem(
              "Flag: NoUndocking", "",
              (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0)) {
        dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking;
      }
      if (ImGui::MenuItem(
              "Flag: NoResize", "",
              (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) {
        dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
      }
      if (ImGui::MenuItem(
              "Flag: AutoHideTabBar", "",
              (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) {
        dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
      }
      if (ImGui::MenuItem(
              "Flag: PassthruCentralNode", "",
              (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0,
              opt_fullscreen)) {
        dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
      }
      ImGui::Separator();

      if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
        *p_open = false;
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
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
               ImVec2{static_cast<float>(m_viewportSize.x),
                      static_cast<float>(m_viewportSize.y)},
               ImVec2{0, 1}, ImVec2{1, 0});
  ImGui::PopStyleVar();
  ImGui::End();

  ImGui::End();
}

void EditorLayer::onUpdate(double deltaTimeSeconds) {
  if (m_viewportSize != m_newViewportSize) {
    NT_CORE_TRACE("Resizing framebuffer to ({}, {})", m_newViewportSize.x,
                  m_newViewportSize.y);
    m_viewportSize = m_newViewportSize;
    m_scene->setViewport(m_viewportSize.x, m_viewportSize.y);
    m_frameBuffer->resize(m_viewportSize.x, m_viewportSize.y);
  }

  if (m_viewportFocused) {
    // TODO review
    m_scene->getSystems()->onUpdate<OrthographicCameraControllerSystem>(
        deltaTimeSeconds);
  }

  m_frameBuffer->bind();
  m_scene->onUpdate(deltaTimeSeconds);
  m_frameBuffer->unbind();

  onImGuiRender();
}
}  // namespace Neat