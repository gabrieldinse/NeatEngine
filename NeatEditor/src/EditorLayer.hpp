#include <memory>

#include "Neat.hpp"
#include "Neat/ImGui/ImGuiRender.hpp"
#include "Neat/Scene/Scene.hpp"
#include "SceneHierarchyPanel.hpp"

#include <ImGui/imgui.h>

namespace Neat {
class EditorLayer : public Layer {
 public:
  EditorLayer(const Ref<EventDispatcher> &eventManager);
  ~EditorLayer();

  void onImGuiRender();
  virtual void onUpdate(double deltaTimeSeconds) override;
  bool onMouseScrolled([[maybe_unused]] const MouseScrolledEvent &event) {
    return not m_viewportFocused or not m_viewportHovered;
  }
  bool onKeyPressed(const KeyPressedEvent &event);

 private:
  void newScene();
  void handleOpenFileDialog();
  void handleSaveFileAsDialog();
  void openOpenFileDialog();
  void openSaveFileAsDialog();

 private:
  Ref<Scene> m_scene;
  SceneHierarchyPanel m_sceneHierarchyPanel;
  Ref<EventDispatcher> m_eventDispatcher;

  Ref<FrameBuffer> m_frameBuffer;
  bool m_viewportFocused = false;
  bool m_viewportHovered = false;

  Vector2U m_viewportSize{0, 0};
  Vector2U m_newViewportSize{0, 0};
};
}  // namespace Neat