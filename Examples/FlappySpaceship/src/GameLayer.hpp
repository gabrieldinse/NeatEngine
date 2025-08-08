#include <memory>
#include <utility>

#include "Neat/ImGui/ImGuiRender.hpp"
#include <Neat.hpp>

#include <ImGui/imgui.h>

struct PillarTag {};
struct BackgroundTag {};
struct PillarBackgroundTag {};

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
  void play(float deltaTimeSeconds);
  void mainMenu();
  void gameOver();
  void onImGui();
  void onPlayerUpdate(float deltaTimeSeconds);
  void onBackgroundUpdate();
  void onPillarUpdate();
  std::pair<float, float> genPillarsYPositions();
  void collisionTest();
  bool onCollisionEvent(const CollisionEvent &event) {
    m_gameState = GameState::GameOver;
    return true;
  }
  bool onMouseButtonPressedEvent(const Neat::MouseButtonPressedEvent &event);
  bool onWindowResizeEvent(const Neat::WindowResizeEvent &event);
  unsigned getScore() {
    return static_cast<unsigned>(
        (m_player.getComponent<Neat::TransformComponent>()->position.x + 10.f) /
        10.0f);
  }
  static bool pointInTriangle(const Neat::Vector2F &p, const Neat::Vector2F &p0,
                              const Neat::Vector2F &p1,
                              const Neat::Vector2F &p2);

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
  Neat::Entity m_player;
  ImFont *m_fontSmall;
  ImFont *m_font;
  Neat::Vector3F m_pillarHSV;
  Neat::Vector4F m_pilllarRGB;
};