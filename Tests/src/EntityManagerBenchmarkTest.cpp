#include <gtest/gtest.h>

#include <ECS/ECS.hpp>
#include <Core/Timer.hpp>
#include <TestUtils.hpp>

namespace Neat {
class EntityManagerBenchmarkTest : public testing::Test {
 protected:
  EntityManagerBenchmarkTest() {
    eventDispatcher = makeRef<EventDispatcher>();
    entityManager = makeRef<EntityManager>(eventDispatcher);
    eventDispatcher->get<EntityCreatedEvent>()
        .connect<&EntityManagerBenchmarkTest::onEntityCreated>(*this);
    eventDispatcher->get<EntityDestroyedEvent>()
        .connect<&EntityManagerBenchmarkTest::onEntityDestroyed>(*this);
    eventDispatcher->get<ComponentAddedEvent<SpeedComponent>>()
        .connect<&EntityManagerBenchmarkTest::onSpeedComponentAdded>(*this);
    eventDispatcher->get<ComponentAddedEvent<PlayerStatsComponent>>()
        .connect<&EntityManagerBenchmarkTest::onPlayerStatsComponentAdded>(
            *this);
    eventDispatcher->get<ComponentAddedEvent<InventoryComponent>>()
        .connect<&EntityManagerBenchmarkTest::onInventoryComponentAdded>(*this);
    eventDispatcher->get<ComponentRemovedEvent<SpeedComponent>>()
        .connect<&EntityManagerBenchmarkTest::onSpeedComponentRemoved>(*this);
    eventDispatcher->get<ComponentRemovedEvent<PlayerStatsComponent>>()
        .connect<&EntityManagerBenchmarkTest::onPlayerStatsComponentRemoved>(
            *this);
    eventDispatcher->get<ComponentRemovedEvent<InventoryComponent>>()
        .connect<&EntityManagerBenchmarkTest::onInventoryComponentRemoved>(
            *this);
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

TEST_F(EntityManagerBenchmarkTest, CreateEntitiesBenchmark) {
  const int numEntities = 1000000;
  Timer timer;
  timer.start();
  for (int i = 0; i < numEntities; ++i) {
    [[maybe_unused]] auto entity = entityManager->createEntity();
  }

  double duration = timer.stop();
  std::cout << "Created " << numEntities << " entities in " << duration
            << " seconds.\n";
}

TEST_F(EntityManagerBenchmarkTest, DestroyEntitiesBenchmark) {
  const int numEntities = 1000000;
  std::vector<Entity> entities;
  entities.reserve(numEntities);
  for (int i = 0; i < numEntities; ++i) {
    entities.push_back(entityManager->createEntity());
  }

  Timer timer;
  timer.start();
  for (const auto &entity : entities) {
    entityManager->destroyEntity(entity);
  }
  eventDispatcher->update();

  double duration = timer.stop();
  std::cout << "Destroyed " << numEntities << " entities in " << duration
            << " seconds.\n";
}
}  // namespace Neat