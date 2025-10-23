#include <gtest/gtest.h>

#include <EventDispatching/EventDispatcher.hpp>
#include <Core/Timer.hpp>
#include <TestUtils.hpp>

namespace Neat {
class EventDispatcherBenchmarkTest : public testing::Test {
 protected:
  EventDispatcherBenchmarkTest() {
    dispatcher1.get<EventA>().connect<&ListenerA::handle>(listenerA);
    dispatcher1.get<EventB>().connect<&ListenerB::process>(listenerB);
    dispatcher1.get<EventC>().connect<&ListenerB::handleEventC>(listenerB);
    dispatcher1.get<EventC>().connect<&ListenerC::handle>(listenerC);
  }

  EventDispatcher dispatcher1{};
  EventDispatcher dispatcher2{};
  ListenerA listenerA{};
  ListenerB listenerB{};
  ListenerC listenerC{};
  ListenerB listenerB2{};
  ListenerC listenerC2{};
};

TEST_F(EventDispatcherBenchmarkTest, TriggerEventsBenchmark) {
  int count = 1000000;
  Timer timer;
  timer.start();

  for (int i = 0; i < count; ++i) {
    dispatcher1.trigger(EventA{i});
  }

  auto duration = timer.stop();
  std::cout << "EventA triggered " << count << " times in " << duration
            << " seconds.\n";

  timer.start();
  for (int i = 0; i < count; ++i) {
    dispatcher1.trigger<EventB>();
  }
  duration = timer.stop();
  std::cout << "EventB triggered " << count << " times in " << duration
            << " seconds.\n";
}

TEST_F(EventDispatcherBenchmarkTest, TriggerEventsMultipleListenersBenchmark) {
  std::vector<ListenerA> listenersA(10);
  for (int i = 0; i < 10; ++i) {
    dispatcher1.get<EventA>().connect<&ListenerA::handle>(listenersA[i]);
  }

  Timer timer;
  int count = 100000;
  timer.start();
  for (int i = 0; i < count; ++i) {
    dispatcher1.trigger(EventA{i});
  }
  auto duration = timer.stop();
  std::cout << "EventA triggered to " << listenersA.size() << " listeners "
            << count << " times in " << duration << " seconds.\n";

  std::vector<ListenerB> listenersB(100);
  for (int i = 0; i < 100; ++i) {
    dispatcher1.get<EventB>().connect<&ListenerB::process>(listenersB[i]);
  }

  int count2 = 10000;
  timer.start();
  for (int i = 0; i < count2; ++i) {
    dispatcher1.trigger<EventB>();
  }

  duration = timer.stop();
  std::cout << "EventB triggered to " << listenersB.size() << " listeners "
            << count2 << " times in " << duration << " seconds.\n";
}

TEST_F(EventDispatcherBenchmarkTest, EnqueueAndUpdateBenchmark) {
  int count = 1000000;
  Timer timer;
  timer.start();

  for (int i = 0; i < count; ++i) {
    dispatcher1.enqueue(EventA{i});
  }

  dispatcher1.update();
  auto duration = timer.stop();
  std::cout << "EventA enqueued and updated " << count << " times in "
            << duration << " seconds.\n";

  timer.start();
  for (int i = 0; i < count; ++i) {
    dispatcher1.enqueue<EventB>();
  }

  dispatcher1.update();
  duration = timer.stop();
  std::cout << "EventB enqueued and updated " << count << " times in "
            << duration << " seconds.\n";
}

TEST_F(EventDispatcherBenchmarkTest,
       EnqueueAndUpdateMultipleListenersBenchmark) {
  std::vector<ListenerA> listenersA(10);
  for (int i = 0; i < 10; ++i) {
    dispatcher1.get<EventA>().connect<&ListenerA::handle>(listenersA[i]);
  }

  Timer timer;
  int count = 100000;
  timer.start();
  for (int i = 0; i < count; ++i) {
    dispatcher1.enqueue(EventA{i});
  }
  dispatcher1.update();
  auto duration = timer.stop();
  std::cout << "EventA enqueued and updated to " << listenersA.size()
            << " listeners " << count << " times in " << duration
            << " seconds.\n";

  std::vector<ListenerB> listenersB(100);
  for (int i = 0; i < 100; ++i) {
    dispatcher1.get<EventB>().connect<&ListenerB::process>(listenersB[i]);
  }

  int count2 = 10000;
  timer.start();
  for (int i = 0; i < count2; ++i) {
    dispatcher1.enqueue<EventB>();
  }
  dispatcher1.update();
  duration = timer.stop();
  std::cout << "EventB enqueued and updated to " << listenersB.size()
            << " listeners " << count2 << " times in " << duration
            << " seconds.\n";
}
}  // namespace Neat