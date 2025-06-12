#include <gtest/gtest.h>
#include <string>

#include <Neat/Events/EventConnections.hpp>

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
  bool handle(const EventA& event) {
    std::cout << "ListenerA EventA: val=" << event.val << std::endl;
    count++;
    val = event.val;
    return false;
  }
  int val = 0;
  int count = 0;
};

struct ListenerB {
  bool process(const EventB& event) {
    std::cout << "ListenerB EventB: msg=" << event.msg << std::endl;
    count++;
    msg = event.msg;
    return false;
  }
  bool handleEventC(const EventC& event) {
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
  bool handle(const EventC& event) {
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

class EventConnectionsTest : public testing::Test {
 protected:
  EventConnectionsTest() {
    connA.connect<&ListenerA::handle>(listenerA);
    connB.connect<&ListenerB::process>(listenerB);
    connC.connect<&ListenerB::handleEventC>(listenerB);
    connC.connect<&ListenerC::handle>(listenerC);
  }
  Neat::EventConnections<EventA> connA{};
  Neat::EventConnections<EventB> connB{};
  Neat::EventConnections<EventC> connC{};
  Neat::EventConnections<EventC> connC2{};
  ListenerA listenerA{};
  ListenerB listenerB{};
  ListenerC listenerC{};
  ListenerB listenerB2{};
  ListenerC listenerC2{};
};

TEST_F(EventConnectionsTest, SendEventsConnectingAndDisconnecting) {
  std::cout << "Sending event" << std::endl;
  connA.update(EventA(100));
  EXPECT_EQ(listenerA.val, 100);
  EXPECT_EQ(listenerA.count, 1);

  std::cout << "Sending event" << std::endl;
  connA.update(EventA(200));
  EXPECT_EQ(listenerA.val, 200);
  EXPECT_EQ(listenerA.count, 2);

  connA.disconnect<&ListenerA::handle>(listenerA);
  std::cout << "Sending event" << std::endl;
  connA.update(EventA(300));
  EXPECT_EQ(listenerA.val, 200);
  EXPECT_EQ(listenerA.count, 2);
}

TEST_F(EventConnectionsTest, MultipleEventListeners) {
  std::string msg{"My message"};
  std::string msg2{"My message"};

  std::cout << "Sending events" << std::endl;
  connA.update(EventA(100));
  connB.update(EventB(msg));
  connC.update(EventC(3.14f, 2.72f));
  connB.update(EventB(msg2));

  EXPECT_EQ(listenerA.val, 100);
  EXPECT_EQ(listenerA.count, 1);
  EXPECT_EQ(listenerB.posX, 3.14f);
  EXPECT_EQ(listenerB.posY, 2.72f);
  EXPECT_EQ(listenerB.msg, msg2);
  EXPECT_EQ(listenerB.count, 3);
  EXPECT_EQ(listenerC.posX, 3.14f);
  EXPECT_EQ(listenerC.posY, 2.72f);
  EXPECT_EQ(listenerC.count, 1);
}

TEST_F(EventConnectionsTest, EventHandled) {
  connC2.connect<&ListenerC::handle>(listenerC2);  // listenerC2 connects first
  connC2.connect<&ListenerB::handleEventC>(listenerB2);

  std::cout << "Sending event" << std::endl;
  connC2.update(
      EventC(1.11f, 2.22f));  // listenerC2 handles the event (returns true)
  EXPECT_EQ(listenerC2.posX, 1.11f);
  EXPECT_EQ(listenerC2.posY, 2.22f);
  EXPECT_EQ(listenerC2.count, 1);

  // listenerB2 won't handle the event
  EXPECT_EQ(listenerB2.posX, 0.0f);
  EXPECT_EQ(listenerB2.posY, 0.0f);
  EXPECT_EQ(listenerB2.msg, "");
  EXPECT_EQ(listenerB2.count, 0);
}