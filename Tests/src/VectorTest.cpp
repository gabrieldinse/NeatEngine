
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

  // Non-default, less than 4 bytes, types
  Vector<4, Char> vector4c{'a', 'b', 'c', 'd'};
  Vector<3, Char> vector3c{'a', 'b', 'c'};
  Vector<2, Char> vector2c{'a', 'b'};
  Vector<1, Char> vector1c{'a'};
  Vector<4, Short> vector4s{1, 2, 3, 4};
  Vector<3, Short> vector3s{1, 2, 3};
  Vector<2, Short> vector2s{1, 2};
  Vector<1, Short> vector1s{1};
  Vector<4, UShort> vector4us{1, 2, 3, 4};
  Vector<3, UShort> vector3us{1, 2, 3};
  Vector<2, UShort> vector2us{1, 2};
  Vector<1, UShort> vector1us{1};
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

  EXPECT_EQ(vector4c[0], 'a');
  EXPECT_EQ(vector4c[1], 'b');
  EXPECT_EQ(vector4c[2], 'c');
  EXPECT_EQ(vector4c[3], 'd');
  EXPECT_EQ(vector3c[0], 'a');
  EXPECT_EQ(vector3c[1], 'b');
  EXPECT_EQ(vector3c[2], 'c');
  EXPECT_EQ(vector2c[0], 'a');
  EXPECT_EQ(vector2c[1], 'b');
  EXPECT_EQ(vector1c[0], 'a');

  EXPECT_EQ(vector4s[0], 1);
  EXPECT_EQ(vector4s[1], 2);
  EXPECT_EQ(vector4s[2], 3);
  EXPECT_EQ(vector4s[3], 4);
  EXPECT_EQ(vector3s[0], 1);
  EXPECT_EQ(vector3s[1], 2);
  EXPECT_EQ(vector3s[2], 3);
  EXPECT_EQ(vector2s[0], 1);
  EXPECT_EQ(vector2s[1], 2);
  EXPECT_EQ(vector1s[0], 1);

  EXPECT_EQ(vector4us[0], 1U);
  EXPECT_EQ(vector4us[1], 2U);
  EXPECT_EQ(vector4us[2], 3U);
  EXPECT_EQ(vector4us[3], 4U);
  EXPECT_EQ(vector3us[0], 1U);
  EXPECT_EQ(vector3us[1], 2U);
  EXPECT_EQ(vector3us[2], 3U);
  EXPECT_EQ(vector2us[0], 1U);
  EXPECT_EQ(vector2us[1], 2U);
  EXPECT_EQ(vector1us[0], 1U);
}

