#include <memory>

#include "ExampleLayer.hpp"

ExampleLayer::ExampleLayer(
    const Neat::Ref<Neat::EventDispatcher> &eventDispatcher)
    : m_checkerboardTexture(
          Neat::Texture2D::create("assets/textures/texture1.png")),
      m_spritesheetTexture(
          Neat::Texture2D::create("assets/textures/spritesheet1.png")),
      m_stairsTexture(Neat::SubTexture2D::createFromIndex(m_spritesheetTexture,
                                                          {7, 6}, {64, 64})),
      stairsTexture2(Neat::SubTexture2D::createFromIndex(m_spritesheetTexture,
                                                         {8, 6}, {64, 64})) {
  m_entities = Neat::makeRef<Neat::EntityManager>(eventDispatcher);
  m_systems = Neat::makeRef<Neat::SystemManager>(m_entities, eventDispatcher);
  eventDispatcher->get<Neat::WindowResizeEvent>()
      .connect<&ExampleLayer::onWindowResize>(*this);
  eventDispatcher->get<Neat::MouseMovedEvent>()
      .connect<&ExampleLayer::onMouseMoved>(*this);
  // auto q = Neat::Quaternion::fromAngleAxis(Neat::radians(45.0f),
  // Neat::Vector3F(1, 0, 0)); auto q2 = glm::angleAxis(glm::radians(45.0f),
  // glm::vec3(1.0f, 0.0f, 0.0f)); NT_TRACE(q); NT_TRACE(Neat::log(q));
  // NT_TRACE(Neat::pow(q, 0.5f));
  // NT_TRACE("");
  // NT_TRACE(glm::to_string(q2));
  // NT_TRACE(glm::to_string(glm::log(q2)));
  // NT_TRACE(glm::to_string(glm::pow(q2, 0.5f)));
  // NT_ASSERT(false, "");

  auto camera = Neat::makeRef<Neat::OrthographicCamera>(
      Neat::Vector2F{0.0f, 0.0f}, 1280.0f / 720.0f);
  auto camera_controller_system =
      m_systems->addSystem<Neat::OrthographicCameraControllerSystem>(camera);
  m_systems->addSystem<Neat::Render2DSystem>(camera);
  m_systems->init();

  for (std::size_t i = 0; i < this->numberOfLines; ++i) {
    for (std::size_t j = 0; j < this->numberOfColumns; ++j) {
      auto flatColorQuad = m_entities->createEntity();
      flatColorQuad.addComponent<Neat::RenderableSpriteComponent>(
          Neat::Vector4F{float(i) / this->numberOfLines,
                         float(j) / this->numberOfColumns, 1.0f, 1.0f});
      flatColorQuad.addComponent<Neat::TransformComponent>(
          Neat::Vector3F{0.1f * j, 0.1f * i, 0.0f},
          Neat::Vector3F{0.1f, 0.1f, 1.0f});
    }
  }

  // Set values different from the default
  m_checkerboardTexture->setMinification(Neat::Texture2DFilter::Nearest);
  m_checkerboardTexture->setMagnification(Neat::Texture2DFilter::Nearest);
  m_checkerboardTexture->setWrapS(Neat::Texture2DWrapping::ClampToEdge);

  auto checkerboardQuad = m_entities->createEntity();
  checkerboardQuad.addComponent<Neat::RenderableSpriteComponent>(
      this->m_checkerboardTexture, Neat::Vector4F{0.8f, 0.4f, 0.3f, 0.75f},
      5.0f);
  checkerboardQuad.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, 0.0f, 0.5f}, Neat::Vector3F{1.0f, 1.0f, 1.0f},
      Neat::Vector3F{0.0f, 0.0f, 45.0f});
}

void ExampleLayer::onImGuiRender() {
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

  // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window
  // not dockable into, because it would be confusing to have two docking
  // targets within each others.
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

  // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render
  // our background and handle the pass-thru hole, so we ask Begin() to not
  // render a background.
  if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
    window_flags |= ImGuiWindowFlags_NoBackground;

  // Important: note that we proceed even if Begin() returns false (aka window
  // is collapsed). This is because we want to keep our DockSpace() active. If a
  // DockSpace() is inactive, all active windows docked into it will lose their
  // parent and become undocked. We cannot preserve the docking relationship
  // between an active window and an inactive docking, otherwise any change of
  // dockspace/settings would lead to windows being stuck in limbo and never
  // being visible.
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
        Neat::Application::get().close();
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

  auto stats = Neat::Renderer2D::getStats();
  ImGui::Begin("Example Layer");
  ImGui::Text("Renderer2D stats:");
  ImGui::Text("Draw calls: %d", stats.drawCalls);
  ImGui::Text("Quads: %d", stats.quadCount);
  ImGui::Text("Indexes: %d", stats.getTotalIndexCount());
  ImGui::Text("Vertexes: %d\n", stats.getTotalVertexCount());
  ImGui::End();

  // ImGui::SliderInt("Number of columns", &this->numberOfColumns, 0, 500);
  // ImGui::SliderInt("Number of lines", &this->numberOfLines, 0, 500);

  // ImGui::ColorEdit4("Square Color", this->tint.dataPointer());
  ImGui::End();
}

void ExampleLayer::onUpdate(double deltaTimeSeconds) {
  m_systems->onUpdate<Neat::OrthographicCameraControllerSystem>(
      deltaTimeSeconds);
  m_systems->onUpdate<Neat::Render2DSystem>(deltaTimeSeconds);
  onImGuiRender();
}

bool ExampleLayer::onWindowResize(const Neat::WindowResizeEvent &event) {
  NT_CORE_INFO("Example handle window resize event.");
  return false;
}

bool ExampleLayer::onMouseMoved(
    [[maybe_unused]] const Neat::MouseMovedEvent &event) {
  // NT_CORE_TRACE("Mouse moved to ({0}, {1})", event.xPos, event.yPos);
  return false;
}