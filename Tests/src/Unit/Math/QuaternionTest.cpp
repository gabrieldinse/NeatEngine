
#include <gtest/gtest.h>

#include <Math/Vector.hpp>

namespace Neat {
class QuaternionTest : public testing::Test {
 protected:
  QuaternionTest() {}
  QuaternionF quaternionf{1.0f, 2.0f, 3.0f, 4.0f};
  QuaternionD quaterniond{1.0, 2.0, 3.0, 4.0};
};

TEST_F(QuaternionTest, DefaultConstructor) {
  QuaternionF qf;
  EXPECT_EQ(qf.w(), 1.0f);
  EXPECT_EQ(qf.x(), 0.0f);
  EXPECT_EQ(qf.y(), 0.0f);
  EXPECT_EQ(qf.z(), 0.0f);

  QuaternionD qd;
  EXPECT_EQ(qd.w(), 1.0);
  EXPECT_EQ(qd.x(), 0.0);
  EXPECT_EQ(qd.y(), 0.0);
  EXPECT_EQ(qd.z(), 0.0);
}

TEST_F(QuaternionTest, ScalarAndVectorConstructor) {
  QuaternionF qf(1.5, Vector3F{2.5, 3.5, 4.5});
  EXPECT_EQ(qf.w(), 1.5);
  EXPECT_EQ(qf.x(), 2.5);
  EXPECT_EQ(qf.y(), 3.5);
  EXPECT_EQ(qf.z(), 4.5);

  QuaternionD qd(1.5, Vector3D{2.5, 3.5, 4.5});
  EXPECT_EQ(qd.w(), 1.5);
  EXPECT_EQ(qd.x(), 2.5);
  EXPECT_EQ(qd.y(), 3.5);
  EXPECT_EQ(qd.z(), 4.5);
}

TEST_F(QuaternionTest, ScalarsConstructor) {
  QuaternionF qf(1.5, 2.5, 3.5, 4.5);
  EXPECT_EQ(qf.w(), 1.5);
  EXPECT_EQ(qf.x(), 2.5);
  EXPECT_EQ(qf.y(), 3.5);
  EXPECT_EQ(qf.z(), 4.5);

  QuaternionD qd(1.5, 2.5, 3.5, 4.5);
  EXPECT_EQ(qd.w(), 1.5);
  EXPECT_EQ(qd.x(), 2.5);
  EXPECT_EQ(qd.y(), 3.5);
  EXPECT_EQ(qd.z(), 4.5);
}

TEST_F(QuaternionTest, CopyConstructor) {
  QuaternionF qfCopy(quaternionf);
  EXPECT_EQ(qfCopy.w(), 1.0f);
  EXPECT_EQ(qfCopy.x(), 2.0f);
  EXPECT_EQ(qfCopy.y(), 3.0f);
  EXPECT_EQ(qfCopy.z(), 4.0f);

  QuaternionD qdCopy(quaterniond);
  EXPECT_EQ(qdCopy.w(), 1.0);
  EXPECT_EQ(qdCopy.x(), 2.0);
  EXPECT_EQ(qdCopy.y(), 3.0);
  EXPECT_EQ(qdCopy.z(), 4.0);
}

TEST_F(QuaternionTest, ConversionCopyConstructor) {
  QuaternionD qdFromF(quaternionf);
  EXPECT_EQ(qdFromF.w(), 1.0);
  EXPECT_EQ(qdFromF.x(), 2.0);
  EXPECT_EQ(qdFromF.y(), 3.0);
  EXPECT_EQ(qdFromF.z(), 4.0);

  QuaternionF qfFromD(quaterniond);
  EXPECT_EQ(qfFromD.w(), 1.0f);
  EXPECT_EQ(qfFromD.x(), 2.0f);
  EXPECT_EQ(qfFromD.y(), 3.0f);
  EXPECT_EQ(qfFromD.z(), 4.0f);
}
}  // namespace Neat