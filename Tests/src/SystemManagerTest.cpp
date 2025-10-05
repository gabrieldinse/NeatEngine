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
    EXPECT_EQ(
        systemManager->getSystem<TestingSystem>().value()->onUpdateCounter, 0);
    EXPECT_EQ(
        systemManager->getSystem<TestingSystem2>().value()->onUpdateCounter, 0);
    EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter,
              0);
    EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter,
              0);
  }
  void expectInitialized() {
    EXPECT_EQ(
        systemManager->getSystem<TestingSystem>().value()->onUpdateCounter, 0);
    EXPECT_EQ(
        systemManager->getSystem<TestingSystem2>().value()->onUpdateCounter, 0);
    EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter,
              1);
    EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter,
              1);
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
}

TEST_F(SystemManagerTest, UpdateAllSystems) {
  expectDefault();
  systemManager->updateAll(entityManager, eventDispatcher, 0.016);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->onUpdateCounter,
            1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->onUpdateCounter,
            1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 1);

  systemManager->updateAll(entityManager, eventDispatcher, 0.016);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->onUpdateCounter,
            2);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->onUpdateCounter,
            2);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 1);
}

TEST_F(SystemManagerTest, UpdateOneSystem) {
  expectDefault();
  systemManager->onUpdate<TestingSystem>(entityManager, eventDispatcher, 0.016);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->onUpdateCounter,
            1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->onUpdateCounter,
            0);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 1);

  systemManager->onUpdate<TestingSystem2>(entityManager, eventDispatcher,
                                          0.016);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->onUpdateCounter,
            1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->onUpdateCounter,
            1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->initCounter, 1);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->initCounter, 1);

  systemManager->onUpdate<TestingSystem>(entityManager, eventDispatcher, 0.016);
  EXPECT_EQ(systemManager->getSystem<TestingSystem>().value()->onUpdateCounter,
            2);
  EXPECT_EQ(systemManager->getSystem<TestingSystem2>().value()->onUpdateCounter,
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
  systemManager->onUpdate<TestingSystem3>(entityManager, eventDispatcher,
                                          0.016);
  systemManager->onUpdate<TestingSystem4>(entityManager, eventDispatcher,
                                          0.016);
  expectInitialized();
}
}  // namespace Neat