TEST_F(VectorTest, CoordinatesAccessingXYZW) {
  EXPECT_EQ(vector4f.x(), 1.0f);
  EXPECT_EQ(vector4f.y(), 2.0f);
  EXPECT_EQ(vector4f.z(), 3.0f);
  EXPECT_EQ(vector4f.w(), 4.0f);
  EXPECT_EQ(vector3f.x(), 1.0f);
  EXPECT_EQ(vector3f.y(), 2.0f);
  EXPECT_EQ(vector3f.z(), 3.0f);
  EXPECT_EQ(vector2f.x(), 1.0f);
  EXPECT_EQ(vector2f.y(), 2.0f);
  EXPECT_EQ(vector1f.x(), 1.0f);

  EXPECT_EQ(vector4d.x(), 1.0);
  EXPECT_EQ(vector4d.y(), 2.0);
  EXPECT_EQ(vector4d.z(), 3.0);
  EXPECT_EQ(vector4d.w(), 4.0);
  EXPECT_EQ(vector3d.x(), 1.0);
  EXPECT_EQ(vector3d.y(), 2.0);
  EXPECT_EQ(vector3d.z(), 3.0);
  EXPECT_EQ(vector2d.x(), 1.0);
  EXPECT_EQ(vector2d.y(), 2.0);
  EXPECT_EQ(vector1d.x(), 1.0);

  EXPECT_EQ(vector4i.x(), 1);
  EXPECT_EQ(vector4i.y(), 2);
  EXPECT_EQ(vector4i.z(), 3);
  EXPECT_EQ(vector4i.w(), 4);
  EXPECT_EQ(vector3i.x(), 1);
  EXPECT_EQ(vector3i.y(), 2);
  EXPECT_EQ(vector3i.z(), 3);
  EXPECT_EQ(vector2i.x(), 1);
  EXPECT_EQ(vector2i.y(), 2);
  EXPECT_EQ(vector1i.x(), 1);

  EXPECT_EQ(vector4u.x(), 1U);
  EXPECT_EQ(vector4u.y(), 2U);
  EXPECT_EQ(vector4u.z(), 3U);
  EXPECT_EQ(vector4u.w(), 4U);
  EXPECT_EQ(vector3u.x(), 1U);
  EXPECT_EQ(vector3u.y(), 2U);
  EXPECT_EQ(vector3u.z(), 3U);
  EXPECT_EQ(vector2u.x(), 1U);
  EXPECT_EQ(vector2u.y(), 2U);
  EXPECT_EQ(vector1u.x(), 1U);

  EXPECT_TRUE(vector4b.x());
  EXPECT_FALSE(vector4b.y());
  EXPECT_TRUE(vector4b.z());
  EXPECT_FALSE(vector4b.w());
  EXPECT_TRUE(vector3b.x());
  EXPECT_FALSE(vector3b.y());
  EXPECT_TRUE(vector3b.z());
  EXPECT_TRUE(vector2b.x());
  EXPECT_FALSE(vector2b.y());
  EXPECT_TRUE(vector1b.x());

  EXPECT_EQ(vector4c.x(), 'a');
  EXPECT_EQ(vector4c.y(), 'b');
  EXPECT_EQ(vector4c.z(), 'c');
  EXPECT_EQ(vector4c.w(), 'd');
  EXPECT_EQ(vector3c.x(), 'a');
  EXPECT_EQ(vector3c.y(), 'b');
  EXPECT_EQ(vector3c.z(), 'c');
  EXPECT_EQ(vector2c.x(), 'a');
  EXPECT_EQ(vector2c.y(), 'b');
  EXPECT_EQ(vector1c.x(), 'a');

  EXPECT_EQ(vector4s.x(), 1);
  EXPECT_EQ(vector4s.y(), 2);
  EXPECT_EQ(vector4s.z(), 3);
  EXPECT_EQ(vector4s.w(), 4);
  EXPECT_EQ(vector3s.x(), 1);
  EXPECT_EQ(vector3s.y(), 2);
  EXPECT_EQ(vector3s.z(), 3);
  EXPECT_EQ(vector2s.x(), 1);
  EXPECT_EQ(vector2s.y(), 2);
  EXPECT_EQ(vector1s.x(), 1);

  EXPECT_EQ(vector4us.x(), 1U);
  EXPECT_EQ(vector4us.y(), 2U);
  EXPECT_EQ(vector4us.z(), 3U);
  EXPECT_EQ(vector4us.w(), 4U);
  EXPECT_EQ(vector3us.x(), 1U);
  EXPECT_EQ(vector3us.y(), 2U);
  EXPECT_EQ(vector3us.z(), 3U);
  EXPECT_EQ(vector2us.x(), 1U);
  EXPECT_EQ(vector2us.y(), 2U);
  EXPECT_EQ(vector1us.x(), 1U);
}

