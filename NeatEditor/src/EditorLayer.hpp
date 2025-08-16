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
  bool onWindowResize(const WindowResizeEvent &event);
  bool onMouseMoved(const MouseMovedEvent &event);

 private:
  Ref<SystemManager> m_systems;
  Ref<EntityManager> m_entities;

  Ref<Texture2D> m_checkerboardTexture;
  Ref<Texture2D> m_spritesheetTexture;
  Ref<SubTexture2D> m_stairsTexture;
  Ref<SubTexture2D> stairsTexture2;

  Ref<FrameBuffer> m_frameBuffer;

  Vector4F tint = {0.8f, 0.3f, 0.2f, 1.0f};

  int numberOfColumns = 20;
  int numberOfLines = 20;
};
} // namespace Neat