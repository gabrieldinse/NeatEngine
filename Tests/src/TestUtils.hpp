#pragma once

#include <string>
#include <type_traits>

#include <ECS/ECS.hpp>
#include <Math/Math.hpp>
#include <Core/Layer.hpp>
#include <Core/Limits.hpp>
#include <Core/Constants.hpp>

namespace Neat {
struct EventA {
  int val = 0;
};

struct EventB {
  std::string msg{};
};

struct EventC {
  float posX = 0.0f;
  float posY = 0.0f;
};

struct ListenerA {
  bool handle(const EventA &event) {
    count++;
    val = event.val;
    return false;
  }
  int val = 0;
  int count = 0;
};

struct MyStruct {
  void foo() {}
};
struct MyOtherStruct {
  int method(int) { return 0x123; }
};
struct ThirdStruct : public MyStruct {};

struct ListenerB {
  bool process(const EventB &event) {
    count++;
    msg = event.msg;
    return false;
  }
  bool handleEventC(const EventC &event) {
    count++;
    posX = event.posX;
    posY = event.posY;
    return false;
  }
  std::string msg{};
  float posX = 0.0f;
  float posY = 0.0f;
  int count = 0;
};

struct ListenerC {
  bool handle(const EventC &event) {
    count++;
    posX = event.posX;
    posY = event.posY;
    return true;
  }
  float posX = 0.0f;
  float posY = 0.0f;
  int count = 0;
};

struct ListenerD {
  bool handleA(const EventA &event) {
    count++;
    val = event.val;
    return true;
  }
  int val = 0;
  int count = 0;
};

int func1(int x);
int func2(int x);

struct TestingSystem : public System<TestingSystem> {
  TestingSystem() = default;

  virtual void onUpdate(
      [[maybe_unused]] const Ref<EntityManager> &entityManager,
      [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
      [[maybe_unused]] double deltaTimeSeconds,
      [[maybe_unused]] LayerID layerID = NoneLayer) override {
    updateCounter++;
  }
  virtual void onInitialize(
      [[maybe_unused]] const Ref<EntityManager> &entityManager,
      [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
      [[maybe_unused]] LayerID layerID = NoneLayer) override {
    initCounter++;
  }
  virtual void onShutdown(
      [[maybe_unused]] const Ref<EntityManager> &entityManager,
      [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
      [[maybe_unused]] LayerID layerID = NoneLayer) override {
    shutdownCounter++;
  }

  int initCounter = 0;
  int updateCounter = 0;
  int shutdownCounter = 0;
};

struct TestingSystem2 : public System<TestingSystem2> {
  TestingSystem2() = default;

  virtual void onUpdate(
      [[maybe_unused]] const Ref<EntityManager> &entityManager,
      [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
      [[maybe_unused]] double deltaTimeSeconds,
      [[maybe_unused]] LayerID layerID = NoneLayer) override {
    updateCounter++;
  }
  virtual void onInitialize(
      [[maybe_unused]] const Ref<EntityManager> &entityManager,
      [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
      [[maybe_unused]] LayerID layerID = NoneLayer) override {
    initCounter++;
  }
  virtual void onShutdown(
      [[maybe_unused]] const Ref<EntityManager> &entityManager,
      [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
      [[maybe_unused]] LayerID layerID = NoneLayer) override {
    shutdownCounter++;
  }

  int initCounter = 0;
  int updateCounter = 0;
  int shutdownCounter = 0;
};

struct TestingSystem3 : public System<TestingSystem3> {};
struct TestingSystem4 : public System<TestingSystem4> {};

struct SpeedComponent {
  Vector3F velocity{0.0f, 0.0f, 0.0f};

  bool operator==(const SpeedComponent &other) const {
    return velocity == other.velocity;
  }
};

struct PlayerStatsComponent {
  int health = 0;
  int mana = 0;
  int damage = 0;

  bool operator==(const PlayerStatsComponent &other) const {
    return health == other.health and mana == other.mana and
           damage == other.damage;
  }
};

struct InventoryComponent {
  std::vector<std::string> items{};

  bool operator==(const InventoryComponent &other) const {
    return items == other.items;
  }
};

struct InvalidComponent {};

class TestingLayer : public Layer {
 public:
  TestingLayer() { layerID = layerIDCounter++; }
  virtual void attach() override { attached = true; }
  virtual void detach() override { detached = true; }
  virtual void update([[maybe_unused]] double deltaTimeSeconds = 0.0) override {
    updated = true;
  }
  bool attached = false;
  bool detached = false;
  bool updated = false;
  int updateIndex = 0;
  LayerID layerID;
  static inline LayerID layerIDCounter = 0;
};

template <typename T>
void expectNearVectorValues(const T &vecA, const T &vecB) {
  if constexpr (std::is_floating_point_v<typename T::ValueType>) {
    for (UInt32 i = 0; i < T::N; ++i) {
      if constexpr (std::is_same_v<typename T::ValueType, float>) {
        EXPECT_NEAR(vecA.elements[i], vecB.elements[i], 1e-4f);
      } else {
        EXPECT_NEAR(vecA.elements[i], vecB.elements[i], 1e-6f);
      }
    }
  } else {
    EXPECT_EQ(vecA, vecB);
  }
}
}  // namespace Neat
