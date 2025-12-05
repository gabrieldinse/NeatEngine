#include <gtest/gtest.h>

#include <TestUtils.hpp>
#include "ECS/EntityManager.hpp"

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
  eventDispatcher->update();
  EXPECT_EQ(entityManager->size(), 1);
  EXPECT_TRUE(entity1.isValid());
  EXPECT_TRUE(entityManager->hasEntity(entity1));
  EXPECT_EQ(lastEntityCreated.id().index(), entity1.id().index());

  auto entity2 = entityManager->createEntity();
  eventDispatcher->update();
  EXPECT_EQ(entityManager->size(), 2);
  EXPECT_TRUE(entity2.isValid());
  EXPECT_TRUE(entityManager->hasEntity(entity2));
  EXPECT_EQ(lastEntityCreated.id().index(), entity2.id().index());
}

TEST_F(EntityManagerTest, DestroyEntity) {
  auto entity1 = entityManager->createEntity();
  EXPECT_EQ(entityManager->size(), 1);

  [[maybe_unused]] auto entity2 = entityManager->createEntity();
  EXPECT_EQ(entityManager->size(), 2);

  entityManager->destroyEntity(entity1);
  eventDispatcher->update();
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
  eventDispatcher->update();

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
  eventDispatcher->update();

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
  auto entity2Opt = entityManager->getEntity(entity1.id());
  EXPECT_TRUE(entity2Opt.has_value());

  auto entity2 = *entity2Opt;
  EXPECT_EQ(entity1, entity2);
  EXPECT_TRUE(entity2.isValid());
  EXPECT_TRUE(entityManager->hasEntity(entity2));

  auto entity3Opt = entityManager->getEntity(entity1.id().index());
  EXPECT_TRUE(entity3Opt.has_value());

  auto entity3 = *entity3Opt;
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

  auto speedComponentHandleOpt =
      entity1.addComponent<SpeedComponent>(Vector3F{5.0f, 10.0f, 15.0f});
  EXPECT_TRUE(speedComponentHandleOpt.has_value());

  auto speedComponentHandle = *speedComponentHandleOpt;
  EXPECT_TRUE(entity1.hasComponent<SpeedComponent>());
  EXPECT_TRUE(entity1.hasAnyComponent());
  EXPECT_TRUE(speedComponentHandle.isValid());
  EXPECT_TRUE(entity1.getComponent<SpeedComponent>().has_value());
  EXPECT_EQ(entity1.getComponent<SpeedComponent>().value()->velocity,
            (Vector3F{5.0f, 10.0f, 15.0f}));
  EXPECT_EQ(speedComponentHandle->velocity, (Vector3F{5.0f, 10.0f, 15.0f}));
  EXPECT_NE(lastSpeedComponentAdded.velocity, (Vector3F{5.0f, 10.0f, 15.0f}));

  eventDispatcher->update();
  EXPECT_EQ(lastSpeedComponentAdded.velocity, (Vector3F{5.0f, 10.0f, 15.0f}));
  EXPECT_FALSE(entity1.hasComponent<PlayerStatsComponent>());

  auto playerStatsComponentHandleOpt =
      entity1.addComponent<PlayerStatsComponent>(100, 50, 10);
  EXPECT_TRUE(playerStatsComponentHandleOpt.has_value());

  auto playerStatsComponentHandle = *playerStatsComponentHandleOpt;
  EXPECT_TRUE(entity1.hasComponent<PlayerStatsComponent>());
  EXPECT_TRUE(entity1.hasAnyComponent());
  EXPECT_TRUE(playerStatsComponentHandle.isValid());
  EXPECT_EQ(*entity1.getComponent<PlayerStatsComponent>().value(),
            (PlayerStatsComponent{100, 50, 10}));
  EXPECT_EQ(playerStatsComponentHandle->health, 100);
  EXPECT_EQ(playerStatsComponentHandle->mana, 50);
  EXPECT_EQ(playerStatsComponentHandle->damage, 10);
  EXPECT_NE(lastPlayerStatsComponentAdded.health, 100);

  eventDispatcher->update();
  EXPECT_EQ(lastPlayerStatsComponentAdded.health, 100);
}

