#include <gtest/gtest.h>

#include <ECS/ECS.hpp>
#include <TestUtils.hpp>

namespace Neat {
class SystemManagerTest : public testing::Test {
 protected:
  SystemManagerTest() {
    eventDispatcher = makeRef<EventDispatcher>();
    entityManager = makeRef<EntityManager>(eventDispatcher);
    systemManager = makeRef<SystemManager>();
    systemManager->addSystem<TestingSystem>();
    systemManager->addSystem<TestingSystem2>();
  }
  void expectDefault() {
    EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->updateCounter,
              0);
    EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->updateCounter,
              0);
    EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter,
              0);
    EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter,
              0);
  }
  void expectInitialized() {
    EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->updateCounter,
              0);
    EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->updateCounter,
              0);
    EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter,
              1);
    EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter,
              1);
  }
  void expectShutdown() {
    EXPECT_EQ(
        systemManager->getSystem<TestingSystem>().value()->shutdownCounter, 1);
    EXPECT_EQ(
        systemManager->getSystem<TestingSystem2>().value()->shutdownCounter, 1);
  }
  Ref<EventDispatcher> eventDispatcher;
  Ref<EntityManager> entityManager;
  Ref<SystemManager> systemManager;
};

TEST_F(SystemManagerTest, DoNotInitSystems) { expectDefault(); }

TEST_F(SystemManagerTest, InitSystems) {
  expectDefault();
  systemManager->initialize(entityManager, eventDispatcher);
  expectInitialized();

  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->shutdownCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->shutdownCounter,
            0);
  EXPECT_TRUE(
      systemManager->getSystem<TestingSystem>().value()->isInitialized());
  EXPECT_TRUE(
      systemManager->getSystem<TestingSystem2>().value()->isInitialized());
}

TEST_F(SystemManagerTest, ShutdownSystems) {
  expectDefault();
  systemManager->initialize(entityManager, eventDispatcher);
  expectInitialized();

  systemManager->shutdown(entityManager, eventDispatcher);
  EXPECT_FALSE(
      systemManager->getSystem<TestingSystem>().value()->isInitialized());
  EXPECT_FALSE(
      systemManager->getSystem<TestingSystem2>().value()->isInitialized());
  expectShutdown();
}

TEST_F(SystemManagerTest, UpdateAllSystems) {
  expectDefault();
  systemManager->updateAll(entityManager, eventDispatcher, 0.016);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->updateCounter,
            1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->updateCounter,
            1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 1);

  systemManager->updateAll(entityManager, eventDispatcher, 0.016);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->updateCounter,
            2);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->updateCounter,
            2);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 1);
}

TEST_F(SystemManagerTest, UpdateOneSystem) {
  expectDefault();
  systemManager->update<TestingSystem>(entityManager, eventDispatcher, 0.016);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->updateCounter,
            1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->updateCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 0);

  systemManager->update<TestingSystem2>(entityManager, eventDispatcher, 0.016);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->updateCounter,
            1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->updateCounter,
            1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 1);

  systemManager->update<TestingSystem>(entityManager, eventDispatcher, 0.016);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->updateCounter,
            2);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->updateCounter,
            1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 1);
}

TEST_F(SystemManagerTest, GetSystemNotAdded) {
  expectDefault();
  EXPECT_FALSE(systemManager->getSystem<TestingSystem3>().has_value());
  EXPECT_FALSE(systemManager->getSystem<TestingSystem4>().has_value());
  expectDefault();
}

TEST_F(SystemManagerTest, GetAddedSystem) {
  expectDefault();
  EXPECT_TRUE(systemManager->getSystem<TestingSystem>().has_value());
  EXPECT_TRUE(systemManager->getSystem<TestingSystem2>().has_value());
  expectDefault();
}

TEST_F(SystemManagerTest, UpdateSystemNotAdded) {
  expectDefault();
  systemManager->update<TestingSystem3>(entityManager, eventDispatcher, 0.016);
  systemManager->update<TestingSystem4>(entityManager, eventDispatcher, 0.016);
  expectDefault();
}

TEST_F(SystemManagerTest, InitializeOneSystem) {
  expectDefault();

  systemManager->initialize<TestingSystem3>(entityManager, eventDispatcher);
  expectDefault();

  EXPECT_FALSE(
      systemManager->getSystem<TestingSystem>().value()->isInitialized());
  EXPECT_FALSE(
      systemManager->getSystem<TestingSystem2>().value()->isInitialized());

  systemManager->initialize<TestingSystem>(entityManager, eventDispatcher);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->updateCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->updateCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 0);
  EXPECT_TRUE(
      systemManager->getSystem<TestingSystem>().value()->isInitialized());
  EXPECT_FALSE(
      systemManager->getSystem<TestingSystem2>().value()->isInitialized());

  systemManager->initialize<TestingSystem2>(entityManager, eventDispatcher);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->updateCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->updateCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 1);
  EXPECT_TRUE(
      systemManager->getSystem<TestingSystem>().value()->isInitialized());
  EXPECT_TRUE(
      systemManager->getSystem<TestingSystem2>().value()->isInitialized());
}

TEST_F(SystemManagerTest, shutdownOneSystem) {
  expectDefault();

  systemManager->initialize(entityManager, eventDispatcher);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->updateCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->updateCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->shutdownCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->shutdownCounter,
            0);
  EXPECT_TRUE(
      systemManager->getSystem<TestingSystem>().value()->isInitialized());
  EXPECT_TRUE(
      systemManager->getSystem<TestingSystem2>().value()->isInitialized());

  systemManager->shutdown<TestingSystem>(entityManager, eventDispatcher);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->updateCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->updateCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->shutdownCounter,
            1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->shutdownCounter,
            0);
  EXPECT_FALSE(
      systemManager->getSystem<TestingSystem>().value()->isInitialized());
  EXPECT_TRUE(
      systemManager->getSystem<TestingSystem2>().value()->isInitialized());

  systemManager->shutdown<TestingSystem2>(entityManager, eventDispatcher);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->updateCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->updateCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->shutdownCounter,
            1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->shutdownCounter,
            1);
  EXPECT_FALSE(
      systemManager->getSystem<TestingSystem>().value()->isInitialized());
  EXPECT_FALSE(
      systemManager->getSystem<TestingSystem2>().value()->isInitialized());
  EXPECT_TRUE(systemManager->getSystem<TestingSystem>().value()->isShutdown());
  EXPECT_TRUE(systemManager->getSystem<TestingSystem2>().value()->isShutdown());
}
}  // namespace Neat