TEST_F(VectorTest, CoordinatesAccessingRGBA) {
  EXPECT_EQ(vector4f.r(), 1.0f);
  EXPECT_EQ(vector4f.g(), 2.0f);
  EXPECT_EQ(vector4f.b(), 3.0f);
  EXPECT_EQ(vector4f.a(), 4.0f);
  EXPECT_EQ(vector3f.r(), 1.0f);
  EXPECT_EQ(vector3f.g(), 2.0f);
  EXPECT_EQ(vector3f.b(), 3.0f);
  EXPECT_EQ(vector2f.r(), 1.0f);
  EXPECT_EQ(vector2f.g(), 2.0f);
  EXPECT_EQ(vector1f.r(), 1.0f);

  EXPECT_EQ(vector4d.r(), 1.0);
  EXPECT_EQ(vector4d.g(), 2.0);
  EXPECT_EQ(vector4d.b(), 3.0);
  EXPECT_EQ(vector4d.a(), 4.0);
  EXPECT_EQ(vector3d.r(), 1.0);
  EXPECT_EQ(vector3d.g(), 2.0);
  EXPECT_EQ(vector3d.b(), 3.0);
  EXPECT_EQ(vector2d.r(), 1.0);
  EXPECT_EQ(vector2d.g(), 2.0);
  EXPECT_EQ(vector1d.r(), 1.0);

  EXPECT_EQ(vector4i.r(), 1);
  EXPECT_EQ(vector4i.g(), 2);
  EXPECT_EQ(vector4i.b(), 3);
  EXPECT_EQ(vector4i.a(), 4);
  EXPECT_EQ(vector3i.r(), 1);
  EXPECT_EQ(vector3i.g(), 2);
  EXPECT_EQ(vector3i.b(), 3);
  EXPECT_EQ(vector2i.r(), 1);
  EXPECT_EQ(vector2i.g(), 2);
  EXPECT_EQ(vector1i.r(), 1);

  EXPECT_EQ(vector4u.r(), 1U);
  EXPECT_EQ(vector4u.g(), 2U);
  EXPECT_EQ(vector4u.b(), 3U);
  EXPECT_EQ(vector4u.a(), 4U);
  EXPECT_EQ(vector3u.r(), 1U);
  EXPECT_EQ(vector3u.g(), 2U);
  EXPECT_EQ(vector3u.b(), 3U);
  EXPECT_EQ(vector2u.r(), 1U);
  EXPECT_EQ(vector2u.g(), 2U);
  EXPECT_EQ(vector1u.r(), 1U);

  EXPECT_TRUE(vector4b.r());
  EXPECT_FALSE(vector4b.g());
  EXPECT_TRUE(vector4b.b());
  EXPECT_FALSE(vector4b.a());
  EXPECT_TRUE(vector3b.r());
  EXPECT_FALSE(vector3b.g());
  EXPECT_TRUE(vector3b.b());
  EXPECT_TRUE(vector2b.r());
  EXPECT_FALSE(vector2b.g());
  EXPECT_TRUE(vector1b.r());

  EXPECT_EQ(vector4c.r(), 'a');
  EXPECT_EQ(vector4c.g(), 'b');
  EXPECT_EQ(vector4c.b(), 'c');
  EXPECT_EQ(vector4c.a(), 'd');
  EXPECT_EQ(vector3c.r(), 'a');
  EXPECT_EQ(vector3c.g(), 'b');
  EXPECT_EQ(vector3c.b(), 'c');
  EXPECT_EQ(vector2c.r(), 'a');
  EXPECT_EQ(vector2c.g(), 'b');
  EXPECT_EQ(vector1c.r(), 'a');

  EXPECT_EQ(vector4s.r(), 1);
  EXPECT_EQ(vector4s.g(), 2);
  EXPECT_EQ(vector4s.b(), 3);
  EXPECT_EQ(vector4s.a(), 4);
  EXPECT_EQ(vector3s.r(), 1);
  EXPECT_EQ(vector3s.g(), 2);
  EXPECT_EQ(vector3s.b(), 3);
  EXPECT_EQ(vector2s.r(), 1);
  EXPECT_EQ(vector2s.g(), 2);
  EXPECT_EQ(vector1s.r(), 1);

  EXPECT_EQ(vector4us.r(), 1U);
  EXPECT_EQ(vector4us.g(), 2U);
  EXPECT_EQ(vector4us.b(), 3U);
  EXPECT_EQ(vector4us.a(), 4U);
  EXPECT_EQ(vector3us.r(), 1U);
  EXPECT_EQ(vector3us.g(), 2U);
  EXPECT_EQ(vector3us.b(), 3U);
  EXPECT_EQ(vector2us.r(), 1U);
  EXPECT_EQ(vector2us.g(), 2U);
  EXPECT_EQ(vector1us.r(), 1U);
}

