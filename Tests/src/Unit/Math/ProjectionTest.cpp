#include <gtest/gtest.h>

#include <TestUtils.hpp>

namespace Neat {
TEST(ProjectionTest, OrthographicProjection) {
  Matrix4F orthoMatrix =
      orthographicProjection(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
  Matrix4F expectedMatrix{1.0f, 0.0f, 0.0f, 0.0f, 0.0f,         1.0f,
                          0.0f, 0.0f, 0.0f, 0.0f, -0.02002002f, -1.002002f,
                          0.0f, 0.0f, 0.0f, 1.0f};
  expectNearMatrixValues(orthoMatrix, expectedMatrix);

  Matrix4D orthoMatrixD =
      orthographicProjection(-2.0, 2.0, -2.0, 2.0, 0.1, 100.0);
  Matrix4D expectedMatrixD{0.5, 0.0, 0.0, 0.0, 0.0,         0.5,
                           0.0, 0.0, 0.0, 0.0, -0.02002002, -1.002002,
                           0.0, 0.0, 0.0, 1.0};
  expectNearMatrixValues(orthoMatrixD, expectedMatrixD);

  Matrix4F orthoMatrixAspectRatio = orthographicProjection(
      -1.7777777f, 1.7777777f, -1.0f, 1.0f, 0.1f, 100.0f);
  Matrix4F expectedMatrixAspectRatio{
      0.5625f, 0.0f, 0.0f,         0.0f,       0.0f, 1.0f, 0.0f, 0.0f,
      0.0f,    0.0f, -0.02002002f, -1.002002f, 0.0f, 0.0f, 0.0f, 1.0f};
  expectNearMatrixValues(orthoMatrixAspectRatio, expectedMatrixAspectRatio);

  Matrix4D orthoMatrixAspectRatioD = orthographicProjection(
      -1.7777777777777, 1.7777777777777, -1.0, 1.0, 0.1, 100.0);
  Matrix4D expectedMatrixAspectRatioD{
      0.5625, 0.0, 0.0,         0.0,       0.0, 1.0, 0.0, 0.0,
      0.0,    0.0, -0.02002002, -1.002002, 0.0, 0.0, 0.0, 1.0};
  expectNearMatrixValues(orthoMatrixAspectRatioD, expectedMatrixAspectRatioD);
}

TEST(ProjectionTest, PerspectiveProjection) {
  Matrix4F perspectiveMatrix =
      perspectiveProjection(degreesToRadians(60.0f), 1.7777777f, 0.1f, 1000.0f);
  Matrix4F expectedMatrix{
      0.974278621f, 0.0f, 0.0f,     0.0f,      0.0f, 1.732050807f, 0.0f,  0.0f,
      0.0f,         0.0f, -1.0002f, -0.20002f, 0.0f, 0.0f,         -1.0f, 0.0f};
  expectNearMatrixValues(perspectiveMatrix, expectedMatrix);

  Matrix4D perspectiveMatrixD =
      perspectiveProjection(degreesToRadians(60.0), 1.7777777, 0.1, 1000.0);
  Matrix4D expectedMatrixD{0.974278621, 0.0, 0.0,  0.0, 0.0,     1.732050807,
                           0.0,         0.0, 0.0,  0.0, -1.0002, -0.20002,
                           0.0,         0.0, -1.0, 0.0};
  expectNearMatrixValues(perspectiveMatrixD, expectedMatrixD);

  Matrix4F perspectiveMatrix2 =
      perspectiveProjection(degreesToRadians(45.0f), 1.3333f, 0.1f, 500.0f);
  Matrix4F expectedMatrix2{
      1.81070543f, 0.0f, 0.0f,     0.0f,      0.0f, 2.41421356f, 0.0f,  0.0f,
      0.0f,        0.0f, -1.0004f, -0.20002f, 0.0f, 0.0f,        -1.0f, 0.0f};
  expectNearMatrixValues(perspectiveMatrix2, expectedMatrix2);

  Matrix4D perspectiveMatrix2D =
      perspectiveProjection(degreesToRadians(45.0), 1.3333, 0.1, 500.0);
  Matrix4D expectedMatrix2D{1.81070543, 0.0, 0.0,  0.0, 0.0,     2.41421356,
                            0.0,        0.0, 0.0,  0.0, -1.0004, -0.20004,
                            0.0,        0.0, -1.0, 0.0};
  expectNearMatrixValues(perspectiveMatrix2D, expectedMatrix2D);
}
}  // namespace Neat