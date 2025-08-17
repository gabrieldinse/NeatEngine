
#include <gtest/gtest.h>

#include <Neat/Math/Vector.hpp>

namespace Neat {
class VectorTest : public testing::Test {
 protected:
  VectorTest() {}
  Vector4F vector4f{1.0f, 2.0f, 3.0f, 4.0f};
  Vector4D vector4d{1.0, 2.0, 3.0, 4.0};
  Vector4I vector4i{1, 2, 3, 4};
  Vector4U vector4u{1, 2, 3, 4};
  Vector4B vector4b{true, false, true, false};
  Vector3F vector3f{1.0f, 2.0f, 3.0f};
  Vector3D vector3d{1.0, 2.0, 3.0};
  Vector3I vector3i{1, 2, 3};
  Vector3U vector3u{1, 2, 3};
  Vector3B vector3b{true, false, true};
  Vector2F vector2f{1.0f, 2.0f};
  Vector2D vector2d{1.0, 2.0};
  Vector2I vector2i{1, 2};
  Vector2U vector2u{1, 2};
  Vector2B vector2b{true, false};
  Vector1F vector1f{1.0f};
  Vector1D vector1d{1.0};
  Vector1I vector1i{1};
  Vector1U vector1u{1};
  Vector1B vector1b{true};
};

TEST_F(VectorTest, OperatorAt) {
  EXPECT_EQ(vector4f[0], 1.0f);
  EXPECT_EQ(vector4f[1], 2.0f);
  EXPECT_EQ(vector4f[2], 3.0f);
  EXPECT_EQ(vector4f[3], 4.0f);
  EXPECT_EQ(vector3f[0], 1.0f);
  EXPECT_EQ(vector3f[1], 2.0f);
  EXPECT_EQ(vector3f[2], 3.0f);
  EXPECT_EQ(vector2f[0], 1.0f);
  EXPECT_EQ(vector2f[1], 2.0f);
  EXPECT_EQ(vector1f[0], 1.0f);

  EXPECT_EQ(vector4d[0], 1.0);
  EXPECT_EQ(vector4d[1], 2.0);
  EXPECT_EQ(vector4d[2], 3.0);
  EXPECT_EQ(vector4d[3], 4.0);
  EXPECT_EQ(vector3d[0], 1.0);
  EXPECT_EQ(vector3d[1], 2.0);
  EXPECT_EQ(vector3d[2], 3.0);
  EXPECT_EQ(vector2d[0], 1.0);
  EXPECT_EQ(vector2d[1], 2.0);
  EXPECT_EQ(vector1d[0], 1.0);

  EXPECT_EQ(vector4i[0], 1);
  EXPECT_EQ(vector4i[1], 2);
  EXPECT_EQ(vector4i[2], 3);
  EXPECT_EQ(vector4i[3], 4);
  EXPECT_EQ(vector3i[0], 1);
  EXPECT_EQ(vector3i[1], 2);
  EXPECT_EQ(vector3i[2], 3);
  EXPECT_EQ(vector2i[0], 1);
  EXPECT_EQ(vector2i[1], 2);
  EXPECT_EQ(vector1i[0], 1);

  EXPECT_EQ(vector4u[0], 1U);
  EXPECT_EQ(vector4u[1], 2U);
  EXPECT_EQ(vector4u[2], 3U);
  EXPECT_EQ(vector4u[3], 4U);
  EXPECT_EQ(vector3u[0], 1U);
  EXPECT_EQ(vector3u[1], 2U);
  EXPECT_EQ(vector3u[2], 3U);
  EXPECT_EQ(vector2u[0], 1U);
  EXPECT_EQ(vector2u[1], 2U);
  EXPECT_EQ(vector1u[0], 1U);

  EXPECT_TRUE(vector4b[0]);
  EXPECT_FALSE(vector4b[1]);
  EXPECT_TRUE(vector4b[2]);
  EXPECT_FALSE(vector4b[3]);
  EXPECT_TRUE(vector3b[0]);
  EXPECT_FALSE(vector3b[1]);
  EXPECT_TRUE(vector3b[2]);
  EXPECT_TRUE(vector2b[0]);
  EXPECT_FALSE(vector2b[1]);
  EXPECT_TRUE(vector1b[0]);
}

TEST_F(VectorTest, CoordinatesAccessingXYZW) {
  EXPECT_EQ(vector4f.x, 1.0f);
  EXPECT_EQ(vector4f.y, 2.0f);
  EXPECT_EQ(vector4f.z, 3.0f);
  EXPECT_EQ(vector4f.w, 4.0f);
  EXPECT_EQ(vector3f.x, 1.0f);
  EXPECT_EQ(vector3f.y, 2.0f);
  EXPECT_EQ(vector3f.z, 3.0f);
  EXPECT_EQ(vector2f.x, 1.0f);
  EXPECT_EQ(vector2f.y, 2.0f);
  EXPECT_EQ(vector1f.x, 1.0f);

  EXPECT_EQ(vector4d.x, 1.0);
  EXPECT_EQ(vector4d.y, 2.0);
  EXPECT_EQ(vector4d.z, 3.0);
  EXPECT_EQ(vector4d.w, 4.0);
  EXPECT_EQ(vector3d.x, 1.0);
  EXPECT_EQ(vector3d.y, 2.0);
  EXPECT_EQ(vector3d.z, 3.0);
  EXPECT_EQ(vector2d.x, 1.0);
  EXPECT_EQ(vector2d.y, 2.0);
  EXPECT_EQ(vector1d.x, 1.0);

  EXPECT_EQ(vector4i.x, 1);
  EXPECT_EQ(vector4i.y, 2);
  EXPECT_EQ(vector4i.z, 3);
  EXPECT_EQ(vector4i.w, 4);
  EXPECT_EQ(vector3i.x, 1);
  EXPECT_EQ(vector3i.y, 2);
  EXPECT_EQ(vector3i.z, 3);
  EXPECT_EQ(vector2i.x, 1);
  EXPECT_EQ(vector2i.y, 2);
  EXPECT_EQ(vector1i.x, 1);

  EXPECT_EQ(vector4u.x, 1U);
  EXPECT_EQ(vector4u.y, 2U);
  EXPECT_EQ(vector4u.z, 3U);
  EXPECT_EQ(vector4u.w, 4U);
  EXPECT_EQ(vector3u.x, 1U);
  EXPECT_EQ(vector3u.y, 2U);
  EXPECT_EQ(vector3u.z, 3U);
  EXPECT_EQ(vector2u.x, 1U);
  EXPECT_EQ(vector2u.y, 2U);
  EXPECT_EQ(vector1u.x, 1U);

  EXPECT_TRUE(vector4b.x);
  EXPECT_FALSE(vector4b.y);
  EXPECT_TRUE(vector4b.z);
  EXPECT_FALSE(vector4b.w);
  EXPECT_TRUE(vector3b.x);
  EXPECT_FALSE(vector3b.y);
  EXPECT_TRUE(vector3b.z);
  EXPECT_TRUE(vector2b.x);
  EXPECT_FALSE(vector2b.y);
  EXPECT_TRUE(vector1b.x);
}

TEST_F(VectorTest, CoordinatesAccessingRGBA) {
  EXPECT_EQ(vector4f.r, 1.0f);
  EXPECT_EQ(vector4f.g, 2.0f);
  EXPECT_EQ(vector4f.b, 3.0f);
  EXPECT_EQ(vector4f.a, 4.0f);
  EXPECT_EQ(vector3f.r, 1.0f);
  EXPECT_EQ(vector3f.g, 2.0f);
  EXPECT_EQ(vector3f.b, 3.0f);
  EXPECT_EQ(vector2f.r, 1.0f);
  EXPECT_EQ(vector2f.g, 2.0f);
  EXPECT_EQ(vector1f.r, 1.0f);

  EXPECT_EQ(vector4d.r, 1.0);
  EXPECT_EQ(vector4d.g, 2.0);
  EXPECT_EQ(vector4d.b, 3.0);
  EXPECT_EQ(vector4d.a, 4.0);
  EXPECT_EQ(vector3d.r, 1.0);
  EXPECT_EQ(vector3d.g, 2.0);
  EXPECT_EQ(vector3d.b, 3.0);
  EXPECT_EQ(vector2d.r, 1.0);
  EXPECT_EQ(vector2d.g, 2.0);
  EXPECT_EQ(vector1d.r, 1.0);

  EXPECT_EQ(vector4i.r, 1);
  EXPECT_EQ(vector4i.g, 2);
  EXPECT_EQ(vector4i.b, 3);
  EXPECT_EQ(vector4i.a, 4);
  EXPECT_EQ(vector3i.r, 1);
  EXPECT_EQ(vector3i.g, 2);
  EXPECT_EQ(vector3i.b, 3);
  EXPECT_EQ(vector2i.r, 1);
  EXPECT_EQ(vector2i.g, 2);
  EXPECT_EQ(vector1i.r, 1);

  EXPECT_EQ(vector4u.r, 1U);
  EXPECT_EQ(vector4u.g, 2U);
  EXPECT_EQ(vector4u.b, 3U);
  EXPECT_EQ(vector4u.a, 4U);
  EXPECT_EQ(vector3u.r, 1U);
  EXPECT_EQ(vector3u.g, 2U);
  EXPECT_EQ(vector3u.b, 3U);
  EXPECT_EQ(vector2u.r, 1U);
  EXPECT_EQ(vector2u.g, 2U);
  EXPECT_EQ(vector1u.r, 1U);

  EXPECT_TRUE(vector4b.r);
  EXPECT_FALSE(vector4b.g);
  EXPECT_TRUE(vector4b.b);
  EXPECT_FALSE(vector4b.a);
  EXPECT_TRUE(vector3b.r);
  EXPECT_FALSE(vector3b.g);
  EXPECT_TRUE(vector3b.b);
  EXPECT_TRUE(vector2b.r);
  EXPECT_FALSE(vector2b.g);
  EXPECT_TRUE(vector1b.r);
}

TEST_F(VectorTest, CoordinatesAccessingIJKL) {
  EXPECT_EQ(vector4f.i, 1.0f);
  EXPECT_EQ(vector4f.j, 2.0f);
  EXPECT_EQ(vector4f.k, 3.0f);
  EXPECT_EQ(vector4f.l, 4.0f);
  EXPECT_EQ(vector3f.i, 1.0f);
  EXPECT_EQ(vector3f.j, 2.0f);
  EXPECT_EQ(vector3f.k, 3.0f);
  EXPECT_EQ(vector2f.i, 1.0f);
  EXPECT_EQ(vector2f.j, 2.0f);
  EXPECT_EQ(vector1f.i, 1.0f);

  EXPECT_EQ(vector4d.i, 1.0);
  EXPECT_EQ(vector4d.j, 2.0);
  EXPECT_EQ(vector4d.k, 3.0);
  EXPECT_EQ(vector4d.l, 4.0);
  EXPECT_EQ(vector3d.i, 1.0);
  EXPECT_EQ(vector3d.j, 2.0);
  EXPECT_EQ(vector3d.k, 3.0);
  EXPECT_EQ(vector2d.i, 1.0);
  EXPECT_EQ(vector2d.j, 2.0);
  EXPECT_EQ(vector1d.i, 1.0);

  EXPECT_EQ(vector4i.i, 1);
  EXPECT_EQ(vector4i.j, 2);
  EXPECT_EQ(vector4i.k, 3);
  EXPECT_EQ(vector4i.l, 4);
  EXPECT_EQ(vector3i.i, 1);
  EXPECT_EQ(vector3i.j, 2);
  EXPECT_EQ(vector3i.k, 3);
  EXPECT_EQ(vector2i.i, 1);
  EXPECT_EQ(vector2i.j, 2);
  EXPECT_EQ(vector1i.i, 1);

  EXPECT_EQ(vector4u.i, 1U);
  EXPECT_EQ(vector4u.j, 2U);
  EXPECT_EQ(vector4u.k, 3U);
  EXPECT_EQ(vector4u.l, 4U);
  EXPECT_EQ(vector3u.i, 1U);
  EXPECT_EQ(vector3u.j, 2U);
  EXPECT_EQ(vector3u.k, 3U);
  EXPECT_EQ(vector2u.i, 1U);
  EXPECT_EQ(vector2u.j, 2U);
  EXPECT_EQ(vector1u.i, 1U);

  EXPECT_TRUE(vector4b.i);
  EXPECT_FALSE(vector4b.j);
  EXPECT_TRUE(vector4b.k);
  EXPECT_FALSE(vector4b.l);
  EXPECT_TRUE(vector3b.i);
  EXPECT_FALSE(vector3b.j);
  EXPECT_TRUE(vector3b.k);
  EXPECT_TRUE(vector2b.i);
  EXPECT_FALSE(vector2b.j);
  EXPECT_TRUE(vector1b.i);
}

TEST_F(VectorTest, CoordinatesAccessingSTPQ) {
  EXPECT_EQ(vector4f.s, 1.0f);
  EXPECT_EQ(vector4f.t, 2.0f);
  EXPECT_EQ(vector4f.p, 3.0f);
  EXPECT_EQ(vector4f.q, 4.0f);
  EXPECT_EQ(vector3f.s, 1.0f);
  EXPECT_EQ(vector3f.t, 2.0f);
  EXPECT_EQ(vector3f.p, 3.0f);
  EXPECT_EQ(vector2f.s, 1.0f);
  EXPECT_EQ(vector2f.t, 2.0f);
  EXPECT_EQ(vector1f.s, 1.0f);

  EXPECT_EQ(vector4d.s, 1.0);
  EXPECT_EQ(vector4d.t, 2.0);
  EXPECT_EQ(vector4d.p, 3.0);
  EXPECT_EQ(vector4d.q, 4.0);
  EXPECT_EQ(vector3d.s, 1.0);
  EXPECT_EQ(vector3d.t, 2.0);
  EXPECT_EQ(vector3d.p, 3.0);
  EXPECT_EQ(vector2d.s, 1.0);
  EXPECT_EQ(vector2d.t, 2.0);
  EXPECT_EQ(vector1d.s, 1.0);

  EXPECT_EQ(vector4i.s, 1);
  EXPECT_EQ(vector4i.t, 2);
  EXPECT_EQ(vector4i.p, 3);
  EXPECT_EQ(vector4i.q, 4);
  EXPECT_EQ(vector3i.s, 1);
  EXPECT_EQ(vector3i.t, 2);
  EXPECT_EQ(vector3i.p, 3);
  EXPECT_EQ(vector2i.s, 1);
  EXPECT_EQ(vector2i.t, 2);
  EXPECT_EQ(vector1i.s, 1);

  EXPECT_EQ(vector4u.s, 1U);
  EXPECT_EQ(vector4u.t, 2U);
  EXPECT_EQ(vector4u.p, 3U);
  EXPECT_EQ(vector4u.q, 4U);
  EXPECT_EQ(vector3u.s, 1U);
  EXPECT_EQ(vector3u.t, 2U);
  EXPECT_EQ(vector3u.p, 3U);
  EXPECT_EQ(vector2u.s, 1U);
  EXPECT_EQ(vector2u.t, 2U);
  EXPECT_EQ(vector1u.s, 1U);

  EXPECT_TRUE(vector4b.s);
  EXPECT_FALSE(vector4b.t);
  EXPECT_TRUE(vector4b.p);
  EXPECT_FALSE(vector4b.q);
  EXPECT_TRUE(vector3b.s);
  EXPECT_FALSE(vector3b.t);
  EXPECT_TRUE(vector3b.p);
  EXPECT_TRUE(vector2b.s);
  EXPECT_FALSE(vector2b.t);
  EXPECT_TRUE(vector1b.s);
}
}  // namespace Neat