#include <memory>

#include "GameLayer.hpp"

GameLayer::GameLayer(const Neat::Ref<Neat::EventDispatcher> &eventDispatcher)
    : m_eventDispatcher(eventDispatcher),
      m_spaceshipTexture(
          Neat::Texture2D::create("Resources/Textures/Ship.png")),
      m_pillarTexture(
          Neat::Texture2D::create("Resources/Textures/Triangle.png")) {
  ImGuiIO io = ImGui::GetIO();
  m_fontSmall = io.Fonts->AddFontFromFileTTF(
      "Resources/Fonts/OpenSans-Regular.ttf", 20.0f);
  m_font = io.Fonts->AddFontFromFileTTF("Resources/Fonts/OpenSans-Regular.ttf",
                                        120.0f);
  m_spaceshipTexture->setMinification(
      Neat::Texture2DFilter::LinearMipmapNearest);
  m_spaceshipTexture->setMagnification(Neat::Texture2DFilter::Nearest);
  m_eventDispatcher->get<CollisionEvent>()
      .connect<&GameLayer::onCollisionEvent>(*this);
  m_eventDispatcher->get<Neat::MouseButtonPressedEvent>()
      .connect<&GameLayer::onMouseButtonPressedEvent>(*this);
  m_eventDispatcher->get<Neat::WindowResizeEvent>()
      .connect<&GameLayer::onWindowResizeEvent>(*this);
  initialize();
}

void GameLayer::initialize() {
  m_movePillarThresholdPosX = 30.0f;
  m_pillarHSV = Neat::Vector3F{0.0f, 0.8f, 0.8f};

  m_entityManager = Neat::makeRef<Neat::EntityManager>(m_eventDispatcher);
  m_systems =
      Neat::makeRef<Neat::SystemManager>(m_entityManager, m_eventDispatcher);

  m_camera = m_entityManager->createEntity();
  m_camera.addComponent<Neat::CameraComponent>(
      Neat::OrthographicProperties{1600, 900, 16.0f});
  m_camera.addComponent<Neat::TransformComponent>(Neat::Vector2F{-10.0f, 0.0f});
  m_camera.addComponent<Neat::ActiveCameraTagComponent>();

  m_systems->addSystem<Neat::OrthographicCameraControllerSystem>();
  m_systems->addSystem<Neat::Render2DSystem>();
  m_systems->initialize();

  auto background = m_entityManager->createEntity();
  background.addComponent<Neat::RenderableSpriteComponent>(
      Neat::Color::forestBrown);
  background.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, 0.0f, -0.5f}, Neat::Vector2F{50.0f, 50.0f});
  background.addComponent<BackgroundTag>();

  auto floor = m_entityManager->createEntity();
  floor.addComponent<Neat::RenderableSpriteComponent>(Neat::Color::white);
  floor.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, -34.0f, 0.0f}, Neat::Vector2F{50.0f, 50.0f});
  floor.addComponent<BackgroundTag>();
  floor.addComponent<PillarBackgroundTag>();

  auto ceiling = m_entityManager->createEntity();
  ceiling.addComponent<Neat::RenderableSpriteComponent>(Neat::Color::white);
  ceiling.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, 34.0f, 0.0f}, Neat::Vector2F{50.0f, 50.0f});
  ceiling.addComponent<BackgroundTag>();
  ceiling.addComponent<PillarBackgroundTag>();

  for (int i = 0; i < m_numPillars; ++i) {
    auto [topPillarYPos, bottomPillarYPos] = genPillarsYPositions();
    float topPillarZPos = 0.1f * i;
    float bottomPillarZPos = 0.1f * i + 0.05f;

    auto topPillar = m_entityManager->createEntity();
    topPillar.addComponent<Neat::RenderableSpriteComponent>(m_pillarTexture);
    topPillar.addComponent<Neat::TransformComponent>(
        Neat::Vector3F{10.f * i, topPillarYPos, topPillarZPos},
        Neat::Vector2F{15.0f, 20.0f}, 180.0f);
    topPillar.addComponent<PillarTag>();

    auto bottomPillar = m_entityManager->createEntity();
    bottomPillar.addComponent<Neat::RenderableSpriteComponent>(m_pillarTexture);
    bottomPillar.addComponent<Neat::TransformComponent>(
        Neat::Vector3F{10.0f * i, bottomPillarYPos, bottomPillarZPos},
        Neat::Vector2F{15.0f, 20.0f});
    bottomPillar.addComponent<PillarTag>();
  }

  m_player = m_entityManager->createEntity();
  m_player.addComponent<Neat::RenderableSpriteComponent>(m_spaceshipTexture);
  m_player.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{-10.0f, 0.0f, 0.5f}, Neat::Vector2F{1.0f, 1.3f}, -90.0f);
  m_player.addComponent<PlayerVelocity>();
}

void GameLayer::onUpdate(double deltaTimeSeconds) {
  switch (m_gameState) {
    case GameState::Playing:
      play(deltaTimeSeconds);
      break;
    case GameState::MainMenu:
      mainMenu();
      break;
    case GameState::GameOver:
      gameOver();
      break;
  }
  // onImGui();
}