TEST_F(VectorTest, CoordinatesAccessingIJKL) {
  EXPECT_EQ(vector4f.i(), 1.0f);
  EXPECT_EQ(vector4f.j(), 2.0f);
  EXPECT_EQ(vector4f.k(), 3.0f);
  EXPECT_EQ(vector4f.l(), 4.0f);
  EXPECT_EQ(vector3f.i(), 1.0f);
  EXPECT_EQ(vector3f.j(), 2.0f);
  EXPECT_EQ(vector3f.k(), 3.0f);
  EXPECT_EQ(vector2f.i(), 1.0f);
  EXPECT_EQ(vector2f.j(), 2.0f);
  EXPECT_EQ(vector1f.i(), 1.0f);

  EXPECT_EQ(vector4d.i(), 1.0);
  EXPECT_EQ(vector4d.j(), 2.0);
  EXPECT_EQ(vector4d.k(), 3.0);
  EXPECT_EQ(vector4d.l(), 4.0);
  EXPECT_EQ(vector3d.i(), 1.0);
  EXPECT_EQ(vector3d.j(), 2.0);
  EXPECT_EQ(vector3d.k(), 3.0);
  EXPECT_EQ(vector2d.i(), 1.0);
  EXPECT_EQ(vector2d.j(), 2.0);
  EXPECT_EQ(vector1d.i(), 1.0);

  EXPECT_EQ(vector4i.i(), 1);
  EXPECT_EQ(vector4i.j(), 2);
  EXPECT_EQ(vector4i.k(), 3);
  EXPECT_EQ(vector4i.l(), 4);
  EXPECT_EQ(vector3i.i(), 1);
  EXPECT_EQ(vector3i.j(), 2);
  EXPECT_EQ(vector3i.k(), 3);
  EXPECT_EQ(vector2i.i(), 1);
  EXPECT_EQ(vector2i.j(), 2);
  EXPECT_EQ(vector1i.i(), 1);

  EXPECT_EQ(vector4u.i(), 1U);
  EXPECT_EQ(vector4u.j(), 2U);
  EXPECT_EQ(vector4u.k(), 3U);
  EXPECT_EQ(vector4u.l(), 4U);
  EXPECT_EQ(vector3u.i(), 1U);
  EXPECT_EQ(vector3u.j(), 2U);
  EXPECT_EQ(vector3u.k(), 3U);
  EXPECT_EQ(vector2u.i(), 1U);
  EXPECT_EQ(vector2u.j(), 2U);
  EXPECT_EQ(vector1u.i(), 1U);

  EXPECT_TRUE(vector4b.i());
  EXPECT_FALSE(vector4b.j());
  EXPECT_TRUE(vector4b.k());
  EXPECT_FALSE(vector4b.l());
  EXPECT_TRUE(vector3b.i());
  EXPECT_FALSE(vector3b.j());
  EXPECT_TRUE(vector3b.k());
  EXPECT_TRUE(vector2b.i());
  EXPECT_FALSE(vector2b.j());
  EXPECT_TRUE(vector1b.i());

  EXPECT_EQ(vector4c.i(), 'a');
  EXPECT_EQ(vector4c.j(), 'b');
  EXPECT_EQ(vector4c.k(), 'c');
  EXPECT_EQ(vector4c.l(), 'd');
  EXPECT_EQ(vector3c.i(), 'a');
  EXPECT_EQ(vector3c.j(), 'b');
  EXPECT_EQ(vector3c.k(), 'c');
  EXPECT_EQ(vector2c.i(), 'a');
  EXPECT_EQ(vector2c.j(), 'b');
  EXPECT_EQ(vector1c.i(), 'a');

  EXPECT_EQ(vector4s.i(), 1);
  EXPECT_EQ(vector4s.j(), 2);
  EXPECT_EQ(vector4s.k(), 3);
  EXPECT_EQ(vector4s.l(), 4);
  EXPECT_EQ(vector3s.i(), 1);
  EXPECT_EQ(vector3s.j(), 2);
  EXPECT_EQ(vector3s.k(), 3);
  EXPECT_EQ(vector2s.i(), 1);
  EXPECT_EQ(vector2s.j(), 2);
  EXPECT_EQ(vector1s.i(), 1);

  EXPECT_EQ(vector4us.i(), 1U);
  EXPECT_EQ(vector4us.j(), 2U);
  EXPECT_EQ(vector4us.k(), 3U);
  EXPECT_EQ(vector4us.l(), 4U);
  EXPECT_EQ(vector3us.i(), 1U);
  EXPECT_EQ(vector3us.j(), 2U);
  EXPECT_EQ(vector3us.k(), 3U);
  EXPECT_EQ(vector2us.i(), 1U);
  EXPECT_EQ(vector2us.j(), 2U);
  EXPECT_EQ(vector1us.i(), 1U);
}

