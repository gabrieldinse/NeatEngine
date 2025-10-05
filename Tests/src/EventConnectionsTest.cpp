#include <gtest/gtest.h>

#include <Neat/EventDispatching/EventConnections.hpp>
#include <TestUtils.hpp>

namespace Neat {
class EventConnectionsTest : public testing::Test {
 protected:
  EventConnectionsTest() {
    connA.connect<&ListenerA::handle>(listenerA);
    connB.connect<&ListenerB::process>(listenerB);
    connC.connect<&ListenerB::handleEventC>(listenerB);
    connC.connect<&ListenerC::handle>(listenerC);
    connA.connect<&ListenerD::handleA>(listenerD);

    connALayer.connect<&ListenerA::handle>(listenerALayer, 0, layerID);
    connBLayer.connect<&ListenerB::process>(listenerBLayer, 0, layerID);
    connCLayer.connect<&ListenerB::handleEventC>(listenerBLayer, 0, layerID);
    connCLayer.connect<&ListenerC::handle>(listenerCLayer, 0, layerID);

    connBLayer.connect<&ListenerB::process>(listenerB2Layer, 0, layerID2);
  }
  EventConnections<EventA> connA{};
  EventConnections<EventB> connB{};
  EventConnections<EventC> connC{};
  EventConnections<EventC> connC2{};
  ListenerA listenerA{};
  ListenerB listenerB{};
  ListenerC listenerC{};
  ListenerB listenerB2{};
  ListenerC listenerC2{};
  ListenerD listenerD{};

  EventConnections<EventA> connALayer{};
  EventConnections<EventB> connBLayer{};
  EventConnections<EventC> connCLayer{};
  const LayerID layerID{100};
  const LayerID layerID2{101};
  ListenerA listenerALayer{};
  ListenerB listenerBLayer{};
  ListenerB listenerB2Layer{};
  ListenerC listenerCLayer{};