TEST_F(EntityManagerTest, GetComponent) {
  auto entity1 = entityManager->createEntity();
  entity1.addComponent<SpeedComponent>(Vector3F{5.0f, 10.0f, 15.0f});
  entity1.addComponent<PlayerStatsComponent>(100, 50, 10);

  auto speedComponentHandleOpt = entity1.getComponent<SpeedComponent>();
  EXPECT_TRUE(speedComponentHandleOpt.has_value());

  auto speedComponentHandle = *speedComponentHandleOpt;
  EXPECT_EQ(speedComponentHandle->velocity, (Vector3F{5.0f, 10.0f, 15.0f}));

  auto playerStatsComponentHandleOpt =
      entity1.getComponent<PlayerStatsComponent>();
  EXPECT_TRUE(playerStatsComponentHandleOpt.has_value());

  auto playerStatsComponentHandle = *playerStatsComponentHandleOpt;
  EXPECT_EQ(playerStatsComponentHandle->health, 100);
  EXPECT_EQ(playerStatsComponentHandle->mana, 50);
  EXPECT_EQ(playerStatsComponentHandle->damage, 10);

  auto invalidComponentHandleOpt = entity1.getComponent<InventoryComponent>();
  auto invalidComponentHandleOpt2 = entity1.getComponent<InvalidComponent>();
  EXPECT_FALSE(invalidComponentHandleOpt.has_value());
  EXPECT_FALSE(invalidComponentHandleOpt2.has_value());
}

TEST_F(EntityManagerTest, RemoveComponent) {
  auto entity1 = entityManager->createEntity();
  auto speedComponentHandleOpt =
      entity1.addComponent<SpeedComponent>(Vector3F{5.0f, 10.0f, 15.0f});
  EXPECT_TRUE(speedComponentHandleOpt.has_value());

  auto speedComponentHandle = *speedComponentHandleOpt;
  EXPECT_TRUE(entity1.hasComponent<SpeedComponent>());
  EXPECT_FALSE(entity1.hasComponent<PlayerStatsComponent>());

  entity1.removeComponent<SpeedComponent>();
  EXPECT_FALSE(entity1.hasComponent<SpeedComponent>());
  EXPECT_FALSE(entity1.hasComponent<PlayerStatsComponent>());
  EXPECT_FALSE(entity1.hasAnyComponent());
  EXPECT_FALSE(speedComponentHandle.isValid());
  EXPECT_NE(lastSpeedComponentRemoved.velocity, (Vector3F{5.0f, 10.0f, 15.0f}));

  eventDispatcher->update();
  EXPECT_EQ(lastSpeedComponentRemoved.velocity, (Vector3F{5.0f, 10.0f, 15.0f}));

  entity1.addComponent<SpeedComponent>(Vector3F{50.0f, 100.0f, 150.0f});
  auto playerStatsComponentHandleOpt =
      entity1.addComponent<PlayerStatsComponent>(100, 50, 10);
  EXPECT_TRUE(playerStatsComponentHandleOpt.has_value());

  auto playerStatsComponentHandle = *playerStatsComponentHandleOpt;
  entity1.removeComponent<PlayerStatsComponent>();
  eventDispatcher->update();
  EXPECT_FALSE(entity1.hasComponent<PlayerStatsComponent>());
  EXPECT_TRUE(entity1.hasComponent<SpeedComponent>());
  EXPECT_TRUE(entity1.hasAnyComponent());
  EXPECT_FALSE(playerStatsComponentHandle.isValid());
  EXPECT_EQ(lastPlayerStatsComponentRemoved.health, 100);
}

