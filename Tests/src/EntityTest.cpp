#include <gtest/gtest.h>

#include <Neat/ECS/ECS.hpp>
#include <TestUtils.hpp>

namespace Neat {
class EntityTest : public testing::Test {
 protected:
  EntityTest() {
    eventDispatcher = makeRef<EventDispatcher>();
    entityManager = makeRef<EntityManager>(eventDispatcher);
    eventDispatcher->get<EntityCreatedEvent>()
        .connect<&EntityTest::onEntityCreated>(*this);
    eventDispatcher->get<EntityDestroyedEvent>()
        .connect<&EntityTest::onEntityDestroyed>(*this);
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

TEST_F(EntityTest, InvalidEntity) {
  EXPECT_FALSE(entityManager->hasEntity(invalidEntity));
  EXPECT_FALSE(invalidEntity.isValid());
}

TEST_F(EntityTest, CreateEntity) {
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

TEST_F(EntityTest, DestroyEntity) {
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

TEST_F(EntityTest, ResetEntityManager) {
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
}
}  // namespace Neat