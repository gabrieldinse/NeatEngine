#include <gtest/gtest.h>
#include <string>

#include <Utils/SafeQueue.hpp>

namespace Neat {
class SafeQueueTest : public testing::Test {
 protected:
  SafeQueueTest() {
    q1.push(1);
    q2.push(2);
    q2.push(3);
    // q3 should be left empty
  }
  SafeQueue<int> q1;
  SafeQueue<int> q2;
  SafeQueue<int> q3;
  SafeQueue<std::string> q4;
};

TEST_F(SafeQueueTest, PopElements) {
  auto elem = q1.tryPop();
  EXPECT_TRUE(elem.has_value());
  EXPECT_EQ(elem.value(), 1);

  auto elem_none = q1.tryPop(100);
  EXPECT_FALSE(elem_none.has_value());

  auto elem2 = q2.tryPop();
  EXPECT_TRUE(elem2.has_value());
  EXPECT_EQ(elem2.value(), 2);

  auto elem3 = q2.tryPop();
  EXPECT_TRUE(elem3.has_value());
  EXPECT_EQ(elem3.value(), 3);

  auto elem_none2 = q2.tryPop(100);
  EXPECT_FALSE(elem_none2.has_value());

  auto elem_none3 = q3.tryPop(100);
  EXPECT_FALSE(elem_none3.has_value());
}

TEST_F(SafeQueueTest, PushAnsPopElements) {
  q1.tryPop();
  q1.push(50);
  q1.push(-1);
  auto elem = q1.tryPop();
  EXPECT_TRUE(elem.has_value());
  EXPECT_EQ(elem.value(), 50);

  auto elem2 = q1.tryPop();
  EXPECT_TRUE(elem2.has_value());
  EXPECT_EQ(elem2.value(), -1);

  auto elem_none = q1.tryPop(100);
  EXPECT_FALSE(elem_none.has_value());

  q2.push(150);
  auto elem3 = q2.tryPop();
  EXPECT_TRUE(elem3.has_value());
  EXPECT_EQ(elem3.value(), 2);

  auto elem4 = q2.tryPop();
  EXPECT_TRUE(elem4.has_value());
  EXPECT_EQ(elem4.value(), 3);

  auto elem5 = q2.tryPop();
  EXPECT_TRUE(elem5.has_value());
  EXPECT_EQ(elem5.value(), 150);

  auto elem_none2 = q2.tryPop(100);
  EXPECT_FALSE(elem_none2.has_value());

  auto elem_none3 = q3.tryPop(100);
  EXPECT_FALSE(elem_none3.has_value());

  q3.push(200);
  auto elem6 = q3.tryPop();
  EXPECT_TRUE(elem6.has_value());
  EXPECT_EQ(elem6.value(), 200);
}

TEST_F(SafeQueueTest, PushLvalueAndRvalueReferences) {
  auto elem_none = q4.tryPop(100);
  EXPECT_FALSE(elem_none.has_value());

  std::string test_string{"TEST"};
  q4.push(test_string);
  auto elem = q4.tryPop();
  EXPECT_TRUE(elem.has_value());
  EXPECT_EQ(elem.value(), test_string);

  q4.push(std::move(test_string));  // test_string is now empty
  EXPECT_TRUE(test_string.empty());
  auto elem2 = q4.tryPop();
  EXPECT_TRUE(elem2.has_value());
  EXPECT_NE(elem2.value(), test_string);
}
}  // namespace Neat