TEST_F(VectorTest, CoordinatesAccessingSTPQ) {
  EXPECT_EQ(vector4f.s(), 1.0f);
  EXPECT_EQ(vector4f.t(), 2.0f);
  EXPECT_EQ(vector4f.p(), 3.0f);
  EXPECT_EQ(vector4f.q(), 4.0f);
  EXPECT_EQ(vector3f.s(), 1.0f);
  EXPECT_EQ(vector3f.t(), 2.0f);
  EXPECT_EQ(vector3f.p(), 3.0f);
  EXPECT_EQ(vector2f.s(), 1.0f);
  EXPECT_EQ(vector2f.t(), 2.0f);
  EXPECT_EQ(vector1f.s(), 1.0f);

  EXPECT_EQ(vector4d.s(), 1.0);
  EXPECT_EQ(vector4d.t(), 2.0);
  EXPECT_EQ(vector4d.p(), 3.0);
  EXPECT_EQ(vector4d.q(), 4.0);
  EXPECT_EQ(vector3d.s(), 1.0);
  EXPECT_EQ(vector3d.t(), 2.0);
  EXPECT_EQ(vector3d.p(), 3.0);
  EXPECT_EQ(vector2d.s(), 1.0);
  EXPECT_EQ(vector2d.t(), 2.0);
  EXPECT_EQ(vector1d.s(), 1.0);

  EXPECT_EQ(vector4i.s(), 1);
  EXPECT_EQ(vector4i.t(), 2);
  EXPECT_EQ(vector4i.p(), 3);
  EXPECT_EQ(vector4i.q(), 4);
  EXPECT_EQ(vector3i.s(), 1);
  EXPECT_EQ(vector3i.t(), 2);
  EXPECT_EQ(vector3i.p(), 3);
  EXPECT_EQ(vector2i.s(), 1);
  EXPECT_EQ(vector2i.t(), 2);
  EXPECT_EQ(vector1i.s(), 1);

  EXPECT_EQ(vector4u.s(), 1U);
  EXPECT_EQ(vector4u.t(), 2U);
  EXPECT_EQ(vector4u.p(), 3U);
  EXPECT_EQ(vector4u.q(), 4U);
  EXPECT_EQ(vector3u.s(), 1U);
  EXPECT_EQ(vector3u.t(), 2U);
  EXPECT_EQ(vector3u.p(), 3U);
  EXPECT_EQ(vector2u.s(), 1U);
  EXPECT_EQ(vector2u.t(), 2U);
  EXPECT_EQ(vector1u.s(), 1U);

  EXPECT_TRUE(vector4b.s());
  EXPECT_FALSE(vector4b.t());
  EXPECT_TRUE(vector4b.p());
  EXPECT_FALSE(vector4b.q());
  EXPECT_TRUE(vector3b.s());
  EXPECT_FALSE(vector3b.t());
  EXPECT_TRUE(vector3b.p());
  EXPECT_TRUE(vector2b.s());
  EXPECT_FALSE(vector2b.t());
  EXPECT_TRUE(vector1b.s());

  EXPECT_EQ(vector4c.s(), 'a');
  EXPECT_EQ(vector4c.t(), 'b');
  EXPECT_EQ(vector4c.p(), 'c');
  EXPECT_EQ(vector4c.q(), 'd');
  EXPECT_EQ(vector3c.s(), 'a');
  EXPECT_EQ(vector3c.t(), 'b');
  EXPECT_EQ(vector3c.p(), 'c');
  EXPECT_EQ(vector2c.s(), 'a');
  EXPECT_EQ(vector2c.t(), 'b');
  EXPECT_EQ(vector1c.s(), 'a');

  EXPECT_EQ(vector4s.s(), 1);
  EXPECT_EQ(vector4s.t(), 2);
  EXPECT_EQ(vector4s.p(), 3);
  EXPECT_EQ(vector4s.q(), 4);
  EXPECT_EQ(vector3s.s(), 1);
  EXPECT_EQ(vector3s.t(), 2);
  EXPECT_EQ(vector3s.p(), 3);
  EXPECT_EQ(vector2s.s(), 1);
  EXPECT_EQ(vector2s.t(), 2);
  EXPECT_EQ(vector1s.s(), 1);

  EXPECT_EQ(vector4us.s(), 1U);
  EXPECT_EQ(vector4us.t(), 2U);
  EXPECT_EQ(vector4us.p(), 3U);
  EXPECT_EQ(vector4us.q(), 4U);
  EXPECT_EQ(vector3us.s(), 1U);
  EXPECT_EQ(vector3us.t(), 2U);
  EXPECT_EQ(vector3us.p(), 3U);
  EXPECT_EQ(vector2us.s(), 1U);
  EXPECT_EQ(vector2us.t(), 2U);
  EXPECT_EQ(vector1us.s(), 1U);
}

