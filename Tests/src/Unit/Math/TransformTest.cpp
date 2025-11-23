#include <gtest/gtest.h>

#include "TestUtils.hpp"
#include "Math/Transform.hpp"

namespace Neat {
TEST(TransformTest, Translate) {
  Matrix4F translationMatrix = translate(Vector3F{1.0f, 2.0f, 3.0f});
  Matrix4F expectedMatrix{1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 2.0f,
                          0.0f, 0.0f, 1.0f, 3.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  EXPECT_EQ(translationMatrix, expectedMatrix);

  Matrix4D translationMatrixD = translate(Vector3D{2.5, -1.5, 4.0});
  Matrix4D expectedMatrixD{1.0, 0.0, 0.0, 2.5, 0.0, 1.0, 0.0, -1.5,
                           0.0, 0.0, 1.0, 4.0, 0.0, 0.0, 0.0, 1.0};
  EXPECT_EQ(translationMatrixD, expectedMatrixD);
}

TEST(TransformTest, TranslateWithMatrixInput) {
  Matrix4F baseMatrix{1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                      0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  Matrix4F translationMatrix =
      translate(baseMatrix, Vector3F{1.0f, 2.0f, 3.0f});
  Matrix4F expectedMatrix{1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 3.0f,
                          0.5f, 0.0f, 1.0f, 3.5f, 0.0f, 0.0f, 0.0f, 1.0f};
  EXPECT_EQ(translationMatrix, expectedMatrix);

  Matrix4D baseMatrixD{1.0, -0.8, 3.0, 0.0, 2.0, 1.0, 0.0, 0.0,
                       0.0, 0.0,  1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
  Matrix4D translationMatrixD =
      translate(baseMatrixD, Vector3D{2.5, -1.5, 4.0});
  Matrix4D expectedMatrixD{1.0, -0.8, 3.0,  15.7, 2.0, 1.0, 0.0,  3.5,
                           0.0, 0.0,  1.00, 4.0,  0.0, 0.0, 0.00, 1.0};
  EXPECT_EQ(translationMatrixD, expectedMatrixD);
}
}  // namespace Neat