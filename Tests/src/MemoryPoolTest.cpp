#include <gtest/gtest.h>

#include <string>

#include <Neat/Utils/MemoryPool.hpp>
#include <TestUtils.hpp>

namespace Neat {
class MemoryPoolTest : public testing::Test {
 protected:
  MemoryPoolTest() {}
  ~MemoryPoolTest() {}
  void destroy() {
    for (UInt32 i = 0; i < pool.size(); ++i) {
      pool.destroy(i);
    }
  }
  MemoryPool<std::string, 24> pool;
};

TEST_F(MemoryPoolTest, Default) {
  EXPECT_EQ(pool.size(), 0);
  EXPECT_EQ(pool.capacity(), 0);
}

TEST_F(MemoryPoolTest, Push) {
  EXPECT_EQ(pool.size(), 0);
  EXPECT_EQ(pool.capacity(), 0);

  pool.push();
  EXPECT_EQ(pool.size(), 1);
  EXPECT_EQ(pool.capacity(), 24);

  pool.push();
  pool.push();
  EXPECT_EQ(pool.size(), 3);
  EXPECT_EQ(pool.capacity(), 24);
}

TEST_F(MemoryPoolTest, Construct) {
  pool.push();
  EXPECT_EQ(pool.size(), 1);
  EXPECT_EQ(pool.capacity(), 24);
  pool.construct(0, "test");

  pool.push();
  EXPECT_EQ(pool.size(), 2);
  EXPECT_EQ(pool.capacity(), 24);
  pool.construct(1, "test1");

  pool.push();
  EXPECT_EQ(pool.size(), 3);
  EXPECT_EQ(pool.capacity(), 24);
  pool.construct(2, "test2");

  EXPECT_EQ(pool.size(), 3);
  EXPECT_EQ(pool.capacity(), 24);

  destroy();
}

TEST_F(MemoryPoolTest, Resize) {
  pool.resize(5);
  EXPECT_EQ(pool.size(), 5);
  EXPECT_EQ(pool.chunks(), 1);
  EXPECT_EQ(pool.capacity(), 24);

  pool.resize(20);
  EXPECT_EQ(pool.size(), 20);
  EXPECT_EQ(pool.chunks(), 1);
  EXPECT_EQ(pool.capacity(), 24);

  pool.resize(50);
  EXPECT_EQ(pool.size(), 50);
  EXPECT_EQ(pool.chunks(), 3);
  EXPECT_EQ(pool.capacity(), 72);
}

TEST_F(MemoryPoolTest, Reserve) {
  pool.reserve(10);
  EXPECT_EQ(pool.size(), 0);
  EXPECT_EQ(pool.chunks(), 1);
  EXPECT_EQ(pool.capacity(), 24);

  pool.reserve(25);
  EXPECT_EQ(pool.size(), 0);
  EXPECT_EQ(pool.chunks(), 2);
  EXPECT_EQ(pool.capacity(), 48);

  pool.reserve(50);
  EXPECT_EQ(pool.size(), 0);
  EXPECT_EQ(pool.chunks(), 3);
  EXPECT_EQ(pool.capacity(), 72);
}

TEST_F(MemoryPoolTest, Get) {
  pool.resize(3);
  pool.construct(0, "test");
  pool.construct(1, "test1");
  pool.construct(2, "test2");

  EXPECT_EQ(*static_cast<std::string *>(pool.get(0)), "test");
  EXPECT_EQ(*static_cast<std::string *>(pool.get(1)), "test1");
  EXPECT_EQ(*static_cast<std::string *>(pool.get(2)), "test2");

  destroy();
}

TEST_F(MemoryPoolTest, OperatorAt) {
  pool.resize(3);
  pool.construct(0, "test");
  pool.construct(1, "test1");
  pool.construct(2, "test2");

  EXPECT_EQ(pool[0], "test");
  EXPECT_EQ(pool[1], "test1");
  EXPECT_EQ(pool[2], "test2");

  destroy();
}

TEST_F(MemoryPoolTest, At) {
  pool.resize(3);
  pool.construct(0, "test");
  pool.construct(1, "test1");
  pool.construct(2, "test2");

  EXPECT_EQ(pool.at(0), "test");
  EXPECT_EQ(pool.at(1), "test1");
  EXPECT_EQ(pool.at(2), "test2");

  destroy();
}

TEST_F(MemoryPoolTest, DestroyAndConstructAgain) {
  pool.resize(3);
  pool.construct(0, "test");
  pool.construct(1, "test1");
  pool.construct(2, "test2");

  EXPECT_EQ(pool[0], "test");
  EXPECT_EQ(pool[1], "test1");
  EXPECT_EQ(pool[2], "test2");

  destroy();

  pool.construct(0, "test00");
  pool.construct(1, "test11");
  pool.construct(2, "test22");

  EXPECT_EQ(pool[0], "test00");
  EXPECT_EQ(pool[1], "test11");
  EXPECT_EQ(pool[2], "test22");

  destroy();
}
}  // namespace Neat