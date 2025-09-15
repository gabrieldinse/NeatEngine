#pragma once

#include <string>
#include <Neat/ECS/ECS.hpp>
#include <Neat/Math/Math.hpp>

namespace Neat {
struct EventA {
  int val;
};

struct EventB {
  std::string msg;
};

struct EventC {
  float posX;
  float posY;
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

struct TestingSystem : public System<TestingSystem> {
  TestingSystem() = default;

  virtual void onUpdate([[maybe_unused]] Ref<EntityManager> &entityManager,
                        [[maybe_unused]] Ref<EventDispatcher> &eventDispatcher,
                        [[maybe_unused]] double deltaTimeSeconds) override {
    onUpdateCounter++;
  }
  virtual void initialize(
      [[maybe_unused]] Ref<EntityManager> &entityManager,
      [[maybe_unused]] Ref<EventDispatcher> &eventDispatcher) override {
    initCounter++;
  }

  int initCounter = 0;
  int onUpdateCounter = 0;
};

struct TestingSystem2 : public System<TestingSystem2> {
  TestingSystem2() = default;

  virtual void onUpdate([[maybe_unused]] Ref<EntityManager> &entityManager,
                        [[maybe_unused]] Ref<EventDispatcher> &eventDispatcher,
                        [[maybe_unused]] double deltaTimeSeconds) override {
    onUpdateCounter++;
  }
  virtual void initialize(
      [[maybe_unused]] Ref<EntityManager> &entityManager,
      [[maybe_unused]] Ref<EventDispatcher> &eventDispatcher) override {
    initCounter++;
  }

  int initCounter = 0;
  int onUpdateCounter = 0;
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

}  // namespace Neat
