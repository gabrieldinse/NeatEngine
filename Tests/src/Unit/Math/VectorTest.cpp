
#include <gtest/gtest.h>

#include <TestUtils.hpp>

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

TEST_F(VectorTest, VectorSizes) {
  EXPECT_EQ(Vector4F::N, 4);
  EXPECT_EQ(Vector4D::N, 4);
  EXPECT_EQ(Vector4I::N, 4);
  EXPECT_EQ(Vector4U::N, 4);

  EXPECT_EQ(Vector3F::N, 3);
  EXPECT_EQ(Vector3D::N, 3);
  EXPECT_EQ(Vector3I::N, 3);
  EXPECT_EQ(Vector3U::N, 3);

  EXPECT_EQ(Vector2F::N, 2);
  EXPECT_EQ(Vector2D::N, 2);
  EXPECT_EQ(Vector2I::N, 2);
  EXPECT_EQ(Vector2U::N, 2);

  EXPECT_EQ(Vector1F::N, 1);
  EXPECT_EQ(Vector1D::N, 1);
  EXPECT_EQ(Vector1I::N, 1);
  EXPECT_EQ(Vector1U::N, 1);

  EXPECT_EQ(Vector4F::Size, 4);
  EXPECT_EQ(Vector4D::Size, 4);
  EXPECT_EQ(Vector4I::Size, 4);
  EXPECT_EQ(Vector4U::Size, 4);

  EXPECT_EQ(Vector3F::Size, 3);
  EXPECT_EQ(Vector3D::Size, 3);
  EXPECT_EQ(Vector3I::Size, 3);
  EXPECT_EQ(Vector3U::Size, 3);

  EXPECT_EQ(Vector2F::Size, 2);
  EXPECT_EQ(Vector2D::Size, 2);
  EXPECT_EQ(Vector2I::Size, 2);
  EXPECT_EQ(Vector2U::Size, 2);

  EXPECT_EQ(Vector1F::Size, 1);
  EXPECT_EQ(Vector1D::Size, 1);
  EXPECT_EQ(Vector1I::Size, 1);
  EXPECT_EQ(Vector1U::Size, 1);
}

TEST_F(VectorTest, IndexOperator) {
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

  // Assignment tests
  vector4f[0] = 10.0f;
  vector3f[1] = 20.0f;
  vector2f[0] = 30.0f;
  vector1f[0] = 40.0f;
  EXPECT_EQ(vector4f[0], 10.0f);
  EXPECT_EQ(vector3f[1], 20.0f);
  EXPECT_EQ(vector2f[0], 30.0f);
  EXPECT_EQ(vector1f[0], 40.0f);
}

TEST_F(VectorTest, CallOperator) {
  EXPECT_EQ(vector4f(0), 1.0f);
  EXPECT_EQ(vector4f(1), 2.0f);
  EXPECT_EQ(vector4f(2), 3.0f);
  EXPECT_EQ(vector4f(3), 4.0f);
  EXPECT_EQ(vector3f(0), 1.0f);
  EXPECT_EQ(vector3f(1), 2.0f);
  EXPECT_EQ(vector3f(2), 3.0f);
  EXPECT_EQ(vector2f(0), 1.0f);
  EXPECT_EQ(vector2f(1), 2.0f);
  EXPECT_EQ(vector1f(0), 1.0f);

  EXPECT_EQ(vector4d(0), 1.0);
  EXPECT_EQ(vector4d(1), 2.0);
  EXPECT_EQ(vector4d(2), 3.0);
  EXPECT_EQ(vector4d(3), 4.0);
  EXPECT_EQ(vector3d(0), 1.0);
  EXPECT_EQ(vector3d(1), 2.0);
  EXPECT_EQ(vector3d(2), 3.0);
  EXPECT_EQ(vector2d(0), 1.0);
  EXPECT_EQ(vector2d(1), 2.0);
  EXPECT_EQ(vector1d(0), 1.0);

  EXPECT_EQ(vector4i(0), 1);
  EXPECT_EQ(vector4i(1), 2);
  EXPECT_EQ(vector4i(2), 3);
  EXPECT_EQ(vector4i(3), 4);
  EXPECT_EQ(vector3i(0), 1);
  EXPECT_EQ(vector3i(1), 2);
  EXPECT_EQ(vector3i(2), 3);
  EXPECT_EQ(vector2i(0), 1);
  EXPECT_EQ(vector2i(1), 2);
  EXPECT_EQ(vector1i(0), 1);

  EXPECT_EQ(vector4u(0), 1U);
  EXPECT_EQ(vector4u(1), 2U);
  EXPECT_EQ(vector4u(2), 3U);
  EXPECT_EQ(vector4u(3), 4U);
  EXPECT_EQ(vector3u(0), 1U);
  EXPECT_EQ(vector3u(1), 2U);
  EXPECT_EQ(vector3u(2), 3U);
  EXPECT_EQ(vector2u(0), 1U);
  EXPECT_EQ(vector2u(1), 2U);
  EXPECT_EQ(vector1u(0), 1U);

  EXPECT_TRUE(vector4b(0));
  EXPECT_FALSE(vector4b(1));
  EXPECT_TRUE(vector4b(2));
  EXPECT_FALSE(vector4b(3));
  EXPECT_TRUE(vector3b(0));
  EXPECT_FALSE(vector3b(1));
  EXPECT_TRUE(vector3b(2));
  EXPECT_TRUE(vector2b(0));
  EXPECT_FALSE(vector2b(1));
  EXPECT_TRUE(vector1b(0));

  EXPECT_EQ(vector4c(0), 'a');
  EXPECT_EQ(vector4c(1), 'b');
  EXPECT_EQ(vector4c(2), 'c');
  EXPECT_EQ(vector4c(3), 'd');
  EXPECT_EQ(vector3c(0), 'a');
  EXPECT_EQ(vector3c(1), 'b');
  EXPECT_EQ(vector3c(2), 'c');
  EXPECT_EQ(vector2c(0), 'a');
  EXPECT_EQ(vector2c(1), 'b');
  EXPECT_EQ(vector1c(0), 'a');

  EXPECT_EQ(vector4s(0), 1);
  EXPECT_EQ(vector4s(1), 2);
  EXPECT_EQ(vector4s(2), 3);
  EXPECT_EQ(vector4s(3), 4);
  EXPECT_EQ(vector3s(0), 1);
  EXPECT_EQ(vector3s(1), 2);
  EXPECT_EQ(vector3s(2), 3);
  EXPECT_EQ(vector2s(0), 1);
  EXPECT_EQ(vector2s(1), 2);
  EXPECT_EQ(vector1s(0), 1);

  EXPECT_EQ(vector4us(0), 1U);
  EXPECT_EQ(vector4us(1), 2U);
  EXPECT_EQ(vector4us(2), 3U);
  EXPECT_EQ(vector4us(3), 4U);
  EXPECT_EQ(vector3us(0), 1U);
  EXPECT_EQ(vector3us(1), 2U);
  EXPECT_EQ(vector3us(2), 3U);
  EXPECT_EQ(vector2us(0), 1U);
  EXPECT_EQ(vector2us(1), 2U);
  EXPECT_EQ(vector1us(0), 1U);

  // Assignment tests
  vector4f(0) = 10.0f;
  vector4f(1) = 20.0f;
  vector4f(2) = 30.0f;
  vector4f(3) = 40.0f;
  vector3f(0) = 50.0f;
  vector3f(1) = 60.0f;
  vector3f(2) = 70.0f;
  vector2f(0) = 80.0f;
  vector2f(1) = 90.0f;
  vector1f(0) = 100.0f;
  EXPECT_EQ(vector4f(0), 10.0f);
  EXPECT_EQ(vector4f(1), 20.0f);
  EXPECT_EQ(vector4f(2), 30.0f);
  EXPECT_EQ(vector4f(3), 40.0f);
  EXPECT_EQ(vector3f(0), 50.0f);
  EXPECT_EQ(vector3f(1), 60.0f);
  EXPECT_EQ(vector3f(2), 70.0f);
  EXPECT_EQ(vector2f(0), 80.0f);
  EXPECT_EQ(vector2f(1), 90.0f);
  EXPECT_EQ(vector1f(0), 100.0f);
}

TEST_F(VectorTest, XYZW) {
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

  // Assignment tests
  vector4f.x() = 10.0f;
  vector4f.y() = 20.0f;
  vector4f.z() = 30.0f;
  vector4f.w() = 40.0f;
  vector3f.x() = 50.0f;
  vector3f.y() = 60.0f;
  vector3f.z() = 70.0f;
  vector2f.x() = 80.0f;
  vector2f.y() = 90.0f;
  vector1f.x() = 100.0f;
  EXPECT_EQ(vector4f.x(), 10.0f);
  EXPECT_EQ(vector4f.y(), 20.0f);
  EXPECT_EQ(vector4f.z(), 30.0f);
  EXPECT_EQ(vector4f.w(), 40.0f);
  EXPECT_EQ(vector3f.x(), 50.0f);
  EXPECT_EQ(vector3f.y(), 60.0f);
  EXPECT_EQ(vector3f.z(), 70.0f);
  EXPECT_EQ(vector2f.x(), 80.0f);
  EXPECT_EQ(vector2f.y(), 90.0f);
  EXPECT_EQ(vector1f.x(), 100.0f);
}

TEST_F(VectorTest, RGBA) {
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

  // Assignment tests
  vector4f.r() = 10.0f;
  vector4f.g() = 20.0f;
  vector4f.b() = 30.0f;
  vector4f.a() = 40.0f;
  vector3f.r() = 50.0f;
  vector3f.g() = 60.0f;
  vector3f.b() = 70.0f;
  vector2f.r() = 80.0f;
  vector2f.g() = 90.0f;
  vector1f.r() = 100.0f;
  EXPECT_EQ(vector4f.r(), 10.0f);
  EXPECT_EQ(vector4f.g(), 20.0f);
  EXPECT_EQ(vector4f.b(), 30.0f);
  EXPECT_EQ(vector4f.a(), 40.0f);
  EXPECT_EQ(vector3f.r(), 50.0f);
  EXPECT_EQ(vector3f.g(), 60.0f);
  EXPECT_EQ(vector3f.b(), 70.0f);
  EXPECT_EQ(vector2f.r(), 80.0f);
  EXPECT_EQ(vector2f.g(), 90.0f);
  EXPECT_EQ(vector1f.r(), 100.0f);
}