void GameLayer::play(float deltaTimeSeconds) {
  m_pillarHSV.x += 0.1f * deltaTimeSeconds;
  if (m_pillarHSV.x > 1.0f) {
    m_pillarHSV.x = 0.0f;
  }
  m_pilllarRGB = Neat::Color::HSVToRGB(m_pillarHSV);
  onPlayerUpdate(deltaTimeSeconds);
  onBackgroundUpdate();
  onPillarUpdate();
  collisionTest();
  m_camera.getComponent<Neat::TransformComponent>()->setPosition(
      m_player.getComponent<Neat::TransformComponent>()->getPosition2D());
  m_systems->onUpdate<Neat::OrthographicCameraControllerSystem>(
      deltaTimeSeconds);
  m_systems->onUpdate<Neat::Render2DSystem>(deltaTimeSeconds);
  ImGui::PushFont(m_font);
  std::string scoreString = std::string{"Score: "} + std::to_string(getScore());
  ImGui::GetForegroundDrawList()->AddText(m_font, 48.0f, ImGui::GetWindowPos(),
                                          0xffffffff, scoreString.c_str());
  ImGui::PopFont();
}

void GameLayer::mainMenu() {
  auto pos = ImGui::GetWindowPos();
  auto width = Neat::Application::get().getWindow().getWidth();
  auto height = Neat::Application::get().getWindow().getHeight();
  pos.x += width * 0.5f - 300.0f;
  pos.y += 50.0f;
  ImGui::GetForegroundDrawList()->AddText(m_font, 120.0f, pos, 0xffffffff,
                                          "Click to Play!");
}

void GameLayer::gameOver() {
  auto pos = ImGui::GetWindowPos();
  auto width = Neat::Application::get().getWindow().getWidth();
  auto height = Neat::Application::get().getWindow().getHeight();
  pos.x += width * 0.5f - 300.0f;
  pos.y += 50.0f;
  ImGui::GetForegroundDrawList()->AddText(m_font, 120.0f, pos, 0xffffffff,
                                          "Game Over!");
  std::string scoreString = std::string{"Score: "} + std::to_string(getScore());
  ImGui::GetForegroundDrawList()->AddText(m_font, 48.0f, ImGui::GetWindowPos(),
                                          0xffffffff, scoreString.c_str());
}

void GameLayer::onPlayerUpdate(float deltaTimeSeconds) {
  auto playerVelocity{m_player.getComponent<PlayerVelocity>()};
  auto playerTransform{m_player.getComponent<Neat::TransformComponent>()};
  playerTransform->incrementX(playerVelocity->value.x * deltaTimeSeconds);
  if (Neat::Input::isKeyPressed(Neat::Key::Space)) {
    playerVelocity->value.y += m_engineForce * deltaTimeSeconds;
    playerTransform->incrementY(playerVelocity->value.y * deltaTimeSeconds);
  } else {
    playerVelocity->value.y -= m_gravity * deltaTimeSeconds;
    playerTransform->incrementY(playerVelocity->value.y * deltaTimeSeconds);
  }
  playerTransform->setRotation(
      atan2(playerVelocity->value.y, playerVelocity->value.x) * 180.0f /
          Neat::pi<float> -
      90.0f);
}

void GameLayer::onBackgroundUpdate() {
  auto playerTransform{m_player.getComponent<Neat::TransformComponent>()};
  Neat::ComponentHandle<BackgroundTag> backgroundTag;
  Neat::ComponentHandle<Neat::TransformComponent> backgroundTransform;
  for ([[maybe_unused]] auto entity :
       m_entityManager
           ->entitiesWithComponents<BackgroundTag, Neat::TransformComponent>(
               backgroundTag, backgroundTransform)) {
    backgroundTransform->setX(playerTransform->position.x);
  }

  Neat::ComponentHandle<PillarBackgroundTag> pillarBackgroundTag;
  Neat::ComponentHandle<Neat::RenderableSpriteComponent> sprite;
  for ([[maybe_unused]] auto entity :
       m_entityManager->entitiesWithComponents<PillarBackgroundTag,
                                               Neat::RenderableSpriteComponent>(
           pillarBackgroundTag, sprite)) {
    sprite->color = m_pilllarRGB;
  }
}

