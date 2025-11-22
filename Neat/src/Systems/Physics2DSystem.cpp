#include "NeatPCH.hpp"

#include "Physics2DSystem.hpp"
#include "Physics2DUtils.hpp"

#include "ECS/EntityManager.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/RigidBody2DComponent.hpp"
#include "Components/BoxCollider2DComponent.hpp"

#include <box2d/box2d.h>

namespace Neat {
Physics2DSystem::~Physics2DSystem() {
  if (b2World_IsValid(m_worldID)) {
    b2DestroyWorld(m_worldID);
  }
}

void Physics2DSystem::onInitialize(
    const Ref<EntityManager> &entityManager,
    [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
    [[maybe_unused]] LayerID layerID) {
  b2WorldDef worldDef = b2DefaultWorldDef();
  b2Vec2 gravity{0.0f, -9.81f};
  worldDef.gravity = gravity;
  m_worldID = b2CreateWorld(&worldDef);

  auto entities =
      entityManager
          ->entitiesWithComponents<TransformComponent, RigidBody2DComponent>();
  for (auto entity : entities) {
    auto transformOpt = entity.getComponent<TransformComponent>();
    auto rigidBodyOpt = entity.getComponent<RigidBody2DComponent>();
    if (not transformOpt or not rigidBodyOpt) {
      continue;
    }

    auto transform = *transformOpt;
    auto rigidBody = *rigidBodyOpt;
    b2BodyDef bodyDefinition = b2DefaultBodyDef();
    bodyDefinition.type = Physics2DUtils::toB2BodyType(rigidBody->type);
    bodyDefinition.position =
        b2Vec2{transform->position.x(), transform->position.y()};
    bodyDefinition.rotation = b2MakeRot(transform->getRotationZ());
    bodyDefinition.fixedRotation = rigidBody->fixedRotation;
    rigidBody->bodyID = b2CreateBody(m_worldID, &bodyDefinition);

    if (entity.hasComponent<BoxCollider2DComponent>()) {
      auto boxColliderOpt = entity.getComponent<BoxCollider2DComponent>();
      if (not boxColliderOpt) {
        continue;
      }

      auto boxCollider = *boxColliderOpt;
      b2Polygon box =
          b2MakeBox(boxCollider->size.x() * 0.5f, boxCollider->size.y() * 0.5f);
      b2ShapeDef shapeDefinition = b2DefaultShapeDef();
      shapeDefinition.density = boxCollider->density;
      shapeDefinition.material.friction = boxCollider->friction;
      shapeDefinition.material.restitution = boxCollider->bounceFactor;
      b2CreatePolygonShape(rigidBody->bodyID, &shapeDefinition, &box);
    }
  }
}

void Physics2DSystem::onShutdown(
    [[maybe_unused]] const Ref<EntityManager> &entityManager,
    [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
    [[maybe_unused]] LayerID layerID) {
  if (b2World_IsValid(m_worldID)) {
    b2DestroyWorld(m_worldID);
  }
}

void Physics2DSystem::onUpdate(
    [[maybe_unused]] const Ref<EntityManager> &entityManager,
    [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
    [[maybe_unused]] double deltaTimeSeconds,
    [[maybe_unused]] LayerID layerID) {
  const Int32 subStep = 4;
  b2World_Step(m_worldID, deltaTimeSeconds, subStep);
  auto entities =
      entityManager
          ->entitiesWithComponents<TransformComponent, RigidBody2DComponent>();
  for (auto entity : entities) {
    auto transformOpt = entity.getComponent<TransformComponent>();
    auto rigidBodyOpt = entity.getComponent<RigidBody2DComponent>();
    if (not transformOpt or not rigidBodyOpt) {
      continue;
    }

    auto transform = *transformOpt;
    auto rigidBody = *rigidBodyOpt;
    const auto &position = b2Body_GetPosition(rigidBody->bodyID);
    transform->setPosition(position.x, position.y);
    transform->setRotationZRadians(
        b2Rot_GetAngle(b2Body_GetRotation(rigidBody->bodyID)));
  }
}
}  // namespace Neat