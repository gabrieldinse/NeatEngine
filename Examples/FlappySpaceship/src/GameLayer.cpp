#include <memory>

#include "GameLayer.hpp"

#include <ImGui/imgui.h>

GameLayer::GameLayer(const Neat::Ref<Neat::EventDispatcher> &eventDispatcher)
    : m_eventDispatcher(eventDispatcher),
      m_spaceshipTexture(
          Neat::Texture2D::create("Resources/Textures/Ship.png")),
      m_pillarTexture(
          Neat::Texture2D::create("Resources/Textures/Triangle.png")) {
  m_spaceshipTexture->setMinification(
      Neat::Texture2DFilter::LinearMipmapNearest);
  m_spaceshipTexture->setMagnification(Neat::Texture2DFilter::Nearest);
  init();
}

void GameLayer::init() {
  m_movePillarThresholdPosX = 30.0f;

  m_camera = Neat::makeRef<Neat::OrthographicCamera>(
      Neat::Vector2F{-10.f, 0.0f}, 1280.0f / 720.0f, 8.0f);
  m_entities = Neat::makeRef<Neat::EntityManager>(m_eventDispatcher);
  m_systems = Neat::makeRef<Neat::SystemManager>(m_entities, m_eventDispatcher);

  auto camera_controller_system =
      m_systems->addSystem<Neat::OrthographicCameraControllerSystem>(m_camera);
  m_systems->addSystem<Neat::Render2DSystem>(m_camera);

  m_systems->init();

  auto background = m_entities->createEntity();
  background.addComponent<Neat::RenderableSpriteComponent>(
      Neat::Color::forestBrown);
  background.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, 0.0f, -0.5f}, Neat::Vector2F{50.0f, 50.0f});
  background.addComponent<BrackgroundTag>();

  auto floor = m_entities->createEntity();
  floor.addComponent<Neat::RenderableSpriteComponent>(Neat::Color::white);
  floor.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, -34.0f, 0.0f}, Neat::Vector2F{50.0f, 50.0f});
  floor.addComponent<BrackgroundTag>();

  auto ceiling = m_entities->createEntity();
  ceiling.addComponent<Neat::RenderableSpriteComponent>(Neat::Color::white);
  ceiling.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, 34.0f, 0.0f}, Neat::Vector2F{50.0f, 50.0f});
  ceiling.addComponent<BrackgroundTag>();

  auto &random = Neat::Random::getInstance();
  for (int i = 0; i < m_numPillars; ++i) {
    float pillarsCenter = random.getFloat(-17.5f, 17.5f);
    float pillarsGapSize = 2.0f + random.getFloat(0.0f, 5.0f);
    float topPillarYPos =
        10.0f - ((10.0f - pillarsCenter) * 0.2f) + pillarsGapSize * 0.5f;
    float bottomPillarYPos =
        -10.0f - ((-10.0f - pillarsCenter) * 0.2f) - pillarsGapSize * 0.5f;
    float topPillarZPos = 0.1f * i;
    float bottomPillarZPos = 0.1f * i + 0.05f;

    auto topPillar = m_entities->createEntity();
    topPillar.addComponent<Neat::RenderableSpriteComponent>(m_pillarTexture);
    topPillar.addComponent<Neat::TransformComponent>(
        Neat::Vector3F{10.f * i, topPillarYPos, topPillarZPos},
        Neat::Vector2F{15.0f, 20.0f}, 180.0f);
    topPillar.addComponent<PillarTag>();

    auto bottomPillar = m_entities->createEntity();
    bottomPillar.addComponent<Neat::RenderableSpriteComponent>(m_pillarTexture);
    bottomPillar.addComponent<Neat::TransformComponent>(
        Neat::Vector3F{10.0f * i, bottomPillarYPos, bottomPillarZPos},
        Neat::Vector2F{15.0f, 20.0f});
    bottomPillar.addComponent<PillarTag>();
  }

  auto topPillar = m_entities->createEntity();
  topPillar.addComponent<Neat::RenderableSpriteComponent>(m_pillarTexture);
  topPillar.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, 10.0f, 0.0f}, Neat::Vector2F{15.0f, 20.0f}, 180.0f);

  auto spaceship = m_entities->createEntity();
  spaceship.addComponent<Neat::RenderableSpriteComponent>(m_spaceshipTexture);
  spaceship.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{-10.0f, 0.0f, 0.5f}, Neat::Vector2F{1.0f, 1.3f}, -90.0f);
  spaceship.addComponent<PlayerTag>();
  spaceship.addComponent<PlayerVelocity>();
}

