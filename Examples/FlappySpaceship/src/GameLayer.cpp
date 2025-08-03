#include <memory>

#include "GameLayer.hpp"

#include <ImGui/imgui.h>

GameLayer::GameLayer(const Neat::Ref<Neat::EventDispatcher> &eventDispatcher)
    : m_spaceshipTexture(
          Neat::Texture2D::create("Resources/Textures/Ship.png")),
      m_pillarTexture(
          Neat::Texture2D::create("Resources/Textures/Triangle.png")) {
  m_spaceshipTexture->setMinification(
      Neat::Texture2DFilter::LinearMipmapNearest);
  m_spaceshipTexture->setMagnification(Neat::Texture2DFilter::Nearest);

  m_entities = Neat::makeRef<Neat::EntityManager>(eventDispatcher);
  m_systems = Neat::makeRef<Neat::SystemManager>(m_entities, eventDispatcher);

  auto camera_controller_system =
      m_systems->addSystem<Neat::OrthographicCameraControllerSystem>(
          1280.0f / 720.0f, 8.0f);
  m_systems->addSystem<Neat::Render2DSystem>(
      camera_controller_system->getCamera());

  m_systems->init();

  auto background = m_entities->createEntity();
  background.addComponent<Neat::RenderableSpriteComponent>(
      Neat::Color::forestBrown);
  background.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, 0.0f, -0.5f}, Neat::Vector2F{50.0f, 50.0f});

  auto floor = m_entities->createEntity();
  floor.addComponent<Neat::RenderableSpriteComponent>(Neat::Color::white);
  floor.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, -34.0f, 0.0f}, Neat::Vector2F{50.0f, 50.0f});

  auto ceiling = m_entities->createEntity();
  ceiling.addComponent<Neat::RenderableSpriteComponent>(Neat::Color::white);
  ceiling.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, 34.0f, 0.0f}, Neat::Vector2F{50.0f, 50.0f});

  auto topPillar = m_entities->createEntity();
  topPillar.addComponent<Neat::RenderableSpriteComponent>(m_pillarTexture);
  topPillar.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, 10.0f, 0.0f}, Neat::Vector2F{15.0f, 20.0f}, 180.0f);

  auto spaceship = m_entities->createEntity();
  spaceship.addComponent<Neat::RenderableSpriteComponent>(m_spaceshipTexture);
  spaceship.addComponent<Neat::TransformComponent>(
      Neat::Vector3F{0.0f, 0.0f, 0.5f}, Neat::Vector2F{1.0f, 1.3f}, -90.0f);
}

void GameLayer::onUpdate(double deltaTimeSeconds) {
  m_systems->onUpdate<Neat::OrthographicCameraControllerSystem>(
      deltaTimeSeconds);
  m_systems->onUpdate<Neat::Render2DSystem>(deltaTimeSeconds);
}