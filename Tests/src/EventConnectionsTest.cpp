#include <gtest/gtest.h>

#include <EventDispatching/EventConnections.hpp>
#include <TestUtils.hpp>

namespace Neat {
bool calledNonMember = false;

bool foo(const EventA &event) {
  EXPECT_EQ(event.val, 1234);
  calledNonMember = true;
  return false;
}

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

TEST_F(EventConnectionsTest, EnableAndDisable) {
  connALayer.update(EventA{100});
  EXPECT_EQ(listenerALayer.val, 100);
  EXPECT_EQ(listenerALayer.count, 1);

  connALayer.update(EventA{200});
  EXPECT_EQ(listenerALayer.val, 200);
  EXPECT_EQ(listenerALayer.count, 2);

  connBLayer.disable(layerID);

  connBLayer.update(EventB{msg});
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
  connBLayer.update(EventB{msg});
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

    connA.update(100);
    connB.update(msg);
    connC.update(3.33f, 2.22f);
    connB.update(msg2);

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

  connA.update(500);
  connB.update(msg + " after scope");
  connC.update(999.9f, 888.8f);
  connB.update(msg2 + " after scope");

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

  connA.update(800);
  connB.update(msg + " after reset");
  connC.update(123.456f, 654.321f);
  connB.update(msg2 + " after reset");

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

TEST_F(EventConnectionsTest, NonMemberFunctionUpdate) {
  EventConnections<EventA> connNonMember{};

  calledNonMember = false;
  connNonMember.connect([](const EventA &event) {
    EXPECT_EQ(event.val, 1234);
    calledNonMember = true;
    return false;
  });

  connNonMember.update(EventA{1234});
  EXPECT_TRUE(calledNonMember);
}

TEST_F(EventConnectionsTest, PlainFunctionUpdate) {
  EventConnections<EventA> connNonMember{};

  calledNonMember = false;
  connNonMember.connect<foo>();

  connNonMember.update(EventA{1234});
  EXPECT_TRUE(calledNonMember);
}

TEST_F(EventConnectionsTest, NonMemberFunctionConnectAndDisconnect) {
  EventConnections<EventA> connNonMember{};

  auto nonMemberFunc = [](const EventA &event) {
    EXPECT_EQ(event.val, 1234);
    calledNonMember = true;
    return false;
  };

  connNonMember.connect(nonMemberFunc);

  connNonMember.update(EventA{1234});
  EXPECT_TRUE(calledNonMember);

  calledNonMember = false;
  connNonMember.disconnect(nonMemberFunc);
}

TEST_F(EventConnectionsTest, NonMemberFunctionConnectScoped) {
  EventConnections<EventA> connNonMember{};

  auto nonMemberFunc = [](const EventA &event) {
    EXPECT_EQ(event.val, 1234);
    calledNonMember = true;
    return false;
  };

  calledNonMember = false;
  auto connScope = connNonMember.connectScoped(nonMemberFunc);

  connNonMember.update(EventA{1234});
  EXPECT_TRUE(calledNonMember);

  calledNonMember = false;
  connScope.reset();

  connNonMember.update(EventA{1234});
  EXPECT_FALSE(calledNonMember);

  {
    auto connScope2 = connNonMember.connectScoped(nonMemberFunc);
    calledNonMember = false;
    connNonMember.update(EventA{1234});
    EXPECT_TRUE(calledNonMember);
    calledNonMember = false;
  }

  // Here, connScope2 is out of scope and thus disconnected
  connNonMember.update(EventA{1234});
  EXPECT_FALSE(calledNonMember);
}

TEST_F(EventConnectionsTest, LambdaWithCaptureUpdate) {
  EventConnections<EventA> connLambdaWithCapture{};
  bool localCalled = false;

  connLambdaWithCapture.connect([&](const EventA &event) {
    EXPECT_EQ(event.val, 1234);
    localCalled = true;
    return false;
  });

  connLambdaWithCapture.update(EventA{1234});
  EXPECT_TRUE(localCalled);
}

TEST_F(EventConnectionsTest, LambdaWithCaptureConnectAndDisconnect) {
  EventConnections<EventA> connLambdaWithCapture{};
  bool localCalled = false;

  auto lambdaWithCapture = [&](const EventA &event) {
    EXPECT_EQ(event.val, 1234);
    localCalled = true;
    return false;
  };

  connLambdaWithCapture.connect(lambdaWithCapture);

  connLambdaWithCapture.update(EventA{1234});
  EXPECT_TRUE(localCalled);

  localCalled = false;
  connLambdaWithCapture.disconnect(lambdaWithCapture);
}

TEST_F(EventConnectionsTest, LambdaWithCaptureConnectScoped) {
  EventConnections<EventA> connLambdaWithCapture{};
  bool localCalled = false;

  auto lambdaWithCapture = [&](const EventA &event) {
    EXPECT_EQ(event.val, 1234);
    localCalled = true;
    return false;
  };

  localCalled = false;
  auto connScope = connLambdaWithCapture.connectScoped(lambdaWithCapture);

  connLambdaWithCapture.update(EventA{1234});
  EXPECT_TRUE(localCalled);

  localCalled = false;
  connScope.reset();

  connLambdaWithCapture.update(EventA{1234});
  EXPECT_FALSE(localCalled);

  {
    auto connScope2 = connLambdaWithCapture.connectScoped(lambdaWithCapture);
    localCalled = false;
    connLambdaWithCapture.update(EventA{1234});
    EXPECT_TRUE(localCalled);
    localCalled = false;
  }

  // Here, connScope2 is out of scope and thus disconnected
  connLambdaWithCapture.update(EventA{1234});
  EXPECT_FALSE(localCalled);
}
}  // namespace Neat