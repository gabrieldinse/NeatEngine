
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
  matrix3f[1, 0] = 24.0f;
  matrix2f[0, 1] = 12.0f;
  EXPECT_EQ((matrix4f[2, 3]), 42.0f);
  EXPECT_EQ((matrix3f[1, 0]), 24.0f);
  EXPECT_EQ((matrix2f[0, 1]), 12.0f);
}
}  // namespace Neat