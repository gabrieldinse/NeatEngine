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
  }

  bool onEntityCreated(const EntityCreatedEvent &event) {
    lastEntityCreated = event.entity;
    return false;
  }

  bool onEntityDestroyed(const EntityDestroyedEvent &event) {
    lastEntityDestroyed = event.entity;
    return false;
  }

  Ref<EventDispatcher> eventDispatcher;
  Ref<EntityManager> entityManager;
  Entity invalidEntity;
  Entity lastEntityCreated;
  Entity lastEntityDestroyed;
};

TEST_F(EntityManagerTest, InvalidEntity) {
  EXPECT_FALSE(entityManager->hasEntity(invalidEntity));
  EXPECT_FALSE(invalidEntity.isValid());
}

TEST_F(EntityManagerTest, CreateEntity) {
  EXPECT_EQ(entityManager->size(), 0);

  auto entity = entityManager->createEntity();
  eventDispatcher->onUpdate();
  EXPECT_EQ(entityManager->size(), 1);
  EXPECT_TRUE(entity.isValid());
  EXPECT_TRUE(entityManager->hasEntity(entity));
  EXPECT_EQ(lastEntityCreated.id().index(), entity.id().index());

  auto entity2 = entityManager->createEntity();
  eventDispatcher->onUpdate();
  EXPECT_EQ(entityManager->size(), 2);
  EXPECT_TRUE(entity2.isValid());
  EXPECT_TRUE(entityManager->hasEntity(entity2));
  EXPECT_EQ(lastEntityCreated.id().index(), entity2.id().index());
}

TEST_F(EntityManagerTest, DestroyEntity) {
  auto entity = entityManager->createEntity();
  EXPECT_EQ(entityManager->size(), 1);

  auto entity2 = entityManager->createEntity();
  EXPECT_EQ(entityManager->size(), 2);

  entityManager->destroyEntity(entity);
  eventDispatcher->onUpdate();
  EXPECT_EQ(entityManager->size(), 1);

  EXPECT_FALSE(entityManager->hasEntity(entity));
  EXPECT_FALSE(entity.isValid());
  EXPECT_EQ(lastEntityDestroyed.id().index(), entity.id().index());
}

TEST_F(EntityManagerTest, ResetEntityManager) {
  EXPECT_EQ(entityManager->size(), 0);
  auto entity = entityManager->createEntity();

  EXPECT_EQ(entityManager->size(), 1);
  auto entity2 = entityManager->createEntity();
  eventDispatcher->onUpdate();

  EXPECT_EQ(entityManager->size(), 2);
  EXPECT_TRUE(entity2.isValid());
  EXPECT_TRUE(entityManager->hasEntity(entity2));
  EXPECT_EQ(lastEntityCreated.id().index(), entity2.id().index());

  entityManager->reset();
  EXPECT_EQ(entityManager->size(), 0);
  EXPECT_FALSE(entity.isValid());
  EXPECT_FALSE(entityManager->hasEntity(entity));
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
  auto entity = entityManager->createEntity();
  auto entity2 = entityManager->createEntity();
  auto entity3 = entityManager->createEntity();

  EXPECT_TRUE(entity < entity2);
  EXPECT_TRUE(entity < entity2);
  EXPECT_TRUE(entity < entity3);
  EXPECT_TRUE(entity2 < entity3);

  entityManager->destroyEntity(entity2);
  // Gets entity ID
  auto entity4 = entityManager->createEntity();

  EXPECT_TRUE(entity < entity4);
  EXPECT_TRUE(entity < entity4);
  EXPECT_TRUE(entity < entity3);
  EXPECT_TRUE(entity3 < entity4);

  entityManager->reset();

  entity = entityManager->createEntity();
  entity2 = entityManager->createEntity();
  entity3 = entityManager->createEntity();

  EXPECT_TRUE(entity < entity2);
  EXPECT_TRUE(entity < entity2);
  EXPECT_TRUE(entity < entity3);
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

TEST_F(EntityManagerTest, EntitiesEquality) {
  auto entity1 = entityManager->createEntity();
  auto entity2 = entityManager->createEntity();
  EXPECT_NE(entity1, entity2);

  entity1 = entity2;
  EXPECT_EQ(entity1, entity2);
}
}  // namespace Neat