TEST_F(VectorTest, DefaultConstructor) {
  Vector4F vector4f2{};
  Vector3F vector3f2{};
  Vector2F vector2f2{};
  Vector1F vector1f2{};
  Vector4I vector4i2{};
  Vector3I vector3i2{};
  Vector2I vector2i2{};
  Vector1I vector1i2{};

  EXPECT_EQ(vector4f2.x(), 0.0f);
  EXPECT_EQ(vector4f2.y(), 0.0f);
  EXPECT_EQ(vector4f2.z(), 0.0f);
  EXPECT_EQ(vector4f2.w(), 0.0f);
  EXPECT_EQ(vector3f2.x(), 0.0f);
  EXPECT_EQ(vector3f2.y(), 0.0f);
  EXPECT_EQ(vector3f2.z(), 0.0f);
  EXPECT_EQ(vector2f2.x(), 0.0f);
  EXPECT_EQ(vector2f2.y(), 0.0f);
  EXPECT_EQ(vector1f2.x(), 0.0f);

  EXPECT_EQ(vector4i2.x(), 0);
  EXPECT_EQ(vector4i2.y(), 0);
  EXPECT_EQ(vector4i2.z(), 0);
  EXPECT_EQ(vector4i2.w(), 0);
  EXPECT_EQ(vector3i2.x(), 0);
  EXPECT_EQ(vector3i2.y(), 0);
  EXPECT_EQ(vector3i2.z(), 0);
  EXPECT_EQ(vector2i2.x(), 0);
  EXPECT_EQ(vector2i2.y(), 0);
  EXPECT_EQ(vector1i2.x(), 0);
}

TEST_F(VectorTest, ScalarConstructor) {
  Vector4F vector4f2{1.5f};
  Vector3F vector3f2{2.5f};
  Vector2F vector2f2{3.5f};
  Vector1F vector1f2{4.5f};
  Vector4I vector4i2{10};
  Vector3I vector3i2{20};
  Vector2I vector2i2{30};
  Vector1I vector1i2{40};

  EXPECT_EQ(vector4f2.x(), 1.5f);
  EXPECT_EQ(vector4f2.y(), 1.5f);
  EXPECT_EQ(vector4f2.z(), 1.5f);
  EXPECT_EQ(vector4f2.w(), 1.5f);
  EXPECT_EQ(vector3f2.x(), 2.5f);
  EXPECT_EQ(vector3f2.y(), 2.5f);
  EXPECT_EQ(vector3f2.z(), 2.5f);
  EXPECT_EQ(vector2f2.x(), 3.5f);
  EXPECT_EQ(vector2f2.y(), 3.5f);
  EXPECT_EQ(vector1f2.x(), 4.5f);

  EXPECT_EQ(vector4i2.x(), 10);
  EXPECT_EQ(vector4i2.y(), 10);
  EXPECT_EQ(vector4i2.z(), 10);
  EXPECT_EQ(vector4i2.w(), 10);
  EXPECT_EQ(vector3i2.x(), 20);
  EXPECT_EQ(vector3i2.y(), 20);
  EXPECT_EQ(vector3i2.z(), 20);
  EXPECT_EQ(vector2i2.x(), 30);
  EXPECT_EQ(vector2i2.y(), 30);
  EXPECT_EQ(vector1i2.x(), 40);
}

