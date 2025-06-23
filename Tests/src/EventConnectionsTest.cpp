#include <gtest/gtest.h>

#include <Neat/Events/EventConnections.hpp>
#include <TestUtils.hpp>

class EventConnectionsTest : public testing::Test {
 protected:
  EventConnectionsTest() {
    connA.connect<&ListenerA::handle>(listenerA);
    connB.connect<&ListenerB::process>(listenerB);
    connC.connect<&ListenerB::handleEventC>(listenerB);
    connC.connect<&ListenerC::handle>(listenerC);
    connA.connect<&ListenerD::handleA>(listenerD);
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
  ListenerD listenerD{};
};

TEST_F(EventConnectionsTest, SendEventsConnectingAndDisconnecting) {
  connA.update(EventA{100});
  EXPECT_EQ(listenerA.val, 100);
  EXPECT_EQ(listenerA.count, 1);

  connA.update(EventA{200});
  EXPECT_EQ(listenerA.val, 200);
  EXPECT_EQ(listenerA.count, 2);

  connA.disconnect<&ListenerA::handle>(listenerA);
  connA.update(EventA{300});
  EXPECT_EQ(listenerA.val, 200);
  EXPECT_EQ(listenerA.count, 2);
}

TEST_F(EventConnectionsTest, MultipleEventListeners) {
  std::string msg{"My message"};
  std::string msg2{"My message"};

  connA.update(EventA{100});
  connB.update(EventB{msg});
  connC.update(EventC{3.14f, 2.72f});
  connB.update(EventB{msg2});

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

  connC2.update(
      EventC{1.11f, 2.22f});  // listenerC2 handles the event (returns true)
  EXPECT_EQ(listenerC2.posX, 1.11f);
  EXPECT_EQ(listenerC2.posY, 2.22f);
  EXPECT_EQ(listenerC2.count, 1);

  // listenerB2 won't handle the event
  EXPECT_EQ(listenerB2.posX, 0.0f);
  EXPECT_EQ(listenerB2.posY, 0.0f);
  EXPECT_EQ(listenerB2.msg, "");
  EXPECT_EQ(listenerB2.count, 0);
}

TEST_F(EventConnectionsTest, MultipleEventListenersVariadicTemplate) {
  std::string msg{"My message"};
  std::string msg2{"My message"};

  connA.update(100);
  connB.update(msg);
  connC.update(3.14f, 2.72f);
  connB.update(msg2);

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

TEST_F(EventConnectionsTest, MultipleEventListenersConstReference) {
  std::string msg{"My message"};
  std::string msg2{"My message"};

  EventA eventA{100};
  EventB eventB{msg};
  EventC eventC{3.14f, 2.72f};
  EventB eventB2{msg2};
  connA.update(eventA);
  connB.update(eventB);
  connC.update(eventC);
  connB.update(eventB2);

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

TEST_F(EventConnectionsTest, ConnectWithPriority) {
  std::string msg{"My message"};
  std::string msg2{"My message"};

  connA.disconnect<&ListenerA::handle>(listenerA);
  connB.disconnect<&ListenerB::process>(listenerB);
  connC.disconnect<&ListenerB::handleEventC>(listenerB);
  connC.disconnect<&ListenerC::handle>(listenerC);
  connA.disconnect<&ListenerD::handleA>(listenerD);

  connA.connect<&ListenerA::handle>(listenerA, 10000);
  connB.connect<&ListenerB::process>(listenerB, 20000);
  connC.connect<&ListenerC::handle>(listenerC, 5);
  connC.connect<&ListenerB::handleEventC>(listenerB, 5);
  connA.connect<&ListenerD::handleA>(listenerD, 3);

  EventA eventA{100};
  EventB eventB{msg};
  EventC eventC{3.14f, 2.72f};
  EventB eventB2{msg2};
  connA.update(100);
  connB.update(msg);
  connC.update(3.33f, 2.22f);
  connB.update(msg2);

  EXPECT_EQ(listenerA.val, 0);
  EXPECT_EQ(listenerA.count, 0);
  EXPECT_EQ(listenerB.posX, 0.0f);
  EXPECT_EQ(listenerB.posY, 0.0f);
  EXPECT_EQ(listenerB.msg, msg2);
  EXPECT_EQ(listenerB.count, 2);
  EXPECT_EQ(listenerC.posX, 3.33f);
  EXPECT_EQ(listenerC.posY, 2.22f);
  EXPECT_EQ(listenerC.count, 1);
  EXPECT_EQ(listenerD.val, 100);
  EXPECT_EQ(listenerD.count, 1);
}