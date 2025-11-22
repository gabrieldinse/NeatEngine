#include <algorithm>

#include <gtest/gtest.h>

#include <Math/Matrix.hpp>

#include "Math/Types/Matrix2x2.hpp"

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

TEST_F(MatrixTest, MatrixSizes) {
  EXPECT_EQ(Matrix4F::M, 4);
  EXPECT_EQ(Matrix4F::N, 4);
  EXPECT_EQ(Matrix4F::Size, 16);

  EXPECT_EQ(Matrix4D::M, 4);
  EXPECT_EQ(Matrix4D::N, 4);
  EXPECT_EQ(Matrix4D::Size, 16);

  EXPECT_EQ(Matrix4I::M, 4);
  EXPECT_EQ(Matrix4I::N, 4);
  EXPECT_EQ(Matrix4I::Size, 16);

  EXPECT_EQ(Matrix4U::M, 4);
  EXPECT_EQ(Matrix4U::N, 4);
  EXPECT_EQ(Matrix4U::Size, 16);

  EXPECT_EQ(Matrix3F::M, 3);
  EXPECT_EQ(Matrix3F::N, 3);
  EXPECT_EQ(Matrix3F::Size, 9);

  EXPECT_EQ(Matrix3D::M, 3);
  EXPECT_EQ(Matrix3D::N, 3);
  EXPECT_EQ(Matrix3D::Size, 9);

  EXPECT_EQ(Matrix3I::M, 3);
  EXPECT_EQ(Matrix3I::N, 3);
  EXPECT_EQ(Matrix3I::Size, 9);

  EXPECT_EQ(Matrix3U::M, 3);
  EXPECT_EQ(Matrix3U::N, 3);
  EXPECT_EQ(Matrix3U::Size, 9);

  EXPECT_EQ(Matrix2F::M, 2);
  EXPECT_EQ(Matrix2F::N, 2);
  EXPECT_EQ(Matrix2F::Size, 4);

  EXPECT_EQ(Matrix2D::M, 2);
  EXPECT_EQ(Matrix2D::N, 2);
  EXPECT_EQ(Matrix2D::Size, 4);

  EXPECT_EQ(Matrix2I::M, 2);
  EXPECT_EQ(Matrix2I::N, 2);
  EXPECT_EQ(Matrix2I::Size, 4);

  EXPECT_EQ(Matrix2U::M, 2);
  EXPECT_EQ(Matrix2U::N, 2);
  EXPECT_EQ(Matrix2U::Size, 4);
}

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

TEST_F(MatrixTest, CallOperator) {
  EXPECT_EQ(matrix4f(0), 1.0f);
  EXPECT_EQ(matrix4d(0), 1.0);
  EXPECT_EQ(matrix4i(0), 1);
  EXPECT_EQ(matrix4u(0), 1);
  EXPECT_EQ(matrix4b(0), true);
  EXPECT_EQ(matrix3f(0), 1.0f);
  EXPECT_EQ(matrix3d(0), 1.0);
  EXPECT_EQ(matrix3i(0), 1);
  EXPECT_EQ(matrix3u(0), 1);
  EXPECT_EQ(matrix3b(0), true);
  EXPECT_EQ(matrix2f(0), 1.0f);
  EXPECT_EQ(matrix2d(0), 1.0);
  EXPECT_EQ(matrix2i(0), 1);
  EXPECT_EQ(matrix2u(0), 1);
  EXPECT_EQ(matrix2b(0), true);

  EXPECT_EQ(matrix4f(1), 2.0f);
  EXPECT_EQ(matrix4d(1), 2.0);
  EXPECT_EQ(matrix4i(1), 2);
  EXPECT_EQ(matrix4u(1), 2);
  EXPECT_EQ(matrix4b(1), false);
  EXPECT_EQ(matrix3f(1), 2.0f);
  EXPECT_EQ(matrix3d(1), 2.0);
  EXPECT_EQ(matrix3i(1), 2);
  EXPECT_EQ(matrix3u(1), 2);
  EXPECT_EQ(matrix3b(1), false);
  EXPECT_EQ(matrix2f(1), 2.0f);
  EXPECT_EQ(matrix2d(1), 2.0);
  EXPECT_EQ(matrix2i(1), 2);
  EXPECT_EQ(matrix2u(1), 2);
  EXPECT_EQ(matrix2b(1), false);

  EXPECT_EQ(matrix4f(2), 3.0f);
  EXPECT_EQ(matrix4d(2), 3.0);
  EXPECT_EQ(matrix4i(2), 3);
  EXPECT_EQ(matrix4u(2), 3);
  EXPECT_EQ(matrix4b(2), true);
  EXPECT_EQ(matrix3f(2), 3.0f);
  EXPECT_EQ(matrix3d(2), 3.0);
  EXPECT_EQ(matrix3i(2), 3);
  EXPECT_EQ(matrix3u(2), 3);
  EXPECT_EQ(matrix3b(2), true);
  EXPECT_EQ(matrix2f(2), 3.0f);
  EXPECT_EQ(matrix2d(2), 3.0);
  EXPECT_EQ(matrix2i(2), 3);
  EXPECT_EQ(matrix2u(2), 3);
  EXPECT_EQ(matrix2b(2), true);

  EXPECT_EQ(matrix4f(3), 4.0f);
  EXPECT_EQ(matrix4d(3), 4.0);
  EXPECT_EQ(matrix4i(3), 4);
  EXPECT_EQ(matrix4u(3), 4);
  EXPECT_EQ(matrix4b(3), false);
  EXPECT_EQ(matrix3f(3), 4.0f);
  EXPECT_EQ(matrix3d(3), 4.0);
  EXPECT_EQ(matrix3i(3), 4);
  EXPECT_EQ(matrix3u(3), 4);
  EXPECT_EQ(matrix3b(3), false);
  EXPECT_EQ(matrix2f(3), 4.0f);
  EXPECT_EQ(matrix2d(3), 4.0);
  EXPECT_EQ(matrix2i(3), 4);
  EXPECT_EQ(matrix2u(3), 4);
  EXPECT_EQ(matrix2b(3), false);

  EXPECT_EQ(matrix4f(4), 5.0f);
  EXPECT_EQ(matrix4d(4), 5.0);
  EXPECT_EQ(matrix4i(4), 5);
  EXPECT_EQ(matrix4u(4), 5);
  EXPECT_EQ(matrix4b(4), true);
  EXPECT_EQ(matrix3f(4), 5.0f);
  EXPECT_EQ(matrix3d(4), 5.0);
  EXPECT_EQ(matrix3i(4), 5);
  EXPECT_EQ(matrix3u(4), 5);
  EXPECT_EQ(matrix3b(4), true);

  EXPECT_EQ(matrix4f(5), 6.0f);
  EXPECT_EQ(matrix4d(5), 6.0);
  EXPECT_EQ(matrix4i(5), 6);
  EXPECT_EQ(matrix4u(5), 6);
  EXPECT_EQ(matrix4b(5), false);
  EXPECT_EQ(matrix3f(5), 6.0f);
  EXPECT_EQ(matrix3d(5), 6.0);
  EXPECT_EQ(matrix3i(5), 6);
  EXPECT_EQ(matrix3u(5), 6);
  EXPECT_EQ(matrix3b(5), false);

  EXPECT_EQ(matrix4f(6), 7.0f);
  EXPECT_EQ(matrix4d(6), 7.0);
  EXPECT_EQ(matrix4i(6), 7);
  EXPECT_EQ(matrix4u(6), 7);
  EXPECT_EQ(matrix4b(6), true);
  EXPECT_EQ(matrix3f(6), 7.0f);
  EXPECT_EQ(matrix3d(6), 7.0);
  EXPECT_EQ(matrix3i(6), 7);
  EXPECT_EQ(matrix3u(6), 7);
  EXPECT_EQ(matrix3b(6), true);

  EXPECT_EQ(matrix4f(7), 8.0f);
  EXPECT_EQ(matrix4d(7), 8.0);
  EXPECT_EQ(matrix4i(7), 8);
  EXPECT_EQ(matrix4u(7), 8);
  EXPECT_EQ(matrix4b(7), false);
  EXPECT_EQ(matrix3f(7), 8.0f);
  EXPECT_EQ(matrix3d(7), 8.0);
  EXPECT_EQ(matrix3i(7), 8);
  EXPECT_EQ(matrix3u(7), 8);
  EXPECT_EQ(matrix3b(7), false);

  EXPECT_EQ(matrix4f(8), 9.0f);
  EXPECT_EQ(matrix4d(8), 9.0);
  EXPECT_EQ(matrix4i(8), 9);
  EXPECT_EQ(matrix4u(8), 9);
  EXPECT_EQ(matrix4b(8), true);
  EXPECT_EQ(matrix3f(8), 9.0f);
  EXPECT_EQ(matrix3d(8), 9.0);
  EXPECT_EQ(matrix3i(8), 9);
  EXPECT_EQ(matrix3u(8), 9);
  EXPECT_EQ(matrix3b(8), true);

  EXPECT_EQ(matrix4f(9), 10.0f);
  EXPECT_EQ(matrix4d(9), 10.0);
  EXPECT_EQ(matrix4i(9), 10);
  EXPECT_EQ(matrix4u(9), 10);
  EXPECT_EQ(matrix4b(9), false);

  EXPECT_EQ(matrix4f(10), 11.0f);
  EXPECT_EQ(matrix4d(10), 11.0);
  EXPECT_EQ(matrix4i(10), 11);
  EXPECT_EQ(matrix4u(10), 11);
  EXPECT_EQ(matrix4b(10), true);

  EXPECT_EQ(matrix4f(11), 12.0f);
  EXPECT_EQ(matrix4d(11), 12.0);
  EXPECT_EQ(matrix4i(11), 12);
  EXPECT_EQ(matrix4u(11), 12);
  EXPECT_EQ(matrix4b(11), false);

  EXPECT_EQ(matrix4f(12), 13.0f);
  EXPECT_EQ(matrix4d(12), 13.0);
  EXPECT_EQ(matrix4i(12), 13);
  EXPECT_EQ(matrix4u(12), 13);
  EXPECT_EQ(matrix4b(12), true);

  EXPECT_EQ(matrix4f(13), 14.0f);
  EXPECT_EQ(matrix4d(13), 14.0);
  EXPECT_EQ(matrix4i(13), 14);
  EXPECT_EQ(matrix4u(13), 14);
  EXPECT_EQ(matrix4b(13), false);

  EXPECT_EQ(matrix4f(14), 15.0f);
  EXPECT_EQ(matrix4d(14), 15.0);
  EXPECT_EQ(matrix4i(14), 15);
  EXPECT_EQ(matrix4u(14), 15);
  EXPECT_EQ(matrix4b(14), true);

  EXPECT_EQ(matrix4f(15), 16.0f);
  EXPECT_EQ(matrix4d(15), 16.0);
  EXPECT_EQ(matrix4i(15), 16);
  EXPECT_EQ(matrix4u(15), 16);
  EXPECT_EQ(matrix4b(15), false);

  // Assignment tests
  matrix4f(10) = 42.0f;
  EXPECT_EQ(matrix4f(10), 42.0f);
  matrix4d(5) = 3.14;
  EXPECT_EQ(matrix4d(5), 3.14);
  matrix4i(0) = 99;
  EXPECT_EQ(matrix4i(0), 99);
  matrix4u(12) = 77;
  EXPECT_EQ(matrix4u(12), 77);
  matrix4b(7) = true;
  EXPECT_EQ(matrix4b(7), true);
  matrix3f(4) = 24.0f;
  EXPECT_EQ(matrix3f(4), 24.0f);
  matrix3d(8) = 6.28;
  EXPECT_EQ(matrix3d(8), 6.28);
  matrix3i(2) = 88;
  EXPECT_EQ(matrix3i(2), 88);
  matrix3u(6) = 55;
  EXPECT_EQ(matrix3u(6), 55);
  matrix3b(3) = true;
  EXPECT_EQ(matrix3b(3), true);
  matrix2f(2) = 11.0f;
  EXPECT_EQ(matrix2f(2), 11.0f);
  matrix2d(1) = 22.0;
  EXPECT_EQ(matrix2d(1), 22.0);
  matrix2i(3) = 33;
  EXPECT_EQ(matrix2i(3), 33);
  matrix2u(0) = 44;
  EXPECT_EQ(matrix2u(0), 44);
  matrix2b(2) = false;
  EXPECT_EQ(matrix2b(2), false);
}

