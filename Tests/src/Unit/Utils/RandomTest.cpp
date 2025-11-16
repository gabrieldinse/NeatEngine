#include <gtest/gtest.h>

#include "Utils/Random.hpp"

namespace Neat {
TEST(RandomTest, GetFloatTest) {
  Random& random = Random::getInstance();
  float value = 0.0f;

  value = random.getFloat(1.0f, 10.0f);
  EXPECT_GE(value, 1.0f);
  EXPECT_LE(value, 10.0f);

  value = random.getFloat(0.0f, 1.0f);
  EXPECT_GE(value, 0.0f);
  EXPECT_LE(value, 1.0f);

  value = random.getFloat(-1.0f, 1.0f);
  EXPECT_GE(value, -1.0f);
  EXPECT_LE(value, 1.0f);

  value = random.getFloat(-50.0f, -0.098f);
  EXPECT_GE(value, -50.0f);
  EXPECT_LE(value, -0.098f);

  value = random.getFloat(-0.0f, 0.0f);
  EXPECT_EQ(value, 0.0f);
}
}  // namespace Neat