TEST_F(EntityManagerTest, ReplaceComponent) {
  auto entity1 = entityManager->createEntity();
  auto speedComponentHandleOpt =
      entity1.addComponent<SpeedComponent>(Vector3F{5.0f, 10.0f, 15.0f});
  EXPECT_TRUE(speedComponentHandleOpt.has_value());

  auto speedComponentHandle = *speedComponentHandleOpt;
  EXPECT_EQ(speedComponentHandle->velocity, (Vector3F{5.0f, 10.0f, 15.0f}));

  auto replacedSpeedComponentHandleOpt =
      entity1.replaceComponent<SpeedComponent>(Vector3F{50.0f, 100.0f, 150.0f});
  EXPECT_TRUE(replacedSpeedComponentHandleOpt.has_value());

  auto replacedSpeedComponentHandle = *replacedSpeedComponentHandleOpt;
  EXPECT_EQ(replacedSpeedComponentHandle->velocity,
            (Vector3F{50.0f, 100.0f, 150.0f}));
  EXPECT_EQ(speedComponentHandle->velocity, (Vector3F{50.0f, 100.0f, 150.0f}));

  auto playerStatsComponentHandleOpt =
      entity1.replaceComponent<PlayerStatsComponent>(200, 100, 20);
  EXPECT_TRUE(playerStatsComponentHandleOpt.has_value());

  auto playerStatsComponentHandle = *playerStatsComponentHandleOpt;
  EXPECT_EQ(playerStatsComponentHandle->health, 200);
  EXPECT_EQ(playerStatsComponentHandle->mana, 100);
  EXPECT_EQ(playerStatsComponentHandle->damage, 20);
}

TEST_F(EntityManagerTest, GetComponents) {
  auto entity1 = entityManager->createEntity();
  entity1.addComponent<SpeedComponent>(Vector3F{5.0f, 10.0f, 15.0f});
  entity1.addComponent<PlayerStatsComponent>(100, 50, 10);

  auto [speedComponentHandleOpt, playerStatsComponentHandleOpt,
        invalidComponentHandleOpt] =
      entity1.getComponents<SpeedComponent, PlayerStatsComponent,
                            InvalidComponent>();
  EXPECT_TRUE(speedComponentHandleOpt.has_value());
  EXPECT_TRUE(playerStatsComponentHandleOpt.has_value());
  EXPECT_FALSE(invalidComponentHandleOpt.has_value());

  auto speedComponentHandle = *speedComponentHandleOpt;
  auto playerStatsComponentHandle = *playerStatsComponentHandleOpt;
  EXPECT_EQ(speedComponentHandle->velocity, (Vector3F{5.0f, 10.0f, 15.0f}));
  EXPECT_EQ(playerStatsComponentHandle->health, 100);
  EXPECT_EQ(playerStatsComponentHandle->mana, 50);
  EXPECT_EQ(playerStatsComponentHandle->damage, 10);
}

TEST_F(EntityManagerTest, AddComponentFromCopy) {
  auto entity1 = entityManager->createEntity();
  PlayerStatsComponent statsComponent{150, 75, 15};

  auto playerStatsComponentHandleOpt =
      entity1.addComponentFromCopy<PlayerStatsComponent>(statsComponent);
  EXPECT_TRUE(playerStatsComponentHandleOpt.has_value());

  auto playerStatsComponentHandle = *playerStatsComponentHandleOpt;
  EXPECT_TRUE(entity1.hasComponent<PlayerStatsComponent>());
  EXPECT_TRUE(entity1.hasAnyComponent());
  EXPECT_TRUE(playerStatsComponentHandle.isValid());
  EXPECT_EQ(*entity1.getComponent<PlayerStatsComponent>().value(),
            (PlayerStatsComponent{150, 75, 15}));
  EXPECT_EQ(playerStatsComponentHandle->health, 150);
  EXPECT_EQ(playerStatsComponentHandle->mana, 75);
  EXPECT_EQ(playerStatsComponentHandle->damage, 15);
}