void GameLayer::onPillarUpdate() {
  auto playerTransform{m_player.getComponent<Neat::TransformComponent>()};
  Neat::ComponentHandle<PillarTag> pillarTag;
  Neat::ComponentHandle<Neat::TransformComponent> pillarTransform;
  Neat::ComponentHandle<Neat::RenderableSpriteComponent> sprite;
  auto [topPillarYPos, bottomPillarYPos] = genPillarsYPositions();
  bool moved_pillar = false;
  for ([[maybe_unused]] auto entity :
       m_entityManager
           ->entitiesWithComponents<PillarTag, Neat::TransformComponent,
                                    Neat::RenderableSpriteComponent>(
               pillarTag, pillarTransform, sprite)) {
    sprite->color = m_pilllarRGB;
    if (playerTransform->position.x > m_movePillarThresholdPosX) {
      if (pillarTransform->position.x <= m_movePillarThresholdPosX - 25.0f) {
        NT_TRACE("Moving pillar to new position. Current {0}, New {1}",
                 pillarTransform->position.x,
                 m_movePillarThresholdPosX + 20.0f);
        if (pillarTransform->position.y > 0.0f) {
          pillarTransform->position.x = m_movePillarThresholdPosX + 20.0f;
          pillarTransform->position.y = topPillarYPos;
        } else {
          pillarTransform->position.x = m_movePillarThresholdPosX + 20.0f;
          pillarTransform->position.y = bottomPillarYPos;
        }
        moved_pillar = true;
      }
    }
  }
  if (moved_pillar) {
    m_movePillarThresholdPosX += 10.0f;
  }
}

void GameLayer::onImGui() {
  ImGui::Begin("MyWindow");
  if (ImGui::Button("Reset Game")) {
    initialize();
  }
  ImGui::SliderFloat("Gravity", &m_gravity, 0.0f, 100.0f);
  ImGui::SliderFloat("Engine Force", &m_engineForce, 0.0f, 200.0f);
  ImGui::End();
}

std::pair<float, float> GameLayer::genPillarsYPositions() {
  auto &random = Neat::Random::getInstance();
  float pillarsCenter = random.getFloat(-17.5f, 17.5f);
  float pillarsGapSize = 2.0f + random.getFloat(0.0f, 5.0f);
  float topPillarYPos =
      10.0f - ((10.0f - pillarsCenter) * 0.2f) + pillarsGapSize * 0.5f;
  float bottomPillarYPos =
      -10.0f - ((-10.0f - pillarsCenter) * 0.2f) - pillarsGapSize * 0.5f;
  return {topPillarYPos, bottomPillarYPos};
}

void GameLayer::collisionTest() {
  auto playerTransform{m_player.getComponent<Neat::TransformComponent>()};

  if (Neat::abs(playerTransform->position.y) > 8.5f) {
    m_eventDispatcher->enqueue<CollisionEvent>();
  }

  Neat::Vector4F playerVertices[4] = {{-0.5f, -0.5f, 0.0f, 1.0f},
                                      {0.5f, -0.5f, 0.0f, 1.0f},
                                      {0.5f, 0.5f, 0.0f, 1.0f},
                                      {-0.5f, 0.5f, 0.0f, 1.0f}};

  for (int i = 0; i < 4; ++i) {
    playerVertices[i] = playerTransform->getTransform() * playerVertices[i];
  }

  Neat::ComponentHandle<PillarTag> pillarTag;
  Neat::ComponentHandle<Neat::TransformComponent> pillarTransform;
  Neat::ComponentHandle<Neat::RenderableSpriteComponent> sprite;
  auto [topPillarYPos, bottomPillarYPos] = genPillarsYPositions();
  bool moved_pillar = false;
  for ([[maybe_unused]] auto entity :
       m_entityManager
           ->entitiesWithComponents<PillarTag, Neat::TransformComponent,
                                    Neat::RenderableSpriteComponent>(
               pillarTag, pillarTransform, sprite)) {
    Neat::Vector4F pillarVertices[3] = {
        {-0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f},
        {0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f},
        {0.0f + 0.0f, 0.5f - 0.1f, 0.0f, 1.0f},
    };
    for (int i = 0; i < 3; ++i) {
      pillarVertices[i] = pillarTransform->getTransform() * pillarVertices[i];
    }

    for (const auto &vert : playerVertices) {
      if (pointInTriangle({vert.x, vert.y},
                          {pillarVertices[0].x, pillarVertices[0].y},
                          {pillarVertices[1].x, pillarVertices[1].y},
                          {pillarVertices[2].x, pillarVertices[2].y})) {
        m_eventDispatcher->enqueue<CollisionEvent>();
        return;
      }
    }
  }
}

bool GameLayer::pointInTriangle(const Neat::Vector2F &p,
                                const Neat::Vector2F &p0,
                                const Neat::Vector2F &p1,
                                const Neat::Vector2F &p2) {
  float s =
      p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
  float t =
      p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

  if ((s < 0) != (t < 0)) return false;

  float A =
      -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

  return A < 0 ? (s <= 0 && s + t >= A) : (s >= 0 && s + t <= A);
}

bool GameLayer::onMouseButtonPressedEvent(
    const Neat::MouseButtonPressedEvent &event) {
  if (event.button == Neat::MouseButton::ButtonLeft) {
    if (m_gameState == GameState::GameOver) {
      initialize();
    }
    m_gameState = GameState::Playing;
  }
  return true;
}

bool GameLayer::onWindowResizeEvent(const Neat::WindowResizeEvent &event) {
  m_camera.removeComponent<Neat::CameraComponent>();
  m_camera.addComponent<Neat::CameraComponent>(
      Neat::OrthographicProperties{event.width, event.height, 8.0f});

  return true;
}