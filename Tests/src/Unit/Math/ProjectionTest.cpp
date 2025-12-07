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
}  // namespace Neat