TEST_F(MatrixTest, IndexOperator) {
  EXPECT_TRUE(std::ranges::equal(matrix4f[0],
                                 std::array<Float, 4>{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_TRUE(std::ranges::equal(matrix4f[1],
                                 std::array<Float, 4>{5.0f, 6.0f, 7.0f, 8.0f}));
  EXPECT_TRUE(std::ranges::equal(
      matrix4f[2], std::array<Float, 4>{9.0f, 10.0f, 11.0f, 12.0f}));
  EXPECT_TRUE(std::ranges::equal(
      matrix4f[3], std::array<Float, 4>{13.0f, 14.0f, 15.0f, 16.0f}));
  EXPECT_TRUE(std::ranges::equal(matrix4d[0],
                                 std::array<Double, 4>{1.0, 2.0, 3.0, 4.0}));
  EXPECT_TRUE(std::ranges::equal(matrix4d[1],
                                 std::array<Double, 4>{5.0, 6.0, 7.0, 8.0}));
  EXPECT_TRUE(std::ranges::equal(matrix4d[2],
                                 std::array<Double, 4>{9.0, 10.0, 11.0, 12.0}));
  EXPECT_TRUE(std::ranges::equal(
      matrix4d[3], std::array<Double, 4>{13.0, 14.0, 15.0, 16.0}));
  EXPECT_TRUE(
      std::ranges::equal(matrix4i[0], std::array<Int32, 4>{1, 2, 3, 4}));
  EXPECT_TRUE(
      std::ranges::equal(matrix4i[1], std::array<Int32, 4>{5, 6, 7, 8}));
  EXPECT_TRUE(
      std::ranges::equal(matrix4i[2], std::array<Int32, 4>{9, 10, 11, 12}));
  EXPECT_TRUE(
      std::ranges::equal(matrix4i[3], std::array<Int32, 4>{13, 14, 15, 16}));
  EXPECT_TRUE(
      std::ranges::equal(matrix4u[0], std::array<UInt32, 4>{1, 2, 3, 4}));
  EXPECT_TRUE(
      std::ranges::equal(matrix4u[1], std::array<UInt32, 4>{5, 6, 7, 8}));
  EXPECT_TRUE(
      std::ranges::equal(matrix4u[2], std::array<UInt32, 4>{9, 10, 11, 12}));
  EXPECT_TRUE(
      std::ranges::equal(matrix4u[3], std::array<UInt32, 4>{13, 14, 15, 16}));

  EXPECT_TRUE(
      std::ranges::equal(matrix3f[0], std::array<Float, 3>{1.0f, 2.0f, 3.0f}));
  EXPECT_TRUE(
      std::ranges::equal(matrix3f[1], std::array<Float, 3>{4.0f, 5.0f, 6.0f}));
  EXPECT_TRUE(
      std::ranges::equal(matrix3f[2], std::array<Float, 3>{7.0f, 8.0f, 9.0f}));
  EXPECT_TRUE(
      std::ranges::equal(matrix3d[0], std::array<Double, 3>{1.0, 2.0, 3.0}));
  EXPECT_TRUE(
      std::ranges::equal(matrix3d[1], std::array<Double, 3>{4.0, 5.0, 6.0}));
  EXPECT_TRUE(
      std::ranges::equal(matrix3d[2], std::array<Double, 3>{7.0, 8.0, 9.0}));
  EXPECT_TRUE(std::ranges::equal(matrix3i[0], std::array<Int32, 3>{1, 2, 3}));
  EXPECT_TRUE(std::ranges::equal(matrix3i[1], std::array<Int32, 3>{4, 5, 6}));
  EXPECT_TRUE(std::ranges::equal(matrix3i[2], std::array<Int32, 3>{7, 8, 9}));
  EXPECT_TRUE(std::ranges::equal(matrix3u[0], std::array<UInt32, 3>{1, 2, 3}));
  EXPECT_TRUE(std::ranges::equal(matrix3u[1], std::array<UInt32, 3>{4, 5, 6}));
  EXPECT_TRUE(std::ranges::equal(matrix3u[2], std::array<UInt32, 3>{7, 8, 9}));

  EXPECT_TRUE(
      std::ranges::equal(matrix2f[0], std::array<Float, 2>{1.0f, 2.0f}));
  EXPECT_TRUE(
      std::ranges::equal(matrix2f[1], std::array<Float, 2>{3.0f, 4.0f}));
  EXPECT_TRUE(std::ranges::equal(matrix2d[0], std::array<Double, 2>{1.0, 2.0}));
  EXPECT_TRUE(std::ranges::equal(matrix2d[1], std::array<Double, 2>{3.0, 4.0}));
  EXPECT_TRUE(std::ranges::equal(matrix2i[0], std::array<Int32, 2>{1, 2}));
  EXPECT_TRUE(std::ranges::equal(matrix2i[1], std::array<Int32, 2>{3, 4}));
  EXPECT_TRUE(std::ranges::equal(matrix2u[0], std::array<UInt32, 2>{1, 2}));
  EXPECT_TRUE(std::ranges::equal(matrix2u[1], std::array<UInt32, 2>{3, 4}));
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

TEST_F(MatrixTest, MultipleScalarsConversionConstructor) {
  Matrix4D matrix4d{1, 2.0f,  3U,  4L,  5,  6.0f,  7U,  8L,
                    9, 10.0f, 11U, 12L, 13, 14.0f, 15U, 16L};
  Matrix4F matrix4f{1, 2.0,  3U,  4L,  5,  6.0,  7U,  8L,
                    9, 10.0, 11U, 12L, 13, 14.0, 15U, 16L};
  Matrix4I matrix4i{1L, 2.0f,  3U,  4,  5L,  6.0f,  7U,  8,
                    9L, 10.0f, 11U, 12, 13L, 14.0f, 15U, 16};
  Matrix4U matrix4u{1U, 2.0f,  3.0,  4L,  5U,  6.0f,  7.0,  8L,
                    9U, 10.0f, 11.0, 12L, 13U, 14.0f, 15.0, 16L};
  Matrix3F matrix3f{1, 2.0, 3U, 4L, 5, 6.0, 7U, 8L, 9};
  Matrix3D matrix3d{1, 2.0f, 3U, 4L, 5, 6.0f, 7U, 8L, 9};
  Matrix3I matrix3i{1L, 2.0f, 3U, 4, 5L, 6.0f, 7U, 8, 9L};
  Matrix3U matrix3u{1U, 2.0f, 3.0, 4L, 5U, 6.0f, 7.0, 8L, 9U};
  Matrix2D matrix2d{1, 2.0f, 3U, 4L};
  Matrix2F matrix2f{1, 2.0, 3U, 4L};
  Matrix2I matrix2i{1L, 2.0f, 3U, 4};
  Matrix2U matrix2u{1U, 2.0f, 3.0, 4L};

  EXPECT_EQ(matrix4d, (Matrix4D{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
                                10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0}));
  EXPECT_EQ(matrix4f,
            (Matrix4F{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f,
                      10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f}));
  EXPECT_EQ(matrix4i,
            (Matrix4D{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));
  EXPECT_EQ(matrix4u,
            (Matrix4U{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));
  EXPECT_EQ(matrix3f,
            (Matrix3F{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f}));
  EXPECT_EQ(matrix3d, (Matrix3D{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}));
  EXPECT_EQ(matrix3i, (Matrix3I{1, 2, 3, 4, 5, 6, 7, 8, 9}));
  EXPECT_EQ(matrix3u, (Matrix3U{1, 2, 3, 4, 5, 6, 7, 8, 9}));
  EXPECT_EQ(matrix2d, (Matrix2D{1.0, 2.0, 3.0, 4.0}));
  EXPECT_EQ(matrix2f, (Matrix2F{1.0f, 2.0f, 3.0f, 4.0f}));
  EXPECT_EQ(matrix2i, (Matrix2I{1, 2, 3, 4}));
  EXPECT_EQ(matrix2u, (Matrix2U{1, 2, 3, 4}));
}

TEST_F(MatrixTest, SameDimensionConversionConstructor) {
  Matrix4F customMatrix4f{1.0f,  2.0f,  3.0f,  4.0f,  5.0f,  6.0f,
                          7.0f,  8.0f,  9.0f,  10.0f, 11.0f, 12.0f,
                          13.0f, 14.0f, 15.0f, 16.0f};
  Matrix4D customMatrix4d{1.0, 2.0,  3.0,   4.0,   5.0,   6.0,   7.0,   8.0,
                          9.0, 10.0, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
  Matrix3F customMatrix3f{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  Matrix3D customMatrix3d{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  Matrix2F customMatrix2f{1.0f, 2.0f, 3.0f, 4.0f};
  Matrix2D customMatrix2d{1.0, 2.0, 3.0, 4.0};
  Matrix4I customMatrix4i{1, 2,  3,  4,  5,  6,  7,  8,
                          9, 10, 11, 12, 13, 14, 15, 16};
  Matrix3I customMatrix3i{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix2I customMatrix2i{1, 2, 3, 4};
  Matrix4U customMatrix4u{1, 2,  3,  4,  5,  6,  7,  8,
                          9, 10, 11, 12, 13, 14, 15, 16};
  Matrix3U customMatrix3u{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix2U customMatrix2u{1, 2, 3, 4};

  EXPECT_EQ(Matrix4D{customMatrix4f}, customMatrix4d);
  EXPECT_EQ(Matrix4D{customMatrix4u}, customMatrix4d);
  EXPECT_EQ(Matrix4D{customMatrix4i}, customMatrix4d);

  EXPECT_EQ(Matrix4F{customMatrix4d}, customMatrix4f);
  EXPECT_EQ(Matrix4F{customMatrix4i}, customMatrix4f);
  EXPECT_EQ(Matrix4F{customMatrix4u}, customMatrix4f);

  EXPECT_EQ(Matrix3D{customMatrix3f}, customMatrix3d);
  EXPECT_EQ(Matrix3D{customMatrix3u}, customMatrix3d);
  EXPECT_EQ(Matrix3D{customMatrix3i}, customMatrix3d);

  EXPECT_EQ(Matrix4U{customMatrix4d}, customMatrix4u);
  EXPECT_EQ(Matrix4U{customMatrix4f}, customMatrix4u);
  EXPECT_EQ(Matrix4U{customMatrix4i}, customMatrix4u);

  EXPECT_EQ(Matrix4I{customMatrix4f}, customMatrix4i);
  EXPECT_EQ(Matrix4I{customMatrix4u}, customMatrix4i);
  EXPECT_EQ(Matrix4I{customMatrix4d}, customMatrix4i);

  EXPECT_EQ(Matrix3F{customMatrix3d}, customMatrix3f);
  EXPECT_EQ(Matrix3F{customMatrix3i}, customMatrix3f);
  EXPECT_EQ(Matrix3F{customMatrix3u}, customMatrix3f);

  EXPECT_EQ(Matrix3I{customMatrix3f}, customMatrix3i);
  EXPECT_EQ(Matrix3I{customMatrix3u}, customMatrix3i);
  EXPECT_EQ(Matrix3I{customMatrix3d}, customMatrix3i);

  EXPECT_EQ(Matrix3U{customMatrix3i}, customMatrix3u);
  EXPECT_EQ(Matrix3U{customMatrix3f}, customMatrix3u);
  EXPECT_EQ(Matrix3U{customMatrix3d}, customMatrix3u);

  EXPECT_EQ(Matrix2D{customMatrix2f}, customMatrix2d);
  EXPECT_EQ(Matrix2D{customMatrix2u}, customMatrix2d);
  EXPECT_EQ(Matrix2D{customMatrix2i}, customMatrix2d);

  EXPECT_EQ(Matrix2F{customMatrix2d}, customMatrix2f);
  EXPECT_EQ(Matrix2F{customMatrix2i}, customMatrix2f);
  EXPECT_EQ(Matrix2F{customMatrix2u}, customMatrix2f);

  EXPECT_EQ(Matrix2I{customMatrix2f}, customMatrix2i);
  EXPECT_EQ(Matrix2I{customMatrix2u}, customMatrix2i);
  EXPECT_EQ(Matrix2I{customMatrix2d}, customMatrix2i);

  EXPECT_EQ(Matrix2U{customMatrix2f}, customMatrix2u);
  EXPECT_EQ(Matrix2U{customMatrix2i}, customMatrix2u);
  EXPECT_EQ(Matrix2U{customMatrix2d}, customMatrix2u);
}

TEST_F(MatrixTest, DifferentDimensionsConversionConstructor) {
  Matrix4F customMatrix4f{1.0f,  2.0f,  3.0f,  4.0f,  5.0f,  6.0f,
                          7.0f,  8.0f,  9.0f,  10.0f, 11.0f, 12.0f,
                          13.0f, 14.0f, 15.0f, 16.0f};
  Matrix4D customMatrix4d{1.0, 2.0,  3.0,   4.0,   5.0,   6.0,   7.0,   8.0,
                          9.0, 10.0, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
  Matrix3F customMatrix3f{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  Matrix3D customMatrix3d{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  Matrix2F customMatrix2f{1.0f, 2.0f, 3.0f, 4.0f};
  Matrix2D customMatrix2d{1.0, 2.0, 3.0, 4.0};
  Matrix4I customMatrix4i{1, 2,  3,  4,  5,  6,  7,  8,
                          9, 10, 11, 12, 13, 14, 15, 16};
  Matrix3I customMatrix3i{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix2I customMatrix2i{1, 2, 3, 4};
  Matrix4U customMatrix4u{1, 2,  3,  4,  5,  6,  7,  8,
                          9, 10, 11, 12, 13, 14, 15, 16};
  Matrix3U customMatrix3u{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix2U customMatrix2u{1, 2, 3, 4};

  Matrix4F matrix4From3f{1.0f, 2.0f, 3.0f, 0.0f, 4.0f, 5.0f, 6.0f, 0.0f,
                         7.0f, 8.0f, 9.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  Matrix4F matrix4From2f{1.0f, 2.0f, 0.0f, 0.0f, 3.0f, 4.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  Matrix4D matrix4From3D{1.0, 2.0, 3.0, 0.0, 4.0, 5.0, 6.0, 0.0,
                         7.0, 8.0, 9.0, 0.0, 0.0, 0.0, 0.0, 1.0};
  Matrix4D matrix4From2D{1.0, 2.0, 0.0, 0.0, 3.0, 4.0, 0.0, 0.0,
                         0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
  Matrix4U matrix4From3U{1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0, 0, 0, 0, 1};
  Matrix4U matrix4From2U{1, 2, 0, 0, 3, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  Matrix4I matrix4From3I{1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0, 0, 0, 0, 1};
  Matrix4I matrix4From2I{1, 2, 0, 0, 3, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

  Matrix3F matrix3From2f{1.0f, 2.0f, 0.0f, 3.0f, 4.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  Matrix3D matrix3From2d{1.0, 2.0, 0.0, 3.0, 4.0, 0.0, 0.0, 0.0, 1.0};
  Matrix3U matrix3From2u{1, 2, 0, 3, 4, 0, 0, 0, 1};
  Matrix3I matrix3From2i{1, 2, 0, 3, 4, 0, 0, 0, 1};
  Matrix3F matrix3From4f{1.0f, 2.0f, 3.0f,  5.0f, 6.0f,
                         7.0f, 9.0f, 10.0f, 11.0f};
  Matrix3D matrix3From4d{1.0, 2.0, 3.0, 5.0, 6.0, 7.0, 9.0, 10.0, 11.0};
  Matrix3U matrix3From4u{1, 2, 3, 5, 6, 7, 9, 10, 11};
  Matrix3I matrix3From4i{1, 2, 3, 5, 6, 7, 9, 10, 11};
  Matrix2F matrix2From3f{1.0f, 2.0f, 4.0f, 5.0f};
  Matrix2D matrix2From3d{1.0, 2.0, 4.0, 5.0};
  Matrix2U matrix2From3u{1, 2, 4, 5};
  Matrix2I matrix2From3i{1, 2, 4, 5};
  Matrix2F matrix2From4f{1.0f, 2.0f, 5.0f, 6.0f};
  Matrix2D matrix2From4d{1.0, 2.0, 5.0, 6.0};
  Matrix2U matrix2From4u{1, 2, 5, 6};
  Matrix2I matrix2From4i{1, 2, 5, 6};

  EXPECT_EQ(Matrix4D{customMatrix3f}, matrix4From3D);
  EXPECT_EQ(Matrix4D{customMatrix2f}, matrix4From2D);
  EXPECT_EQ(Matrix4D{customMatrix3u}, matrix4From3U);
  EXPECT_EQ(Matrix4D{customMatrix2u}, matrix4From2U);
  EXPECT_EQ(Matrix4D{customMatrix3i}, matrix4From3I);
  EXPECT_EQ(Matrix4D{customMatrix2i}, matrix4From2I);
  EXPECT_EQ(Matrix4F{customMatrix3d}, matrix4From3f);
  EXPECT_EQ(Matrix4F{customMatrix2d}, matrix4From2f);
  EXPECT_EQ(Matrix4F{customMatrix3u}, matrix4From3U);
  EXPECT_EQ(Matrix4F{customMatrix2u}, matrix4From2U);
  EXPECT_EQ(Matrix4F{customMatrix3i}, matrix4From3I);
  EXPECT_EQ(Matrix4F{customMatrix2i}, matrix4From2I);
  EXPECT_EQ(Matrix4U{customMatrix3d}, matrix4From3U);
  EXPECT_EQ(Matrix4U{customMatrix2d}, matrix4From2U);
  EXPECT_EQ(Matrix4U{customMatrix3f}, matrix4From3U);
  EXPECT_EQ(Matrix4U{customMatrix2f}, matrix4From2U);
  EXPECT_EQ(Matrix4U{customMatrix3i}, matrix4From3U);
  EXPECT_EQ(Matrix4U{customMatrix2i}, matrix4From2U);
  EXPECT_EQ(Matrix4I{customMatrix3d}, matrix4From3I);
  EXPECT_EQ(Matrix4I{customMatrix2d}, matrix4From2I);
  EXPECT_EQ(Matrix4I{customMatrix3f}, matrix4From3I);
  EXPECT_EQ(Matrix4I{customMatrix2f}, matrix4From2I);
  EXPECT_EQ(Matrix4I{customMatrix3u}, matrix4From3I);
  EXPECT_EQ(Matrix4I{customMatrix2u}, matrix4From2I);

  EXPECT_EQ(Matrix3D{customMatrix4f}, matrix3From4d);
  EXPECT_EQ(Matrix3D{customMatrix4u}, matrix3From4u);
  EXPECT_EQ(Matrix3D{customMatrix4i}, matrix3From4i);
  EXPECT_EQ(Matrix3U{customMatrix4f}, matrix3From4u);
  EXPECT_EQ(Matrix3U{customMatrix4u}, matrix3From4u);
  EXPECT_EQ(Matrix3U{customMatrix4i}, matrix3From4u);
  EXPECT_EQ(Matrix3I{customMatrix4f}, matrix3From4i);
  EXPECT_EQ(Matrix3I{customMatrix4u}, matrix3From4i);
  EXPECT_EQ(Matrix3I{customMatrix4d}, matrix3From4i);
  EXPECT_EQ(Matrix3F{customMatrix4d}, matrix3From4f);
  EXPECT_EQ(Matrix3F{customMatrix4u}, matrix3From4f);
  EXPECT_EQ(Matrix3F{customMatrix4i}, matrix3From4f);
  EXPECT_EQ(Matrix3D{customMatrix2f}, matrix3From2d);
  EXPECT_EQ(Matrix3D{customMatrix2u}, matrix3From2u);
  EXPECT_EQ(Matrix3D{customMatrix2i}, matrix3From2i);
  EXPECT_EQ(Matrix3F{customMatrix2d}, matrix3From2f);
  EXPECT_EQ(Matrix3F{customMatrix2u}, matrix3From2u);
  EXPECT_EQ(Matrix3F{customMatrix2i}, matrix3From2i);
  EXPECT_EQ(Matrix3U{customMatrix2f}, matrix3From2u);
  EXPECT_EQ(Matrix3U{customMatrix2u}, matrix3From2u);
  EXPECT_EQ(Matrix3U{customMatrix2d}, matrix3From2u);
  EXPECT_EQ(Matrix3I{customMatrix2f}, matrix3From2i);
  EXPECT_EQ(Matrix3I{customMatrix2u}, matrix3From2i);
  EXPECT_EQ(Matrix3I{customMatrix2d}, matrix3From2i);

  EXPECT_EQ(Matrix2D{customMatrix4f}, matrix2From4d);
  EXPECT_EQ(Matrix2D{customMatrix4u}, matrix2From4u);
  EXPECT_EQ(Matrix2D{customMatrix4i}, matrix2From4i);
  EXPECT_EQ(Matrix2F{customMatrix3d}, matrix2From3f);
  EXPECT_EQ(Matrix2F{customMatrix3u}, matrix2From3u);
  EXPECT_EQ(Matrix2F{customMatrix3i}, matrix2From3i);
  EXPECT_EQ(Matrix2I{customMatrix4f}, matrix2From4i);
  EXPECT_EQ(Matrix2I{customMatrix4u}, matrix2From4i);
  EXPECT_EQ(Matrix2I{customMatrix4d}, matrix2From4i);
  EXPECT_EQ(Matrix2U{customMatrix4f}, matrix2From4u);
  EXPECT_EQ(Matrix2U{customMatrix4u}, matrix2From4u);
  EXPECT_EQ(Matrix2U{customMatrix4d}, matrix2From4u);
  EXPECT_EQ(Matrix2I{customMatrix3f}, matrix2From3i);
  EXPECT_EQ(Matrix2I{customMatrix3u}, matrix2From3i);
  EXPECT_EQ(Matrix2I{customMatrix3d}, matrix2From3i);
  EXPECT_EQ(Matrix2U{customMatrix3f}, matrix2From3u);
  EXPECT_EQ(Matrix2U{customMatrix3u}, matrix2From3u);
  EXPECT_EQ(Matrix2U{customMatrix3d}, matrix2From3u);
  EXPECT_EQ(Matrix2F{customMatrix3f}, matrix2From3f);
  EXPECT_EQ(Matrix2F{customMatrix3u}, matrix2From3f);
  EXPECT_EQ(Matrix2F{customMatrix3d}, matrix2From3f);
  EXPECT_EQ(Matrix2D{customMatrix3f}, matrix2From3d);
  EXPECT_EQ(Matrix2D{customMatrix3u}, matrix2From3d);
  EXPECT_EQ(Matrix2D{customMatrix3d}, matrix2From3d);
  EXPECT_EQ(Matrix2F{customMatrix4f}, matrix2From4f);
  EXPECT_EQ(Matrix2F{customMatrix4u}, matrix2From4f);
  EXPECT_EQ(Matrix2F{customMatrix4d}, matrix2From4f);
  EXPECT_EQ(Matrix2D{customMatrix4f}, matrix2From4d);
  EXPECT_EQ(Matrix2D{customMatrix4u}, matrix2From4d);
  EXPECT_EQ(Matrix2D{customMatrix4d}, matrix2From4d);
}

TEST_F(MatrixTest, FromVectorsConstructor) {
  Vector4F row1f{1.0f, 2.0f, 3.0f, 4.0f};
  Vector4F row2f{5.0f, 6.0f, 7.0f, 8.0f};
  Vector4F row3f{9.0f, 10.0f, 11.0f, 12.0f};
  Vector4F row4f{13.0f, 14.0f, 15.0f, 16.0f};
  Vector4D row1d{1.0, 2.0, 3.0, 4.0};
  Vector4D row2d{5.0, 6.0, 7.0, 8.0};
  Vector4D row3d{9.0, 10.0, 11.0, 12.0};
  Vector4D row4d{13.0, 14.0, 15.0, 16.0};
  Vector4I row1i{1, 2, 3, 4};
  Vector4I row2i{5, 6, 7, 8};
  Vector4I row3i{9, 10, 11, 12};
  Vector4I row4i{13, 14, 15, 16};
  Vector4U row1u{1, 2, 3, 4};
  Vector4U row2u{5, 6, 7, 8};
  Vector4U row3u{9, 10, 11, 12};
  Vector4U row4u{13, 14, 15, 16};
  Vector3F row1_3f{1.0f, 2.0f, 3.0f};
  Vector3F row2_3f{4.0f, 5.0f, 6.0f};
  Vector3F row3_3f{7.0f, 8.0f, 9.0f};
  Vector3D row1_3d{1.0, 2.0, 3.0};
  Vector3D row2_3d{4.0, 5.0, 6.0};
  Vector3D row3_3d{7.0, 8.0, 9.0};
  Vector3I row1_3i{1, 2, 3};
  Vector3I row2_3i{4, 5, 6};
  Vector3I row3_3i{7, 8, 9};
  Vector3U row1_3u{1, 2, 3};
  Vector3U row2_3u{4, 5, 6};
  Vector3U row3_3u{7, 8, 9};
  Vector2F row1_2f{1.0f, 2.0f};
  Vector2F row2_2f{3.0f, 4.0f};
  Vector2D row1_2d{1.0, 2.0};
  Vector2D row2_2d{3.0, 4.0};
  Vector2I row1_2i{1, 2};
  Vector2I row2_2i{3, 4};
  Vector2U row1_2u{1, 2};
  Vector2U row2_2u{3, 4};

  Matrix4F vecFMatrix4f{row1f, row2f, row3f, row4f};
  Matrix4F vecDMatrix4f{row1d, row2d, row3d, row4d};
  Matrix4F vecIMatrix4f{row1i, row2i, row3i, row4i};
  Matrix4F vecUMatrix4f{row1u, row2u, row3u, row4u};
  Matrix3F vecFMatrix3f{row1_3f, row2_3f, row3_3f};
  Matrix3F vecDMatrix3f{row1_3d, row2_3d, row3_3d};
  Matrix3F vecIMatrix3f{row1_3i, row2_3i, row3_3i};
  Matrix3F vecUMatrix3f{row1_3u, row2_3u, row3_3u};
  Matrix2F vecFMatrix2f{row1_2f, row2_2f};
  Matrix2F vecDMatrix2f{row1_2d, row2_2d};
  Matrix2F vecIMatrix2f{row1_2i, row2_2i};
  Matrix2F vecUMatrix2f{row1_2u, row2_2u};
  Matrix4D vecDMatrix4d{row1d, row2d, row3d, row4d};
  Matrix4D vecFMatrix4d{row1f, row2f, row3f, row4f};
  Matrix4D vecIMatrix4d{row1i, row2i, row3i, row4i};
  Matrix4D vecUMatrix4d{row1u, row2u, row3u, row4u};
  Matrix3D vecDMatrix3d{row1_3d, row2_3d, row3_3d};
  Matrix3D vecFMatrix3d{row1_3f, row2_3f, row3_3f};
  Matrix3D vecIMatrix3d{row1_3i, row2_3i, row3_3i};
  Matrix3D vecUMatrix3d{row1_3u, row2_3u, row3_3u};
  Matrix2D vecDMatrix2d{row1_2d, row2_2d};
  Matrix2D vecFMatrix2d{row1_2f, row2_2f};
  Matrix2D vecIMatrix2d{row1_2i, row2_2i};
  Matrix2D vecUMatrix2d{row1_2u, row2_2u};
  Matrix4I vecIMatrix4i{row1i, row2i, row3i, row4i};
  Matrix4I vecFMatrix4i{row1f, row2f, row3f, row4f};
  Matrix4I vecDMatrix4i{row1d, row2d, row3d, row4d};
  Matrix4I vecUMatrix4i{row1u, row2u, row3u, row4u};
  Matrix3I vecIMatrix3i{row1_3i, row2_3i, row3_3i};
  Matrix3I vecFMatrix3i{row1_3f, row2_3f, row3_3f};
  Matrix3I vecDMatrix3i{row1_3d, row2_3d, row3_3d};
  Matrix3I vecUMatrix3i{row1_3u, row2_3u, row3_3u};
  Matrix2I vecIMatrix2i{row1_2i, row2_2i};
  Matrix2I vecFMatrix2i{row1_2f, row2_2f};
  Matrix2I vecDMatrix2i{row1_2d, row2_2d};
  Matrix2I vecUMatrix2i{row1_2u, row2_2u};
  Matrix4U vecUMatrix4u{row1u, row2u, row3u, row4u};
  Matrix4U vecFMatrix4u{row1f, row2f, row3f, row4f};
  Matrix4U vecDMatrix4u{row1d, row2d, row3d, row4d};
  Matrix4U vecIMatrix4u{row1i, row2i, row3i, row4i};
  Matrix3U vecUMatrix3u{row1_3u, row2_3u, row3_3u};
  Matrix3U vecFMatrix3u{row1_3f, row2_3f, row3_3f};
  Matrix3U vecDMatrix3u{row1_3d, row2_3d, row3_3d};
  Matrix3U vecIMatrix3u{row1_3i, row2_3i, row3_3i};
  Matrix2U vecUMatrix2u{row1_2u, row2_2u};
  Matrix2U vecFMatrix2u{row1_2f, row2_2f};
  Matrix2U vecDMatrix2u{row1_2d, row2_2d};
  Matrix2U vecIMatrix2u{row1_2i, row2_2i};

  EXPECT_EQ(vecFMatrix4f, matrix4f);
  EXPECT_EQ(vecDMatrix4f, matrix4f);
  EXPECT_EQ(vecIMatrix4f, matrix4f);
  EXPECT_EQ(vecUMatrix4f, matrix4f);
  EXPECT_EQ(vecFMatrix3f, matrix3f);
  EXPECT_EQ(vecDMatrix3f, matrix3f);
  EXPECT_EQ(vecIMatrix3f, matrix3f);
  EXPECT_EQ(vecUMatrix3f, matrix3f);
  EXPECT_EQ(vecFMatrix2f, matrix2f);
  EXPECT_EQ(vecDMatrix2f, matrix2f);
  EXPECT_EQ(vecIMatrix2f, matrix2f);
  EXPECT_EQ(vecUMatrix2f, matrix2f);
  EXPECT_EQ(vecDMatrix4d, matrix4d);
  EXPECT_EQ(vecFMatrix4d, matrix4d);
  EXPECT_EQ(vecIMatrix4d, matrix4d);
  EXPECT_EQ(vecUMatrix4d, matrix4d);
  EXPECT_EQ(vecDMatrix3d, matrix3d);
  EXPECT_EQ(vecFMatrix3d, matrix3d);
  EXPECT_EQ(vecIMatrix3d, matrix3d);
  EXPECT_EQ(vecUMatrix3d, matrix3d);
  EXPECT_EQ(vecDMatrix2d, matrix2d);
  EXPECT_EQ(vecFMatrix2d, matrix2d);
  EXPECT_EQ(vecIMatrix2d, matrix2d);
  EXPECT_EQ(vecUMatrix2d, matrix2d);
  EXPECT_EQ(vecIMatrix4i, matrix4i);
  EXPECT_EQ(vecFMatrix4i, matrix4i);
  EXPECT_EQ(vecDMatrix4i, matrix4i);
  EXPECT_EQ(vecUMatrix4i, matrix4i);
  EXPECT_EQ(vecIMatrix3i, matrix3i);
  EXPECT_EQ(vecFMatrix3i, matrix3i);
  EXPECT_EQ(vecDMatrix3i, matrix3i);
  EXPECT_EQ(vecUMatrix3i, matrix3i);
  EXPECT_EQ(vecIMatrix2i, matrix2i);
  EXPECT_EQ(vecFMatrix2i, matrix2i);
  EXPECT_EQ(vecDMatrix2i, matrix2i);
  EXPECT_EQ(vecUMatrix2i, matrix2i);
  EXPECT_EQ(vecUMatrix4u, matrix4u);
  EXPECT_EQ(vecFMatrix4u, matrix4u);
  EXPECT_EQ(vecDMatrix4u, matrix4u);
  EXPECT_EQ(vecIMatrix4u, matrix4u);
  EXPECT_EQ(vecUMatrix3u, matrix3u);
  EXPECT_EQ(vecFMatrix3u, matrix3u);
  EXPECT_EQ(vecDMatrix3u, matrix3u);
  EXPECT_EQ(vecIMatrix3u, matrix3u);
  EXPECT_EQ(vecUMatrix2u, matrix2u);
  EXPECT_EQ(vecFMatrix2u, matrix2u);
  EXPECT_EQ(vecDMatrix2u, matrix2u);
  EXPECT_EQ(vecIMatrix2u, matrix2u);
}

TEST_F(MatrixTest, FromDataConstructor) {
  std::array<float, 16> data4f = {1.0f,  2.0f,  3.0f,  4.0f,  5.0f,  6.0f,
                                  7.0f,  8.0f,  9.0f,  10.0f, 11.0f, 12.0f,
                                  13.0f, 14.0f, 15.0f, 16.0f};
  EXPECT_EQ(Matrix4F(data4f.data(), data4f.size()), matrix4f);
  std::array<double, 16> data4d = {1.0,   2.0,   3.0,   4.0,  5.0,   6.0,
                                   7.0,   8.0,   9.0,   10.0, 11.0f, 12.0f,
                                   13.0f, 14.0f, 15.0f, 16.0f};
  EXPECT_EQ(Matrix4D(data4d.data(), data4d.size()), matrix4d);
  std::array<int, 16> data4i = {1, 2,  3,  4,  5,  6,  7,  8,
                                9, 10, 11, 12, 13, 14, 15, 16};
  EXPECT_EQ(Matrix4I(data4i.data(), data4i.size()), matrix4i);
  std::array<unsigned int, 16> data4u = {1, 2,  3,  4,  5,  6,  7,  8,
                                         9, 10, 11, 12, 13, 14, 15, 16};
  EXPECT_EQ(Matrix4U(data4u.data(), data4u.size()), matrix4u);

  std::array<float, 9> data3f = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                                 6.0f, 7.0f, 8.0f, 9.0f};
  EXPECT_EQ(Matrix3F(data3f.data(), data3f.size()), matrix3f);
  std::array<double, 9> data3d = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  EXPECT_EQ(Matrix3D(data3d.data(), data3d.size()), matrix3d);
  std::array<int, 9> data3i = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ(Matrix3I(data3i.data(), data3i.size()), matrix3i);
  std::array<unsigned int, 9> data3u = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ(Matrix3U(data3u.data(), data3u.size()), matrix3u);

  std::array<float, 4> data2f = {1.0f, 2.0f, 3.0f, 4.0f};
  EXPECT_EQ(Matrix2F(data2f.data(), data2f.size()), matrix2f);
  std::array<double, 4> data2d = {1.0, 2.0, 3.0, 4.0};
  EXPECT_EQ(Matrix2D(data2d.data(), data2d.size()), matrix2d);
  std::array<int, 4> data2i = {1, 2, 3, 4};
  EXPECT_EQ(Matrix2I(data2i.data(), data2i.size()), matrix2i);
  std::array<unsigned int, 4> data2u = {1, 2, 3, 4};
  EXPECT_EQ(Matrix2U(data2u.data(), data2u.size()), matrix2u);

  // Size exceeded
  EXPECT_EQ(Matrix4F(data4f.data(), data4f.size() + 5), matrix4f);
  EXPECT_EQ(Matrix4D(data4d.data(), data4d.size() + 5), matrix4d);
  EXPECT_EQ(Matrix4I(data4i.data(), data4i.size() + 5), matrix4i);
  EXPECT_EQ(Matrix4U(data4u.data(), data4u.size() + 5), matrix4u);
  EXPECT_EQ(Matrix3F(data3f.data(), data3f.size() + 5), matrix3f);
  EXPECT_EQ(Matrix3D(data3d.data(), data3d.size() + 5), matrix3d);
  EXPECT_EQ(Matrix3I(data3i.data(), data3i.size() + 5), matrix3i);
  EXPECT_EQ(Matrix3U(data3u.data(), data3u.size() + 5), matrix3u);
  EXPECT_EQ(Matrix2F(data2f.data(), data2f.size() + 5), matrix2f);
  EXPECT_EQ(Matrix2D(data2d.data(), data2d.size() + 5), matrix2d);
  EXPECT_EQ(Matrix2I(data2i.data(), data2i.size() + 5), matrix2i);
  EXPECT_EQ(Matrix2U(data2u.data(), data2u.size() + 5), matrix2u);
}

TEST_F(MatrixTest, NonMemberPlusOperator) {
  Matrix4F expected4f{2.0f,  4.0f,  6.0f,  8.0f,  10.0f, 12.0f, 14.0f, 16.0f,
                      18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f};
  Matrix4D expected4d{2.0,  4.0,  6.0,  8.0,  10.0, 12.0, 14.0, 16.0,
                      18.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0};
  Matrix4U expected4u{2,  4,  6,  8,  10, 12, 14, 16,
                      18, 20, 22, 24, 26, 28, 30, 32};
  Matrix4I expected4i{2,  4,  6,  8,  10, 12, 14, 16,
                      18, 20, 22, 24, 26, 28, 30, 32};
  EXPECT_EQ(matrix4f + matrix4f, expected4f);
  EXPECT_EQ(matrix4d + matrix4d, expected4d);
  EXPECT_EQ(matrix4u + matrix4u, expected4u);
  EXPECT_EQ(matrix4i + matrix4i, expected4i);

  Matrix3F expected3f{2.0f,  4.0f,  6.0f,  8.0f, 10.0f,
                      12.0f, 14.0f, 16.0f, 18.0f};
  Matrix3D expected3d{2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0};
  Matrix3U expected3u{2, 4, 6, 8, 10, 12, 14, 16, 18};
  Matrix3I expected3i{2, 4, 6, 8, 10, 12, 14, 16, 18};
  EXPECT_EQ(matrix3f + matrix3f, expected3f);
  EXPECT_EQ(matrix3d + matrix3d, expected3d);
  EXPECT_EQ(matrix3u + matrix3u, expected3u);
  EXPECT_EQ(matrix3i + matrix3i, expected3i);

  Matrix2F expected2f{2.0f, 4.0f, 6.0f, 8.0f};
  Matrix2D expected2d{2.0, 4.0, 6.0, 8.0};
  Matrix2U expected2u{2, 4, 6, 8};
  Matrix2I expected2i{2, 4, 6, 8};
  EXPECT_EQ(matrix2f + matrix2f, expected2f);
  EXPECT_EQ(matrix2d + matrix2d, expected2d);
  EXPECT_EQ(matrix2u + matrix2u, expected2u);
  EXPECT_EQ(matrix2i + matrix2i, expected2i);
}

TEST_F(MatrixTest, NonMemberMinusOperator) {
  Matrix4F expected4f{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  Matrix4D expected4d{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Matrix4U expected4u{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  Matrix4I expected4i{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  EXPECT_EQ(matrix4f - matrix4f, expected4f);
  EXPECT_EQ(matrix4d - matrix4d, expected4d);
  EXPECT_EQ(matrix4u - matrix4u, expected4u);
  EXPECT_EQ(matrix4i - matrix4i, expected4i);

  Matrix3F expected3f{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  Matrix3D expected3d{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Matrix3U expected3u{0, 0, 0, 0, 0, 0, 0, 0, 0};
  Matrix3I expected3i{0, 0, 0, 0, 0, 0, 0, 0, 0};
  EXPECT_EQ(matrix3f - matrix3f, expected3f);
  EXPECT_EQ(matrix3d - matrix3d, expected3d);
  EXPECT_EQ(matrix3u - matrix3u, expected3u);
  EXPECT_EQ(matrix3i - matrix3i, expected3i);

  Matrix2F expected2f{0.0f, 0.0f, 0.0f, 0.0f};
  Matrix2D expected2d{0.0, 0.0, 0.0, 0.0};
  Matrix2U expected2u{0, 0, 0, 0};
  Matrix2I expected2i{0, 0, 0, 0};
  EXPECT_EQ(matrix2f - matrix2f, expected2f);
  EXPECT_EQ(matrix2d - matrix2d, expected2d);
  EXPECT_EQ(matrix2u - matrix2u, expected2u);
  EXPECT_EQ(matrix2i - matrix2i, expected2i);
}

TEST_F(MatrixTest, NonMemberMultiplyOperator) {
  Matrix4F expected4f{90.0f,  100.0f, 110.0f, 120.0f, 202.0f, 228.0f,
                      254.0f, 280.0f, 314.0f, 356.0f, 398.0f, 440.0f,
                      426.0f, 484.0f, 542.0f, 600.0f};
  Matrix4D expected4d{90.0,  100.0, 110.0, 120.0, 202.0, 228.0, 254.0, 280.0,
                      314.0, 356.0, 398.0, 440.0, 426.0, 484.0, 542.0, 600.0};
  Matrix4I expected4i{90,  100, 110, 120, 202, 228, 254, 280,
                      314, 356, 398, 440, 426, 484, 542, 600};
  Matrix4U expected4u{90,  100, 110, 120, 202, 228, 254, 280,
                      314, 356, 398, 440, 426, 484, 542, 600};

  EXPECT_EQ(matrix4f * matrix4f, expected4f);
  EXPECT_EQ(matrix4d * matrix4d, expected4d);
  EXPECT_EQ(matrix4u * matrix4u, expected4u);
  EXPECT_EQ(matrix4i * matrix4i, expected4i);

  Matrix3F expected3f{30.0f, 36.0f,  42.0f,  66.0f, 81.0f,
                      96.0f, 102.0f, 126.0f, 150.0f};
  Matrix3D expected3d{30.0, 36.0, 42.0, 66.0, 81.0, 96.0, 102.0, 126.0, 150.0};
  Matrix3U expected3u{30, 36, 42, 66, 81, 96, 102, 126, 150};
  Matrix3I expected3i{30, 36, 42, 66, 81, 96, 102, 126, 150};
  EXPECT_EQ(matrix3f * matrix3f, expected3f);
  EXPECT_EQ(matrix3d * matrix3d, expected3d);
  EXPECT_EQ(matrix3u * matrix3u, expected3u);
  EXPECT_EQ(matrix3i * matrix3i, expected3i);

  Matrix2F expected2f{7.0f, 10.0f, 15.0f, 22.0f};
  Matrix2D expected2d{7.0, 10.0, 15.0, 22.0};
  Matrix2U expected2u{7, 10, 15, 22};
  Matrix2I expected2i{7, 10, 15, 22};
  EXPECT_EQ(matrix2f * matrix2f, expected2f);
  EXPECT_EQ(matrix2d * matrix2d, expected2d);
  EXPECT_EQ(matrix2u * matrix2u, expected2u);
  EXPECT_EQ(matrix2i * matrix2i, expected2i);
}

TEST_F(MatrixTest, NonMemberScalarMultiplyOperator) {
  Matrix4F expected4f{2.0f,  4.0f,  6.0f,  8.0f,  10.0f, 12.0f, 14.0f, 16.0f,
                      18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f};
  Matrix4D expected4d{20.0,  40.0,  60.0,  80.0,  100.0, 120.0, 140.0, 160.0,
                      180.0, 200.0, 220.0, 240.0, 260.0, 280.0, 300.0, 320.0};
  Matrix4U expected4u{200,  400,  600,  800,  1000, 1200, 1400, 1600,
                      1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200};
  Matrix4I expected4i{2000,  4000,  6000,  8000,  10000, 12000, 14000, 16000,
                      18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000};
  EXPECT_EQ(matrix4f * 2.0f, expected4f);
  EXPECT_EQ(matrix4d * 20.0, expected4d);
  EXPECT_EQ(matrix4u * 200u, expected4u);
  EXPECT_EQ(matrix4i * 2000, expected4i);

  Matrix3F expected3f{2.0f,  4.0f,  6.0f,  8.0f, 10.0f,
                      12.0f, 14.0f, 16.0f, 18.0f};
  Matrix3D expected3d{20.0,  40.0,  60.0,  80.0, 100.0,
                      120.0, 140.0, 160.0, 180.0};
  Matrix3U expected3u{200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800};
  Matrix3I expected3i{2000,  4000,  6000,  8000, 10000,
                      12000, 14000, 16000, 18000};
  EXPECT_EQ(matrix3f * 2.0f, expected3f);
  EXPECT_EQ(matrix3d * 20.0, expected3d);
  EXPECT_EQ(matrix3u * 200u, expected3u);
  EXPECT_EQ(matrix3i * 2000, expected3i);

  Matrix2F expected2f{2.0f, 4.0f, 6.0f, 8.0f};
  Matrix2D expected2d{20.0, 40.0, 60.0, 80.0};
  Matrix2U expected2u{200, 400, 600, 800};
  Matrix2I expected2i{2000, 4000, 6000, 8000};
  EXPECT_EQ(matrix2f * 2.0f, expected2f);
  EXPECT_EQ(matrix2d * 20.0, expected2d);
  EXPECT_EQ(matrix2u * 200u, expected2u);
  EXPECT_EQ(matrix2i * 2000, expected2i);
}

TEST_F(MatrixTest, NonMemberScalarMultiplyOperator2) {
  Matrix4F expected4f{2.0f,  4.0f,  6.0f,  8.0f,  10.0f, 12.0f, 14.0f, 16.0f,
                      18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f};
  Matrix4D expected4d{20.0,  40.0,  60.0,  80.0,  100.0, 120.0, 140.0, 160.0,
                      180.0, 200.0, 220.0, 240.0, 260.0, 280.0, 300.0, 320.0};
  Matrix4U expected4u{200,  400,  600,  800,  1000, 1200, 1400, 1600,
                      1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200};
  Matrix4I expected4i{2000,  4000,  6000,  8000,  10000, 12000, 14000, 16000,
                      18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000};
  EXPECT_EQ(2.0f * matrix4f, expected4f);
  EXPECT_EQ(20.0 * matrix4d, expected4d);
  EXPECT_EQ(200u * matrix4u, expected4u);
  EXPECT_EQ(2000 * matrix4i, expected4i);

  Matrix3F expected3f{2.0f,  4.0f,  6.0f,  8.0f, 10.0f,
                      12.0f, 14.0f, 16.0f, 18.0f};
  Matrix3D expected3d{20.0,  40.0,  60.0,  80.0, 100.0,
                      120.0, 140.0, 160.0, 180.0};
  Matrix3U expected3u{200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800};
  Matrix3I expected3i{2000,  4000,  6000,  8000, 10000,
                      12000, 14000, 16000, 18000};
  EXPECT_EQ(2.0f * matrix3f, expected3f);
  EXPECT_EQ(20.0 * matrix3d, expected3d);
  EXPECT_EQ(200u * matrix3u, expected3u);
  EXPECT_EQ(2000 * matrix3i, expected3i);

  Matrix2F expected2f{2.0f, 4.0f, 6.0f, 8.0f};
  Matrix2D expected2d{20.0, 40.0, 60.0, 80.0};
  Matrix2U expected2u{200, 400, 600, 800};
  Matrix2I expected2i{2000, 4000, 6000, 8000};
  EXPECT_EQ(2.0f * matrix2f, expected2f);
  EXPECT_EQ(20.0 * matrix2d, expected2d);
  EXPECT_EQ(200u * matrix2u, expected2u);
  EXPECT_EQ(2000 * matrix2i, expected2i);
}

TEST_F(MatrixTest, NonMemberDivideOperator) {
  Matrix4F expected4f{0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f,
                      4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f};
  Matrix4D expected4d{0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0,
                      4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0};
  Matrix4U expected4u{0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8};
  Matrix4I expected4i{0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8};
  EXPECT_EQ(matrix4f / 2.0f, expected4f);
  EXPECT_EQ(matrix4d / 2.0, expected4d);
  EXPECT_EQ(matrix4u / 2u, expected4u);
  EXPECT_EQ(matrix4i / 2, expected4i);

  Matrix3F expected3f{0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f};
  Matrix3D expected3d{0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5};
  Matrix3U expected3u{0, 1, 1, 2, 2, 3, 3, 4, 4};
  Matrix3I expected3i{0, 1, 1, 2, 2, 3, 3, 4, 4};
  EXPECT_EQ(matrix3f / 2.0f, expected3f);
  EXPECT_EQ(matrix3d / 2.0, expected3d);
  EXPECT_EQ(matrix3u / 2u, expected3u);
  EXPECT_EQ(matrix3i / 2, expected3i);

  Matrix2F expected2f{0.5f, 1.0f, 1.5f, 2.0f};
  Matrix2D expected2d{0.5, 1.0, 1.5, 2.0};
  Matrix2U expected2u{0, 1, 1, 2};
  Matrix2I expected2i{0, 1, 1, 2};
  EXPECT_EQ(matrix2f / 2.0f, expected2f);
  EXPECT_EQ(matrix2d / 2.0, expected2d);
  EXPECT_EQ(matrix2u / 2u, expected2u);
  EXPECT_EQ(matrix2i / 2, expected2i);
}

TEST_F(MatrixTest, AssignmentOperator) {
  Matrix4F matrix4fAssign{10.0f,  20.0f,  30.0f,  40.0f,  50.0f,  60.0f,
                          70.0f,  80.0f,  90.0f,  100.0f, 110.0f, 120.0f,
                          130.0f, 140.0f, 150.0f, 160.0f};
  Matrix4D matrix4dAssign{10.0,  20.0,  30.0,  40.0,  50.0,  60.0,
                          70.0,  80.0,  90.0,  100.0, 110.0, 120.0,
                          130.0, 140.0, 150.0, 160.0};
  Matrix4I matrix4iAssign{10, 20,  30,  40,  50,  60,  70,  80,
                          90, 100, 110, 120, 130, 140, 150, 160};
  Matrix4U matrix4uAssign{10, 20,  30,  40,  50,  60,  70,  80,
                          90, 100, 110, 120, 130, 140, 150, 160};
  matrix4f = matrix4fAssign;
  matrix4d = matrix4dAssign;
  matrix4i = matrix4iAssign;
  matrix4u = matrix4uAssign;
  EXPECT_EQ(matrix4f, matrix4fAssign);
  EXPECT_EQ(matrix4d, matrix4dAssign);
  EXPECT_EQ(matrix4i, matrix4iAssign);
  EXPECT_EQ(matrix4u, matrix4uAssign);

  Matrix3F matrix3fAssign{10.0f, 20.0f, 30.0f, 40.0f, 50.0f,
                          60.0f, 70.0f, 80.0f, 90.0f};
  Matrix3D matrix3dAssign{10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0};
  Matrix3I matrix3iAssign{10, 20, 30, 40, 50, 60, 70, 80, 90};
  Matrix3U matrix3uAssign{10, 20, 30, 40, 50, 60, 70, 80, 90};
  matrix3f = matrix3fAssign;
  matrix3d = matrix3dAssign;
  matrix3i = matrix3iAssign;
  matrix3u = matrix3uAssign;
  EXPECT_EQ(matrix3f, matrix3fAssign);
  EXPECT_EQ(matrix3d, matrix3dAssign);
  EXPECT_EQ(matrix3i, matrix3iAssign);
  EXPECT_EQ(matrix3u, matrix3uAssign);

  Matrix2F matrix2fAssign{10.0f, 20.0f, 30.0f, 40.0f};
  Matrix2D matrix2dAssign{10.0, 20.0, 30.0, 40.0};
  Matrix2I matrix2iAssign{10, 20, 30, 40};
  Matrix2U matrix2uAssign{10, 20, 30, 40};
  matrix2f = matrix2fAssign;
  matrix2d = matrix2dAssign;
  matrix2i = matrix2iAssign;
  matrix2u = matrix2uAssign;
  EXPECT_EQ(matrix2f, matrix2fAssign);
  EXPECT_EQ(matrix2d, matrix2dAssign);
  EXPECT_EQ(matrix2i, matrix2iAssign);
  EXPECT_EQ(matrix2u, matrix2uAssign);
}

TEST_F(MatrixTest, DifferentTypesAssignmentOperator) {
  Matrix4F matrix4fAssign{10.0f,  20.0f,  30.0f,  40.0f,  50.0f,  60.0f,
                          70.0f,  80.0f,  90.0f,  100.0f, 110.0f, 120.0f,
                          130.0f, 140.0f, 150.0f, 160.0f};
  Matrix4D matrix4dAssign{10.0,  20.0,  30.0,  40.0,  50.0,  60.0,
                          70.0,  80.0,  90.0,  100.0, 110.0, 120.0,
                          130.0, 140.0, 150.0, 160.0};
  Matrix4I matrix4iAssign{10, 20,  30,  40,  50,  60,  70,  80,
                          90, 100, 110, 120, 130, 140, 150, 160};
  Matrix4U matrix4uAssign{10, 20,  30,  40,  50,  60,  70,  80,
                          90, 100, 110, 120, 130, 140, 150, 160};
  matrix4f = matrix4dAssign;
  EXPECT_EQ(matrix4f, matrix4fAssign);
  matrix4f = matrix4iAssign;
  EXPECT_EQ(matrix4f, matrix4fAssign);
  matrix4f = matrix4uAssign;
  EXPECT_EQ(matrix4f, matrix4fAssign);
  matrix4d = matrix4fAssign;
  EXPECT_EQ(matrix4d, matrix4dAssign);
  matrix4d = matrix4iAssign;
  EXPECT_EQ(matrix4d, matrix4dAssign);
  matrix4d = matrix4uAssign;
  EXPECT_EQ(matrix4d, matrix4dAssign);
  matrix4i = matrix4fAssign;
  EXPECT_EQ(matrix4i, matrix4iAssign);
  matrix4i = matrix4dAssign;
  EXPECT_EQ(matrix4i, matrix4iAssign);
  matrix4i = matrix4uAssign;
  EXPECT_EQ(matrix4i, matrix4iAssign);
  matrix4u = matrix4fAssign;
  EXPECT_EQ(matrix4u, matrix4uAssign);
  matrix4u = matrix4dAssign;
  EXPECT_EQ(matrix4u, matrix4uAssign);
  matrix4u = matrix4iAssign;
  EXPECT_EQ(matrix4u, matrix4uAssign);

  Matrix3F matrix3fAssign{10.0f, 20.0f, 30.0f, 40.0f, 50.0f,
                          60.0f, 70.0f, 80.0f, 90.0f};
  Matrix3D matrix3dAssign{10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0};
  Matrix3I matrix3iAssign{10, 20, 30, 40, 50, 60, 70, 80, 90};
  Matrix3U matrix3uAssign{10, 20, 30, 40, 50, 60, 70, 80, 90};
  matrix3f = matrix3dAssign;
  EXPECT_EQ(matrix3f, matrix3fAssign);
  matrix3f = matrix3iAssign;
  EXPECT_EQ(matrix3f, matrix3fAssign);
  matrix3f = matrix3uAssign;
  EXPECT_EQ(matrix3f, matrix3fAssign);
  matrix3d = matrix3fAssign;
  EXPECT_EQ(matrix3d, matrix3dAssign);
  matrix3d = matrix3iAssign;
  EXPECT_EQ(matrix3d, matrix3dAssign);
  matrix3d = matrix3uAssign;
  EXPECT_EQ(matrix3d, matrix3dAssign);
  matrix3i = matrix3fAssign;
  EXPECT_EQ(matrix3i, matrix3iAssign);
  matrix3i = matrix3dAssign;
  EXPECT_EQ(matrix3i, matrix3iAssign);
  matrix3i = matrix3uAssign;
  EXPECT_EQ(matrix3i, matrix3iAssign);
  matrix3u = matrix3fAssign;
  EXPECT_EQ(matrix3u, matrix3uAssign);
  matrix3u = matrix3dAssign;
  EXPECT_EQ(matrix3u, matrix3uAssign);
  matrix3u = matrix3iAssign;
  EXPECT_EQ(matrix3u, matrix3uAssign);

  Matrix2F matrix2fAssign{10.0f, 20.0f, 30.0f, 40.0f};
  Matrix2D matrix2dAssign{10.0, 20.0, 30.0, 40.0};
  Matrix2I matrix2iAssign{10, 20, 30, 40};
  Matrix2U matrix2uAssign{10, 20, 30, 40};
  matrix2f = matrix2dAssign;
  EXPECT_EQ(matrix2f, matrix2fAssign);
  matrix2f = matrix2iAssign;
  EXPECT_EQ(matrix2f, matrix2fAssign);
  matrix2f = matrix2uAssign;
  EXPECT_EQ(matrix2f, matrix2fAssign);
  matrix2d = matrix2fAssign;
  EXPECT_EQ(matrix2d, matrix2dAssign);
  matrix2d = matrix2iAssign;
  EXPECT_EQ(matrix2d, matrix2dAssign);
  matrix2d = matrix2uAssign;
  EXPECT_EQ(matrix2d, matrix2dAssign);
  matrix2i = matrix2fAssign;
  EXPECT_EQ(matrix2i, matrix2iAssign);
  matrix2i = matrix2dAssign;
  EXPECT_EQ(matrix2i, matrix2iAssign);
  matrix2i = matrix2uAssign;
  EXPECT_EQ(matrix2i, matrix2iAssign);
  matrix2u = matrix2fAssign;
  EXPECT_EQ(matrix2u, matrix2uAssign);
  matrix2u = matrix2dAssign;
  EXPECT_EQ(matrix2u, matrix2uAssign);
  matrix2u = matrix2iAssign;
  EXPECT_EQ(matrix2u, matrix2uAssign);
}

TEST_F(MatrixTest, NonMemberPlusEqualOperator) {
  Matrix4F expected4f{2.0f,  4.0f,  6.0f,  8.0f,  10.0f, 12.0f, 14.0f, 16.0f,
                      18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f};
  Matrix4D expected4d{2.0,  4.0,  6.0,   8.0,   10.0,  12.0,  14.0,  16.0,
                      18.0, 20.0, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f};
  Matrix4U expected4u{2,  4,  6,  8,  10, 12, 14, 16,
                      18, 20, 22, 24, 26, 28, 30, 32};
  Matrix4I expected4i{2,  4,  6,  8,  10, 12, 14, 16,
                      18, 20, 22, 24, 26, 28, 30, 32};
  matrix4f += matrix4f;
  matrix4d += matrix4d;
  matrix4u += matrix4u;
  matrix4i += matrix4i;
  EXPECT_EQ(matrix4f, expected4f);
  EXPECT_EQ(matrix4d, expected4d);
  EXPECT_EQ(matrix4u, expected4u);
  EXPECT_EQ(matrix4i, expected4i);

  Matrix3F expected3f{2.0f,  4.0f,  6.0f,  8.0f, 10.0f,
                      12.0f, 14.0f, 16.0f, 18.0f};
  Matrix3D expected3d{2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0};
  Matrix3U expected3u{2, 4, 6, 8, 10, 12, 14, 16, 18};
  Matrix3I expected3i{2, 4, 6, 8, 10, 12, 14, 16, 18};
  matrix3f += matrix3f;
  matrix3d += matrix3d;
  matrix3u += matrix3u;
  matrix3i += matrix3i;
  EXPECT_EQ(matrix3f, expected3f);
  EXPECT_EQ(matrix3d, expected3d);
  EXPECT_EQ(matrix3u, expected3u);
  EXPECT_EQ(matrix3i, expected3i);

  Matrix2F expected2f{2.0f, 4.0f, 6.0f, 8.0f};
  Matrix2D expected2d{2.0, 4.0, 6.0, 8.0};
  Matrix2U expected2u{2, 4, 6, 8};
  Matrix2I expected2i{2, 4, 6, 8};
  matrix2f += matrix2f;
  matrix2d += matrix2d;
  matrix2u += matrix2u;
  matrix2i += matrix2i;
  EXPECT_EQ(matrix2f, expected2f);
  EXPECT_EQ(matrix2d, expected2d);
  EXPECT_EQ(matrix2u, expected2u);
  EXPECT_EQ(matrix2i, expected2i);
}

TEST_F(MatrixTest, NonMemberScalarMinusEqualOperator) {
  Matrix4F expected4f{-9.0f, -8.0f, -7.0f, -6.0f, -5.0f, -4.0f, -3.0f, -2.0f,
                      -1.0f, 0.0f,  1.0f,  2.0f,  3.0f,  4.0f,  5.0f,  6.0f};
  Matrix4D expected4d{-9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0,
                      -1.0, 0.0,  1.0,  2.0,  3.0,  4.0,  5.0,  6.0};
  Matrix4U expected4u{Limits::Max<UInt32> - 8,
                      Limits::Max<UInt32> - 7,
                      Limits::Max<UInt32> - 6,
                      Limits::Max<UInt32> - 5,
                      Limits::Max<UInt32> - 4,
                      Limits::Max<UInt32> - 3,
                      Limits::Max<UInt32> - 2,
                      Limits::Max<UInt32> - 1,
                      Limits::Max<UInt32>,
                      0,
                      1,
                      2,
                      3,
                      4,
                      5,
                      6};
  Matrix4I expected4i{-9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
  matrix4f -= 10.0f;
  matrix4d -= 10.0;
  matrix4u -= 10u;
  matrix4i -= 10;
  EXPECT_EQ(matrix4f, expected4f);
  EXPECT_EQ(matrix4d, expected4d);
  EXPECT_EQ(matrix4u, expected4u);
  EXPECT_EQ(matrix4i, expected4i);
}

TEST_F(MatrixTest, NonMemberMinusEqualOperator) {
  Matrix4F expected4f{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  Matrix4D expected4d{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Matrix4U expected4u{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  Matrix4I expected4i{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  matrix4f -= matrix4f;
  matrix4d -= matrix4d;
  matrix4u -= matrix4u;
  matrix4i -= matrix4i;
  EXPECT_EQ(matrix4f, expected4f);
  EXPECT_EQ(matrix4d, expected4d);
  EXPECT_EQ(matrix4u, expected4u);
  EXPECT_EQ(matrix4i, expected4i);

  Matrix3F expected3f{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  Matrix3D expected3d{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Matrix3U expected3u{0, 0, 0, 0, 0, 0, 0, 0, 0};
  Matrix3I expected3i{0, 0, 0, 0, 0, 0, 0, 0, 0};
  matrix3f -= matrix3f;
  matrix3d -= matrix3d;
  matrix3u -= matrix3u;
  matrix3i -= matrix3i;
  EXPECT_EQ(matrix3f, expected3f);
  EXPECT_EQ(matrix3d, expected3d);
  EXPECT_EQ(matrix3u, expected3u);
  EXPECT_EQ(matrix3i, expected3i);

  Matrix2F expected2f{0.0f, 0.0f, 0.0f, 0.0f};
  Matrix2D expected2d{0.0, 0.0, 0.0, 0.0};
  Matrix2U expected2u{0, 0, 0, 0};
  Matrix2I expected2i{0, 0, 0, 0};
  matrix2f -= matrix2f;
  matrix2d -= matrix2d;
  matrix2u -= matrix2u;
  matrix2i -= matrix2i;
  EXPECT_EQ(matrix2f, expected2f);
  EXPECT_EQ(matrix2d, expected2d);
  EXPECT_EQ(matrix2u, expected2u);
  EXPECT_EQ(matrix2i, expected2i);
}

TEST_F(MatrixTest, NonMemberScalarMultiplyEqualOperator) {
  Matrix4F expected4f{2.0f,  4.0f,  6.0f,  8.0f,  10.0f, 12.0f, 14.0f, 16.0f,
                      18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f};
  Matrix4D expected4d{20.0,  40.0,  60.0,  80.0,  100.0, 120.0, 140.0, 160.0,
                      180.0, 200.0, 220.0, 240.0, 260.0, 280.0, 300.0, 320.0};
  Matrix4U expected4u{200,  400,  600,  800,  1000, 1200, 1400, 1600,
                      1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200};
  Matrix4I expected4i{2000,  4000,  6000,  8000,  10000, 12000, 14000, 16000,
                      18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000};
  matrix4f *= 2.0f;
  matrix4d *= 20.0;
  matrix4u *= 200u;
  matrix4i *= 2000;
  EXPECT_EQ(matrix4f, expected4f);
  EXPECT_EQ(matrix4d, expected4d);
  EXPECT_EQ(matrix4u, expected4u);
  EXPECT_EQ(matrix4i, expected4i);

  Matrix3F expected3f{2.0f,  4.0f,  6.0f,  8.0f, 10.0f,
                      12.0f, 14.0f, 16.0f, 18.0f};
  Matrix3D expected3d{20.0,  40.0,  60.0,  80.0, 100.0,
                      120.0, 140.0, 160.0, 180.0};
  Matrix3U expected3u{200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800};
  Matrix3I expected3i{2000,  4000,  6000,  8000, 10000,
                      12000, 14000, 16000, 18000};
  matrix3f *= 2.0f;
  matrix3d *= 20.0;
  matrix3u *= 200u;
  matrix3i *= 2000;
  EXPECT_EQ(matrix3f, expected3f);
  EXPECT_EQ(matrix3d, expected3d);
  EXPECT_EQ(matrix3u, expected3u);
  EXPECT_EQ(matrix3i, expected3i);

  Matrix2F expected2f{2.0f, 4.0f, 6.0f, 8.0f};
  Matrix2D expected2d{20.0, 40.0, 60.0, 80.0};
  Matrix2U expected2u{200, 400, 600, 800};
  Matrix2I expected2i{2000, 4000, 6000, 8000};
  matrix2f *= 2.0f;
  matrix2d *= 20.0;
  matrix2u *= 200u;
  matrix2i *= 2000;
  EXPECT_EQ(matrix2f, expected2f);
  EXPECT_EQ(matrix2d, expected2d);
  EXPECT_EQ(matrix2u, expected2u);
  EXPECT_EQ(matrix2i, expected2i);
}

TEST_F(MatrixTest, OperatorEqual) {
  Matrix4F matrix4fCopy = matrix4f;
  Matrix4D matrix4dCopy = matrix4d;
  Matrix4U matrix4uCopy = matrix4u;
  Matrix4I matrix4iCopy = matrix4i;
  EXPECT_TRUE(matrix4f == matrix4fCopy);
  EXPECT_TRUE(matrix4d == matrix4dCopy);
  EXPECT_TRUE(matrix4u == matrix4uCopy);
  EXPECT_TRUE(matrix4i == matrix4iCopy);

  Matrix3F matrix3fCopy = matrix3f;
  Matrix3D matrix3dCopy = matrix3d;
  Matrix3U matrix3uCopy = matrix3u;
  Matrix3I matrix3iCopy = matrix3i;
  EXPECT_TRUE(matrix3f == matrix3fCopy);
  EXPECT_TRUE(matrix3d == matrix3dCopy);
  EXPECT_TRUE(matrix3u == matrix3uCopy);
  EXPECT_TRUE(matrix3i == matrix3iCopy);

  Matrix2F matrix2fCopy = matrix2f;
  Matrix2D matrix2dCopy = matrix2d;
  Matrix2U matrix2uCopy = matrix2u;
  Matrix2I matrix2iCopy = matrix2i;
  EXPECT_TRUE(matrix2f == matrix2fCopy);
  EXPECT_TRUE(matrix2d == matrix2dCopy);
  EXPECT_TRUE(matrix2u == matrix2uCopy);
  EXPECT_TRUE(matrix2i == matrix2iCopy);

  matrix4fCopy[0, 0] += 1.0f;
  EXPECT_FALSE(matrix4f == matrix4fCopy);
  matrix4dCopy[0, 1] += 1.0;
  EXPECT_FALSE(matrix4d == matrix4dCopy);
  matrix4uCopy[1, 1] += 1;
  EXPECT_FALSE(matrix4u == matrix4uCopy);
  matrix4iCopy[1, 0] += 1;
  EXPECT_FALSE(matrix4i == matrix4iCopy);

  matrix3fCopy[0, 0] += 1.0f;
  EXPECT_FALSE(matrix3f == matrix3fCopy);
  matrix3dCopy[0, 1] += 1.0;
  EXPECT_FALSE(matrix3d == matrix3dCopy);
  matrix3uCopy[1, 1] += 1;
  EXPECT_FALSE(matrix3u == matrix3uCopy);
  matrix3iCopy[1, 0] += 1;
  EXPECT_FALSE(matrix3i == matrix3iCopy);

  matrix2fCopy[0, 0] += 1.0f;
  EXPECT_FALSE(matrix2f == matrix2fCopy);
  matrix2dCopy[0, 1] += 1.0;
  EXPECT_FALSE(matrix2d == matrix2dCopy);
  matrix2uCopy[1, 1] += 1;
  EXPECT_FALSE(matrix2u == matrix2uCopy);
  matrix2iCopy[1, 0] += 1;
  EXPECT_FALSE(matrix2i == matrix2iCopy);
}

TEST_F(MatrixTest, OperatorNotEqual) {
  Matrix4F matrix4fCopy = matrix4f;
  Matrix4D matrix4dCopy = matrix4d;
  Matrix4U matrix4uCopy = matrix4u;
  Matrix4I matrix4iCopy = matrix4i;
  EXPECT_FALSE(matrix4f != matrix4fCopy);
  EXPECT_FALSE(matrix4d != matrix4dCopy);
  EXPECT_FALSE(matrix4u != matrix4uCopy);
  EXPECT_FALSE(matrix4i != matrix4iCopy);

  Matrix3F matrix3fCopy = matrix3f;
  Matrix3D matrix3dCopy = matrix3d;
  Matrix3U matrix3uCopy = matrix3u;
  Matrix3I matrix3iCopy = matrix3i;
  EXPECT_FALSE(matrix3f != matrix3fCopy);
  EXPECT_FALSE(matrix3d != matrix3dCopy);
  EXPECT_FALSE(matrix3u != matrix3uCopy);
  EXPECT_FALSE(matrix3i != matrix3iCopy);

  Matrix2F matrix2fCopy = matrix2f;
  Matrix2D matrix2dCopy = matrix2d;
  Matrix2U matrix2uCopy = matrix2u;
  Matrix2I matrix2iCopy = matrix2i;
  EXPECT_FALSE(matrix2f != matrix2fCopy);
  EXPECT_FALSE(matrix2d != matrix2dCopy);
  EXPECT_FALSE(matrix2u != matrix2uCopy);
  EXPECT_FALSE(matrix2i != matrix2iCopy);

  matrix4fCopy[0, 0] += 1.0f;
  EXPECT_TRUE(matrix4f != matrix4fCopy);
  matrix4dCopy[0, 1] += 1.0;
  EXPECT_TRUE(matrix4d != matrix4dCopy);
  matrix4uCopy[1, 1] += 1;
  EXPECT_TRUE(matrix4u != matrix4uCopy);
  matrix4iCopy[1, 0] += 1;
  EXPECT_TRUE(matrix4i != matrix4iCopy);

  matrix3fCopy[0, 0] += 1.0f;
  EXPECT_TRUE(matrix3f != matrix3fCopy);
  matrix3dCopy[0, 1] += 1.0;
  EXPECT_TRUE(matrix3d != matrix3dCopy);
  matrix3uCopy[1, 1] += 1;
  EXPECT_TRUE(matrix3u != matrix3uCopy);
  matrix3iCopy[1, 0] += 1;
  EXPECT_TRUE(matrix3i != matrix3iCopy);

  matrix2fCopy[0, 0] += 1.0f;
  EXPECT_TRUE(matrix2f != matrix2fCopy);
  matrix2dCopy[0, 1] += 1.0;
  EXPECT_TRUE(matrix2d != matrix2dCopy);
  matrix2uCopy[1, 1] += 1;
  EXPECT_TRUE(matrix2u != matrix2uCopy);
  matrix2iCopy[1, 0] += 1;
  EXPECT_TRUE(matrix2i != matrix2iCopy);
}
}  // namespace Neat