TEST_F(EntityManagerTest, EntitiesWithComponents) {
  auto entity1 = entityManager->createEntity();
  entity1.addComponent<SpeedComponent>(Vector3F{5.0f, 10.0f, 15.0f});

  auto entity2 = entityManager->createEntity();
  entity2.addComponent<PlayerStatsComponent>(100, 50, 10);

  auto entity3 = entityManager->createEntity();
  entity3.addComponent<SpeedComponent>(Vector3F{1.0f, 2.0f, 3.0f});
  entity3.addComponent<PlayerStatsComponent>(200, 100, 20);

  std::vector<Entity> speedEntities;
  for (auto entity : entityManager->entitiesWithComponents<SpeedComponent>()) {
    speedEntities.push_back(entity);
  }
  EXPECT_EQ(speedEntities.size(), 2);
  EXPECT_TRUE((speedEntities[0] == entity1 and speedEntities[1] == entity3) or
              (speedEntities[0] == entity3 and speedEntities[1] == entity1));

  std::vector<Entity> statsEntities;
  for (auto entity :
       entityManager->entitiesWithComponents<PlayerStatsComponent>()) {
    statsEntities.push_back(entity);
  }
  EXPECT_EQ(statsEntities.size(), 2);
  EXPECT_TRUE((statsEntities[0] == entity2 and statsEntities[1] == entity3) or
              (statsEntities[0] == entity3 and statsEntities[1] == entity2));

  std::vector<Entity> bothComponentsEntities;
  for (auto entity :
       entityManager
           ->entitiesWithComponents<SpeedComponent, PlayerStatsComponent>()) {
    bothComponentsEntities.push_back(entity);
  }
  EXPECT_EQ(bothComponentsEntities.size(), 1);
  EXPECT_EQ(bothComponentsEntities[0], entity3);

  std::vector<Entity> noEntities;
  for (auto entity :
       entityManager->entitiesWithComponents<
           SpeedComponent, PlayerStatsComponent, InvalidComponent>()) {
    noEntities.push_back(entity);
  }
  EXPECT_EQ(noEntities.size(), 0);
}

TEST_F(EntityManagerTest, Unpack) {
  auto entity1 = entityManager->createEntity();
  entity1.addComponent<SpeedComponent>(Vector3F{5.0f, 10.0f, 15.0f});
  entity1.addComponent<PlayerStatsComponent>(100, 50, 10);

  ComponentHandle<SpeedComponent> speedComponentHandle;
  ComponentHandle<PlayerStatsComponent> playerStatsComponentHandle;
  ComponentHandle<InventoryComponent> inventoryComponentHandle;
  EXPECT_TRUE(entity1.unpack(speedComponentHandle, playerStatsComponentHandle));
  EXPECT_TRUE(speedComponentHandle.isValid());
  EXPECT_TRUE(playerStatsComponentHandle.isValid());
  EXPECT_FALSE(inventoryComponentHandle.isValid());
  EXPECT_EQ(speedComponentHandle->velocity, (Vector3F{5.0f, 10.0f, 15.0f}));
  EXPECT_EQ(playerStatsComponentHandle->health, 100);
  EXPECT_EQ(playerStatsComponentHandle->mana, 50);
  EXPECT_EQ(playerStatsComponentHandle->damage, 10);

  entity1.getComponent<SpeedComponent>().value()->velocity =
      Vector3F{20.0f, 30.0f, 40.0f};
  entity1.getComponent<PlayerStatsComponent>().value()->health = 300;
  entity1.getComponent<PlayerStatsComponent>().value()->mana = 150;
  entity1.getComponent<PlayerStatsComponent>().value()->damage = 25;

  EXPECT_FALSE(entity1.unpack(speedComponentHandle, playerStatsComponentHandle,
                              inventoryComponentHandle));
  EXPECT_FALSE(inventoryComponentHandle.isValid());
}
}  // namespace Neat