  std::string msg{"My message"};
  std::string msg2{"My message"};
};

TEST_F(EventConnectionsTest, ConnectAndDisconnect) {
  connA.onUpdate(EventA{100});
  EXPECT_EQ(listenerA.val, 100);
  EXPECT_EQ(listenerA.count, 1);

  connA.onUpdate(EventA{200});
  EXPECT_EQ(listenerA.val, 200);
  EXPECT_EQ(listenerA.count, 2);

  connA.disconnect<&ListenerA::handle>(listenerA);
  connA.onUpdate(EventA{300});
  EXPECT_EQ(listenerA.val, 200);
  EXPECT_EQ(listenerA.count, 2);
}

TEST_F(EventConnectionsTest, EnableAndDisable) {
  connALayer.onUpdate(EventA{100});
  EXPECT_EQ(listenerALayer.val, 100);
  EXPECT_EQ(listenerALayer.count, 1);

  connALayer.onUpdate(EventA{200});
  EXPECT_EQ(listenerALayer.val, 200);
  EXPECT_EQ(listenerALayer.count, 2);

  connBLayer.disable(layerID);

  connBLayer.onUpdate(EventB{msg});
  EXPECT_EQ(listenerALayer.val, 200);
  EXPECT_EQ(listenerALayer.count, 2);
  EXPECT_EQ(listenerBLayer.posX, 0.0f);
  EXPECT_EQ(listenerBLayer.posY, 0.0f);
  EXPECT_EQ(listenerBLayer.msg, "");
  EXPECT_EQ(listenerBLayer.count, 0);
  EXPECT_EQ(listenerB2Layer.posX, 0.0f);
  EXPECT_EQ(listenerB2Layer.posY, 0.0f);
  EXPECT_EQ(listenerB2Layer.msg, msg);
  EXPECT_EQ(listenerB2Layer.count, 1);

  connBLayer.enable(layerID);
  connBLayer.onUpdate(EventB{msg});
  EXPECT_EQ(listenerALayer.val, 200);
  EXPECT_EQ(listenerALayer.count, 2);
  EXPECT_EQ(listenerBLayer.posX, 0.0f);
  EXPECT_EQ(listenerBLayer.posY, 0.0f);
  EXPECT_EQ(listenerBLayer.msg, msg);
  EXPECT_EQ(listenerBLayer.count, 1);
  EXPECT_EQ(listenerB2Layer.posX, 0.0f);
  EXPECT_EQ(listenerB2Layer.posY, 0.0f);
  EXPECT_EQ(listenerB2Layer.msg, msg);
  EXPECT_EQ(listenerB2Layer.count, 2);
}

TEST_F(EventConnectionsTest, MultipleEventListeners) {
  connA.onUpdate(EventA{100});
  connB.onUpdate(EventB{msg});
  connC.onUpdate(EventC{3.14f, 2.72f});
  connB.onUpdate(EventB{msg2});

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

  connC2.onUpdate(
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
  connA.onUpdate(100);
  connB.onUpdate(msg);
  connC.onUpdate(3.14f, 2.72f);
  connB.onUpdate(msg2);

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
  EventA eventA{100};
  EventB eventB{msg};
  EventC eventC{3.14f, 2.72f};
  EventB eventB2{msg2};
  connA.onUpdate(eventA);
  connB.onUpdate(eventB);
  connC.onUpdate(eventC);
  connB.onUpdate(eventB2);

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

  connA.onUpdate(100);
  connB.onUpdate(msg);
  connC.onUpdate(3.33f, 2.22f);
  connB.onUpdate(msg2);

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

TEST_F(EventConnectionsTest, ConnectScoped) {
  connA.disconnect<&ListenerA::handle>(listenerA);
  connB.disconnect<&ListenerB::process>(listenerB);
  connC.disconnect<&ListenerB::handleEventC>(listenerB);
  connC.disconnect<&ListenerC::handle>(listenerC);
  connA.disconnect<&ListenerD::handleA>(listenerD);

  auto connAScope = connA.connectScoped<&ListenerA::handle>(listenerA);
  auto connBScope = connB.connectScoped<&ListenerB::process>(listenerB);

  {
    auto connB2Scope = connC.connectScoped<&ListenerB::handleEventC>(listenerB);
    auto connCScope = connC.connectScoped<&ListenerC::handle>(listenerC);

    connA.onUpdate(100);
    connB.onUpdate(msg);
    connC.onUpdate(3.33f, 2.22f);
    connB.onUpdate(msg2);

    EXPECT_EQ(listenerA.val, 100);
    EXPECT_EQ(listenerA.count, 1);
    EXPECT_EQ(listenerB.posX, 3.33f);
    EXPECT_EQ(listenerB.posY, 2.22f);
    EXPECT_EQ(listenerB.msg, msg2);
    EXPECT_EQ(listenerB.count, 3);
    EXPECT_EQ(listenerC.posX, 3.33f);
    EXPECT_EQ(listenerC.posY, 2.22f);
    EXPECT_EQ(listenerC.count, 1);
  }

  // Here, connCScope and connB2Scope are out of scope and thus disconnected

  connA.onUpdate(500);
  connB.onUpdate(msg + " after scope");
  connC.onUpdate(999.9f, 888.8f);
  connB.onUpdate(msg2 + " after scope");

  EXPECT_EQ(listenerA.val, 500);
  EXPECT_EQ(listenerA.count, 2);
  EXPECT_EQ(listenerB.posX, 3.33f);
  EXPECT_EQ(listenerB.posY, 2.22f);
  EXPECT_EQ(listenerB.msg, msg2 + " after scope");
  EXPECT_EQ(listenerB.count, 5);
  EXPECT_EQ(listenerC.posX, 3.33f);
  EXPECT_EQ(listenerC.posY, 2.22f);
  EXPECT_EQ(listenerC.count, 1);

  connAScope.reset();
  // Now, connAScope is disconnected

  connA.onUpdate(800);
  connB.onUpdate(msg + " after reset");
  connC.onUpdate(123.456f, 654.321f);
  connB.onUpdate(msg2 + " after reset");

  EXPECT_EQ(listenerA.val, 500);
  EXPECT_EQ(listenerA.count, 2);
  EXPECT_EQ(listenerB.posX, 3.33f);
  EXPECT_EQ(listenerB.posY, 2.22f);
  EXPECT_EQ(listenerB.msg, msg2 + " after reset");
  EXPECT_EQ(listenerB.count, 7);
  EXPECT_EQ(listenerC.posX, 3.33f);
  EXPECT_EQ(listenerC.posY, 2.22f);
  EXPECT_EQ(listenerC.count, 1);
}
}  // namespace Neat