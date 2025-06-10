#include <gtest/gtest.h>
#include <string>

#include <Neat/Events/EventConnections.hpp>

struct EventA { int val; };
struct EventB { std::string msg; };
struct EventC { float posX; float posY; };

struct ListenerA {
  bool handle(const EventA& event) {
    std::cout << "EventA: val=" << event.val << std::endl;
    count++;
    val = event.val;
    return true;
  }
  int val = 0;
  int count = 0;
};

struct ListenerB {
  bool process(const EventB& event) {
    std::cout << "EventB: msg=" << event.msg << std::endl;
    count++;
    msg = event.msg;
    return true;
  }
  bool handleEventC(const EventC& event) {
    std::cout << "EventC: posX=" << event.posX << ", posY=" << event.posY << std::endl;
    count++;
    posX = event.posX;
    posY = event.posY;
    return true;
  }
  std::string msg;
  float posX = 0.0f;
  float posY = 0.0f;
  int count = 0;
};

TEST(EventsConnectionsTest, TestDifferentClassesIds) {
    Neat::EventConnections<EventA> connA{};
    Neat::EventConnections<EventB> connB{};
    Neat::EventConnections<EventC> connC{};
    ListenerA listenerA{};
    ListenerB listenerB{};

    connA.connect<&ListenerA::handle>(listenerA);
    connA.enqueue(100);
    std::cout << "Sending events" << std::endl;
    connA.update();
    EXPECT_EQ(listenerA.val, 100);
    EXPECT_EQ(listenerA.count, 1);
}