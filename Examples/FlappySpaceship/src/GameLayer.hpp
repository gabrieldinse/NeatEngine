#include <memory>
#include <utility>

#include "Neat/ImGui/ImGuiRender.hpp"
#include <Neat.hpp>

struct PillarTag {};
struct PlayerTag {};
struct BrackgroundTag {};
struct PlayerVelocity {
  Neat::Vector2F value{5.0f, 0.0f};
};

enum class GameState { MainMenu, Playing, GameOver };

struct CollisionEvent {};

class GameLayer : public Neat::Layer {
public:
  GameLayer(const Neat::Ref<Neat::EventDispatcher> &eventManager);
  ~GameLayer() = default;

  void init();
  virtual void onUpdate(double deltaTimeSeconds) override;

private:
  void onImGui();
  void play(float deltaTimeSeconds);
  Neat::Vector2F onPlayerUpdate(float deltaTimeSeconds);
  void onBackgroundUpdate(Neat::Vector2F playerPosition);
  void onPillarUpdate(Neat::Vector2F playerPosition);
  std::pair<float, float> genPillarsYPositions();
  void collisionTest();
  bool onCollisionEvent(const CollisionEvent &event) {
    m_gameState = GameState::GameOver;
    return true;
  }

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
  GameState m_gameState{GameState::MainMenu};
};