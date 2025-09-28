#include <gtest/gtest.h>

#include <Neat/ECS/ECS.hpp>
#include <TestUtils.hpp>

namespace Neat {
class EntityManagerTest : public testing::Test {
 protected:
  EntityManagerTest() {
    eventDispatcher = makeRef<EventDispatcher>();
    entityManager = makeRef<EntityManager>(eventDispatcher);
    eventDispatcher->get<EntityCreatedEvent>()
        .connect<&EntityManagerTest::onEntityCreated>(*this);
    eventDispatcher->get<EntityDestroyedEvent>()
        .connect<&EntityManagerTest::onEntityDestroyed>(*this);
    eventDispatcher->get<ComponentAddedEvent<SpeedComponent>>()
        .connect<&EntityManagerTest::onSpeedComponentAdded>(*this);
    eventDispatcher->get<ComponentAddedEvent<PlayerStatsComponent>>()
        .connect<&EntityManagerTest::onPlayerStatsComponentAdded>(*this);
    eventDispatcher->get<ComponentAddedEvent<InventoryComponent>>()
        .connect<&EntityManagerTest::onInventoryComponentAdded>(*this);
    eventDispatcher->get<ComponentRemovedEvent<SpeedComponent>>()
        .connect<&EntityManagerTest::onSpeedComponentRemoved>(*this);
    eventDispatcher->get<ComponentRemovedEvent<PlayerStatsComponent>>()
        .connect<&EntityManagerTest::onPlayerStatsComponentRemoved>(*this);
    eventDispatcher->get<ComponentRemovedEvent<InventoryComponent>>()
        .connect<&EntityManagerTest::onInventoryComponentRemoved>(*this);
  }

  bool onEntityCreated(const EntityCreatedEvent &event) {
    lastEntityCreated = event.entity;
    return false;
  }

  bool onEntityDestroyed(const EntityDestroyedEvent &event) {
    lastEntityDestroyed = event.entity;
    return false;
  }

  bool onSpeedComponentAdded(const ComponentAddedEvent<SpeedComponent> &event) {
    lastSpeedComponentAdded = event.component;
    return false;
  }

  bool onPlayerStatsComponentAdded(
      const ComponentAddedEvent<PlayerStatsComponent> &event) {
    lastPlayerStatsComponentAdded = event.component;
    return false;
  }

  bool onInventoryComponentAdded(
      const ComponentAddedEvent<InventoryComponent> &event) {
    lastInventoryComponentAdded = event.component;
    return false;
  }

  bool onSpeedComponentRemoved(
      const ComponentRemovedEvent<SpeedComponent> &event) {
    lastSpeedComponentRemoved = event.component;
    return false;
  }

  bool onPlayerStatsComponentRemoved(
      const ComponentRemovedEvent<PlayerStatsComponent> &event) {
    lastPlayerStatsComponentRemoved = event.component;
    return false;
  }

  bool onInventoryComponentRemoved(
      const ComponentRemovedEvent<InventoryComponent> &event) {
    lastInventoryComponentRemoved = event.component;
    return false;
  }

