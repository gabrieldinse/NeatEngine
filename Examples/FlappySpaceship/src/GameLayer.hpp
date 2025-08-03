#include <memory>

#include "Neat/ImGui/ImGuiRender.hpp"
#include <Neat.hpp>

class GameLayer : public Neat::Layer {
public:
  GameLayer(const Neat::Ref<Neat::EventDispatcher> &eventManager);
  ~GameLayer() = default;

  virtual void onUpdate(double deltaTimeSeconds) override;

private:
  Neat::Ref<Neat::SystemManager> m_systems;
  Neat::Ref<Neat::EntityManager> m_entities;

  Neat::Ref<Neat::Texture2D> m_spaceshipTexture;
  Neat::Ref<Neat::Texture2D> m_pillarTexture;
};