TEST_F(VectorTest, IJKL) {
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

  // Assignment tests
  vector4f.i() = 10.0f;
  vector4f.j() = 20.0f;
  vector4f.k() = 30.0f;
  vector4f.l() = 40.0f;
  vector3f.i() = 50.0f;
  vector3f.j() = 60.0f;
  vector3f.k() = 70.0f;
  vector2f.i() = 80.0f;
  vector2f.j() = 90.0f;
  vector1f.i() = 100.0f;
  EXPECT_EQ(vector4f.i(), 10.0f);
  EXPECT_EQ(vector4f.j(), 20.0f);
  EXPECT_EQ(vector4f.k(), 30.0f);
  EXPECT_EQ(vector4f.l(), 40.0f);
  EXPECT_EQ(vector3f.i(), 50.0f);
  EXPECT_EQ(vector3f.j(), 60.0f);
  EXPECT_EQ(vector3f.k(), 70.0f);
  EXPECT_EQ(vector2f.i(), 80.0f);
  EXPECT_EQ(vector2f.j(), 90.0f);
  EXPECT_EQ(vector1f.i(), 100.0f);
}

TEST_F(VectorTest, STPQ) {
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

  // Assignment tests
  vector4f.s() = 10.0f;
  vector4f.t() = 20.0f;
  vector4f.p() = 30.0f;
  vector4f.q() = 40.0f;
  vector3f.s() = 50.0f;
  vector3f.t() = 60.0f;
  vector3f.p() = 70.0f;
  vector2f.s() = 80.0f;
  vector2f.t() = 90.0f;
  vector1f.s() = 100.0f;
  EXPECT_EQ(vector4f.s(), 10.0f);
  EXPECT_EQ(vector4f.t(), 20.0f);
  EXPECT_EQ(vector4f.p(), 30.0f);
  EXPECT_EQ(vector4f.q(), 40.0f);
  EXPECT_EQ(vector3f.s(), 50.0f);
  EXPECT_EQ(vector3f.t(), 60.0f);
  EXPECT_EQ(vector3f.p(), 70.0f);
  EXPECT_EQ(vector2f.s(), 80.0f);
  EXPECT_EQ(vector2f.t(), 90.0f);
  EXPECT_EQ(vector1f.s(), 100.0f);
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

TEST_F(VectorTest, CopyConstructor) {
  Vector4F vector4f2{vector4f};
  Vector3F vector3f2{vector3f};
  Vector2F vector2f2{vector2f};
  Vector1F vector1f2{vector1f};
  Vector4I vector4i2{vector4i};
  Vector3I vector3i2{vector3i};
  Vector2I vector2i2{vector2i};
  Vector1I vector1i2{vector1i};

  EXPECT_EQ(vector4f2, vector4f);
  EXPECT_EQ(vector3f2, vector3f);
  EXPECT_EQ(vector2f2, vector2f);
  EXPECT_EQ(vector1f2, vector1f);
  EXPECT_EQ(vector4i2, vector4i);
  EXPECT_EQ(vector3i2, vector3i);
  EXPECT_EQ(vector2i2, vector2i);
  EXPECT_EQ(vector1i2, vector1i);
}

TEST_F(VectorTest, DifferentSizesConversionConstructor) {
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

TEST_F(VectorTest, DifferentTypesConversionConstructor) {
  Vector4F conversionVec4f{vector4i};
  Vector4F conversionVec4f2{vector4d};
  Vector4F conversionVec4f3{vector4u};
  Vector4I conversionVec4i{vector4f};
  Vector4I conversionVec4i2{vector4d};
  Vector4I conversionVec4i3{vector4u};
  Vector4D conversionVec4d{vector4f};
  Vector4D conversionVec4d2{vector4i};
  Vector4D conversionVec4d3{vector4u};
  Vector4U conversionVec4u{vector4f};
  Vector4U conversionVec4u2{vector4i};
  Vector4U conversionVec4u3{vector4d};

  Vector3F conversionVec3f{vector3i};
  Vector3F conversionVec3f2{vector3d};
  Vector3F conversionVec3f3{vector3u};
  Vector3I conversionVec3i{vector3f};
  Vector3I conversionVec3i2{vector3d};
  Vector3I conversionVec3i3{vector3u};
  Vector3D conversionVec3d{vector3f};
  Vector3D conversionVec3d2{vector3i};
  Vector3D conversionVec3d3{vector3u};
  Vector3U conversionVec3u{vector3f};
  Vector3U conversionVec3u2{vector3i};
  Vector3U conversionVec3u3{vector3d};

  Vector2F conversionVec2f{vector2i};
  Vector2F conversionVec2f2{vector2d};
  Vector2F conversionVec2f3{vector2u};
  Vector2I conversionVec2i{vector2f};
  Vector2I conversionVec2i2{vector2d};
  Vector2I conversionVec2i3{vector2u};
  Vector2D conversionVec2d{vector2f};
  Vector2D conversionVec2d2{vector2i};
  Vector2D conversionVec2d3{vector2u};
  Vector2U conversionVec2u{vector2f};
  Vector2U conversionVec2u2{vector2i};
  Vector2U conversionVec2u3{vector2d};

  Vector1F conversionVec1f{vector1i};
  Vector1F conversionVec1f2{vector1d};
  Vector1F conversionVec1f3{vector1u};
  Vector1I conversionVec1i{vector1f};
  Vector1I conversionVec1i2{vector1d};
  Vector1I conversionVec1i3{vector1u};
  Vector1D conversionVec1d{vector1f};
  Vector1D conversionVec1d2{vector1i};
  Vector1D conversionVec1d3{vector1u};
  Vector1U conversionVec1u{vector1f};
  Vector1U conversionVec1u2{vector1i};
  Vector1U conversionVec1u3{vector1d};

  EXPECT_EQ(conversionVec4f, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(conversionVec4f2, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(conversionVec4f3, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(conversionVec4i, (Vector4I{1, 2, 3, 4}));
  EXPECT_EQ(conversionVec4i2, (Vector4I{1, 2, 3, 4}));
  EXPECT_EQ(conversionVec4i3, (Vector4I{1, 2, 3, 4}));
  EXPECT_EQ(conversionVec4d, (Vector4D{1.0, 2.0, 3.0, 4.0}));
  EXPECT_EQ(conversionVec4d2, (Vector4D{1.0, 2.0, 3.0, 4.0}));
  EXPECT_EQ(conversionVec4d3, (Vector4D{1.0, 2.0, 3.0, 4.0}));
  EXPECT_EQ(conversionVec4u, (Vector4U{1U, 2U, 3U, 4U}));
  EXPECT_EQ(conversionVec4u2, (Vector4U{1U, 2U, 3U, 4U}));
  EXPECT_EQ(conversionVec4u3, (Vector4U{1U, 2U, 3U, 4U}));

  EXPECT_EQ(conversionVec3f, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(conversionVec3f2, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(conversionVec3f3, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(conversionVec3i, (Vector3I{1, 2, 3}));
  EXPECT_EQ(conversionVec3i2, (Vector3I{1, 2, 3}));
  EXPECT_EQ(conversionVec3i3, (Vector3I{1, 2, 3}));
  EXPECT_EQ(conversionVec3d, (Vector3D{1.0, 2.0, 3.0}));
  EXPECT_EQ(conversionVec3d2, (Vector3D{1.0, 2.0, 3.0}));
  EXPECT_EQ(conversionVec3d3, (Vector3D{1.0, 2.0, 3.0}));
  EXPECT_EQ(conversionVec3u, (Vector3U{1U, 2U, 3U}));
  EXPECT_EQ(conversionVec3u2, (Vector3U{1U, 2U, 3U}));
  EXPECT_EQ(conversionVec3u3, (Vector3U{1U, 2U, 3U}));

  EXPECT_EQ(conversionVec2f, (Vector2F{1.0f, 2.0f}));
  EXPECT_EQ(conversionVec2f2, (Vector2F{1.0f, 2.0f}));
  EXPECT_EQ(conversionVec2f3, (Vector2F{1.0f, 2.0f}));
  EXPECT_EQ(conversionVec2i, (Vector2I{1, 2}));
  EXPECT_EQ(conversionVec2i2, (Vector2I{1, 2}));
  EXPECT_EQ(conversionVec2i3, (Vector2I{1, 2}));
  EXPECT_EQ(conversionVec2d, (Vector2D{1.0, 2.0}));
  EXPECT_EQ(conversionVec2d2, (Vector2D{1.0, 2.0}));
  EXPECT_EQ(conversionVec2d3, (Vector2D{1.0, 2.0}));
  EXPECT_EQ(conversionVec2u, (Vector2U{1U, 2U}));
  EXPECT_EQ(conversionVec2u2, (Vector2U{1U, 2U}));
  EXPECT_EQ(conversionVec2u3, (Vector2U{1U, 2U}));

  EXPECT_EQ(conversionVec1f, (Vector1F{1.0f}));
  EXPECT_EQ(conversionVec1f2, (Vector1F{1.0f}));
  EXPECT_EQ(conversionVec1f3, (Vector1F{1.0f}));
  EXPECT_EQ(conversionVec1i, (Vector1I{1}));
  EXPECT_EQ(conversionVec1i2, (Vector1I{1}));
  EXPECT_EQ(conversionVec1i3, (Vector1I{1}));
  EXPECT_EQ(conversionVec1d, (Vector1D{1.0}));
  EXPECT_EQ(conversionVec1d2, (Vector1D{1.0}));
  EXPECT_EQ(conversionVec1d3, (Vector1D{1.0}));
  EXPECT_EQ(conversionVec1u, (Vector1U{1U}));
  EXPECT_EQ(conversionVec1u2, (Vector1U{1U}));
  EXPECT_EQ(conversionVec1u3, (Vector1U{1U}));
}

TEST_F(VectorTest, DifferentSizesAndTypesConversionConstructor) {
  Vector4F conversionVec4f{vector3i};
  Vector4F conversionVec4f9{vector3u};
  Vector4F conversionVec4f7{vector3i};
  Vector4F conversionVec4f10{vector2i};
  Vector4F conversionVec4f12{vector2u};
  Vector4F conversionVec4f4{vector2d};
  Vector4F conversionVec4f11{vector1d};
  Vector4F conversionVec4f5{vector1u};
  Vector4F conversionVec4f8{vector1i};
  Vector4F conversionVec4f2{vector2d, 3.0, 4};
  Vector4F conversionVec4f3{vector1u, 2U, 3.0, 4};
  Vector4F conversionVec4f6{vector3i, 4.0f};

  EXPECT_EQ(conversionVec4f, (Vector4F{1.0f, 2.0f, 3.0f, 0.0f}));
  EXPECT_EQ(conversionVec4f2, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(conversionVec4f3, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(conversionVec4f4, (Vector4F{1.0f, 2.0f, 0.0f, 0.0f}));
  EXPECT_EQ(conversionVec4f5, (Vector4F{1.0f, 0.0f, 0.0f, 0.0f}));
  EXPECT_EQ(conversionVec4f6, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(conversionVec4f9, (Vector4F{1.0f, 2.0f, 3.0f, 0.0f}));
  EXPECT_EQ(conversionVec4f10, (Vector4F{1.0f, 2.0f, 0.0f, 0.0f}));
  EXPECT_EQ(conversionVec4f11, (Vector4F{1.0f, 0.0f, 0.0f, 0.0f}));
  EXPECT_EQ(conversionVec4f12, (Vector4F{1.0f, 2.0f, 0.0f, 0.0f}));
  EXPECT_EQ(conversionVec4f7, (Vector4F{1.0f, 2.0f, 3.0f, 0.0f}));
  EXPECT_EQ(conversionVec4f8, (Vector4F{1.0f, 0.0f, 0.0f, 0.0f}));

  Vector4I conversionVec4i{vector3f};
  Vector4I conversionVec4i2{vector3d};
  Vector4I conversionVec4i3{vector3u};
  Vector4I conversionVec4i4{vector2f};
  Vector4I conversionVec4i5{vector2d};
  Vector4I conversionVec4i6{vector2u};
  Vector4I conversionVec4i7{vector1f};
  Vector4I conversionVec4i8{vector1d};
  Vector4I conversionVec4i9{vector1u};
  Vector4I conversionVec4i10{vector3f, 4U};
  Vector4I conversionVec4i11{vector2d, 3.0, 4.0f};
  Vector4I conversionVec4i12{vector1u, 2, 3U, 4.0};

  EXPECT_EQ(conversionVec4i, (Vector4I{1, 2, 3, 0}));
  EXPECT_EQ(conversionVec4i2, (Vector4I{1, 2, 3, 0}));
  EXPECT_EQ(conversionVec4i3, (Vector4I{1, 2, 3, 0}));
  EXPECT_EQ(conversionVec4i4, (Vector4I{1, 2, 0, 0}));
  EXPECT_EQ(conversionVec4i5, (Vector4I{1, 2, 0, 0}));
  EXPECT_EQ(conversionVec4i6, (Vector4I{1, 2, 0, 0}));
  EXPECT_EQ(conversionVec4i7, (Vector4I{1, 0, 0, 0}));
  EXPECT_EQ(conversionVec4i8, (Vector4I{1, 0, 0, 0}));
  EXPECT_EQ(conversionVec4i9, (Vector4I{1, 0, 0, 0}));
  EXPECT_EQ(conversionVec4i10, (Vector4I{1, 2, 3, 4}));
  EXPECT_EQ(conversionVec4i11, (Vector4I{1, 2, 3, 4}));
  EXPECT_EQ(conversionVec4i12, (Vector4I{1, 2, 3, 4}));

  Vector4D conversionVec4d{vector3f};
  Vector4D conversionVec4d2{vector3i};
  Vector4D conversionVec4d3{vector3u};
  Vector4D conversionVec4d4{vector2f};
  Vector4D conversionVec4d5{vector2i};
  Vector4D conversionVec4d6{vector2u};
  Vector4D conversionVec4d7{vector1f};
  Vector4D conversionVec4d8{vector1i};
  Vector4D conversionVec4d9{vector1u};
  Vector4D conversionVec4d10{vector3f, 4};
  Vector4D conversionVec4d11{vector2i, 3U, 4};
  Vector4D conversionVec4d12{vector1u, 2.0f, 3, 4U};

  EXPECT_EQ(conversionVec4d, (Vector4D{1.0, 2.0, 3.0, 0.0}));
  EXPECT_EQ(conversionVec4d2, (Vector4D{1.0, 2.0, 3.0, 0.0}));
  EXPECT_EQ(conversionVec4d3, (Vector4D{1.0, 2.0, 3.0, 0.0}));
  EXPECT_EQ(conversionVec4d4, (Vector4D{1.0, 2.0, 0.0, 0.0}));
  EXPECT_EQ(conversionVec4d5, (Vector4D{1.0, 2.0, 0.0, 0.0}));
  EXPECT_EQ(conversionVec4d6, (Vector4D{1.0, 2.0, 0.0, 0.0}));
  EXPECT_EQ(conversionVec4d7, (Vector4D{1.0, 0.0, 0.0, 0.0}));
  EXPECT_EQ(conversionVec4d8, (Vector4D{1.0, 0.0, 0.0, 0.0}));
  EXPECT_EQ(conversionVec4d9, (Vector4D{1.0, 0.0, 0.0, 0.0}));
  EXPECT_EQ(conversionVec4d10, (Vector4D{1.0, 2.0, 3.0, 4.0}));
  EXPECT_EQ(conversionVec4d11, (Vector4D{1.0, 2.0, 3.0, 4.0}));
  EXPECT_EQ(conversionVec4d12, (Vector4D{1.0, 2.0, 3.0, 4.0}));

  Vector4U conversionVec4u{vector3f};
  Vector4U conversionVec4u2{vector3i};
  Vector4U conversionVec4u3{vector3d};
  Vector4U conversionVec4u4{vector2f};
  Vector4U conversionVec4u5{vector2i};
  Vector4U conversionVec4u6{vector2d};
  Vector4U conversionVec4u7{vector1f};
  Vector4U conversionVec4u8{vector1i};
  Vector4U conversionVec4u9{vector1d};
  Vector4U conversionVec4u10{vector3f, 4U};
  Vector4U conversionVec4u11{vector2i, 3, 4.0};
  Vector4U conversionVec4u12{vector1d, 2.0, 3, 4.0f};

  EXPECT_EQ(conversionVec4u, (Vector4U{1U, 2U, 3U, 0U}));
  EXPECT_EQ(conversionVec4u2, (Vector4U{1U, 2U, 3U, 0U}));
  EXPECT_EQ(conversionVec4u3, (Vector4U{1U, 2U, 3U, 0U}));
  EXPECT_EQ(conversionVec4u4, (Vector4U{1U, 2U, 0U, 0U}));
  EXPECT_EQ(conversionVec4u5, (Vector4U{1U, 2U, 0U, 0U}));
  EXPECT_EQ(conversionVec4u6, (Vector4U{1U, 2U, 0U, 0U}));
  EXPECT_EQ(conversionVec4u7, (Vector4U{1U, 0U, 0U, 0U}));
  EXPECT_EQ(conversionVec4u8, (Vector4U{1U, 0U, 0U, 0U}));
  EXPECT_EQ(conversionVec4u9, (Vector4U{1U, 0U, 0U, 0U}));
  EXPECT_EQ(conversionVec4u10, (Vector4U{1U, 2U, 3U, 4U}));
  EXPECT_EQ(conversionVec4u11, (Vector4U{1U, 2U, 3U, 4U}));
  EXPECT_EQ(conversionVec4u12, (Vector4U{1U, 2U, 3U, 4U}));

  Vector3F conversionVec3f{vector2i};
  Vector3F conversionVec3f2{vector2u};
  Vector3F conversionVec3f3{vector2d};
  Vector3F conversionVec3f4{vector1i};
  Vector3F conversionVec3f5{vector1u};
  Vector3F conversionVec3f6{vector1d};
  Vector3F conversionVec3f7{vector4i};
  Vector3F conversionVec3f8{vector4u};
  Vector3F conversionVec3f9{vector4d};
  Vector3F conversionVec3f10{vector2i, 3.0f};
  Vector3F conversionVec3f11{vector1u, 2.0f, 3.0f};

  EXPECT_EQ(conversionVec3f, (Vector3F{1.0f, 2.0f, 0.0f}));
  EXPECT_EQ(conversionVec3f2, (Vector3F{1.0f, 2.0f, 0.0f}));
  EXPECT_EQ(conversionVec3f3, (Vector3F{1.0f, 2.0f, 0.0f}));
  EXPECT_EQ(conversionVec3f4, (Vector3F{1.0f, 0.0f, 0.0f}));
  EXPECT_EQ(conversionVec3f5, (Vector3F{1.0f, 0.0f, 0.0f}));
  EXPECT_EQ(conversionVec3f6, (Vector3F{1.0f, 0.0f, 0.0f}));
  EXPECT_EQ(conversionVec3f7, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(conversionVec3f8, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(conversionVec3f9, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(conversionVec3f10, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(conversionVec3f11, (Vector3F{1.0f, 2.0f, 3.0f}));

  Vector3D conversionVec3d{vector2i};
  Vector3D conversionVec3d2{vector2u};
  Vector3D conversionVec3d3{vector2f};
  Vector3D conversionVec3d4{vector1i};
  Vector3D conversionVec3d5{vector1u};
  Vector3D conversionVec3d6{vector1f};
  Vector3D conversionVec3d7{vector4i};
  Vector3D conversionVec3d8{vector4u};
  Vector3D conversionVec3d9{vector4f};
  Vector3D conversionVec3d10{vector2i, 3.0f};
  Vector3D conversionVec3d11{vector1u, 2, 3U};

  EXPECT_EQ(conversionVec3d, (Vector3D{1.0, 2.0, 0.0}));
  EXPECT_EQ(conversionVec3d2, (Vector3D{1.0, 2.0, 0.0}));
  EXPECT_EQ(conversionVec3d3, (Vector3D{1.0, 2.0, 0.0}));
  EXPECT_EQ(conversionVec3d4, (Vector3D{1.0, 0.0, 0.0}));
  EXPECT_EQ(conversionVec3d5, (Vector3D{1.0, 0.0, 0.0}));
  EXPECT_EQ(conversionVec3d6, (Vector3D{1.0, 0.0, 0.0}));
  EXPECT_EQ(conversionVec3d7, (Vector3D{1.0, 2.0, 3.0}));
  EXPECT_EQ(conversionVec3d8, (Vector3D{1.0, 2.0, 3.0}));
  EXPECT_EQ(conversionVec3d9, (Vector3D{1.0, 2.0, 3.0}));
  EXPECT_EQ(conversionVec3d10, (Vector3D{1.0, 2.0, 3.0}));
  EXPECT_EQ(conversionVec3d11, (Vector3D{1.0, 2.0, 3.0}));

  Vector3U conversionVec3u{vector2i};
  Vector3U conversionVec3u2{vector2f};
  Vector3U conversionVec3u3{vector2d};
  Vector3U conversionVec3u4{vector1i};
  Vector3U conversionVec3u5{vector1f};
  Vector3U conversionVec3u6{vector1d};
  Vector3U conversionVec3u7{vector4i};
  Vector3U conversionVec3u8{vector4f};
  Vector3U conversionVec3u9{vector4d};
  Vector3U conversionVec3u10{vector2i, 3.0};
  Vector3U conversionVec3u11{vector1f, 2.0f, 3.0};

  EXPECT_EQ(conversionVec3u, (Vector3U{1U, 2U, 0U}));
  EXPECT_EQ(conversionVec3u2, (Vector3U{1U, 2U, 0U}));
  EXPECT_EQ(conversionVec3u3, (Vector3U{1U, 2U, 0U}));
  EXPECT_EQ(conversionVec3u4, (Vector3U{1U, 0U, 0U}));
  EXPECT_EQ(conversionVec3u5, (Vector3U{1U, 0U, 0U}));
  EXPECT_EQ(conversionVec3u6, (Vector3U{1U, 0U, 0U}));
  EXPECT_EQ(conversionVec3u7, (Vector3U{1U, 2U, 3U}));
  EXPECT_EQ(conversionVec3u8, (Vector3U{1U, 2U, 3U}));
  EXPECT_EQ(conversionVec3u9, (Vector3U{1U, 2U, 3U}));
  EXPECT_EQ(conversionVec3u10, (Vector3U{1U, 2U, 3U}));
  EXPECT_EQ(conversionVec3u11, (Vector3U{1U, 2U, 3U}));

  Vector3I conversionVec3i{vector2f};
  Vector3I conversionVec3i2{vector2u};
  Vector3I conversionVec3i3{vector2d};
  Vector3I conversionVec3i4{vector1f};
  Vector3I conversionVec3i5{vector1u};
  Vector3I conversionVec3i6{vector1d};
  Vector3I conversionVec3i7{vector4f};
  Vector3I conversionVec3i8{vector4u};
  Vector3I conversionVec3i9{vector4d};
  Vector3I conversionVec3i10{vector2f, 3.0f};
  Vector3I conversionVec3i11{vector1u, 2, 3.0};

  EXPECT_EQ(conversionVec3i, (Vector3I{1, 2, 0}));
  EXPECT_EQ(conversionVec3i2, (Vector3I{1, 2, 0}));
  EXPECT_EQ(conversionVec3i3, (Vector3I{1, 2, 0}));
  EXPECT_EQ(conversionVec3i4, (Vector3I{1, 0, 0}));
  EXPECT_EQ(conversionVec3i5, (Vector3I{1, 0, 0}));
  EXPECT_EQ(conversionVec3i6, (Vector3I{1, 0, 0}));
  EXPECT_EQ(conversionVec3i7, (Vector3I{1, 2, 3}));
  EXPECT_EQ(conversionVec3i8, (Vector3I{1, 2, 3}));
  EXPECT_EQ(conversionVec3i9, (Vector3I{1, 2, 3}));
  EXPECT_EQ(conversionVec3i10, (Vector3I{1, 2, 3}));
  EXPECT_EQ(conversionVec3i11, (Vector3I{1, 2, 3}));

  Vector2F conversionVec2f{vector1i};
  Vector2F conversionVec2f2{vector1u};
  Vector2F conversionVec2f3{vector1d};
  Vector2F conversionVec2f4{vector4i};
  Vector2F conversionVec2f5{vector4u};
  Vector2F conversionVec2f6{vector4d};
  Vector2F conversionVec2f7{vector3i};
  Vector2F conversionVec2f8{vector3u};
  Vector2F conversionVec2f9{vector3d};
  Vector2F conversionVec2f10{vector1i, 2.0f};

  EXPECT_EQ(conversionVec2f, (Vector2F{1.0f, 0.0f}));
  EXPECT_EQ(conversionVec2f2, (Vector2F{1.0f, 0.0f}));
  EXPECT_EQ(conversionVec2f3, (Vector2F{1.0f, 0.0f}));
  EXPECT_EQ(conversionVec2f4, (Vector2F{1.0f, 2.0f}));
  EXPECT_EQ(conversionVec2f5, (Vector2F{1.0f, 2.0f}));
  EXPECT_EQ(conversionVec2f6, (Vector2F{1.0f, 2.0f}));
  EXPECT_EQ(conversionVec2f7, (Vector2F{1.0f, 2.0f}));
  EXPECT_EQ(conversionVec2f8, (Vector2F{1.0f, 2.0f}));
  EXPECT_EQ(conversionVec2f9, (Vector2F{1.0f, 2.0f}));
  EXPECT_EQ(conversionVec2f10, (Vector2F{1.0f, 2.0f}));

  Vector2I conversionVec2i{vector1f};
  Vector2I conversionVec2i2{vector1u};
  Vector2I conversionVec2i3{vector1d};
  Vector2I conversionVec2i4{vector4f};
  Vector2I conversionVec2i5{vector4u};
  Vector2I conversionVec2i6{vector4d};
  Vector2I conversionVec2i7{vector3f};
  Vector2I conversionVec2i8{vector3u};
  Vector2I conversionVec2i9{vector3d};
  Vector2I conversionVec2i10{vector1f, 2};

  EXPECT_EQ(conversionVec2i, (Vector2I{1, 0}));
  EXPECT_EQ(conversionVec2i2, (Vector2I{1, 0}));
  EXPECT_EQ(conversionVec2i3, (Vector2I{1, 0}));
  EXPECT_EQ(conversionVec2i4, (Vector2I{1, 2}));
  EXPECT_EQ(conversionVec2i5, (Vector2I{1, 2}));
  EXPECT_EQ(conversionVec2i6, (Vector2I{1, 2}));
  EXPECT_EQ(conversionVec2i7, (Vector2I{1, 2}));
  EXPECT_EQ(conversionVec2i8, (Vector2I{1, 2}));
  EXPECT_EQ(conversionVec2i9, (Vector2I{1, 2}));
  EXPECT_EQ(conversionVec2i10, (Vector2I{1, 2}));

  Vector2D conversionVec2d{vector1f};
  Vector2D conversionVec2d2{vector1i};
  Vector2D conversionVec2d3{vector1u};
  Vector2D conversionVec2d4{vector4f};
  Vector2D conversionVec2d5{vector4i};
  Vector2D conversionVec2d6{vector4u};
  Vector2D conversionVec2d7{vector3f};
  Vector2D conversionVec2d8{vector3i};
  Vector2D conversionVec2d9{vector3u};
  Vector2D conversionVec2d10{vector1f, 2.0};

  EXPECT_EQ(conversionVec2d, (Vector2D{1.0, 0.0}));
  EXPECT_EQ(conversionVec2d2, (Vector2D{1.0, 0.0}));
  EXPECT_EQ(conversionVec2d3, (Vector2D{1.0, 0.0}));
  EXPECT_EQ(conversionVec2d4, (Vector2D{1.0, 2.0}));
  EXPECT_EQ(conversionVec2d5, (Vector2D{1.0, 2.0}));
  EXPECT_EQ(conversionVec2d6, (Vector2D{1.0, 2.0}));
  EXPECT_EQ(conversionVec2d7, (Vector2D{1.0, 2.0}));
  EXPECT_EQ(conversionVec2d8, (Vector2D{1.0, 2.0}));
  EXPECT_EQ(conversionVec2d9, (Vector2D{1.0, 2.0}));
  EXPECT_EQ(conversionVec2d10, (Vector2D{1.0, 2.0}));

  Vector2U conversionVec2u{vector1f};
  Vector2U conversionVec2u2{vector1i};
  Vector2U conversionVec2u3{vector1d};
  Vector2U conversionVec2u4{vector4f};
  Vector2U conversionVec2u5{vector4i};
  Vector2U conversionVec2u6{vector4d};
  Vector2U conversionVec2u7{vector3f};
  Vector2U conversionVec2u8{vector3i};
  Vector2U conversionVec2u9{vector3d};
  Vector2U conversionVec2u10{vector1f, 2.0f};

  EXPECT_EQ(conversionVec2u, (Vector2U{1U, 0U}));
  EXPECT_EQ(conversionVec2u2, (Vector2U{1U, 0U}));
  EXPECT_EQ(conversionVec2u3, (Vector2U{1U, 0U}));
  EXPECT_EQ(conversionVec2u4, (Vector2U{1U, 2U}));
  EXPECT_EQ(conversionVec2u5, (Vector2U{1U, 2U}));
  EXPECT_EQ(conversionVec2u6, (Vector2U{1U, 2U}));
  EXPECT_EQ(conversionVec2u7, (Vector2U{1U, 2U}));
  EXPECT_EQ(conversionVec2u8, (Vector2U{1U, 2U}));
  EXPECT_EQ(conversionVec2u9, (Vector2U{1U, 2U}));
  EXPECT_EQ(conversionVec2u10, (Vector2U{1U, 2U}));

  Vector1F conversionVec1f{vector4i};
  Vector1F conversionVec1f2{vector4u};
  Vector1F conversionVec1f3{vector4d};
  Vector1F conversionVec1f4{vector3i};
  Vector1F conversionVec1f5{vector3u};
  Vector1F conversionVec1f6{vector3d};
  Vector1F conversionVec1f7{vector2i};
  Vector1F conversionVec1f8{vector2u};
  Vector1F conversionVec1f9{vector2d};

  EXPECT_EQ(conversionVec1f, (Vector1F{1.0f}));
  EXPECT_EQ(conversionVec1f2, (Vector1F{1.0f}));
  EXPECT_EQ(conversionVec1f3, (Vector1F{1.0f}));
  EXPECT_EQ(conversionVec1f4, (Vector1F{1.0f}));
  EXPECT_EQ(conversionVec1f5, (Vector1F{1.0f}));
  EXPECT_EQ(conversionVec1f6, (Vector1F{1.0f}));
  EXPECT_EQ(conversionVec1f7, (Vector1F{1.0f}));
  EXPECT_EQ(conversionVec1f8, (Vector1F{1.0f}));
  EXPECT_EQ(conversionVec1f9, (Vector1F{1.0f}));

  Vector1I conversionVec1i{vector4f};
  Vector1I conversionVec1i2{vector4u};
  Vector1I conversionVec1i3{vector4d};
  Vector1I conversionVec1i4{vector3f};
  Vector1I conversionVec1i5{vector3u};
  Vector1I conversionVec1i6{vector3d};
  Vector1I conversionVec1i7{vector2f};
  Vector1I conversionVec1i8{vector2u};
  Vector1I conversionVec1i9{vector2d};

  EXPECT_EQ(conversionVec1i, (Vector1I{1}));
  EXPECT_EQ(conversionVec1i2, (Vector1I{1}));
  EXPECT_EQ(conversionVec1i3, (Vector1I{1}));
  EXPECT_EQ(conversionVec1i4, (Vector1I{1}));
  EXPECT_EQ(conversionVec1i5, (Vector1I{1}));
  EXPECT_EQ(conversionVec1i6, (Vector1I{1}));
  EXPECT_EQ(conversionVec1i7, (Vector1I{1}));
  EXPECT_EQ(conversionVec1i8, (Vector1I{1}));
  EXPECT_EQ(conversionVec1i9, (Vector1I{1}));

  Vector1D conversionVec1d{vector4f};
  Vector1D conversionVec1d2{vector4i};
  Vector1D conversionVec1d3{vector4u};
  Vector1D conversionVec1d4{vector3f};
  Vector1D conversionVec1d5{vector3i};
  Vector1D conversionVec1d6{vector3u};
  Vector1D conversionVec1d7{vector2f};
  Vector1D conversionVec1d8{vector2i};
  Vector1D conversionVec1d9{vector2u};

  EXPECT_EQ(conversionVec1d, (Vector1D{1.0}));
  EXPECT_EQ(conversionVec1d2, (Vector1D{1.0}));
  EXPECT_EQ(conversionVec1d3, (Vector1D{1.0}));
  EXPECT_EQ(conversionVec1d4, (Vector1D{1.0}));
  EXPECT_EQ(conversionVec1d5, (Vector1D{1.0}));
  EXPECT_EQ(conversionVec1d6, (Vector1D{1.0}));
  EXPECT_EQ(conversionVec1d7, (Vector1D{1.0}));
  EXPECT_EQ(conversionVec1d8, (Vector1D{1.0}));
  EXPECT_EQ(conversionVec1d9, (Vector1D{1.0}));

  Vector1U conversionVec1u{vector4f};
  Vector1U conversionVec1u2{vector4i};
  Vector1U conversionVec1u3{vector4d};
  Vector1U conversionVec1u4{vector3f};
  Vector1U conversionVec1u5{vector3i};
  Vector1U conversionVec1u6{vector3d};
  Vector1U conversionVec1u7{vector2f};
  Vector1U conversionVec1u8{vector2i};
  Vector1U conversionVec1u9{vector2d};

  EXPECT_EQ(conversionVec1u, (Vector1U{1U}));
  EXPECT_EQ(conversionVec1u2, (Vector1U{1U}));
  EXPECT_EQ(conversionVec1u3, (Vector1U{1U}));
  EXPECT_EQ(conversionVec1u4, (Vector1U{1U}));
  EXPECT_EQ(conversionVec1u5, (Vector1U{1U}));
  EXPECT_EQ(conversionVec1u6, (Vector1U{1U}));
  EXPECT_EQ(conversionVec1u7, (Vector1U{1U}));
  EXPECT_EQ(conversionVec1u8, (Vector1U{1U}));
  EXPECT_EQ(conversionVec1u9, (Vector1U{1U}));
}

TEST_F(VectorTest, MultipleScalarsConversionConstructor) {
  Vector4F conversionVec4f{1, 2.0, 3U, 4L};
  Vector3F conversionVec3f{1, 2.0, 3U};
  Vector2F conversionVec2f{1, 2.0};
  Vector1F conversionVec1f{1};
  Vector4I conversionVec4i{1.5f, 2.5, 4L, 5U};
  Vector3I conversionVec3i{1.5f, 2.5, 4L};
  Vector2I conversionVec2i{1.5f, 2.5};
  Vector1I conversionVec1i{1.5f};
  Vector4D conversionVec4d{1, 2.0f, 3U, 4L};
  Vector3D conversionVec3d{1, 2.0f, 3U};
  Vector2D conversionVec2d{1, 2.0};
  Vector1D conversionVec1d{1};
  Vector4U conversionVec4u{1, 2.0f, 3U, 4L};
  Vector3U conversionVec3u{1, 2.0f, 3U};
  Vector2U conversionVec2u{1, 2.0};
  Vector1U conversionVec1u{1};
  Vector4B conversionVec4b{1, 0, 1, 0};
  Vector3B conversionVec3b{1, 0, 1};
  Vector2B conversionVec2b{1, 0};
  Vector1B conversionVec1b{1};

  EXPECT_EQ(conversionVec4f, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(conversionVec3f, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(conversionVec2f, (Vector2F{1.0f, 2.0f}));
  EXPECT_EQ(conversionVec1f, (Vector1F{1.0f}));
  EXPECT_EQ(conversionVec4i, (Vector4I{1, 2, 4, 5}));
  EXPECT_EQ(conversionVec3i, (Vector3I{1, 2, 4}));
  EXPECT_EQ(conversionVec2i, (Vector2I{1, 2}));
  EXPECT_EQ(conversionVec1i, (Vector1I{1}));
  EXPECT_EQ(conversionVec4d, (Vector4D{1.0, 2.0, 3.0, 4.0}));
  EXPECT_EQ(conversionVec3d, (Vector3D{1.0, 2.0, 3.0}));
  EXPECT_EQ(conversionVec2d, (Vector2D{1.0, 2.0}));
  EXPECT_EQ(conversionVec1d, (Vector1D{1.0}));
  EXPECT_EQ(conversionVec4u, (Vector4U{1U, 2U, 3U, 4U}));
  EXPECT_EQ(conversionVec3u, (Vector3U{1U, 2U, 3U}));
  EXPECT_EQ(conversionVec2u, (Vector2U{1U, 2U}));
  EXPECT_EQ(conversionVec1u, (Vector1U{1U}));
  EXPECT_EQ(conversionVec4b, (Vector4B{true, false, true, false}));
  EXPECT_EQ(conversionVec3b, (Vector3B{true, false, true}));
  EXPECT_EQ(conversionVec2b, (Vector2B{true, false}));
  EXPECT_EQ(conversionVec1b, (Vector1B{true}));
}

TEST_F(VectorTest, STDArrayConstructor) {
  Vector4F vector4f2{std::array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f}};
  Vector3F vector3f2{std::array<float, 3>{1.0f, 2.0f, 3.0f}};
  Vector3F vector3f3{std::array<float, 3>{1.0f, 2.0f, 3.0f}};
  Vector3F vector3f4{std::array<float, 3>{1.0f, 2.0f, 3.0f}};
  Vector3F vector3f5{std::array<float, 3>{1.0f, 2.0f, 3.0f}};
  Vector4I vector4i2{std::array<int, 4>{10, 20, 30, 40}};
  Vector3I vector3i2{std::array<int, 3>{10, 20, 30}};
  Vector3I vector3i3{std::array<int, 3>{10, 20, 30}};
  Vector3I vector3i4{std::array<int, 3>{10, 20, 30}};
  Vector3I vector3i5{std::array<int, 3>{10, 20, 30}};

  EXPECT_EQ(vector4f2, (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(vector3f2, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(vector3f3, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(vector3f4, (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(vector3f5, (Vector3F{1.0f, 2.0f, 3.0f}));

  EXPECT_EQ(vector4i2, (Vector4I{10, 20, 30, 40}));
  EXPECT_EQ(vector3i2, (Vector3I{10, 20, 30}));
  EXPECT_EQ(vector3i3, (Vector3I{10, 20, 30}));
  EXPECT_EQ(vector3i4, (Vector3I{10, 20, 30}));
  EXPECT_EQ(vector3i5, (Vector3I{10, 20, 30}));
}

TEST_F(VectorTest, AssignmentOperator) {
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

TEST_F(VectorTest, PlusEqualOperator) {
  vector4f = Vector4F{1.5f, 2.5f, 3.5f, 4.5f};
  vector3f = Vector3F{1.5f, 2.5f, 3.5f};
  vector2f = Vector2F{1.5f, 2.5f};
  vector1f = Vector1F{1.5f};
  vector4i = Vector4I{10, 20, 30, 40};
  vector3i = Vector3I{10, 20, 30};
  vector2i = Vector2I{10, 20};
  vector1i = Vector1I{10};

  vector4f += Vector4F{1.5f, 2.5f, 3.5f, 4.5f};
  vector3f += Vector3F{1.5f, 2.5f, 3.5f};
  vector2f += Vector2F{1.5f, 2.5f};
  vector1f += Vector1F{1.5f};
  vector4i += Vector4I{10, 20, 30, 40};
  vector3i += Vector3I{10, 20, 30};
  vector2i += Vector2I{10, 20};
  vector1i += Vector1I{10};

  EXPECT_EQ(vector4f.x(), 3.0f);
  EXPECT_EQ(vector4f.y(), 5.0f);
  EXPECT_EQ(vector4f.z(), 7.0f);
  EXPECT_EQ(vector4f.w(), 9.0f);
  EXPECT_EQ(vector3f.x(), 3.0f);
  EXPECT_EQ(vector3f.y(), 5.0f);
  EXPECT_EQ(vector3f.z(), 7.0f);
  EXPECT_EQ(vector2f.x(), 3.0f);
  EXPECT_EQ(vector2f.y(), 5.0f);
  EXPECT_EQ(vector1f.x(), 3.0f);

  EXPECT_EQ(vector4i.x(), 20);
  EXPECT_EQ(vector4i.y(), 40);
  EXPECT_EQ(vector4i.z(), 60);
  EXPECT_EQ(vector4i.w(), 80);
  EXPECT_EQ(vector3i.x(), 20);
  EXPECT_EQ(vector3i.y(), 40);
  EXPECT_EQ(vector3i.z(), 60);
  EXPECT_EQ(vector2i.x(), 20);
  EXPECT_EQ(vector2i.y(), 40);
  EXPECT_EQ(vector1i.x(), 20);
}

TEST_F(VectorTest, MinusEqualOperator) {
  vector4f = Vector4F{1.5f, 2.5f, 3.5f, 4.5f};
  vector3f = Vector3F{1.5f, 2.5f, 3.5f};
  vector2f = Vector2F{1.5f, 2.5f};
  vector1f = Vector1F{1.5f};
  vector4i = Vector4I{10, 20, 30, 40};
  vector3i = Vector3I{10, 20, 30};
  vector2i = Vector2I{10, 20};
  vector1i = Vector1I{10};

  vector4f -= Vector4F{1.5f, 2.5f, 3.5f, 4.5f};
  vector3f -= Vector3F{1.5f, 2.5f, 3.5f};
  vector2f -= Vector2F{1.5f, 2.5f};
  vector1f -= Vector1F{1.5f};
  vector4i -= Vector4I{10, 20, 30, 40};
  vector3i -= Vector3I{10, 20, 30};
  vector2i -= Vector2I{10, 20};
  vector1i -= Vector1I{10};

  EXPECT_EQ(vector4f.x(), 0.0f);
  EXPECT_EQ(vector4f.y(), 0.0f);
  EXPECT_EQ(vector4f.z(), 0.0f);
  EXPECT_EQ(vector4f.w(), 0.0f);
  EXPECT_EQ(vector3f.x(), 0.0f);
  EXPECT_EQ(vector3f.y(), 0.0f);
  EXPECT_EQ(vector3f.z(), 0.0f);
  EXPECT_EQ(vector2f.x(), 0.0f);
  EXPECT_EQ(vector2f.y(), 0.0f);
  EXPECT_EQ(vector1f.x(), 0.0f);

  EXPECT_EQ(vector4i.x(), 0);
  EXPECT_EQ(vector4i.y(), 0);
  EXPECT_EQ(vector4i.z(), 0);
  EXPECT_EQ(vector4i.w(), 0);
  EXPECT_EQ(vector3i.x(), 0);
  EXPECT_EQ(vector3i.y(), 0);
  EXPECT_EQ(vector3i.z(), 0);
  EXPECT_EQ(vector2i.x(), 0);
  EXPECT_EQ(vector2i.y(), 0);
  EXPECT_EQ(vector1i.x(), 0);
}

TEST_F(VectorTest, MultiplyEqualOperator) {
  vector4f = Vector4F{1.5f, 2.5f, 3.5f, 4.5f};
  vector3f = Vector3F{1.5f, 2.5f, 3.5f};
  vector2f = Vector2F{1.5f, 2.5f};
  vector1f = Vector1F{1.5f};
  vector4i = Vector4I{10, 20, 30, 40};
  vector3i = Vector3I{10, 20, 30};
  vector2i = Vector2I{10, 20};
  vector1i = Vector1I{10};

  vector4f *= Vector4F{10.0f, 10.0f, 10.0f, 10.0f};
  vector3f *= Vector3F{10.0f, 10.0f, 10.0f};
  vector2f *= Vector2F{10.0f, 10.0f};
  vector1f *= Vector1F{10.0f};
  vector4i *= Vector4I{10, 10, 10, 10};
  vector3i *= Vector3I{10, 10, 10};
  vector2i *= Vector2I{10, 10};
  vector1i *= Vector1I{10};

  EXPECT_EQ(vector4f.x(), 15.0f);
  EXPECT_EQ(vector4f.y(), 25.0f);
  EXPECT_EQ(vector4f.z(), 35.0f);
  EXPECT_EQ(vector4f.w(), 45.0f);
  EXPECT_EQ(vector3f.x(), 15.0f);
  EXPECT_EQ(vector3f.y(), 25.0f);
  EXPECT_EQ(vector3f.z(), 35.0f);
  EXPECT_EQ(vector2f.x(), 15.0f);
  EXPECT_EQ(vector2f.y(), 25.0f);
  EXPECT_EQ(vector1f.x(), 15.0f);

  EXPECT_EQ(vector4i.x(), 100);
  EXPECT_EQ(vector4i.y(), 200);
  EXPECT_EQ(vector4i.z(), 300);
  EXPECT_EQ(vector4i.w(), 400);
  EXPECT_EQ(vector3i.x(), 100);
  EXPECT_EQ(vector3i.y(), 200);
  EXPECT_EQ(vector3i.z(), 300);
  EXPECT_EQ(vector2i.x(), 100);
  EXPECT_EQ(vector2i.y(), 200);
  EXPECT_EQ(vector1i.x(), 100);

  vector4f *= 10.0f;
  vector3f *= 10.0f;
  vector2f *= 10.0f;
  vector1f *= 10.0f;
  vector4i *= 10;
  vector3i *= 10;
  vector2i *= 10;
  vector1i *= 10;

  EXPECT_EQ(vector4f.x(), 150.0f);
  EXPECT_EQ(vector4f.y(), 250.0f);
  EXPECT_EQ(vector4f.z(), 350.0f);
  EXPECT_EQ(vector4f.w(), 450.0f);
  EXPECT_EQ(vector3f.x(), 150.0f);
  EXPECT_EQ(vector3f.y(), 250.0f);
  EXPECT_EQ(vector3f.z(), 350.0f);
  EXPECT_EQ(vector2f.x(), 150.0f);
  EXPECT_EQ(vector2f.y(), 250.0f);
  EXPECT_EQ(vector1f.x(), 150.0f);

  EXPECT_EQ(vector4i.x(), 1000);
  EXPECT_EQ(vector4i.y(), 2000);
  EXPECT_EQ(vector4i.z(), 3000);
  EXPECT_EQ(vector4i.w(), 4000);
  EXPECT_EQ(vector3i.x(), 1000);
  EXPECT_EQ(vector3i.y(), 2000);
  EXPECT_EQ(vector3i.z(), 3000);
  EXPECT_EQ(vector2i.x(), 1000);
  EXPECT_EQ(vector2i.y(), 2000);
  EXPECT_EQ(vector1i.x(), 1000);
}

TEST_F(VectorTest, DivideEqualOperator) {
  vector4f = Vector4F{150.0f, 250.0f, 350.0f, 450.0f};
  vector3f = Vector3F{150.0f, 250.0f, 350.0f};
  vector2f = Vector2F{150.0f, 250.0f};
  vector1f = Vector1F{150.0f};
  vector4i = Vector4I{1000, 2000, 3000, 4000};
  vector3i = Vector3I{1000, 2000, 3000};
  vector2i = Vector2I{1000, 2000};
  vector1i = Vector1I{1000};

  vector4f /= 10.0f;
  vector3f /= 10.0f;
  vector2f /= 10.0f;
  vector1f /= 10.0f;
  vector4i /= 10;
  vector3i /= 10;
  vector2i /= 10;
  vector1i /= 10;

  EXPECT_EQ(vector4f.x(), 15.0f);
  EXPECT_EQ(vector4f.y(), 25.0f);
  EXPECT_EQ(vector4f.z(), 35.0f);
  EXPECT_EQ(vector4f.w(), 45.0f);
  EXPECT_EQ(vector3f.x(), 15.0f);
  EXPECT_EQ(vector3f.y(), 25.0f);
  EXPECT_EQ(vector3f.z(), 35.0f);
  EXPECT_EQ(vector2f.x(), 15.0f);
  EXPECT_EQ(vector2f.y(), 25.0f);
  EXPECT_EQ(vector1f.x(), 15.0f);

  EXPECT_EQ(vector4i.x(), 100);
  EXPECT_EQ(vector4i.y(), 200);
  EXPECT_EQ(vector4i.z(), 300);
  EXPECT_EQ(vector4i.w(), 400);
  EXPECT_EQ(vector3i.x(), 100);
  EXPECT_EQ(vector3i.y(), 200);
  EXPECT_EQ(vector3i.z(), 300);
  EXPECT_EQ(vector2i.x(), 100);
  EXPECT_EQ(vector2i.y(), 200);
  EXPECT_EQ(vector1i.x(), 100);
}

TEST_F(VectorTest, OperatorBool) {
  EXPECT_TRUE(vector4f);
  EXPECT_TRUE(vector3f);
  EXPECT_TRUE(vector2f);
  EXPECT_TRUE(vector1f);

  EXPECT_TRUE(vector4i);
  EXPECT_TRUE(vector3i);
  EXPECT_TRUE(vector2i);
  EXPECT_TRUE(vector1i);

  EXPECT_FALSE(vector4b);
  EXPECT_FALSE(vector3b);
  EXPECT_FALSE(vector2b);
  EXPECT_TRUE(vector1b);

  vector4f = Vector4F{0.0f, 0.0f, 0.0f, 0.0f};
  vector3f = Vector3F{0.0f, 0.0f, 0.0f};
  vector2f = Vector2F{0.0f, 0.0f};
  vector1f = Vector1F{0.0f};
  vector4i = Vector4I{0, 0, 0, 0};
  vector3i = Vector3I{0, 0, 0};
  vector2i = Vector2I{0, 0};
  vector1i = Vector1I{0};
  vector4b = Vector4B{false, false, false, false};
  vector3b = Vector3B{false, false, false};
  vector2b = Vector2B{false, false};
  vector1b = Vector1B{false};

  EXPECT_FALSE(vector4f);
  EXPECT_FALSE(vector3f);
  EXPECT_FALSE(vector2f);
  EXPECT_FALSE(vector1f);
  EXPECT_FALSE(vector4i);
  EXPECT_FALSE(vector3i);
  EXPECT_FALSE(vector2i);
  EXPECT_FALSE(vector1i);
  EXPECT_FALSE(vector4b);
  EXPECT_FALSE(vector3b);
  EXPECT_FALSE(vector2b);
  EXPECT_FALSE(vector1b);

  vector4f.x() = 1.0f;
  vector3f.x() = 1.0f;
  vector2f.x() = 1.0f;
  vector1f.x() = 1.0f;
  vector4i.x() = 1;
  vector3i.x() = 1;
  vector2i.x() = 1;
  vector1i.x() = 1;
  vector4b.i() = true;
  vector3b.i() = true;
  vector2b.i() = true;
  vector1b.i() = true;

  EXPECT_TRUE(vector4f);
  EXPECT_TRUE(vector3f);
  EXPECT_TRUE(vector2f);
  EXPECT_TRUE(vector1f);

  EXPECT_TRUE(vector4i);
  EXPECT_TRUE(vector3i);
  EXPECT_TRUE(vector2i);
  EXPECT_TRUE(vector1i);

  EXPECT_FALSE(vector4b);
  EXPECT_FALSE(vector3b);
  EXPECT_FALSE(vector2b);
  EXPECT_TRUE(vector1b);

  vector4b = Vector4B{true, true, true, true};
  vector3b = Vector3B{true, true, true};
  vector2b = Vector2B{true, true};
  vector1b = Vector1B{false};

  EXPECT_TRUE(vector4b);
  EXPECT_TRUE(vector3b);
  EXPECT_TRUE(vector2b);
  EXPECT_FALSE(vector1b);
}

TEST_F(VectorTest, EqualOperator) {
  EXPECT_TRUE((vector4f == Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_TRUE((vector3f == Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_TRUE((vector2f == Vector2F{1.0f, 2.0f}));
  EXPECT_TRUE((vector1f == Vector1F{1.0f}));

  EXPECT_TRUE((vector4i == Vector4I{1, 2, 3, 4}));
  EXPECT_TRUE((vector3i == Vector3I{1, 2, 3}));
  EXPECT_TRUE((vector2i == Vector2I{1, 2}));
  EXPECT_TRUE((vector1i == Vector1I{1}));

  EXPECT_TRUE((vector4b == Vector4B{true, false, true, false}));
  EXPECT_TRUE((vector3b == Vector3B{true, false, true}));
  EXPECT_TRUE((vector2b == Vector2B{true, false}));
  EXPECT_TRUE((vector1b == Vector1B{true}));

  EXPECT_TRUE((vector4c == Vector<4, char>{'a', 'b', 'c', 'd'}));
  EXPECT_TRUE((vector3c == Vector<3, char>{'a', 'b', 'c'}));
  EXPECT_TRUE((vector2c == Vector<2, char>{'a', 'b'}));
  EXPECT_TRUE((vector1c == Vector<1, char>{'a'}));

  EXPECT_TRUE((vector4s == Vector<4, short>{1, 2, 3, 4}));
  EXPECT_TRUE((vector3s == Vector<3, short>{1, 2, 3}));
  EXPECT_TRUE((vector2s == Vector<2, short>{1, 2}));
  EXPECT_TRUE((vector1s == Vector<1, short>{1}));

  EXPECT_TRUE((vector4us == Vector<4, unsigned short>{1U, 2U, 3U, 4U}));
  EXPECT_TRUE((vector3us == Vector<3, unsigned short>{1U, 2U, 3U}));
  EXPECT_TRUE((vector2us == Vector<2, unsigned short>{1U, 2U}));
  EXPECT_TRUE((vector1us == Vector<1, unsigned short>{1U}));

  // False cases
  EXPECT_FALSE((vector4f == Vector4F{1.5f, 2.0f, 3.0f, 4.0f}));
  EXPECT_FALSE((vector3f == Vector3F{1.0f, 2.5f, 3.0f}));
  EXPECT_FALSE((vector2f == Vector2F{1.0f, 2.5f}));
  EXPECT_FALSE((vector1f == Vector1F{1.5f}));

  EXPECT_FALSE((vector4i == Vector4I{1, 3, 3, 4}));
  EXPECT_FALSE((vector3i == Vector3I{1, 3, 3}));
  EXPECT_FALSE((vector2i == Vector2I{1, 3}));
  EXPECT_FALSE((vector1i == Vector1I{2}));

  EXPECT_FALSE((vector4b == Vector4B{false, false, true, false}));
  EXPECT_FALSE((vector3b == Vector3B{false, false, true}));
  EXPECT_FALSE((vector2b == Vector2B{false, false}));
  EXPECT_FALSE((vector1b == Vector1B{false}));

  EXPECT_FALSE((vector4c == Vector<4, char>{'b', 'b', 'c', 'd'}));
  EXPECT_FALSE((vector3c == Vector<3, char>{'b', 'b', 'c'}));
  EXPECT_FALSE((vector2c == Vector<2, char>{'b', 'b'}));
  EXPECT_FALSE((vector1c == Vector<1, char>{'b'}));

  EXPECT_FALSE((vector4s == Vector<4, short>{2, 2, 3, 4}));
  EXPECT_FALSE((vector3s == Vector<3, short>{2, 2, 3}));
  EXPECT_FALSE((vector2s == Vector<2, short>{2, 2}));
  EXPECT_FALSE((vector1s == Vector<1, short>{2}));

  EXPECT_FALSE((vector4us == Vector<4, unsigned short>{1U, 2U, 2U, 4U}));
  EXPECT_FALSE((vector3us == Vector<3, unsigned short>{1U, 2U, 2U}));
  EXPECT_FALSE((vector2us == Vector<2, unsigned short>{1U, 3U}));
  EXPECT_FALSE((vector1us == Vector<1, unsigned short>{2U}));
}

TEST_F(VectorTest, NotEqualOperator) {
  EXPECT_TRUE((vector4f != Vector4F{1.5f, 2.0f, 3.0f, 4.0f}));
  EXPECT_TRUE((vector3f != Vector3F{1.0f, 2.5f, 3.0f}));
  EXPECT_TRUE((vector2f != Vector2F{1.0f, 2.5f}));
  EXPECT_TRUE((vector1f != Vector1F{1.5f}));

  EXPECT_TRUE((vector4i != Vector4I{1, 3, 3, 4}));
  EXPECT_TRUE((vector3i != Vector3I{1, 3, 3}));
  EXPECT_TRUE((vector2i != Vector2I{1, 3}));
  EXPECT_TRUE((vector1i != Vector1I{2}));

  EXPECT_TRUE((vector4b != Vector4B{false, false, true, false}));
  EXPECT_TRUE((vector3b != Vector3B{false, false, true}));
  EXPECT_TRUE((vector2b != Vector2B{false, false}));
  EXPECT_TRUE((vector1b != Vector1B{false}));

  EXPECT_TRUE((vector4c != Vector<4, char>{'b', 'b', 'c', 'd'}));
  EXPECT_TRUE((vector3c != Vector<3, char>{'b', 'b', 'c'}));
  EXPECT_TRUE((vector2c != Vector<2, char>{'b', 'b'}));
  EXPECT_TRUE((vector1c != Vector<1, char>{'b'}));

  EXPECT_TRUE((vector4s != Vector<4, short>{2, 2, 3, 4}));
  EXPECT_TRUE((vector3s != Vector<3, short>{2, 2, 3}));
  EXPECT_TRUE((vector2s != Vector<2, short>{2, 2}));
  EXPECT_TRUE((vector1s != Vector<1, short>{2}));

  EXPECT_TRUE((vector4us != Vector<4, unsigned short>{1U, 2U, 2U, 4U}));
  EXPECT_TRUE((vector3us != Vector<3, unsigned short>{1U, 2U, 2U}));
  EXPECT_TRUE((vector2us != Vector<2, unsigned short>{1U, 3U}));
  EXPECT_TRUE((vector1us != Vector<1, unsigned short>{2U}));
}

TEST_F(VectorTest, ToTuple) {
  EXPECT_EQ(vector4f.toTuple(), (std::make_tuple(1.0f, 2.0f, 3.0f, 4.0f)));
  EXPECT_EQ(vector3f.toTuple(), (std::make_tuple(1.0f, 2.0f, 3.0f)));
  EXPECT_EQ(vector2f.toTuple(), (std::make_tuple(1.0f, 2.0f)));
  EXPECT_EQ(vector1f.toTuple(), (std::make_tuple(1.0f)));

  EXPECT_EQ(vector4i.toTuple(), (std::make_tuple(1, 2, 3, 4)));
  EXPECT_EQ(vector3i.toTuple(), (std::make_tuple(1, 2, 3)));
  EXPECT_EQ(vector2i.toTuple(), (std::make_tuple(1, 2)));
  EXPECT_EQ(vector1i.toTuple(), (std::make_tuple(1)));

  EXPECT_EQ(vector4b.toTuple(), (std::make_tuple(true, false, true, false)));
  EXPECT_EQ(vector3b.toTuple(), (std::make_tuple(true, false, true)));
  EXPECT_EQ(vector2b.toTuple(), (std::make_tuple(true, false)));
  EXPECT_EQ(vector1b.toTuple(), (std::make_tuple(true)));

  EXPECT_EQ(vector4c.toTuple(), (std::make_tuple('a', 'b', 'c', 'd')));
  EXPECT_EQ(vector3c.toTuple(), (std::make_tuple('a', 'b', 'c')));
  EXPECT_EQ(vector2c.toTuple(), (std::make_tuple('a', 'b')));
  EXPECT_EQ(vector1c.toTuple(), (std::make_tuple('a')));

  EXPECT_EQ(vector4s.toTuple(), (std::make_tuple(1, 2, 3, 4)));
  EXPECT_EQ(vector3s.toTuple(), (std::make_tuple(1, 2, 3)));
  EXPECT_EQ(vector2s.toTuple(), (std::make_tuple(1, 2)));
  EXPECT_EQ(vector1s.toTuple(), (std::make_tuple(1)));

  EXPECT_EQ(vector4us.toTuple(), (std::make_tuple(1U, 2U, 3U, 4U)));
  EXPECT_EQ(vector3us.toTuple(), (std::make_tuple(1U, 2U, 3U)));
  EXPECT_EQ(vector2us.toTuple(), (std::make_tuple(1U, 2U)));
  EXPECT_EQ(vector1us.toTuple(), (std::make_tuple(1U)));
}

TEST_F(VectorTest, Size) {
  EXPECT_EQ(vector4f.size(), 4);
  EXPECT_EQ(vector3f.size(), 3);
  EXPECT_EQ(vector2f.size(), 2);
  EXPECT_EQ(vector1f.size(), 1);

  EXPECT_EQ(vector4i.size(), 4);
  EXPECT_EQ(vector3i.size(), 3);
  EXPECT_EQ(vector2i.size(), 2);
  EXPECT_EQ(vector1i.size(), 1);

  EXPECT_EQ(vector4b.size(), 4);
  EXPECT_EQ(vector3b.size(), 3);
  EXPECT_EQ(vector2b.size(), 2);
  EXPECT_EQ(vector1b.size(), 1);

  EXPECT_EQ(vector4c.size(), 4);
  EXPECT_EQ(vector3c.size(), 3);
  EXPECT_EQ(vector2c.size(), 2);
  EXPECT_EQ(vector1c.size(), 1);

  EXPECT_EQ(vector4s.size(), 4);
  EXPECT_EQ(vector3s.size(), 3);
  EXPECT_EQ(vector2s.size(), 2);
  EXPECT_EQ(vector1s.size(), 1);

  EXPECT_EQ(vector4us.size(), 4);
  EXPECT_EQ(vector3us.size(), 3);
  EXPECT_EQ(vector2us.size(), 2);
  EXPECT_EQ(vector1us.size(), 1);
}

TEST_F(VectorTest, NonMemberPlusOperator) {
  Vector4F result4f = vector4f + Vector4F{1.0f, 1.0f, 1.0f, 1.0f};
  Vector3F result3f = vector3f + Vector3F{1.0f, 1.0f, 1.0f};
  Vector2F result2f = vector2f + Vector2F{1.0f, 1.0f};
  Vector1F result1f = vector1f + Vector1F{1.0f};

  Vector4I result4i = vector4i + Vector4I{1, 1, 1, 1};
  Vector3I result3i = vector3i + Vector3I{1, 1, 1};
  Vector2I result2i = vector2i + Vector2I{1, 1};
  Vector1I result1i = vector1i + Vector1I{1};

  EXPECT_EQ(result4f, (Vector4F{2.0f, 3.0f, 4.0f, 5.0f}));
  EXPECT_EQ(result3f, (Vector3F{2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(result2f, (Vector2F{2.0f, 3.0f}));
  EXPECT_EQ(result1f, (Vector1F{2.0f}));

  EXPECT_EQ(result4i, (Vector4I{2, 3, 4, 5}));
  EXPECT_EQ(result3i, (Vector3I{2, 3, 4}));
  EXPECT_EQ(result2i, (Vector2I{2, 3}));
  EXPECT_EQ(result1i, (Vector1I{2}));
}

TEST_F(VectorTest, NonMemberMinusOperator) {
  Vector4F result4f = vector4f - Vector4F{1.0f, 1.0f, 1.0f, 1.0f};
  Vector3F result3f = vector3f - Vector3F{1.0f, 1.0f, 1.0f};
  Vector2F result2f = vector2f - Vector2F{1.0f, 1.0f};
  Vector1F result1f = vector1f - Vector1F{1.0f};

  Vector4I result4i = vector4i - Vector4I{1, 1, 1, 1};
  Vector3I result3i = vector3i - Vector3I{1, 1, 1};
  Vector2I result2i = vector2i - Vector2I{1, 1};
  Vector1I result1i = vector1i - Vector1I{1};

  EXPECT_EQ(result4f, (Vector4F{0.0f, 1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(result3f, (Vector3F{0.0f, 1.0f, 2.0f}));
  EXPECT_EQ(result2f, (Vector2F{0.0f, 1.0f}));
  EXPECT_EQ(result1f, (Vector1F{0.0f}));

  EXPECT_EQ(result4i, (Vector4I{0, 1, 2, 3}));
  EXPECT_EQ(result3i, (Vector3I{0, 1, 2}));
  EXPECT_EQ(result2i, (Vector2I{0, 1}));
  EXPECT_EQ(result1i, (Vector1I{0}));
}

TEST_F(VectorTest, NonMemberMinusSingleOperator) {
  Vector4F result4f = -vector4f;
  Vector3F result3f = -vector3f;
  Vector2F result2f = -vector2f;
  Vector1F result1f = -vector1f;

  Vector4I result4i = -vector4i;
  Vector3I result3i = -vector3i;
  Vector2I result2i = -vector2i;
  Vector1I result1i = -vector1i;

  EXPECT_EQ(result4f, (Vector4F{-1.0f, -2.0f, -3.0f, -4.0f}));
  EXPECT_EQ(result3f, (Vector3F{-1.0f, -2.0f, -3.0f}));
  EXPECT_EQ(result2f, (Vector2F{-1.0f, -2.0f}));
  EXPECT_EQ(result1f, (Vector1F{-1.0f}));

  EXPECT_EQ(result4i, (Vector4I{-1, -2, -3, -4}));
  EXPECT_EQ(result3i, (Vector3I{-1, -2, -3}));
  EXPECT_EQ(result2i, (Vector2I{-1, -2}));
  EXPECT_EQ(result1i, (Vector1I{-1}));
}

TEST_F(VectorTest, NonMemberMultiplyOperator) {
  Vector4F result4f = vector4f * Vector4F{2.0f, 2.0f, 2.0f, 2.0f};
  Vector3F result3f = vector3f * Vector3F{2.0f, 2.0f, 2.0f};
  Vector2F result2f = vector2f * Vector2F{2.0f, 2.0f};
  Vector1F result1f = vector1f * Vector1F{2.0f};

  Vector4I result4i = vector4i * Vector4I{2, 2, 2, 2};
  Vector3I result3i = vector3i * Vector3I{2, 2, 2};
  Vector2I result2i = vector2i * Vector2I{2, 2};
  Vector1I result1i = vector1i * Vector1I{2};

  EXPECT_EQ(result4f, (Vector4F{2.0f, 4.0f, 6.0f, 8.0f}));
  EXPECT_EQ(result3f, (Vector3F{2.0f, 4.0f, 6.0f}));
  EXPECT_EQ(result2f, (Vector2F{2.0f, 4.0f}));
  EXPECT_EQ(result1f, (Vector1F{2.0f}));

  EXPECT_EQ(result4i, (Vector4I{2, 4, 6, 8}));
  EXPECT_EQ(result3i, (Vector3I{2, 4, 6}));
  EXPECT_EQ(result2i, (Vector2I{2, 4}));
  EXPECT_EQ(result1i, (Vector1I{2}));
}

TEST_F(VectorTest, NonMemberMultiplyVector1Operator) {
  Vector4F result4f = vector4f * Vector1F{2.0f};
  Vector3F result3f = vector3f * Vector1F{2.0f};
  Vector2F result2f = vector2f * Vector1F{2.0f};
  Vector1F result1f = vector1f * Vector1F{2.0f};
  Vector4I result4i = vector4i * Vector1I{2};
  Vector3I result3i = vector3i * Vector1I{2};
  Vector2I result2i = vector2i * Vector1I{2};
  Vector1I result1i = vector1i * Vector1I{2};

  EXPECT_EQ(result4f, (Vector4F{2.0f, 4.0f, 6.0f, 8.0f}));
  EXPECT_EQ(result3f, (Vector3F{2.0f, 4.0f, 6.0f}));
  EXPECT_EQ(result2f, (Vector2F{2.0f, 4.0f}));
  EXPECT_EQ(result1f, (Vector1F{2.0f}));

  EXPECT_EQ(result4i, (Vector4I{2, 4, 6, 8}));
  EXPECT_EQ(result3i, (Vector3I{2, 4, 6}));
  EXPECT_EQ(result2i, (Vector2I{2, 4}));
  EXPECT_EQ(result1i, (Vector1I{2}));
}

TEST_F(VectorTest, NonMemberMultiplyVector1Operator2) {
  Vector4F result4f = Vector1F{2.0f} * vector4f;
  Vector3F result3f = Vector1F{2.0f} * vector3f;
  Vector2F result2f = Vector1F{2.0f} * vector2f;
  Vector1F result1f = Vector1F{2.0f} * vector1f;

  Vector4I result4i = Vector1I{2} * vector4i;
  Vector3I result3i = Vector1I{2} * vector3i;
  Vector2I result2i = Vector1I{2} * vector2i;
  Vector1I result1i = Vector1I{2} * vector1i;

  EXPECT_EQ(result4f, (Vector4F{2.0f, 4.0f, 6.0f, 8.0f}));
  EXPECT_EQ(result3f, (Vector3F{2.0f, 4.0f, 6.0f}));
  EXPECT_EQ(result2f, (Vector2F{2.0f, 4.0f}));
  EXPECT_EQ(result1f, (Vector1F{2.0f}));

  EXPECT_EQ(result4i, (Vector4I{2, 4, 6, 8}));
  EXPECT_EQ(result3i, (Vector3I{2, 4, 6}));
  EXPECT_EQ(result2i, (Vector2I{2, 4}));
  EXPECT_EQ(result1i, (Vector1I{2}));
}

TEST_F(VectorTest, NonMemberMultiplyScalarOperator) {
  Vector4F result4f = vector4f * 2.0f;
  Vector3F result3f = vector3f * 2.0f;
  Vector2F result2f = vector2f * 2.0f;
  Vector1F result1f = vector1f * 2.0f;

  Vector4I result4i = vector4i * 2;
  Vector3I result3i = vector3i * 2;
  Vector2I result2i = vector2i * 2;
  Vector1I result1i = vector1i * 2;

  EXPECT_EQ(result4f, (Vector4F{2.0f, 4.0f, 6.0f, 8.0f}));
  EXPECT_EQ(result3f, (Vector3F{2.0f, 4.0f, 6.0f}));
  EXPECT_EQ(result2f, (Vector2F{2.0f, 4.0f}));
  EXPECT_EQ(result1f, (Vector1F{2.0f}));

  EXPECT_EQ(result4i, (Vector4I{2, 4, 6, 8}));
  EXPECT_EQ(result3i, (Vector3I{2, 4, 6}));
  EXPECT_EQ(result2i, (Vector2I{2, 4}));
  EXPECT_EQ(result1i, (Vector1I{2}));
}

TEST_F(VectorTest, NonMemberMultiplyScalarOperator2) {
  Vector4F result4f = 2.0f * vector4f;
  Vector3F result3f = 2.0f * vector3f;
  Vector2F result2f = 2.0f * vector2f;
  Vector1F result1f = 2.0f * vector1f;

  Vector4I result4i = 2 * vector4i;
  Vector3I result3i = 2 * vector3i;
  Vector2I result2i = 2 * vector2i;
  Vector1I result1i = 2 * vector1i;

  EXPECT_EQ(result4f, (Vector4F{2.0f, 4.0f, 6.0f, 8.0f}));
  EXPECT_EQ(result3f, (Vector3F{2.0f, 4.0f, 6.0f}));
  EXPECT_EQ(result2f, (Vector2F{2.0f, 4.0f}));
  EXPECT_EQ(result1f, (Vector1F{2.0f}));

  EXPECT_EQ(result4i, (Vector4I{2, 4, 6, 8}));
  EXPECT_EQ(result3i, (Vector3I{2, 4, 6}));
  EXPECT_EQ(result2i, (Vector2I{2, 4}));
  EXPECT_EQ(result1i, (Vector1I{2}));
}

TEST_F(VectorTest, NonMemberDivideOperator) {
  Vector4F result4f = vector4f / 2.0f;
  Vector3F result3f = vector3f / 2.0f;
  Vector2F result2f = vector2f / 2.0f;
  Vector1F result1f = vector1f / 2.0f;

  Vector4I result4i = vector4i / 2;
  Vector3I result3i = vector3i / 2;
  Vector2I result2i = vector2i / 2;
  Vector1I result1i = vector1i / 2;

  EXPECT_EQ(result4f, (Vector4F{0.5f, 1.0f, 1.5f, 2.0f}));
  EXPECT_EQ(result3f, (Vector3F{0.5f, 1.0f, 1.5f}));
  EXPECT_EQ(result2f, (Vector2F{0.5f, 1.0f}));
  EXPECT_EQ(result1f, (Vector1F{0.5f}));

  EXPECT_EQ(result4i, (Vector4I{0, 1, 1, 2}));
  EXPECT_EQ(result3i, (Vector3I{0, 1, 1}));
  EXPECT_EQ(result2i, (Vector2I{0, 1}));
  EXPECT_EQ(result1i, (Vector1I{0}));
}

TEST_F(VectorTest, Norm) {
  EXPECT_FLOAT_EQ(norm(vector4f), std::sqrt(30.0f));
  EXPECT_FLOAT_EQ(norm(vector3f), std::sqrt(14.0f));
  EXPECT_FLOAT_EQ(norm(vector2f), std::sqrt(5.0f));
  EXPECT_FLOAT_EQ(norm(vector1f), 1.0f);
  EXPECT_EQ(norm(vector4i), static_cast<Int>(std::sqrt(30)));
  EXPECT_EQ(norm(vector3i), static_cast<Int>(std::sqrt(14)));
  EXPECT_EQ(norm(vector2i), static_cast<Int>(std::sqrt(5)));
  EXPECT_EQ(norm(vector1i), 1);
}

TEST_F(VectorTest, DotProduct) {
  EXPECT_FLOAT_EQ(dot(vector4f, Vector4F{1.0f, 1.0f, 1.0f, 1.0f}), 10.0f);
  EXPECT_FLOAT_EQ(dot(vector3f, Vector3F{1.0f, 1.0f, 1.0f}), 6.0f);
  EXPECT_FLOAT_EQ(dot(vector2f, Vector2F{1.0f, 1.0f}), 3.0f);
  EXPECT_FLOAT_EQ(dot(vector1f, Vector1F{1.0f}), 1.0f);

  EXPECT_EQ(dot(vector4i, Vector4I{1, 1, 1, 1}), 10);
  EXPECT_EQ(dot(vector3i, Vector3I{1, 1, 1}), 6);
  EXPECT_EQ(dot(vector2i, Vector2I{1, 1}), 3);
  EXPECT_EQ(dot(vector1i, Vector1I{1}), 1);
}
}  // namespace Neat