  Ref<EventDispatcher> eventDispatcher;
  Ref<EntityManager> entityManager;
  Entity invalidEntity;
  Entity lastEntityCreated;
  Entity lastEntityDestroyed;
  SpeedComponent lastSpeedComponentAdded;
  PlayerStatsComponent lastPlayerStatsComponentAdded;
  InventoryComponent lastInventoryComponentAdded;
  SpeedComponent lastSpeedComponentRemoved;
  PlayerStatsComponent lastPlayerStatsComponentRemoved;
  InventoryComponent lastInventoryComponentRemoved;
};

TEST_F(EntityManagerTest, InvalidEntity) {
  EXPECT_FALSE(entityManager->hasEntity(invalidEntity));
  EXPECT_FALSE(invalidEntity.isValid());

  Entity emptyEntity;
  EXPECT_FALSE(entityManager->hasEntity(emptyEntity));
  EXPECT_FALSE(emptyEntity.isValid());
  EXPECT_FALSE(emptyEntity);
}

TEST_F(EntityManagerTest, CreateEntity) {
  EXPECT_EQ(entityManager->size(), 0);

  auto entity1 = entityManager->createEntity();
  eventDispatcher->onUpdate();
  EXPECT_EQ(entityManager->size(), 1);
  EXPECT_TRUE(entity1.isValid());
  EXPECT_TRUE(entityManager->hasEntity(entity1));
  EXPECT_EQ(lastEntityCreated.id().index(), entity1.id().index());

  auto entity2 = entityManager->createEntity();
  eventDispatcher->onUpdate();
  EXPECT_EQ(entityManager->size(), 2);
  EXPECT_TRUE(entity2.isValid());
  EXPECT_TRUE(entityManager->hasEntity(entity2));
  EXPECT_EQ(lastEntityCreated.id().index(), entity2.id().index());
}

TEST_F(EntityManagerTest, DestroyEntity) {
  auto entity1 = entityManager->createEntity();
  EXPECT_EQ(entityManager->size(), 1);

  entityManager->createEntity();
  EXPECT_EQ(entityManager->size(), 2);

  entityManager->destroyEntity(entity1);
  eventDispatcher->onUpdate();
  EXPECT_EQ(entityManager->size(), 1);

  EXPECT_FALSE(entityManager->hasEntity(entity1));
  EXPECT_FALSE(entity1.isValid());
  EXPECT_EQ(lastEntityDestroyed.id().index(), entity1.id().index());
}

TEST_F(EntityManagerTest, ResetEntityManager) {
  EXPECT_EQ(entityManager->size(), 0);
  auto entity1 = entityManager->createEntity();

  EXPECT_EQ(entityManager->size(), 1);
  auto entity2 = entityManager->createEntity();
  eventDispatcher->onUpdate();

  EXPECT_EQ(entityManager->size(), 2);
  EXPECT_TRUE(entity2.isValid());
  EXPECT_TRUE(entityManager->hasEntity(entity2));
  EXPECT_EQ(lastEntityCreated.id().index(), entity2.id().index());

  entityManager->reset();
  EXPECT_EQ(entityManager->size(), 0);
  EXPECT_FALSE(entity1.isValid());
  EXPECT_FALSE(entityManager->hasEntity(entity1));
  EXPECT_FALSE(entity2.isValid());
  EXPECT_FALSE(entityManager->hasEntity(entity2));

  auto entity3 = entityManager->createEntity();
  eventDispatcher->onUpdate();

  EXPECT_EQ(entityManager->size(), 1);
  EXPECT_TRUE(entity3.isValid());
  EXPECT_TRUE(entityManager->hasEntity(entity3));
  EXPECT_EQ(lastEntityCreated.id().index(), entity3.id().index());
}

TEST_F(EntityManagerTest, EntitiesIDs) {
  auto entity1 = entityManager->createEntity();
  auto entity2 = entityManager->createEntity();
  auto entity3 = entityManager->createEntity();

  EXPECT_TRUE(entity1 < entity2);
  EXPECT_TRUE(entity1 < entity2);
  EXPECT_TRUE(entity1 < entity3);
  EXPECT_TRUE(entity2 < entity3);

  entityManager->destroyEntity(entity2);
  auto entity4 = entityManager->createEntity();

  EXPECT_TRUE(entity1 < entity4);
  EXPECT_TRUE(entity1 < entity4);
  EXPECT_TRUE(entity1 < entity3);
  EXPECT_TRUE(entity3 < entity4);

  entityManager->reset();

  entity1 = entityManager->createEntity();
  entity2 = entityManager->createEntity();
  entity3 = entityManager->createEntity();

  EXPECT_TRUE(entity1 < entity2);
  EXPECT_TRUE(entity1 < entity2);
  EXPECT_TRUE(entity1 < entity3);
  EXPECT_TRUE(entity2 < entity3);
}

TEST_F(EntityManagerTest, IterateOverEntities) {
  auto entity1 = entityManager->createEntity();
  auto entity2 = entityManager->createEntity();
  auto entity3 = entityManager->createEntity();

  auto entities = entityManager->entities();
  auto it = entities.begin();

  EXPECT_EQ(*(it), entity1);
  ++it;
  EXPECT_EQ(*(it), entity2);
  ++it;
  EXPECT_EQ(*(it), entity3);
  ++it;
  EXPECT_EQ(it, entities.end());

  for (Entity entity : entityManager->entities()) {
    EXPECT_TRUE(entity.isValid());
    EXPECT_TRUE(entityManager->hasEntity(entity));
  }
}

TEST_F(EntityManagerTest, EntityCopyAndAssignment) {
  auto entity1 = entityManager->createEntity();
  auto entity2 = entityManager->createEntity();
  EXPECT_NE(entity1, entity2);

  entity1 = entity2;
  EXPECT_EQ(entity1, entity2);
  EXPECT_TRUE(entity1.isValid());
  EXPECT_TRUE(entity2.isValid());

  auto &entity3 = entity1;
  EXPECT_EQ(entity3, entity1);
  EXPECT_TRUE(entity3.isValid());
  EXPECT_TRUE(entity1.isValid());

  auto entity4 = entity3;
  EXPECT_EQ(entity4, entity3);
  EXPECT_TRUE(entity4.isValid());
  EXPECT_TRUE(entity3.isValid());

  EXPECT_TRUE(entity1);
  EXPECT_TRUE(entity2);
  EXPECT_TRUE(entity3);
  EXPECT_TRUE(entity4);
}

TEST_F(EntityManagerTest, GetEntity) {
  auto entity1 = entityManager->createEntity();
  auto entity2 = entityManager->getEntity(entity1.id());
  EXPECT_EQ(entity1, entity2);
  EXPECT_TRUE(entity2.isValid());
  EXPECT_TRUE(entityManager->hasEntity(entity2));

  auto entity3 = entityManager->getEntity(entity1.id().index());
  EXPECT_EQ(entity1, entity3);
  EXPECT_TRUE(entity3.isValid());
  EXPECT_TRUE(entityManager->hasEntity(entity3));
}

TEST_F(EntityManagerTest, DoesNotHaveComponent) {
  auto entity1 = entityManager->createEntity();
  EXPECT_FALSE(entity1.hasComponent<std::string>());
  EXPECT_FALSE(entity1.hasAnyComponent());
}

TEST_F(EntityManagerTest, AddComponent) {
  auto entity1 = entityManager->createEntity();
  EXPECT_FALSE(entity1.hasComponent<SpeedComponent>());
  EXPECT_FALSE(entity1.hasAnyComponent());
  EXPECT_NE(lastSpeedComponentAdded.velocity, (Vector3F{5.0f, 10.0f, 15.0f}));

  auto speedComponentHandle =
      entity1.addComponent<SpeedComponent>(Vector3F{5.0f, 10.0f, 15.0f});
  EXPECT_TRUE(entity1.hasComponent<SpeedComponent>());
  EXPECT_TRUE(entity1.hasAnyComponent());
  EXPECT_TRUE(speedComponentHandle.isValid());
  EXPECT_EQ(entity1.getComponent<SpeedComponent>()->velocity,
            (Vector3F{5.0f, 10.0f, 15.0f}));
  EXPECT_EQ(speedComponentHandle->velocity, (Vector3F{5.0f, 10.0f, 15.0f}));
  EXPECT_NE(lastSpeedComponentAdded.velocity, (Vector3F{5.0f, 10.0f, 15.0f}));

  eventDispatcher->onUpdate();
  EXPECT_EQ(lastSpeedComponentAdded.velocity, (Vector3F{5.0f, 10.0f, 15.0f}));
  EXPECT_FALSE(entity1.hasComponent<PlayerStatsComponent>());

  auto playerStatsComponentHandle =
      entity1.addComponent<PlayerStatsComponent>(100, 50, 10);
  EXPECT_TRUE(entity1.hasComponent<PlayerStatsComponent>());
  EXPECT_TRUE(entity1.hasAnyComponent());
  EXPECT_TRUE(playerStatsComponentHandle.isValid());
  EXPECT_EQ(*entity1.getComponent<PlayerStatsComponent>(),
            (PlayerStatsComponent{100, 50, 10}));
  EXPECT_EQ(playerStatsComponentHandle->health, 100);
  EXPECT_EQ(playerStatsComponentHandle->mana, 50);
  EXPECT_EQ(playerStatsComponentHandle->damage, 10);
  EXPECT_NE(lastPlayerStatsComponentAdded.health, 100);

  eventDispatcher->onUpdate();
  EXPECT_EQ(lastPlayerStatsComponentAdded.health, 100);
}

TEST_F(EntityManagerTest, RemoveComponent) {
  auto entity1 = entityManager->createEntity();
  [[maybe_unused]] auto speedComponentHandle =
      entity1.addComponent<SpeedComponent>(Vector3F{5.0f, 10.0f, 15.0f});
  EXPECT_TRUE(entity1.hasComponent<SpeedComponent>());
  EXPECT_FALSE(entity1.hasComponent<PlayerStatsComponent>());

  entity1.removeComponent<SpeedComponent>();
  EXPECT_FALSE(entity1.hasComponent<SpeedComponent>());
  EXPECT_FALSE(entity1.hasComponent<PlayerStatsComponent>());
  EXPECT_FALSE(entity1.hasAnyComponent());
  EXPECT_FALSE(speedComponentHandle.isValid());
  EXPECT_NE(lastSpeedComponentRemoved.velocity, (Vector3F{5.0f, 10.0f, 15.0f}));

  eventDispatcher->onUpdate();
  EXPECT_EQ(lastSpeedComponentRemoved.velocity, (Vector3F{5.0f, 10.0f, 15.0f}));

  entity1.addComponent<SpeedComponent>(Vector3F{50.0f, 100.0f, 150.0f});
  auto playerStatsComponentHandle =
      entity1.addComponent<PlayerStatsComponent>(100, 50, 10);

  entity1.removeComponent<PlayerStatsComponent>();
  eventDispatcher->onUpdate();
  EXPECT_FALSE(entity1.hasComponent<PlayerStatsComponent>());
  EXPECT_TRUE(entity1.hasComponent<SpeedComponent>());
  EXPECT_TRUE(entity1.hasAnyComponent());
  EXPECT_FALSE(playerStatsComponentHandle.isValid());
  EXPECT_EQ(lastPlayerStatsComponentRemoved.health, 100);
}
}  // namespace Neat