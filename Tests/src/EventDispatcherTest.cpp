#include <gtest/gtest.h>

#include <Neat/Events/EventDispatcher.hpp>
#include <TestUtils.hpp>

class EventDispatcherTest : public testing::Test {
 protected:
  EventDispatcherTest() {
    dispatcher1.get<EventA>().connect<&ListenerA::handle>(listenerA);
    dispatcher1.get<EventB>().connect<&ListenerB::process>(listenerB);
    dispatcher1.get<EventC>().connect<&ListenerB::handleEventC>(listenerB);
    dispatcher1.get<EventC>().connect<&ListenerC::handle>(listenerC);
  }
  Neat::EventDispatcher dispatcher1{};
  Neat::EventDispatcher dispatcher2{};
  ListenerA listenerA{};
  ListenerB listenerB{};
  ListenerC listenerC{};
  ListenerB listenerB2{};
  ListenerC listenerC2{};
};

TEST_F(EventDispatcherTest, TriggerEvents) {
  dispatcher1.trigger(EventA{100});
  EXPECT_EQ(listenerA.val, 100);
  EXPECT_EQ(listenerA.count, 1);

  dispatcher1.trigger(EventA{200});
  EXPECT_EQ(listenerA.val, 200);
  EXPECT_EQ(listenerA.count, 2);

  dispatcher1.trigger<EventA>(300);
  EXPECT_EQ(listenerA.val, 300);
  EXPECT_EQ(listenerA.count, 3);

  EventA eventA{400};
  dispatcher1.trigger(eventA);
  EXPECT_EQ(listenerA.val, 400);
  EXPECT_EQ(listenerA.count, 4);
}

TEST_F(EventDispatcherTest, TriggerMultipleEventListeners) {
  std::string msg{"My message"};
  std::string msg2{"My message"};

  dispatcher1.trigger(EventA{100});
  dispatcher1.trigger(EventB{msg});
  dispatcher1.trigger(EventC{3.14f, 2.72f});
  dispatcher1.trigger(EventB{msg2});

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

TEST_F(EventDispatcherTest, DisconnectAndTrigger) {
  std::string msg{"My message"};
  std::string msg2{"My other message"};
  dispatcher1.get<EventA>().disconnect<&ListenerA::handle>(listenerA);

  dispatcher1.trigger(EventA{100});
  dispatcher1.trigger(EventB{msg});
  dispatcher1.trigger(EventC{3.14f, 2.72f});
  dispatcher1.trigger(EventB{msg2});

  EXPECT_EQ(listenerA.val, 0);
  EXPECT_EQ(listenerA.count, 0);
  EXPECT_EQ(listenerB.posX, 3.14f);
  EXPECT_EQ(listenerB.posY, 2.72f);
  EXPECT_EQ(listenerB.msg, msg2);
  EXPECT_EQ(listenerB.count, 3);
  EXPECT_EQ(listenerC.posX, 3.14f);
  EXPECT_EQ(listenerC.posY, 2.72f);
  EXPECT_EQ(listenerC.count, 1);

  dispatcher1.get<EventB>().disconnect<&ListenerB::process>(listenerB);

  dispatcher1.trigger(EventA{200});
  dispatcher1.trigger(EventB{msg + " extended"});
  dispatcher1.trigger(EventC{-1.0f, 0.5f});
  dispatcher1.trigger(EventB{msg2 + "modified"});

  EXPECT_EQ(listenerA.val, 0);
  EXPECT_EQ(listenerA.count, 0);
  EXPECT_EQ(listenerB.posX, -1.0f);
  EXPECT_EQ(listenerB.posY, 0.5f);
  EXPECT_EQ(listenerB.msg, msg2);
  EXPECT_EQ(listenerB.count, 4);
  EXPECT_EQ(listenerC.posX, -1.0);
  EXPECT_EQ(listenerC.posY, 0.5f);
  EXPECT_EQ(listenerC.count, 2);
}

// TEST_F(EventDispatcherTest, EventHandled) {
//   connC2.connect<&ListenerC::handle>(listenerC2);  // listenerC2 connects
//   first connC2.connect<&ListenerB::handleEventC>(listenerB2);
//
//   connC2.update(
//       EventC{1.11f, 2.22f});  // listenerC2 handles the event (returns true)
//   EXPECT_EQ(listenerC2.posX, 1.11f);
//   EXPECT_EQ(listenerC2.posY, 2.22f);
//   EXPECT_EQ(listenerC2.count, 1);
//
//   // listenerB2 won't handle the event
//   EXPECT_EQ(listenerB2.posX, 0.0f);
//   EXPECT_EQ(listenerB2.posY, 0.0f);
//   EXPECT_EQ(listenerB2.msg, "");
//   EXPECT_EQ(listenerB2.count, 0);
// }
//
// TEST_F(EventDispatcherTest, MultipleEventListenersVariadicTemplate) {
//   std::string msg{"My message"};
//   std::string msg2{"My message"};
//
//   connA.update(100);
//   connB.update(msg);
//   connC.update(3.14f, 2.72f);
//   connB.update(msg2);
//
//   EXPECT_EQ(listenerA.val, 100);
//   EXPECT_EQ(listenerA.count, 1);
//   EXPECT_EQ(listenerB.posX, 3.14f);
//   EXPECT_EQ(listenerB.posY, 2.72f);
//   EXPECT_EQ(listenerB.msg, msg2);
//   EXPECT_EQ(listenerB.count, 3);
//   EXPECT_EQ(listenerC.posX, 3.14f);
//   EXPECT_EQ(listenerC.posY, 2.72f);
//   EXPECT_EQ(listenerC.count, 1);
// }
//
// TEST_F(EventDispatcherTest, MultipleEventListenersConstReference) {
//   std::string msg{"My message"};
//   std::string msg2{"My message"};
//
//   EventA eventA{100};
//   EventB eventB{msg};
//   EventC eventC{3.14f, 2.72f};
//   EventB eventB2{msg2};
//   connA.update(eventA);
//   connB.update(eventB);
//   connC.update(eventC);
//   connB.update(eventB2);
//
//   EXPECT_EQ(listenerA.val, 100);
//   EXPECT_EQ(listenerA.count, 1);
//   EXPECT_EQ(listenerB.posX, 3.14f);
//   EXPECT_EQ(listenerB.posY, 2.72f);
//   EXPECT_EQ(listenerB.msg, msg2);
//   EXPECT_EQ(listenerB.count, 3);
//   EXPECT_EQ(listenerC.posX, 3.14f);
//   EXPECT_EQ(listenerC.posY, 2.72f);
//   EXPECT_EQ(listenerC.count, 1);
// }