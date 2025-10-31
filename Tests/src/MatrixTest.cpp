
#include <gtest/gtest.h>

#include <Math/Matrix.hpp>

namespace Neat {
class MatrixTest : public testing::Test {
 protected:
  MatrixTest() {}
  Matrix4F matrix4f{1.0f, 2.0f,  3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,
                    9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
  Matrix4D matrix4d{1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                    9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};
  Matrix4I matrix4i{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  Matrix4U matrix4u{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  Matrix4B matrix4b{true, false, true, false, true, false, true, false,
                    true, false, true, false, true, false, true, false};
  Matrix3F matrix3f{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  Matrix3D matrix3d{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  Matrix3I matrix3i{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix3U matrix3u{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix3B matrix3b{true, false, true, false, true, false, true, false, true};
  Matrix2F matrix2f{1.0f, 2.0f, 3.0f, 4.0f};
  Matrix2D matrix2d{1.0, 2.0, 3.0, 4.0};
  Matrix2I matrix2i{1, 2, 3, 4};
  Matrix2U matrix2u{1, 2, 3, 4};
  Matrix2B matrix2b{true, false, true, false};
};

TEST_F(MatrixTest, RowOperator) {
  EXPECT_EQ(matrix4f.row(0), (Vector4F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(matrix4f.row(1), (Vector4F{5.0f, 6.0f, 7.0f, 8.0f}));
  EXPECT_EQ(matrix4f.row(2), (Vector4F{9.0f, 10.0f, 11.0f, 12.0f}));
  EXPECT_EQ(matrix4f.row(3), (Vector4F{13.0f, 14.0f, 15.0f, 16.0f}));

  EXPECT_EQ(matrix4d.row(0), (Vector4D{1.0, 2.0, 3.0, 4.0}));
  EXPECT_EQ(matrix4d.row(1), (Vector4D{5.0, 6.0, 7.0, 8.0}));
  EXPECT_EQ(matrix4d.row(2), (Vector4D{9.0, 10.0, 11.0, 12.0}));
  EXPECT_EQ(matrix4d.row(3), (Vector4D{13.0, 14.0, 15.0, 16.0}));

  EXPECT_EQ(matrix4i.row(0), (Vector4I{1, 2, 3, 4}));
  EXPECT_EQ(matrix4i.row(1), (Vector4I{5, 6, 7, 8}));
  EXPECT_EQ(matrix4i.row(2), (Vector4I{9, 10, 11, 12}));
  EXPECT_EQ(matrix4i.row(3), (Vector4I{13, 14, 15, 16}));

  EXPECT_EQ(matrix4u.row(0), (Vector4U{1, 2, 3, 4}));
  EXPECT_EQ(matrix4u.row(1), (Vector4U{5, 6, 7, 8}));
  EXPECT_EQ(matrix4u.row(2), (Vector4U{9, 10, 11, 12}));
  EXPECT_EQ(matrix4u.row(3), (Vector4U{13, 14, 15, 16}));

  EXPECT_EQ(matrix4b.row(0), (Vector4B{true, false, true, false}));
  EXPECT_EQ(matrix4b.row(1), (Vector4B{true, false, true, false}));
  EXPECT_EQ(matrix4b.row(2), (Vector4B{true, false, true, false}));
  EXPECT_EQ(matrix4b.row(3), (Vector4B{true, false, true, false}));

  EXPECT_EQ(matrix3f.row(0), (Vector3F{1.0f, 2.0f, 3.0f}));
  EXPECT_EQ(matrix3f.row(1), (Vector3F{4.0f, 5.0f, 6.0f}));
  EXPECT_EQ(matrix3f.row(2), (Vector3F{7.0f, 8.0f, 9.0f}));

  EXPECT_EQ(matrix3d.row(0), (Vector3D{1.0, 2.0, 3.0}));
  EXPECT_EQ(matrix3d.row(1), (Vector3D{4.0, 5.0, 6.0}));
  EXPECT_EQ(matrix3d.row(2), (Vector3D{7.0, 8.0, 9.0}));

  EXPECT_EQ(matrix3i.row(0), (Vector3I{1, 2, 3}));
  EXPECT_EQ(matrix3i.row(1), (Vector3I{4, 5, 6}));
  EXPECT_EQ(matrix3i.row(2), (Vector3I{7, 8, 9}));

  EXPECT_EQ(matrix3u.row(0), (Vector3U{1, 2, 3}));
  EXPECT_EQ(matrix3u.row(1), (Vector3U{4, 5, 6}));
  EXPECT_EQ(matrix3u.row(2), (Vector3U{7, 8, 9}));

  EXPECT_EQ(matrix3b.row(0), (Vector3B{true, false, true}));
  EXPECT_EQ(matrix3b.row(1), (Vector3B{false, true, false}));
  EXPECT_EQ(matrix3b.row(2), (Vector3B{true, false, true}));

  EXPECT_EQ(matrix2f.row(0), (Vector2F{1.0f, 2.0f}));
  EXPECT_EQ(matrix2f.row(1), (Vector2F{3.0f, 4.0f}));

  EXPECT_EQ(matrix2d.row(0), (Vector2D{1.0, 2.0}));
  EXPECT_EQ(matrix2d.row(1), (Vector2D{3.0, 4.0}));

  EXPECT_EQ(matrix2i.row(0), (Vector2I{1, 2}));
  EXPECT_EQ(matrix2i.row(1), (Vector2I{3, 4}));

  EXPECT_EQ(matrix2u.row(0), (Vector2U{1, 2}));
  EXPECT_EQ(matrix2u.row(1), (Vector2U{3, 4}));

  EXPECT_EQ(matrix2b.row(0), (Vector2B{true, false}));
  EXPECT_EQ(matrix2b.row(1), (Vector2B{true, false}));
}

TEST_F(MatrixTest, ColOperator) {
  EXPECT_EQ(matrix4f.col(0), (Vector4F{1.0f, 5.0f, 9.0f, 13.0f}));
  EXPECT_EQ(matrix4f.col(1), (Vector4F{2.0f, 6.0f, 10.0f, 14.0f}));
  EXPECT_EQ(matrix4f.col(2), (Vector4F{3.0f, 7.0f, 11.0f, 15.0f}));
  EXPECT_EQ(matrix4f.col(3), (Vector4F{4.0f, 8.0f, 12.0f, 16.0f}));

  EXPECT_EQ(matrix4d.col(0), (Vector4D{1.0, 5.0, 9.0, 13.0}));
  EXPECT_EQ(matrix4d.col(1), (Vector4D{2.0, 6.0, 10.0, 14.0}));
  EXPECT_EQ(matrix4d.col(2), (Vector4D{3.0, 7.0, 11.0, 15.0}));
  EXPECT_EQ(matrix4d.col(3), (Vector4D{4.0, 8.0, 12.0, 16.0}));

  EXPECT_EQ(matrix4i.col(0), (Vector4I{1, 5, 9, 13}));
  EXPECT_EQ(matrix4i.col(1), (Vector4I{2, 6, 10, 14}));
  EXPECT_EQ(matrix4i.col(2), (Vector4I{3, 7, 11, 15}));
  EXPECT_EQ(matrix4i.col(3), (Vector4I{4, 8, 12, 16}));

  EXPECT_EQ(matrix4u.col(0), (Vector4U{1, 5, 9, 13}));
  EXPECT_EQ(matrix4u.col(1), (Vector4U{2, 6, 10, 14}));
  EXPECT_EQ(matrix4u.col(2), (Vector4U{3, 7, 11, 15}));
  EXPECT_EQ(matrix4u.col(3), (Vector4U{4, 8, 12, 16}));

  EXPECT_EQ(matrix4b.col(0), (Vector4B{true, true, true, true}));
  EXPECT_EQ(matrix4b.col(1), (Vector4B{false, false, false, false}));
  EXPECT_EQ(matrix4b.col(2), (Vector4B{true, true, true, true}));
  EXPECT_EQ(matrix4b.col(3), (Vector4B{false, false, false, false}));

  EXPECT_EQ(matrix3f.col(0), (Vector3F{1.0f, 4.0f, 7.0f}));
  EXPECT_EQ(matrix3f.col(1), (Vector3F{2.0f, 5.0f, 8.0f}));
  EXPECT_EQ(matrix3f.col(2), (Vector3F{3.0f, 6.0f, 9.0f}));

  EXPECT_EQ(matrix3d.col(0), (Vector3D{1.0, 4.0, 7.0}));
  EXPECT_EQ(matrix3d.col(1), (Vector3D{2.0, 5.0, 8.0}));
  EXPECT_EQ(matrix3d.col(2), (Vector3D{3.0, 6.0, 9.0}));

  EXPECT_EQ(matrix3i.col(0), (Vector3I{1, 4, 7}));
  EXPECT_EQ(matrix3i.col(1), (Vector3I{2, 5, 8}));
  EXPECT_EQ(matrix3i.col(2), (Vector3I{3, 6, 9}));

  EXPECT_EQ(matrix3u.col(0), (Vector3U{1, 4, 7}));
  EXPECT_EQ(matrix3u.col(1), (Vector3U{2, 5, 8}));
  EXPECT_EQ(matrix3u.col(2), (Vector3U{3, 6, 9}));

  EXPECT_EQ(matrix3b.col(0), (Vector3B{true, false, true}));
  EXPECT_EQ(matrix3b.col(1), (Vector3B{false, true, false}));
  EXPECT_EQ(matrix3b.col(2), (Vector3B{true, false, true}));

  EXPECT_EQ(matrix2f.col(0), (Vector2F{1.0f, 3.0f}));
  EXPECT_EQ(matrix2f.col(1), (Vector2F{2.0f, 4.0f}));

  EXPECT_EQ(matrix2d.col(0), (Vector2D{1.0, 3.0}));
  EXPECT_EQ(matrix2d.col(1), (Vector2D{2.0, 4.0}));

  EXPECT_EQ(matrix2i.col(0), (Vector2I{1, 3}));
  EXPECT_EQ(matrix2i.col(1), (Vector2I{2, 4}));

  EXPECT_EQ(matrix2u.col(0), (Vector2U{1, 3}));
  EXPECT_EQ(matrix2u.col(1), (Vector2U{2, 4}));

  EXPECT_EQ(matrix2b.col(0), (Vector2B{true, true}));
  EXPECT_EQ(matrix2b.col(1), (Vector2B{false, false}));
}

TEST_F(MatrixTest, Transpose) {
  EXPECT_EQ(transpose(matrix4f),
            (Matrix4F{1.0f, 5.0f, 9.0f, 13.0f, 2.0f, 6.0f, 10.0f, 14.0f, 3.0f,
                      7.0f, 11.0f, 15.0f, 4.0f, 8.0f, 12.0f, 16.0f}));
  EXPECT_EQ(transpose(matrix4d),
            (Matrix4D{1.0, 5.0, 9.0, 13.0, 2.0, 6.0, 10.0, 14.0, 3.0, 7.0, 11.0,
                      15.0, 4.0, 8.0, 12.0, 16.0}));
  EXPECT_EQ(transpose(matrix4i),
            (Matrix4I{1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16}));
  EXPECT_EQ(transpose(matrix4u),
            (Matrix4U{1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16}));
  EXPECT_EQ(transpose(matrix4b),
            (Matrix4B{true, true, true, true, false, false, false, false, true,
                      true, true, true, false, false, false, false}));
  EXPECT_EQ(transpose(matrix3f),
            (Matrix3F{1.0f, 4.0f, 7.0f, 2.0f, 5.0f, 8.0f, 3.0f, 6.0f, 9.0f}));
  EXPECT_EQ(transpose(matrix3d),
            (Matrix3D{1.0, 4.0, 7.0, 2.0, 5.0, 8.0, 3.0, 6.0, 9.0}));
  EXPECT_EQ(transpose(matrix3i), (Matrix3I{1, 4, 7, 2, 5, 8, 3, 6, 9}));
  EXPECT_EQ(transpose(matrix3u), (Matrix3U{1, 4, 7, 2, 5, 8, 3, 6, 9}));
  EXPECT_EQ(transpose(matrix3b), (Matrix3B{true, false, true, false, true,
                                           false, true, false, true}));
  EXPECT_EQ(transpose(matrix2f), (Matrix2F{1.0f, 3.0f, 2.0f, 4.0f}));
  EXPECT_EQ(transpose(matrix2d), (Matrix2D{1.0, 3.0, 2.0, 4.0}));
  EXPECT_EQ(transpose(matrix2i), (Matrix2I{1, 3, 2, 4}));
  EXPECT_EQ(transpose(matrix2u), (Matrix2U{1, 3, 2, 4}));
  EXPECT_EQ(transpose(matrix2b), (Matrix2B{true, true, false, false}));
}

TEST_F(MatrixTest, MultidimensionalCallOperator) {
  // 4D matrices
  EXPECT_EQ(matrix4f(0, 0), 1.0f);
  EXPECT_EQ(matrix4f(0, 1), 2.0f);
  EXPECT_EQ(matrix4f(0, 2), 3.0f);
  EXPECT_EQ(matrix4f(0, 3), 4.0f);
  EXPECT_EQ(matrix4f(1, 0), 5.0f);
  EXPECT_EQ(matrix4f(1, 1), 6.0f);
  EXPECT_EQ(matrix4f(1, 2), 7.0f);
  EXPECT_EQ(matrix4f(1, 3), 8.0f);
  EXPECT_EQ(matrix4f(2, 0), 9.0f);
  EXPECT_EQ(matrix4f(2, 1), 10.0f);
  EXPECT_EQ(matrix4f(2, 2), 11.0f);
  EXPECT_EQ(matrix4f(2, 3), 12.0f);
  EXPECT_EQ(matrix4f(3, 0), 13.0f);
  EXPECT_EQ(matrix4f(3, 1), 14.0f);
  EXPECT_EQ(matrix4f(3, 2), 15.0f);
  EXPECT_EQ(matrix4f(3, 3), 16.0f);

  EXPECT_EQ(matrix4d(0, 0), 1.0);
  EXPECT_EQ(matrix4d(0, 1), 2.0);
  EXPECT_EQ(matrix4d(0, 2), 3.0);
  EXPECT_EQ(matrix4d(0, 3), 4.0);
  EXPECT_EQ(matrix4d(1, 0), 5.0);
  EXPECT_EQ(matrix4d(1, 1), 6.0);
  EXPECT_EQ(matrix4d(1, 2), 7.0);
  EXPECT_EQ(matrix4d(1, 3), 8.0);
  EXPECT_EQ(matrix4d(2, 0), 9.0);
  EXPECT_EQ(matrix4d(2, 1), 10.0);
  EXPECT_EQ(matrix4d(2, 2), 11.0);
  EXPECT_EQ(matrix4d(2, 3), 12.0);
  EXPECT_EQ(matrix4d(3, 0), 13.0);
  EXPECT_EQ(matrix4d(3, 1), 14.0);
  EXPECT_EQ(matrix4d(3, 2), 15.0);
  EXPECT_EQ(matrix4d(3, 3), 16.0);

  EXPECT_EQ(matrix4i(0, 0), 1);
  EXPECT_EQ(matrix4i(0, 1), 2);
  EXPECT_EQ(matrix4i(0, 2), 3);
  EXPECT_EQ(matrix4i(0, 3), 4);
  EXPECT_EQ(matrix4i(1, 0), 5);
  EXPECT_EQ(matrix4i(1, 1), 6);
  EXPECT_EQ(matrix4i(1, 2), 7);
  EXPECT_EQ(matrix4i(1, 3), 8);
  EXPECT_EQ(matrix4i(2, 0), 9);
  EXPECT_EQ(matrix4i(2, 1), 10);
  EXPECT_EQ(matrix4i(2, 2), 11);
  EXPECT_EQ(matrix4i(2, 3), 12);
  EXPECT_EQ(matrix4i(3, 0), 13);
  EXPECT_EQ(matrix4i(3, 1), 14);
  EXPECT_EQ(matrix4i(3, 2), 15);
  EXPECT_EQ(matrix4i(3, 3), 16);

  EXPECT_EQ(matrix4u(0, 0), 1);
  EXPECT_EQ(matrix4u(0, 1), 2);
  EXPECT_EQ(matrix4u(0, 2), 3);
  EXPECT_EQ(matrix4u(0, 3), 4);
  EXPECT_EQ(matrix4u(1, 0), 5);
  EXPECT_EQ(matrix4u(1, 1), 6);
  EXPECT_EQ(matrix4u(1, 2), 7);
  EXPECT_EQ(matrix4u(1, 3), 8);
  EXPECT_EQ(matrix4u(2, 0), 9);
  EXPECT_EQ(matrix4u(2, 1), 10);
  EXPECT_EQ(matrix4u(2, 2), 11);
  EXPECT_EQ(matrix4u(2, 3), 12);
  EXPECT_EQ(matrix4u(3, 0), 13);
  EXPECT_EQ(matrix4u(3, 1), 14);
  EXPECT_EQ(matrix4u(3, 2), 15);
  EXPECT_EQ(matrix4u(3, 3), 16);

  EXPECT_EQ(matrix4b(0, 0), true);
  EXPECT_EQ(matrix4b(0, 1), false);
  EXPECT_EQ(matrix4b(0, 2), true);
  EXPECT_EQ(matrix4b(0, 3), false);
  EXPECT_EQ(matrix4b(1, 0), true);
  EXPECT_EQ(matrix4b(1, 1), false);
  EXPECT_EQ(matrix4b(1, 2), true);
  EXPECT_EQ(matrix4b(1, 3), false);
  EXPECT_EQ(matrix4b(2, 0), true);
  EXPECT_EQ(matrix4b(2, 1), false);
  EXPECT_EQ(matrix4b(2, 2), true);
  EXPECT_EQ(matrix4b(2, 3), false);
  EXPECT_EQ(matrix4b(3, 0), true);
  EXPECT_EQ(matrix4b(3, 1), false);
  EXPECT_EQ(matrix4b(3, 2), true);
  EXPECT_EQ(matrix4b(3, 3), false);

  // 3D matrices
  EXPECT_EQ(matrix3f(0, 0), 1.0f);
  EXPECT_EQ(matrix3f(0, 1), 2.0f);
  EXPECT_EQ(matrix3f(0, 2), 3.0f);
  EXPECT_EQ(matrix3f(1, 0), 4.0f);
  EXPECT_EQ(matrix3f(1, 1), 5.0f);
  EXPECT_EQ(matrix3f(1, 2), 6.0f);
  EXPECT_EQ(matrix3f(2, 0), 7.0f);
  EXPECT_EQ(matrix3f(2, 1), 8.0f);
  EXPECT_EQ(matrix3f(2, 2), 9.0f);

  EXPECT_EQ(matrix3d(0, 0), 1.0);
  EXPECT_EQ(matrix3d(0, 1), 2.0);
  EXPECT_EQ(matrix3d(0, 2), 3.0);
  EXPECT_EQ(matrix3d(1, 0), 4.0);
  EXPECT_EQ(matrix3d(1, 1), 5.0);
  EXPECT_EQ(matrix3d(1, 2), 6.0);
  EXPECT_EQ(matrix3d(2, 0), 7.0);
  EXPECT_EQ(matrix3d(2, 1), 8.0);
  EXPECT_EQ(matrix3d(2, 2), 9.0);

  EXPECT_EQ(matrix3i(0, 0), 1);
  EXPECT_EQ(matrix3i(0, 1), 2);
  EXPECT_EQ(matrix3i(0, 2), 3);
  EXPECT_EQ(matrix3i(1, 0), 4);
  EXPECT_EQ(matrix3i(1, 1), 5);
  EXPECT_EQ(matrix3i(1, 2), 6);
  EXPECT_EQ(matrix3i(2, 0), 7);
  EXPECT_EQ(matrix3i(2, 1), 8);
  EXPECT_EQ(matrix3i(2, 2), 9);

  EXPECT_EQ(matrix3u(0, 0), 1);
  EXPECT_EQ(matrix3u(0, 1), 2);
  EXPECT_EQ(matrix3u(0, 2), 3);
  EXPECT_EQ(matrix3u(1, 0), 4);
  EXPECT_EQ(matrix3u(1, 1), 5);
  EXPECT_EQ(matrix3u(1, 2), 6);
  EXPECT_EQ(matrix3u(2, 0), 7);
  EXPECT_EQ(matrix3u(2, 1), 8);
  EXPECT_EQ(matrix3u(2, 2), 9);

  EXPECT_EQ(matrix3b(0, 0), true);
  EXPECT_EQ(matrix3b(0, 1), false);
  EXPECT_EQ(matrix3b(0, 2), true);
  EXPECT_EQ(matrix3b(1, 0), false);
  EXPECT_EQ(matrix3b(1, 1), true);
  EXPECT_EQ(matrix3b(1, 2), false);
  EXPECT_EQ(matrix3b(2, 0), true);
  EXPECT_EQ(matrix3b(2, 1), false);
  EXPECT_EQ(matrix3b(2, 2), true);

  // 2D matrices
  EXPECT_EQ(matrix2f(0, 0), 1.0f);
  EXPECT_EQ(matrix2f(0, 1), 2.0f);
  EXPECT_EQ(matrix2f(1, 0), 3.0f);
  EXPECT_EQ(matrix2f(1, 1), 4.0f);

  EXPECT_EQ(matrix2d(0, 0), 1.0);
  EXPECT_EQ(matrix2d(0, 1), 2.0);
  EXPECT_EQ(matrix2d(1, 0), 3.0);
  EXPECT_EQ(matrix2d(1, 1), 4.0);

  EXPECT_EQ(matrix2i(0, 0), 1);
  EXPECT_EQ(matrix2i(0, 1), 2);
  EXPECT_EQ(matrix2i(1, 0), 3);
  EXPECT_EQ(matrix2i(1, 1), 4);

  EXPECT_EQ(matrix2u(0, 0), 1);
  EXPECT_EQ(matrix2u(0, 1), 2);
  EXPECT_EQ(matrix2u(1, 0), 3);
  EXPECT_EQ(matrix2u(1, 1), 4);

  EXPECT_EQ(matrix2b(0, 0), true);
  EXPECT_EQ(matrix2b(0, 1), false);
  EXPECT_EQ(matrix2b(1, 0), true);
  EXPECT_EQ(matrix2b(1, 1), false);

  // Assignment tests
  matrix4f(2, 2) = 42.0f;
  EXPECT_EQ(matrix4f(2, 2), 42.0f);
  matrix4d(1, 3) = 3.14;
  EXPECT_EQ(matrix4d(1, 3), 3.14);
  matrix4i(0, 0) = 99;
  EXPECT_EQ(matrix4i(0, 0), 99);
  matrix4u(3, 1) = 77;
  EXPECT_EQ(matrix4u(3, 1), 77);
  matrix4b(1, 2) = true;
  EXPECT_EQ(matrix4b(1, 2), true);
  matrix4b(2, 3) = false;
  EXPECT_EQ(matrix4b(2, 3), false);
  matrix4b(3, 0) = true;
  EXPECT_EQ(matrix4b(3, 0), true);
  matrix4b(3, 1) = false;
  EXPECT_EQ(matrix4b(3, 1), false);
  matrix3f(0, 2) = 24.0f;
  EXPECT_EQ(matrix3f(0, 2), 24.0f);
  matrix3d(2, 0) = 6.28;
  EXPECT_EQ(matrix3d(2, 0), 6.28);
  matrix3i(1, 1) = 88;
  EXPECT_EQ(matrix3i(1, 1), 88);
  matrix3u(2, 2) = 55;
  EXPECT_EQ(matrix3u(2, 2), 55);
  matrix3b(0, 1) = true;
  EXPECT_EQ(matrix3b(0, 1), true);
  matrix2f(1, 0) = 11.0f;
  EXPECT_EQ(matrix2f(1, 0), 11.0f);
  matrix2d(0, 1) = 22.0;
  EXPECT_EQ(matrix2d(0, 1), 22.0);
  matrix2i(1, 1) = 33;
  EXPECT_EQ(matrix2i(1, 1), 33);
  matrix2u(0, 0) = 44;
  EXPECT_EQ(matrix2u(0, 0), 44);
  matrix2b(1, 0) = false;
  EXPECT_EQ(matrix2b(1, 0), false);
}

TEST_F(MatrixTest, MultidimensionalIndexOperator) {
  // 4D matrices
  EXPECT_EQ((matrix4f[0, 0]), 1.0f);
  EXPECT_EQ((matrix4f[0, 1]), 2.0f);
  EXPECT_EQ((matrix4f[0, 2]), 3.0f);
  EXPECT_EQ((matrix4f[0, 3]), 4.0f);
  EXPECT_EQ((matrix4f[1, 0]), 5.0f);
  EXPECT_EQ((matrix4f[1, 1]), 6.0f);
  EXPECT_EQ((matrix4f[1, 2]), 7.0f);
  EXPECT_EQ((matrix4f[1, 3]), 8.0f);
  EXPECT_EQ((matrix4f[2, 0]), 9.0f);
  EXPECT_EQ((matrix4f[2, 1]), 10.0f);
  EXPECT_EQ((matrix4f[2, 2]), 11.0f);
  EXPECT_EQ((matrix4f[2, 3]), 12.0f);
  EXPECT_EQ((matrix4f[3, 0]), 13.0f);
  EXPECT_EQ((matrix4f[3, 1]), 14.0f);
  EXPECT_EQ((matrix4f[3, 2]), 15.0f);
  EXPECT_EQ((matrix4f[3, 3]), 16.0f);

  EXPECT_EQ((matrix4d[0, 0]), 1.0);
  EXPECT_EQ((matrix4d[0, 1]), 2.0);
  EXPECT_EQ((matrix4d[0, 2]), 3.0);
  EXPECT_EQ((matrix4d[0, 3]), 4.0);
  EXPECT_EQ((matrix4d[1, 0]), 5.0);
  EXPECT_EQ((matrix4d[1, 1]), 6.0);
  EXPECT_EQ((matrix4d[1, 2]), 7.0);
  EXPECT_EQ((matrix4d[1, 3]), 8.0);
  EXPECT_EQ((matrix4d[2, 0]), 9.0);
  EXPECT_EQ((matrix4d[2, 1]), 10.0);
  EXPECT_EQ((matrix4d[2, 2]), 11.0);
  EXPECT_EQ((matrix4d[2, 3]), 12.0);
  EXPECT_EQ((matrix4d[3, 0]), 13.0);
  EXPECT_EQ((matrix4d[3, 1]), 14.0);
  EXPECT_EQ((matrix4d[3, 2]), 15.0);
  EXPECT_EQ((matrix4d[3, 3]), 16.0);

  EXPECT_EQ((matrix4i[0, 0]), 1);
  EXPECT_EQ((matrix4i[0, 1]), 2);
  EXPECT_EQ((matrix4i[0, 2]), 3);
  EXPECT_EQ((matrix4i[0, 3]), 4);
  EXPECT_EQ((matrix4i[1, 0]), 5);
  EXPECT_EQ((matrix4i[1, 1]), 6);
  EXPECT_EQ((matrix4i[1, 2]), 7);
  EXPECT_EQ((matrix4i[1, 3]), 8);
  EXPECT_EQ((matrix4i[2, 0]), 9);
  EXPECT_EQ((matrix4i[2, 1]), 10);
  EXPECT_EQ((matrix4i[2, 2]), 11);
  EXPECT_EQ((matrix4i[2, 3]), 12);
  EXPECT_EQ((matrix4i[3, 0]), 13);
  EXPECT_EQ((matrix4i[3, 1]), 14);
  EXPECT_EQ((matrix4i[3, 2]), 15);
  EXPECT_EQ((matrix4i[3, 3]), 16);

  EXPECT_EQ((matrix4u[0, 0]), 1);
  EXPECT_EQ((matrix4u[0, 1]), 2);
  EXPECT_EQ((matrix4u[0, 2]), 3);
  EXPECT_EQ((matrix4u[0, 3]), 4);
  EXPECT_EQ((matrix4u[1, 0]), 5);
  EXPECT_EQ((matrix4u[1, 1]), 6);
  EXPECT_EQ((matrix4u[1, 2]), 7);
  EXPECT_EQ((matrix4u[1, 3]), 8);
  EXPECT_EQ((matrix4u[2, 0]), 9);
  EXPECT_EQ((matrix4u[2, 1]), 10);
  EXPECT_EQ((matrix4u[2, 2]), 11);
  EXPECT_EQ((matrix4u[2, 3]), 12);
  EXPECT_EQ((matrix4u[3, 0]), 13);
  EXPECT_EQ((matrix4u[3, 1]), 14);
  EXPECT_EQ((matrix4u[3, 2]), 15);
  EXPECT_EQ((matrix4u[3, 3]), 16);

  EXPECT_EQ((matrix4b[0, 0]), true);
  EXPECT_EQ((matrix4b[0, 1]), false);
  EXPECT_EQ((matrix4b[0, 2]), true);
  EXPECT_EQ((matrix4b[0, 3]), false);
  EXPECT_EQ((matrix4b[1, 0]), true);
  EXPECT_EQ((matrix4b[1, 1]), false);
  EXPECT_EQ((matrix4b[1, 2]), true);
  EXPECT_EQ((matrix4b[1, 3]), false);
  EXPECT_EQ((matrix4b[2, 0]), true);
  EXPECT_EQ((matrix4b[2, 1]), false);
  EXPECT_EQ((matrix4b[2, 2]), true);
  EXPECT_EQ((matrix4b[2, 3]), false);
  EXPECT_EQ((matrix4b[3, 0]), true);
  EXPECT_EQ((matrix4b[3, 1]), false);
  EXPECT_EQ((matrix4b[3, 2]), true);
  EXPECT_EQ((matrix4b[3, 3]), false);

  // 3D matrices
  EXPECT_EQ((matrix3f[0, 0]), 1.0f);
  EXPECT_EQ((matrix3f[0, 1]), 2.0f);
  EXPECT_EQ((matrix3f[0, 2]), 3.0f);
  EXPECT_EQ((matrix3f[1, 0]), 4.0f);
  EXPECT_EQ((matrix3f[1, 1]), 5.0f);
  EXPECT_EQ((matrix3f[1, 2]), 6.0f);
  EXPECT_EQ((matrix3f[2, 0]), 7.0f);
  EXPECT_EQ((matrix3f[2, 1]), 8.0f);
  EXPECT_EQ((matrix3f[2, 2]), 9.0f);

  EXPECT_EQ((matrix3d[0, 0]), 1.0);
  EXPECT_EQ((matrix3d[0, 1]), 2.0);
  EXPECT_EQ((matrix3d[0, 2]), 3.0);
  EXPECT_EQ((matrix3d[1, 0]), 4.0);
  EXPECT_EQ((matrix3d[1, 1]), 5.0);
  EXPECT_EQ((matrix3d[1, 2]), 6.0);
  EXPECT_EQ((matrix3d[2, 0]), 7.0);
  EXPECT_EQ((matrix3d[2, 1]), 8.0);
  EXPECT_EQ((matrix3d[2, 2]), 9.0);

  EXPECT_EQ((matrix3i[0, 0]), 1);
  EXPECT_EQ((matrix3i[0, 1]), 2);
  EXPECT_EQ((matrix3i[0, 2]), 3);
  EXPECT_EQ((matrix3i[1, 0]), 4);
  EXPECT_EQ((matrix3i[1, 1]), 5);
  EXPECT_EQ((matrix3i[1, 2]), 6);
  EXPECT_EQ((matrix3i[2, 0]), 7);
  EXPECT_EQ((matrix3i[2, 1]), 8);
  EXPECT_EQ((matrix3i[2, 2]), 9);

  EXPECT_EQ((matrix3u[0, 0]), 1);
  EXPECT_EQ((matrix3u[0, 1]), 2);
  EXPECT_EQ((matrix3u[0, 2]), 3);
  EXPECT_EQ((matrix3u[1, 0]), 4);
  EXPECT_EQ((matrix3u[1, 1]), 5);
  EXPECT_EQ((matrix3u[1, 2]), 6);
  EXPECT_EQ((matrix3u[2, 0]), 7);
  EXPECT_EQ((matrix3u[2, 1]), 8);
  EXPECT_EQ((matrix3u[2, 2]), 9);

  EXPECT_EQ((matrix3b[0, 0]), true);
  EXPECT_EQ((matrix3b[0, 1]), false);
  EXPECT_EQ((matrix3b[0, 2]), true);
  EXPECT_EQ((matrix3b[1, 0]), false);
  EXPECT_EQ((matrix3b[1, 1]), true);
  EXPECT_EQ((matrix3b[1, 2]), false);
  EXPECT_EQ((matrix3b[2, 0]), true);
  EXPECT_EQ((matrix3b[2, 1]), false);
  EXPECT_EQ((matrix3b[2, 2]), true);

  // 2D matrices
  EXPECT_EQ((matrix2f[0, 0]), 1.0f);
  EXPECT_EQ((matrix2f[0, 1]), 2.0f);
  EXPECT_EQ((matrix2f[1, 0]), 3.0f);
  EXPECT_EQ((matrix2f[1, 1]), 4.0f);

  EXPECT_EQ((matrix2d[0, 0]), 1.0);
  EXPECT_EQ((matrix2d[0, 1]), 2.0);
  EXPECT_EQ((matrix2d[1, 0]), 3.0);
  EXPECT_EQ((matrix2d[1, 1]), 4.0);

  EXPECT_EQ((matrix2i[0, 0]), 1);
  EXPECT_EQ((matrix2i[0, 1]), 2);
  EXPECT_EQ((matrix2i[1, 0]), 3);
  EXPECT_EQ((matrix2i[1, 1]), 4);

  EXPECT_EQ((matrix2u[0, 0]), 1);
  EXPECT_EQ((matrix2u[0, 1]), 2);
  EXPECT_EQ((matrix2u[1, 0]), 3);
  EXPECT_EQ((matrix2u[1, 1]), 4);

  EXPECT_EQ((matrix2b[0, 0]), true);
  EXPECT_EQ((matrix2b[0, 1]), false);
  EXPECT_EQ((matrix2b[1, 0]), true);
  EXPECT_EQ((matrix2b[1, 1]), false);

  // Assignment tests
  matrix4f[2, 3] = 42.0f;
  matrix4d[1, 2] = 3.14;
  matrix4i[0, 0] = 99;
  matrix4u[3, 1] = 77;
  matrix4b[1, 2] = true;
  matrix3f[1, 0] = 24.0f;
  matrix3d[2, 2] = 6.28;
  matrix3i[1, 1] = 88;
  matrix3u[0, 2] = 55;
  matrix3b[0, 1] = true;
  matrix2d[1, 0] = 22.0;
  matrix2i[1, 1] = 33;
  matrix2u[0, 0] = 44;
  matrix2f[0, 1] = 12.0f;
  matrix2b[1, 0] = false;
  EXPECT_EQ((matrix4f[2, 3]), 42.0f);
  EXPECT_EQ((matrix3f[1, 0]), 24.0f);
  EXPECT_EQ((matrix2f[0, 1]), 12.0f);
  EXPECT_EQ((matrix4d[1, 2]), 3.14);
  EXPECT_EQ((matrix3d[2, 2]), 6.28);
  EXPECT_EQ((matrix2d[1, 0]), 22.0);
  EXPECT_EQ((matrix4i[0, 0]), 99);
  EXPECT_EQ((matrix3i[1, 1]), 88);
  EXPECT_EQ((matrix2i[1, 1]), 33);
  EXPECT_EQ((matrix4u[3, 1]), 77);
  EXPECT_EQ((matrix3u[0, 2]), 55);
  EXPECT_EQ((matrix2u[0, 0]), 44);
  EXPECT_EQ((matrix4b[1, 2]), true);
  EXPECT_EQ((matrix3b[0, 1]), true);
  EXPECT_EQ((matrix2b[1, 0]), false);
}

TEST_F(MatrixTest, MultipleScalarsConstructor) {
  // This tests are used as a base for other tests, as we will be using this
  // constructor to test other matrices functionalities. That's why we test all
  // of the possible types and sizes here.

  Matrix4F customMatrix4f{1.0f,  2.0f,  3.0f,  4.0f,  5.0f,  6.0f,
                          7.0f,  8.0f,  9.0f,  10.0f, 11.0f, 12.0f,
                          13.0f, 14.0f, 15.0f, 16.0f};
  Matrix4D customMatrix4d{1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                          9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};
  Matrix4I customMatrix4i{1, 2,  3,  4,  5,  6,  7,  8,
                          9, 10, 11, 12, 13, 14, 15, 16};
  Matrix4U customMatrix4u{1, 2,  3,  4,  5,  6,  7,  8,
                          9, 10, 11, 12, 13, 14, 15, 16};
  Matrix4B customMatrix4b{true, false, true, false, true, false, true, false,
                          true, false, true, false, true, false, true, false};
  Matrix3B customMatrix3b{true,  false, true,  false, true,
                          false, true,  false, true};
  Matrix2B customMatrix2b{true, false, false, true};
  Matrix3D customMatrix3d{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  Matrix2D customMatrix2d{1.0, 2.0, 3.0, 4.0};
  Matrix3I customMatrix3i{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix2I customMatrix2i{1, 2, 3, 4};
  Matrix3U customMatrix3u{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix2U customMatrix2u{1, 2, 3, 4};
  Matrix3F customMatrix3f{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  Matrix2F customMatrix2f{1.0f, 2.0f, 3.0f, 4.0f};

  EXPECT_EQ(customMatrix4f(0, 0), 1.0f);
  EXPECT_EQ(customMatrix4f(0, 1), 2.0f);
  EXPECT_EQ(customMatrix4f(0, 2), 3.0f);
  EXPECT_EQ(customMatrix4f(0, 3), 4.0f);
  EXPECT_EQ(customMatrix4f(1, 0), 5.0f);
  EXPECT_EQ(customMatrix4f(1, 1), 6.0f);
  EXPECT_EQ(customMatrix4f(1, 2), 7.0f);
  EXPECT_EQ(customMatrix4f(1, 3), 8.0f);
  EXPECT_EQ(customMatrix4f(2, 0), 9.0f);
  EXPECT_EQ(customMatrix4f(2, 1), 10.0f);
  EXPECT_EQ(customMatrix4f(2, 2), 11.0f);
  EXPECT_EQ(customMatrix4f(2, 3), 12.0f);
  EXPECT_EQ(customMatrix4f(3, 0), 13.0f);
  EXPECT_EQ(customMatrix4f(3, 1), 14.0f);
  EXPECT_EQ(customMatrix4f(3, 2), 15.0f);
  EXPECT_EQ(customMatrix4f(3, 3), 16.0f);
  EXPECT_EQ(customMatrix3f(0, 0), 1.0f);
  EXPECT_EQ(customMatrix3f(0, 1), 2.0f);
  EXPECT_EQ(customMatrix3f(0, 2), 3.0f);
  EXPECT_EQ(customMatrix3f(1, 0), 4.0f);
  EXPECT_EQ(customMatrix3f(1, 1), 5.0f);
  EXPECT_EQ(customMatrix3f(1, 2), 6.0f);
  EXPECT_EQ(customMatrix3f(2, 0), 7.0f);
  EXPECT_EQ(customMatrix3f(2, 1), 8.0f);
  EXPECT_EQ(customMatrix3f(2, 2), 9.0f);
  EXPECT_EQ(customMatrix2f(0, 0), 1.0f);
  EXPECT_EQ(customMatrix2f(0, 1), 2.0f);
  EXPECT_EQ(customMatrix2f(1, 0), 3.0f);
  EXPECT_EQ(customMatrix2f(1, 1), 4.0f);
  EXPECT_EQ(customMatrix4d(0, 0), 1.0);
  EXPECT_EQ(customMatrix4d(0, 1), 2.0);
  EXPECT_EQ(customMatrix4d(0, 2), 3.0);
  EXPECT_EQ(customMatrix4d(0, 3), 4.0);
  EXPECT_EQ(customMatrix4d(1, 0), 5.0);
  EXPECT_EQ(customMatrix4d(1, 1), 6.0);
  EXPECT_EQ(customMatrix4d(1, 2), 7.0);
  EXPECT_EQ(customMatrix4d(1, 3), 8.0);
  EXPECT_EQ(customMatrix4d(2, 0), 9.0);
  EXPECT_EQ(customMatrix4d(2, 1), 10.0);
  EXPECT_EQ(customMatrix4d(2, 2), 11.0);
  EXPECT_EQ(customMatrix4d(2, 3), 12.0);
  EXPECT_EQ(customMatrix4d(3, 0), 13.0);
  EXPECT_EQ(customMatrix4d(3, 1), 14.0);
  EXPECT_EQ(customMatrix4d(3, 2), 15.0);
  EXPECT_EQ(customMatrix4d(3, 3), 16.0);
  EXPECT_EQ(customMatrix3d(0, 0), 1.0);
  EXPECT_EQ(customMatrix3d(0, 1), 2.0);
  EXPECT_EQ(customMatrix3d(0, 2), 3.0);
  EXPECT_EQ(customMatrix3d(1, 0), 4.0);
  EXPECT_EQ(customMatrix3d(1, 1), 5.0);
  EXPECT_EQ(customMatrix3d(1, 2), 6.0);
  EXPECT_EQ(customMatrix3d(2, 0), 7.0);
  EXPECT_EQ(customMatrix3d(2, 1), 8.0);
  EXPECT_EQ(customMatrix3d(2, 2), 9.0);
  EXPECT_EQ(customMatrix2d(0, 0), 1.0);
  EXPECT_EQ(customMatrix2d(0, 1), 2.0);
  EXPECT_EQ(customMatrix2d(1, 0), 3.0);
  EXPECT_EQ(customMatrix2d(1, 1), 4.0);
  EXPECT_EQ(customMatrix4i(0, 0), 1);
  EXPECT_EQ(customMatrix4i(0, 1), 2);
  EXPECT_EQ(customMatrix4i(0, 2), 3);
  EXPECT_EQ(customMatrix4i(0, 3), 4);
  EXPECT_EQ(customMatrix4i(1, 0), 5);
  EXPECT_EQ(customMatrix4i(1, 1), 6);
  EXPECT_EQ(customMatrix4i(1, 2), 7);
  EXPECT_EQ(customMatrix4i(1, 3), 8);
  EXPECT_EQ(customMatrix4i(2, 0), 9);
  EXPECT_EQ(customMatrix4i(2, 1), 10);
  EXPECT_EQ(customMatrix4i(2, 2), 11);
  EXPECT_EQ(customMatrix4i(2, 3), 12);
  EXPECT_EQ(customMatrix4i(3, 0), 13);
  EXPECT_EQ(customMatrix4i(3, 1), 14);
  EXPECT_EQ(customMatrix4i(3, 2), 15);
  EXPECT_EQ(customMatrix4i(3, 3), 16);
  EXPECT_EQ(customMatrix3i(0, 0), 1);
  EXPECT_EQ(customMatrix3i(0, 1), 2);
  EXPECT_EQ(customMatrix3i(0, 2), 3);
  EXPECT_EQ(customMatrix3i(1, 0), 4);
  EXPECT_EQ(customMatrix3i(1, 1), 5);
  EXPECT_EQ(customMatrix3i(1, 2), 6);
  EXPECT_EQ(customMatrix3i(2, 0), 7);
  EXPECT_EQ(customMatrix3i(2, 1), 8);
  EXPECT_EQ(customMatrix3i(2, 2), 9);
  EXPECT_EQ(customMatrix2i(0, 0), 1);
  EXPECT_EQ(customMatrix2i(0, 1), 2);
  EXPECT_EQ(customMatrix2i(1, 0), 3);
  EXPECT_EQ(customMatrix2i(1, 1), 4);
  EXPECT_EQ(customMatrix4u(0, 0), 1);
  EXPECT_EQ(customMatrix4u(0, 1), 2);
  EXPECT_EQ(customMatrix4u(0, 2), 3);
  EXPECT_EQ(customMatrix4u(0, 3), 4);
  EXPECT_EQ(customMatrix4u(1, 0), 5);
  EXPECT_EQ(customMatrix4u(1, 1), 6);
  EXPECT_EQ(customMatrix4u(1, 2), 7);
  EXPECT_EQ(customMatrix4u(1, 3), 8);
  EXPECT_EQ(customMatrix4u(2, 0), 9);
  EXPECT_EQ(customMatrix4u(2, 1), 10);
  EXPECT_EQ(customMatrix4u(2, 2), 11);
  EXPECT_EQ(customMatrix4u(2, 3), 12);
  EXPECT_EQ(customMatrix4u(3, 0), 13);
  EXPECT_EQ(customMatrix4u(3, 1), 14);
  EXPECT_EQ(customMatrix4u(3, 2), 15);
  EXPECT_EQ(customMatrix4u(3, 3), 16);
  EXPECT_EQ(customMatrix3u(0, 0), 1);
  EXPECT_EQ(customMatrix3u(0, 1), 2);
  EXPECT_EQ(customMatrix3u(0, 2), 3);
  EXPECT_EQ(customMatrix3u(1, 0), 4);
  EXPECT_EQ(customMatrix3u(1, 1), 5);
  EXPECT_EQ(customMatrix3u(1, 2), 6);
  EXPECT_EQ(customMatrix3u(2, 0), 7);
  EXPECT_EQ(customMatrix3u(2, 1), 8);
  EXPECT_EQ(customMatrix3u(2, 2), 9);
  EXPECT_EQ(customMatrix2u(0, 0), 1);
  EXPECT_EQ(customMatrix2u(0, 1), 2);
  EXPECT_EQ(customMatrix2u(1, 0), 3);
  EXPECT_EQ(customMatrix2u(1, 1), 4);
  EXPECT_EQ(customMatrix4b(0, 0), true);
  EXPECT_EQ(customMatrix4b(0, 1), false);
  EXPECT_EQ(customMatrix4b(0, 2), true);
  EXPECT_EQ(customMatrix4b(0, 3), false);
  EXPECT_EQ(customMatrix4b(1, 0), true);
  EXPECT_EQ(customMatrix4b(1, 1), false);
  EXPECT_EQ(customMatrix4b(1, 2), true);
  EXPECT_EQ(customMatrix4b(1, 3), false);
  EXPECT_EQ(customMatrix4b(2, 0), true);
  EXPECT_EQ(customMatrix4b(2, 1), false);
  EXPECT_EQ(customMatrix4b(2, 2), true);
  EXPECT_EQ(customMatrix4b(2, 3), false);
  EXPECT_EQ(customMatrix4b(3, 0), true);
  EXPECT_EQ(customMatrix4b(3, 1), false);
  EXPECT_EQ(customMatrix4b(3, 2), true);
  EXPECT_EQ(customMatrix4b(3, 3), false);
  EXPECT_EQ(customMatrix3b(0, 0), true);
  EXPECT_EQ(customMatrix3b(0, 1), false);
  EXPECT_EQ(customMatrix3b(0, 2), true);
  EXPECT_EQ(customMatrix3b(1, 0), false);
  EXPECT_EQ(customMatrix3b(1, 1), true);
  EXPECT_EQ(customMatrix3b(1, 2), false);
  EXPECT_EQ(customMatrix3b(2, 0), true);
  EXPECT_EQ(customMatrix3b(2, 1), false);
  EXPECT_EQ(customMatrix3b(2, 2), true);
  EXPECT_EQ(customMatrix2b(0, 0), true);
  EXPECT_EQ(customMatrix2b(0, 1), false);
  EXPECT_EQ(customMatrix2b(1, 0), false);
  EXPECT_EQ(customMatrix2b(1, 1), true);
}

TEST_F(MatrixTest, DefaultConstructor) {
  Matrix4F defaultMatrix4f{};
  Matrix4D defaultMatrix4d{};
  Matrix4I defaultMatrix4i{};
  Matrix4U defaultMatrix4u{};
  Matrix4B defaultMatrix4b{};

  Matrix3F defaultMatrix3f{};
  Matrix3D defaultMatrix3d{};
  Matrix3I defaultMatrix3i{};
  Matrix3U defaultMatrix3u{};
  Matrix3B defaultMatrix3b{};

  Matrix2F defaultMatrix2f{};
  Matrix2D defaultMatrix2d{};
  Matrix2I defaultMatrix2i{};
  Matrix2U defaultMatrix2u{};
  Matrix2B defaultMatrix2b{};

  EXPECT_EQ(defaultMatrix4f,
            (Matrix4F{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}));
  EXPECT_EQ(defaultMatrix4d,
            (Matrix4D{1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
                      0.0, 0.0, 0.0, 0.0, 1.0}));
  EXPECT_EQ(defaultMatrix4i,
            (Matrix4I{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}));
  EXPECT_EQ(defaultMatrix4u,
            (Matrix4U{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}));
  EXPECT_EQ(defaultMatrix4b,
            (Matrix4B{true, false, false, false, false, true, false, false,
                      false, false, true, false, false, false, false, true}));
  EXPECT_EQ(defaultMatrix3f,
            (Matrix3F{1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}));
  EXPECT_EQ(defaultMatrix3d,
            (Matrix3D{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}));
  EXPECT_EQ(defaultMatrix3i, (Matrix3I{1, 0, 0, 0, 1, 0, 0, 0, 1}));
  EXPECT_EQ(defaultMatrix3u, (Matrix3U{1, 0, 0, 0, 1, 0, 0, 0, 1}));
  EXPECT_EQ(defaultMatrix3b, (Matrix3B{true, false, false, false, true, false,
                                       false, false, true}));
  EXPECT_EQ(defaultMatrix2f, (Matrix2F{1.0f, 0.0f, 0.0f, 1.0f}));
  EXPECT_EQ(defaultMatrix2d, (Matrix2D{1.0, 0.0, 0.0, 1.0}));
  EXPECT_EQ(defaultMatrix2i, (Matrix2I{1, 0, 0, 1}));
  EXPECT_EQ(defaultMatrix2u, (Matrix2U{1, 0, 0, 1}));
  EXPECT_EQ(defaultMatrix2b, (Matrix2B{true, false, false, true}));
}

TEST_F(MatrixTest, SingleScalarConstructor) {
  Matrix4F scalarMatrix4f{1.0f};
  Matrix4D scalarMatrix4d{2.0};
  Matrix4I scalarMatrix4i{3};
  Matrix4U scalarMatrix4u{4};
  Matrix4B scalarMatrix4b{true};
  Matrix3B scalarMatrix3b{false};
  Matrix2B scalarMatrix2b{true};
  Matrix3F scalarMatrix3f{5.0f};
  Matrix3D scalarMatrix3d{6.0};
  Matrix3I scalarMatrix3i{7};
  Matrix3U scalarMatrix3u{8};
  Matrix2F scalarMatrix2f{9.0f};
  Matrix2D scalarMatrix2d{10.0};
  Matrix2I scalarMatrix2i{11};
  Matrix2U scalarMatrix2u{12};

  EXPECT_EQ(scalarMatrix4f,
            (Matrix4F{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}));
  EXPECT_EQ(scalarMatrix4d,
            (Matrix4D{2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0,
                      0.0f, 0.0, 0.0, 0.0, 2.0}));
  EXPECT_EQ(scalarMatrix4i,
            (Matrix4I{3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3}));
  EXPECT_EQ(scalarMatrix4u,
            (Matrix4U{4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4}));
  EXPECT_EQ(scalarMatrix4b,
            (Matrix4B{true, false, false, false, false, true, false, false,
                      false, false, true, false, false, false, false, true}));
  EXPECT_EQ(scalarMatrix3b, (Matrix3B{false, false, false, false, false, false,
                                      false, false, false}));
  EXPECT_EQ(scalarMatrix3f,
            (Matrix3F{5.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 5.0f}));
  EXPECT_EQ(scalarMatrix3d,
            (Matrix3D{6.0, 0.0, 0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 6.0}));
  EXPECT_EQ(scalarMatrix3i, (Matrix3I{7, 0, 0, 0, 7, 0, 0, 0, 7}));
  EXPECT_EQ(scalarMatrix3u, (Matrix3U{8, 0, 0, 0, 8, 0, 0, 0, 8}));
  EXPECT_EQ(scalarMatrix2f, (Matrix2F{9.0f, 0.0f, 0.0f, 9.0f}));
  EXPECT_EQ(scalarMatrix2d, (Matrix2D{10.0, 0.0, 0.0, 10.0}));
  EXPECT_EQ(scalarMatrix2i, (Matrix2I{11, 0, 0, 11}));
  EXPECT_EQ(scalarMatrix2u, (Matrix2U{12, 0, 0, 12}));
  EXPECT_EQ(scalarMatrix2b, (Matrix2B{true, false, false, true}));
}

TEST_F(MatrixTest, STDArrayConstructor) {
  std::array array4f = {1.0f, 2.0f,  3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,
                        9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
  Matrix4F matrix4f(array4f);
  std::array array4d = {1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                        9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};
  Matrix4D matrix4d(array4d);
  std::array<int, 16> array4i = {1, 2,  3,  4,  5,  6,  7,  8,
                                 9, 10, 11, 12, 13, 14, 15, 16};
  Matrix4I matrix4i(array4i);
  std::array<unsigned int, 16> array4u = {1, 2,  3,  4,  5,  6,  7,  8,
                                          9, 10, 11, 12, 13, 14, 15, 16};
  Matrix4U matrix4u(array4u);
  std::array<bool, 16> array4b = {true, false, true, false, true, false,
                                  true, false, true, false, true, false,
                                  true, false, true, false};
  Matrix4B matrix4b(array4b);
  Matrix3F matrix3f(
      std::array{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f});
  Matrix3D matrix3d(std::array{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
  Matrix3I matrix3i(std::array{1, 2, 3, 4, 5, 6, 7, 8, 9});
  Matrix3U matrix3u(std::array{1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U});
  Matrix3B matrix3b(
      std::array{true, false, true, false, true, false, true, false, true});
  Matrix2F matrix2f(std::array{1.0f, 2.0f, 3.0f, 4.0f});
  Matrix2D matrix2d(std::array{1.0, 2.0, 3.0, 4.0});
  Matrix2I matrix2i(std::array{1, 2, 3, 4});
  Matrix2U matrix2u(std::array{1U, 2U, 3U, 4U});
  Matrix2B matrix2b(std::array{true, false, true, false});

  EXPECT_EQ(matrix4f,
            (Matrix4F{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f,
                      10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f}));
  EXPECT_EQ(matrix4d,
            (Matrix4D{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0f, 11.0f,
                      12.0f, 13.0f, 14.0f, 15.0f, 16.0f}));
  EXPECT_EQ(matrix4i,
            (Matrix4I{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));
  EXPECT_EQ(matrix4u,
            (Matrix4U{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));
  EXPECT_EQ(matrix4b,
            (Matrix4B{true, false, true, false, true, false, true, false, true,
                      false, true, false, true, false, true, false}));
  EXPECT_EQ(matrix3f,
            (Matrix3F{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f}));
  EXPECT_EQ(matrix3d, (Matrix3D{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}));
  EXPECT_EQ(matrix3i, (Matrix3I{1, 2, 3, 4, 5, 6, 7, 8, 9}));
  EXPECT_EQ(matrix3u, (Matrix3U{1, 2, 3, 4, 5, 6, 7, 8, 9}));
  EXPECT_EQ(matrix3b, (Matrix3B{true, false, true, false, true, false, true,
                                false, true}));
  EXPECT_EQ(matrix2f, (Matrix2F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(matrix2d, (Matrix2D{1.0, 2.0, 3.0, 4.0}));
  EXPECT_EQ(matrix2i, (Matrix2I{1, 2, 3, 4}));
  EXPECT_EQ(matrix2u, (Matrix2U{1, 2, 3, 4}));
  EXPECT_EQ(matrix2b, (Matrix2B{true, false, true, false}));
}

TEST_F(MatrixTest, CopyConstructor) {
  Matrix4F originalMatrix4f{1.0f,  2.0f,  3.0f,  4.0f,  5.0f,  6.0f,
                            7.0f,  8.0f,  9.0f,  10.0f, 11.0f, 12.0f,
                            13.0f, 14.0f, 15.0f, 16.0f};
  Matrix4F copiedMatrix4f{originalMatrix4f};
  Matrix4D originalMatrix4d{1.0,   2.0,   3.0,   4.0,  5.0,   6.0,
                            7.0,   8.0,   9.0,   10.0, 11.0f, 12.0f,
                            13.0f, 14.0f, 15.0f, 16.0f};
  Matrix4D copiedMatrix4d{originalMatrix4d};
  Matrix4I originalMatrix4i{1, 2,  3,  4,  5,  6,  7,  8,
                            9, 10, 11, 12, 13, 14, 15, 16};
  Matrix4I copiedMatrix4i{originalMatrix4i};
  Matrix4U originalMatrix4u{1, 2,  3,  4,  5,  6,  7,  8,
                            9, 10, 11, 12, 13, 14, 15, 16};
  Matrix4U copiedMatrix4u{originalMatrix4u};
  Matrix3D originalMatrix3d{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  Matrix3D copiedMatrix3d{originalMatrix3d};
  Matrix3U originalMatrix3u{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix3U copiedMatrix3u{originalMatrix3u};
  Matrix3F originalMatrix3f{1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                            6.0f, 7.0f, 8.0f, 9.0f};
  Matrix3F copiedMatrix3f{originalMatrix3f};
  Matrix3I originalMatrix3i{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix3I copiedMatrix3i{originalMatrix3i};
  Matrix2D originalMatrix2d{1.0, 2.0, 3.0, 4.0};
  Matrix2D copiedMatrix2d{originalMatrix2d};
  Matrix2U originalMatrix2u{1, 2, 3, 4};
  Matrix2U copiedMatrix2u{originalMatrix2u};
  Matrix2F originalMatrix2f{1.0f, 2.0f, 3.0f, 4.0f};
  Matrix2F copiedMatrix2f{originalMatrix2f};
  Matrix2I originalMatrix2i{1, 2, 3, 4};
  Matrix2I copiedMatrix2i{originalMatrix2i};

  EXPECT_EQ(copiedMatrix4d, originalMatrix4d);
  EXPECT_EQ(copiedMatrix4i, originalMatrix4i);
  EXPECT_EQ(copiedMatrix4u, originalMatrix4u);
  EXPECT_EQ(copiedMatrix3d, originalMatrix3d);
  EXPECT_EQ(copiedMatrix3u, originalMatrix3u);
  EXPECT_EQ(copiedMatrix3f, originalMatrix3f);
  EXPECT_EQ(copiedMatrix3i, originalMatrix3i);
  EXPECT_EQ(copiedMatrix2d, originalMatrix2d);
  EXPECT_EQ(copiedMatrix2u, originalMatrix2u);
  EXPECT_EQ(copiedMatrix2f, originalMatrix2f);
  EXPECT_EQ(copiedMatrix2i, originalMatrix2i);
}
}  // namespace Neat