#include <memory>

#include "SceneHierarchyPanel.hpp"

#include "Neat.hpp"
#include "Neat/ImGui/ImGuiRender.hpp"
#include "Neat/Scene/Scene.hpp"
#include "Neat/Scene/EditorCamera.hpp"

#include <ImGui/imgui.h>

namespace Neat {
class EditorLayer : public Layer {
 public:
  EditorLayer(const Ref<EventDispatcher> &eventManager);
  ~EditorLayer();

  void onImGuiRender();
  virtual void onUpdate(double deltaTimeSeconds) override;
  bool onMouseScrolled([[maybe_unused]] const MouseScrolledEvent &event) {
    return not m_viewportFocused && not m_viewportHovered;
  }
  bool onKeyPressed(const KeyPressedEvent &event);

 private:
  void newScene();
  void handleOpenFileDialog();
  void handleSaveFileAsDialog();
  void handleGizmos();
  void saveFile();
  void openOpenFileDialog();
  void openSaveFileAsDialog();

 private:
  Ref<Scene> m_scene;
  SceneHierarchyPanel m_sceneHierarchyPanel;
  Ref<EventDispatcher> m_eventDispatcher;
  EditorCamera m_editorCamera;

  Ref<FrameBuffer> m_frameBuffer;
  bool m_viewportFocused = false;
  bool m_viewportHovered = false;

  Vector2U m_viewportSize{0, 0};
  Vector2U m_newViewportSize{0, 0};
  Vector2U m_viewportBounds[2];

  std::string m_openedFilepath;

  int m_gizmoType = -1;
};
}  // namespace Neat