void GameLayer::onUpdate(double deltaTimeSeconds) {
  onImGui();

  Neat::ComponentHandle<PlayerTag> playerTag;
  Neat::ComponentHandle<PlayerVelocity> playerVelocity;
  Neat::ComponentHandle<Neat::TransformComponent> playerTransform;
  Neat::Vector2F playerPosition;
  for ([[maybe_unused]] auto &&entity :
       m_entities->entitiesWithComponents<PlayerTag, PlayerVelocity,
                                          Neat::TransformComponent>(
           playerTag, playerVelocity, playerTransform)) {
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
    playerPosition = playerTransform->getPosition2D();
  }

  Neat::ComponentHandle<BrackgroundTag> backgroundTag;
  Neat::ComponentHandle<Neat::TransformComponent> backgroundTransform;
  for ([[maybe_unused]] auto &&entity :
       m_entities
           ->entitiesWithComponents<BrackgroundTag, Neat::TransformComponent>(
               backgroundTag, backgroundTransform)) {
    backgroundTransform->setX(playerPosition.x);
  }

  if (playerPosition.x > m_movePillarThresholdPosX) {
    Neat::ComponentHandle<PillarTag> pillarTag;
    Neat::ComponentHandle<Neat::TransformComponent> pillarTransform;
    auto &random = Neat::Random::getInstance();
    float pillarsCenter = random.getFloat(-17.5f, 17.5f);
    float pillarsGapSize = 2.0f + random.getFloat(0.0f, 5.0f);
    float topPillarYPos =
        10.0f - ((10.0f - pillarsCenter) * 0.2f) + pillarsGapSize * 0.5f;
    float bottomPillarYPos =
        -10.0f - ((-10.0f - pillarsCenter) * 0.2f) - pillarsGapSize * 0.5f;
    for ([[maybe_unused]] auto &&entity :
         m_entities
             ->entitiesWithComponents<PillarTag, Neat::TransformComponent>(
                 pillarTag, pillarTransform)) {
      if (pillarTransform->position.x <= m_movePillarThresholdPosX - 25.0f) {
        NT_CORE_TRACE("Moving pillar to new position. Current {0}, New {1}",
                      pillarTransform->position.x,
                      m_movePillarThresholdPosX + 20.0f);
        if (pillarTransform->position.y > 0.0f) {
          pillarTransform->position.x = m_movePillarThresholdPosX + 20.0f;
          pillarTransform->position.y = topPillarYPos;
        } else {
          pillarTransform->position.x = m_movePillarThresholdPosX + 20.0f;
          pillarTransform->position.y = bottomPillarYPos;
        }
      }
    }
    m_movePillarThresholdPosX += 10.0f;
  }

  m_camera->setPosition(playerPosition);

  m_systems->onUpdate<Neat::OrthographicCameraControllerSystem>(
      deltaTimeSeconds);
  m_systems->onUpdate<Neat::Render2DSystem>(deltaTimeSeconds);
}

void GameLayer::onImGui() {
  ImGui::Begin("MyWindow");
  if (ImGui::Button("Reset Game")) {
    init();
  }
  ImGui::SliderFloat("Gravity", &m_gravity, 0.0f, 100.0f);
  ImGui::SliderFloat("Engine Force", &m_engineForce, 0.0f, 200.0f);
  ImGui::End();
}
