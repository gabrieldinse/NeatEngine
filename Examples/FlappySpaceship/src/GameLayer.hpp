#include <memory>

#include "Neat/ImGui/ImGuiRender.hpp"
#include <Neat.hpp>

struct PillarTag {};
struct PlayerTag {};
struct BrackgroundTag {};
struct PlayerVelocity {
  Neat::Vector2F value{5.0f, 0.0f};
};

class GameLayer : public Neat::Layer {
public:
  GameLayer(const Neat::Ref<Neat::EventDispatcher> &eventManager);
  ~GameLayer() = default;

  void init();
  virtual void onUpdate(double deltaTimeSeconds) override;
  void onImGui();

private:
  Neat::Ref<Neat::EventDispatcher> m_eventDispatcher;
  Neat::Ref<Neat::OrthographicCamera> m_camera;
  Neat::Ref<Neat::SystemManager> m_systems;
  Neat::Ref<Neat::EntityManager> m_entities;

  Neat::Ref<Neat::Texture2D> m_spaceshipTexture;
  Neat::Ref<Neat::Texture2D> m_pillarTexture;
  int m_numPillars = 5;
  float m_gravity = 20.0f;
  float m_engineForce = 80.0f;
  float m_movePillarThresholdPosX;
};