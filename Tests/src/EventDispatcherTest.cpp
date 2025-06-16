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
  void expectDefault() {
    EXPECT_EQ(listenerA.val, 0);
    EXPECT_EQ(listenerA.count, 0);
    EXPECT_EQ(listenerB.posX, 0.0f);
    EXPECT_EQ(listenerB.posY, 0.0f);
    EXPECT_EQ(listenerB.msg, "");
    EXPECT_EQ(listenerB.count, 0);
    EXPECT_EQ(listenerC.posX, 0.0f);
    EXPECT_EQ(listenerC.posY, 0.0f);
    EXPECT_EQ(listenerC.count, 0);
  }

  void setDefault() {
    listenerA = ListenerA{};
    listenerB = ListenerB{};
    listenerC = ListenerC{};
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

TEST_F(EventDispatcherTest, EnqueueAndUpdateSingleEvents) {
  dispatcher1.enqueue(EventA{100});
  dispatcher1.update();
  EXPECT_EQ(listenerA.val, 100);
  EXPECT_EQ(listenerA.count, 1);

  dispatcher1.enqueue(EventA{200});
  dispatcher1.update();
  EXPECT_EQ(listenerA.val, 200);
  EXPECT_EQ(listenerA.count, 2);

  dispatcher1.enqueue<EventA>(300);
  dispatcher1.update();
  EXPECT_EQ(listenerA.val, 300);
  EXPECT_EQ(listenerA.count, 3);

  EventA eventA{400};
  dispatcher1.enqueue(eventA);
  dispatcher1.update();
  EXPECT_EQ(listenerA.val, 400);
  EXPECT_EQ(listenerA.count, 4);
}

TEST_F(EventDispatcherTest, EnqueueAndUpdateMultipleEventListeners) {
  std::string msg{"My message"};
  std::string msg2{"My message"};

  dispatcher1.enqueue(EventA{100});
  dispatcher1.enqueue(EventB{msg});
  dispatcher1.enqueue(EventC{3.14f, 2.72f});
  dispatcher1.enqueue(EventB{msg2});

  expectDefault();

  dispatcher1.update();

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

TEST_F(EventDispatcherTest, DisconnectAndEnqueueAndUpdate) {
  std::string msg{"My message"};
  std::string msg2{"My other message"};
  dispatcher1.get<EventA>().disconnect<&ListenerA::handle>(listenerA);

  dispatcher1.enqueue(EventA{100});
  dispatcher1.enqueue(EventB{msg});
  dispatcher1.enqueue<EventC>(3.14f, 2.72f);
  dispatcher1.enqueue<EventB>(msg2);

  expectDefault();

  dispatcher1.update();

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

  setDefault();

  dispatcher1.enqueue<EventA>(200);
  dispatcher1.enqueue<EventB>(msg + " extended");
  dispatcher1.enqueue(EventC{-1.0f, 0.5f});
  dispatcher1.enqueue(EventB{msg2 + "modified"});

  expectDefault();

  dispatcher1.update();

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