TEST_F(VectorTest, ConversionConstructor) {
  Vector4F vector4f2{Vector3F{1.0f, 2.0f, 3.0f}, 4.0f};
  Vector4F vector4f3{Vector2F{1.0f, 2.0f}, 3.0f, 4.0f};
  Vector4F vector4f4{Vector1F{1.0f}, 2.0f, 3.0f, 4.0f};
  Vector4F vector4f5{Vector3F{1.0f, 2.0f, 3.0f}};
  Vector4F vector4f6{Vector2F{1.0f, 2.0f}};
  Vector4F vector4f7{Vector1F{1.0f}};
  Vector3F vector3f2{Vector2F{1.0f, 2.0f}, 3.0f};
  Vector3F vector3f3{Vector1F{1.0f}, 2.0f, 3.0f};
  Vector3F vector3f4{Vector2F{1.0f, 2.0f}};
  Vector3F vector3f5{Vector1F{1.0f}};
  Vector3F vector3f6{Vector4F{1.0f, 2.0f, 3.0f, 4.0f}};
  Vector2F vector2f2{Vector1F{1.0f}, 2.0f};
  Vector2F vector2f3{Vector1F{1.0f}};
  Vector2F vector2f4{Vector4F{1.0f, 2.0f, 3.0f, 4.0f}};
  Vector2F vector2f5{Vector3F{1.0f, 2.0f, 3.0f}};

  Vector4I vector4i2{Vector3I{10, 20, 30}, 40};
  Vector4I vector4i3{Vector2I{10, 20}, 30, 40};
  Vector4I vector4i4{Vector1I{10}, 20, 30, 40};
  Vector4I vector4i5{Vector3I{10, 20, 30}};
  Vector4I vector4i6{Vector2I{10, 20}};
  Vector4I vector4i7{Vector1I{10}};
  Vector3I vector3i2{Vector2I{10, 20}, 30};
  Vector3I vector3i3{Vector1I{10}, 20, 30};
  Vector3I vector3i4{Vector2I{10, 20}};
  Vector3I vector3i5{Vector1I{10}};
  Vector3I vector3i6{Vector4I{10, 20, 30, 40}};
  Vector2I vector2i2{Vector1I{10}, 20};
  Vector2I vector2i3{Vector1I{10}};
  Vector2I vector2i4{Vector4I{10, 20, 30, 40}};
  Vector2I vector2i5{Vector4I{10, 20, 30, 40}};

  EXPECT_EQ(vector4f2, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(vector4f3, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(vector4f4, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(vector4f5, (Vector4F{1.0f, 2.0f, 3.0f, 0.0f}));
  EXPECT_EQ(vector4f6, (Vector4F{1.0f, 2.0f, 0.0f, 0.0f}));
  EXPECT_EQ(vector4f7, (Vector4F{1.0f, 0.0f, 0.0f, 0.0f}));
  EXPECT_EQ(vector3f2, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(vector3f3, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(vector3f4, (Vector3F{1.0f, 2.0f, 0.0f}));
  EXPECT_EQ(vector3f5, (Vector3F{1.0f, 0.0f, 0.0f}));
  EXPECT_EQ(vector3f6, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(vector2f2, (Vector2F{1.0f, 2.0f}));
  EXPECT_EQ(vector2f3, (Vector2F{1.0f, 0.0f}));
  EXPECT_EQ(vector2f4, (Vector2F{1.0f, 2.0f}));
  EXPECT_EQ(vector2f5, (Vector2F{1.0f, 2.0f}));

  EXPECT_EQ(vector4i2, (Vector4I{10, 20, 30, 40}));
  EXPECT_EQ(vector4i3, (Vector4I{10, 20, 30, 40}));
  EXPECT_EQ(vector4i4, (Vector4I{10, 20, 30, 40}));
  EXPECT_EQ(vector4i5, (Vector4I{10, 20, 30, 0}));
  EXPECT_EQ(vector4i6, (Vector4I{10, 20, 0, 0}));
  EXPECT_EQ(vector4i7, (Vector4I{10, 0, 0, 0}));
  EXPECT_EQ(vector3i2, (Vector3I{10, 20, 30}));
  EXPECT_EQ(vector3i3, (Vector3I{10, 20, 30}));
  EXPECT_EQ(vector3i4, (Vector3I{10, 20, 0}));
  EXPECT_EQ(vector3i5, (Vector3I{10, 0, 0}));
  EXPECT_EQ(vector3i6, (Vector3I{10, 20, 30}));
  EXPECT_EQ(vector2i2, (Vector2I{10, 20}));
  EXPECT_EQ(vector2i3, (Vector2I{10, 0}));
  EXPECT_EQ(vector2i4, (Vector2I{10, 20}));
  EXPECT_EQ(vector2i5, (Vector2I{10, 20}));
}

// TEST_F(VectorTest, STDArrayConstructor) {
//   Vector4F vector4f2{Vector3F{1.0f, 2.0f, 3.0f}, 4.0f};
//   Vector3F vector3f2{Vector2F{1.0f, 2.0f}, 3.0f};
//   Vector3F vector3f3{Vector1F{1.0f}, 2.0f, 3.0f};
//   Vector3F vector3f4{Vector2F{1.0f, 2.0f}};
//   Vector3F vector3f5{Vector1F{1.0f}};
//   Vector4I vector4i2{Vector3I{10, 20, 30}, 40};
//   Vector3I vector3i2{Vector2I{10, 20}, 30};
//   Vector3I vector3i3{Vector1I{10}, 20, 30};
//   Vector3I vector3i4{Vector2I{10, 20}};
//   Vector3I vector3i5{Vector1I{10}};
//
//   EXPECT_EQ(vector4f2, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
//   EXPECT_EQ(vector4f3, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
//   EXPECT_EQ(vector4f4, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
//   EXPECT_EQ(vector4f5, (Vector4F{1.0f, 2.0f, 3.0f, 0.0f}));
//   EXPECT_EQ(vector4f6, (Vector4F{1.0f, 2.0f, 0.0f, 0.0f}));
//   EXPECT_EQ(vector4f7, (Vector4F{1.0f, 0.0f, 0.0f, 0.0f}));
//   EXPECT_EQ(vector3f2, (Vector3F{1.0f, 2.0f, 3.0f}));
//   EXPECT_EQ(vector3f3, (Vector3F{1.0f, 2.0f, 3.0f}));
//   EXPECT_EQ(vector3f4, (Vector3F{1.0f, 2.0f, 0.0f}));
//   EXPECT_EQ(vector3f5, (Vector3F{1.0f, 0.0f, 0.0f}));
//
//   EXPECT_EQ(vector4i2, (Vector4I{10, 20, 30, 40}));
//   EXPECT_EQ(vector4i3, (Vector4I{10, 20, 30, 40}));
//   EXPECT_EQ(vector4i4, (Vector4I{10, 20, 30, 40}));
//   EXPECT_EQ(vector4i5, (Vector4I{10, 20, 30, 0}));
//   EXPECT_EQ(vector4i6, (Vector4I{10, 20, 0, 0}));
//   EXPECT_EQ(vector4i7, (Vector4I{10, 0, 0, 0}));
//   EXPECT_EQ(vector3i2, (Vector3I{10, 20, 30}));
//   EXPECT_EQ(vector3i3, (Vector3I{10, 20, 30}));
//   EXPECT_EQ(vector3i4, (Vector3I{10, 20, 0}));
//   EXPECT_EQ(vector3i5, (Vector3I{10, 0, 0}));
// }

TEST_F(VectorTest, Assignment) {
  vector4f = Vector4F{1.5f, 2.5f, 3.5f, 4.5f};
  vector3f = Vector3F{1.5f, 2.5f, 3.5f};
  vector2f = Vector2F{1.5f, 2.5f};
  vector1f = Vector1F{1.5f};
  vector4i = Vector4I{10, 20, 30, 40};
  vector3i = Vector3I{10, 20, 30};
  vector2i = Vector2I{10, 20};
  vector1i = Vector1I{10};

  EXPECT_EQ(vector4f.x(), 1.5f);
  EXPECT_EQ(vector4f.y(), 2.5f);
  EXPECT_EQ(vector4f.z(), 3.5f);
  EXPECT_EQ(vector4f.w(), 4.5f);
  EXPECT_EQ(vector3f.x(), 1.5f);
  EXPECT_EQ(vector3f.y(), 2.5f);
  EXPECT_EQ(vector3f.z(), 3.5f);
  EXPECT_EQ(vector2f.x(), 1.5f);
  EXPECT_EQ(vector2f.y(), 2.5f);
  EXPECT_EQ(vector1f.x(), 1.5f);

  EXPECT_EQ(vector4i.x(), 10);
  EXPECT_EQ(vector4i.y(), 20);
  EXPECT_EQ(vector4i.z(), 30);
  EXPECT_EQ(vector4i.w(), 40);
  EXPECT_EQ(vector3i.x(), 10);
  EXPECT_EQ(vector3i.y(), 20);
  EXPECT_EQ(vector3i.z(), 30);
  EXPECT_EQ(vector2i.x(), 10);
  EXPECT_EQ(vector2i.y(), 20);
  EXPECT_EQ(vector1i.x(), 10);
}

}  // namespace Neat