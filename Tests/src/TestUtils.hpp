#pragma once

#include <string>
#include <iostream>
#include <Neat/ECS/ECS.hpp>

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
    std::cout << "ListenerA EventA: val=" << event.val << std::endl;
    count++;
    val = event.val;
    return false;
  }
  int val = 0;
  int count = 0;
};

struct ListenerB {
  bool process(const EventB &event) {
    std::cout << "ListenerB EventB: msg=" << event.msg << std::endl;
    count++;
    msg = event.msg;
    return false;
  }
  bool handleEventC(const EventC &event) {
    std::cout << "ListenerB EventC: posX=" << event.posX
              << ", posY=" << event.posY << std::endl;
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
    std::cout << "ListenerC EventC: posX=" << event.posX
              << ", posY=" << event.posY << std::endl;
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
    std::cout << "ListenerD EventA: val=" << event.val << std::endl;
    count++;
    val = event.val;
    return true;
  }
  int val = 0;
  int count = 0;
};

struct TestingSystem : public System<TestingSystem> {
  TestingSystem() = default;

  virtual void onUpdate(Ref<EntityManager> &entityManager,
                        Ref<EventDispatcher> &eventDispatcher,
                        double deltaTimeSeconds) override {
    onUpdateCounter++;
  }
  virtual void init(Ref<EntityManager> &entityManager,
                    Ref<EventDispatcher> &eventDispatcher) override {
    initCounter++;
  }

  int initCounter = 0;
  int onUpdateCounter = 0;
};

struct TestingSystem2 : public System<TestingSystem2> {
  TestingSystem2() = default;

  virtual void onUpdate(Ref<EntityManager> &entityManager,
                        Ref<EventDispatcher> &eventDispatcher,
                        double deltaTimeSeconds) override {
    onUpdateCounter++;
  }
  virtual void init(Ref<EntityManager> &entityManager,
                    Ref<EventDispatcher> &eventDispatcher) override {
    initCounter++;
  }

  int initCounter = 0;
  int onUpdateCounter = 0;
};

struct TestingSystem3 : public System<TestingSystem3> {};
struct TestingSystem4 : public System<TestingSystem4> {};
}  // namespace Neat