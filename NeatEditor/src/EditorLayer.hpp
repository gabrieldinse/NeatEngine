#include <memory>

#include <Neat.hpp>
#include "Neat/ImGui/ImGuiRender.hpp"

#include <ImGui/imgui.h>

namespace Neat {
class EditorLayer : public Layer {
 public:
  EditorLayer(const Ref<EventDispatcher> &eventManager);
  ~EditorLayer() = default;

  void onImGuiRender();
  virtual void onUpdate(double deltaTimeSeconds) override;
  bool onMouseScrolled([[maybe_unused]] const MouseScrolledEvent &event) {
    return !m_viewportFocused || !m_viewportHovered;
  }

 private:
  Ref<SystemManager> m_systems;
  Ref<EntityManager> m_entities;

  Ref<OrthographicCamera> m_camera;

  Ref<Texture2D> m_checkerboardTexture;
  Ref<Texture2D> m_spritesheetTexture;
  Ref<SubTexture2D> m_stairsTexture;
  Ref<SubTexture2D> stairsTexture2;

  Ref<FrameBuffer> m_frameBuffer;
  bool m_viewportFocused = false;
  bool m_viewportHovered = false;

  Vector2U m_viewportSize{0, 0};
  Vector2U m_newViewportSize{0, 0};
  SizeType m_numberOfColumns = 20;
  SizeType m_numberOfLines = 20;
};
}  // namespace Neat