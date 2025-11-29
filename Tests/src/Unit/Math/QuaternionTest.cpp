
#include <gtest/gtest.h>

#include <TestUtils.hpp>
#include <cstring>
#include "Math/Types/TypeQuaternion.hpp"

namespace Neat {
class QuaternionTest : public testing::Test {
 protected:
  QuaternionTest() {}
  QuaternionF quaternionf{1.0f, 2.0f, 3.0f, 4.0f};
  QuaternionD quaterniond{1.0, 2.0, 3.0, 4.0};
};

TEST_F(QuaternionTest, SizeFunction) {
  EXPECT_EQ(quaternionf.size(), 4);
  EXPECT_EQ(quaterniond.size(), 4);
}

TEST_F(QuaternionTest, QuaternionSizes) {
  EXPECT_EQ(QuaternionF::N, 4);
  EXPECT_EQ(QuaternionD::N, 4);
  EXPECT_EQ(QuaternionF::Size, 4);
  EXPECT_EQ(QuaternionD::Size, 4);
}

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

TEST_F(QuaternionTest, DotProduct) {
  float dotF = dot(quaternionf, quaternionf);
  EXPECT_FLOAT_EQ(dotF, 30.0f);

  double dotD = dot(quaterniond, quaterniond);
  EXPECT_DOUBLE_EQ(dotD, 30.0);
}

TEST_F(QuaternionTest, Norm) {
  float normF = norm(quaternionf);
  EXPECT_FLOAT_EQ(normF, sqrt(30.0f));

  double normD = norm(quaterniond);
  EXPECT_DOUBLE_EQ(normD, sqrt(30.0));
}

TEST_F(QuaternionTest, Normalize) {
  QuaternionF qfNormalized{normalize(quaternionf)};
  expectNearQuaternionValues(
      qfNormalized,
      QuaternionF{0.18257418f, 0.36514837f, 0.54772256f, 0.73029673f});

  QuaternionD qdNormalized{normalize(quaterniond)};
  expectNearQuaternionValues(
      qdNormalized, QuaternionD{0.18257418583505536, 0.3651483716701107,
                                0.5477225575051661, 0.7302967433402214});
}

TEST_F(QuaternionTest, Matrix3Cast) {
  Matrix3F expectedMatrix3F{-0.6666667f, 0.1333333f,  0.7333333f,
                            0.6666667f,  -0.3333333f, 0.6666667f,
                            0.3333333f,  0.9333333f,  0.1333333f};
  Matrix3F matrix3F = matrix3Cast(quaternionf);
  expectNearMatrixValues(matrix3F, expectedMatrix3F);

  Matrix3D expectedMatrix3D{
      -0.6666666666666667, 0.13333333333333333, 0.7333333333333333,
      0.6666666666666667,  -0.3333333333333333, 0.6666666666666667,
      0.3333333333333333,  0.9333333333333333,  0.13333333333333333};
  Matrix3D matrix3D = matrix3Cast(quaterniond);
  expectNearMatrixValues(matrix3D, expectedMatrix3D);
}

TEST_F(QuaternionTest, ToMatrix3) {
  Matrix3F expectedMatrix3F{-0.6666667f, 0.1333333f,  0.7333333f,
                            0.6666667f,  -0.3333333f, 0.6666667f,
                            0.3333333f,  0.9333333f,  0.1333333f};
  Matrix3F matrix3F = quaternionf.toMatrix3();
  expectNearMatrixValues(matrix3F, expectedMatrix3F);

  Matrix3D expectedMatrix3D{
      -0.6666666666666667, 0.13333333333333333, 0.7333333333333333,
      0.6666666666666667,  -0.3333333333333333, 0.6666666666666667,
      0.3333333333333333,  0.9333333333333333,  0.13333333333333333};
  Matrix3D matrix3D = quaterniond.toMatrix3();
  expectNearMatrixValues(matrix3D, expectedMatrix3D);
}

TEST_F(QuaternionTest, Matrix4Cast) {
  Matrix4F expectedMatrix4F{-0.6666667f, 0.1333333f,  0.7333333f, 0.0f,
                            0.6666667f,  -0.3333333f, 0.6666667f, 0.0f,
                            0.3333333f,  0.9333333f,  0.1333333f, 0.0f,
                            0.0f,        0.0f,        0.0f,       1.0f};
  Matrix4F matrix4F = matrix4Cast(quaternionf);
  expectNearMatrixValues(matrix4F, expectedMatrix4F);

  Matrix4D expectedMatrix4D{-0.6666666666666667,
                            0.13333333333333333,
                            0.7333333333333333,
                            0.0,
                            0.6666666666666667,
                            -0.3333333333333333,
                            0.6666666666666667,
                            0.0,
                            0.3333333333333333,
                            0.9333333333333333,
                            0.13333333333333333,
                            0.0,
                            0.0,
                            0.0,
                            0.0,
                            1.0};
  Matrix4D matrix4D = matrix4Cast(quaterniond);
  expectNearMatrixValues(matrix4D, expectedMatrix4D);
}

TEST_F(QuaternionTest, ToMatrix4) {
  Matrix4F expectedMatrix4F{-0.6666667f, 0.1333333f,  0.7333333f, 0.0f,
                            0.6666667f,  -0.3333333f, 0.6666667f, 0.0f,
                            0.3333333f,  0.9333333f,  0.1333333f, 0.0f,
                            0.0f,        0.0f,        0.0f,       1.0f};
  Matrix4F matrix4F = quaternionf.toMatrix4();
  expectNearMatrixValues(matrix4F, expectedMatrix4F);

  Matrix4D expectedMatrix4D{-0.6666666666666667,
                            0.13333333333333333,
                            0.7333333333333333,
                            0.0,
                            0.6666666666666667,
                            -0.3333333333333333,
                            0.6666666666666667,
                            0.0,
                            0.3333333333333333,
                            0.9333333333333333,
                            0.13333333333333333,
                            0.0,
                            0.0,
                            0.0,
                            0.0,
                            1.0};
  Matrix4D matrix4D = quaterniond.toMatrix4();
  expectNearMatrixValues(matrix4D, expectedMatrix4D);
}

TEST_F(QuaternionTest, QuaternionCastFromMatrix3) {
  Matrix3F matrix3F = matrix3Cast(quaternionf);
  QuaternionF qfFromMatrix3 = quaternionCast(matrix3F);
  expectNearQuaternionValues(qfFromMatrix3, normalize(quaternionf));

  Matrix3D matrix3D = matrix3Cast(quaterniond);
  QuaternionD qdFromMatrix3 = quaternionCast(matrix3D);
  expectNearQuaternionValues(qdFromMatrix3, normalize(quaterniond));
}

TEST_F(QuaternionTest, QuaternionCastFromMatrix4) {
  Matrix4F matrix4F = matrix4Cast(quaternionf);
  QuaternionF qfFromMatrix4 = quaternionCast(matrix4F);
  expectNearQuaternionValues(qfFromMatrix4, normalize(quaternionf));

  Matrix4D matrix4D = matrix4Cast(quaterniond);
  QuaternionD qdFromMatrix4 = quaternionCast(matrix4D);
  expectNearQuaternionValues(qdFromMatrix4, normalize(quaterniond));
}

TEST_F(QuaternionTest, FromMatrix3Constructor) {
  QuaternionF qfFromMatrix3(matrix3Cast(quaternionf));
  expectNearQuaternionValues(qfFromMatrix3, normalize(quaternionf));

  QuaternionD qdFromMatrix3(matrix3Cast(quaterniond));
  expectNearQuaternionValues(qdFromMatrix3, normalize(quaterniond));
}

TEST_F(QuaternionTest, FromMatrix4Constructor) {
  QuaternionF qfFromMatrix4(matrix4Cast(quaternionf));
  expectNearQuaternionValues(qfFromMatrix4, normalize(quaternionf));

  QuaternionD qdFromMatrix4(matrix4Cast(quaterniond));
  expectNearQuaternionValues(qdFromMatrix4, normalize(quaterniond));
}

TEST_F(QuaternionTest, IndexOperator) {
  EXPECT_EQ(quaternionf[0], 1.0f);
  EXPECT_EQ(quaternionf[1], 2.0f);
  EXPECT_EQ(quaternionf[2], 3.0f);
  EXPECT_EQ(quaternionf[3], 4.0f);

  EXPECT_EQ(quaterniond[0], 1.0);
  EXPECT_EQ(quaterniond[1], 2.0);
  EXPECT_EQ(quaterniond[2], 3.0);
  EXPECT_EQ(quaterniond[3], 4.0);
}

TEST_F(QuaternionTest, WXYZ) {
  EXPECT_EQ(quaternionf.w(), 1.0f);
  EXPECT_EQ(quaternionf.x(), 2.0f);
  EXPECT_EQ(quaternionf.y(), 3.0f);
  EXPECT_EQ(quaternionf.z(), 4.0f);

  EXPECT_EQ(quaterniond.w(), 1.0);
  EXPECT_EQ(quaterniond.x(), 2.0);
  EXPECT_EQ(quaterniond.y(), 3.0);
  EXPECT_EQ(quaterniond.z(), 4.0);
}

TEST_F(QuaternionTest, ABCD) {
  EXPECT_EQ(quaternionf.a(), 1.0f);
  EXPECT_EQ(quaternionf.b(), 2.0f);
  EXPECT_EQ(quaternionf.c(), 3.0f);
  EXPECT_EQ(quaternionf.d(), 4.0f);

  EXPECT_EQ(quaterniond.a(), 1.0);
  EXPECT_EQ(quaterniond.b(), 2.0);
  EXPECT_EQ(quaterniond.c(), 3.0);
  EXPECT_EQ(quaterniond.d(), 4.0);
}

TEST_F(QuaternionTest, Q0Q1Q2Q3) {
  EXPECT_EQ(quaternionf.q0(), 1.0f);
  EXPECT_EQ(quaternionf.q1(), 2.0f);
  EXPECT_EQ(quaternionf.q2(), 3.0f);
  EXPECT_EQ(quaternionf.q3(), 4.0f);

  EXPECT_EQ(quaterniond.q0(), 1.0);
  EXPECT_EQ(quaterniond.q1(), 2.0);
  EXPECT_EQ(quaterniond.q2(), 3.0);
  EXPECT_EQ(quaterniond.q3(), 4.0);
}

TEST_F(QuaternionTest, AccessScalarComponent) {
  EXPECT_EQ(quaternionf.s(), 1.0f);
  EXPECT_EQ(quaternionf.scalar(), 1.0f);

  EXPECT_EQ(quaterniond.s(), 1.0);
  EXPECT_EQ(quaterniond.scalar(), 1.0);
}

TEST_F(QuaternionTest, AccessVectorComponent) {
  Vector3F vecF = quaternionf.v();
  EXPECT_EQ(vecF.x(), 2.0f);
  EXPECT_EQ(vecF.y(), 3.0f);
  EXPECT_EQ(vecF.z(), 4.0f);

  Vector3D vecD = quaterniond.v();
  EXPECT_EQ(vecD.x(), 2.0);
  EXPECT_EQ(vecD.y(), 3.0);
  EXPECT_EQ(vecD.z(), 4.0);

  Vector3F vecF2 = quaternionf.vector();
  EXPECT_EQ(vecF2.x(), 2.0f);
  EXPECT_EQ(vecF2.y(), 3.0f);
  EXPECT_EQ(vecF2.z(), 4.0f);

  Vector3D vecD2 = quaterniond.vector();
  EXPECT_EQ(vecD2.x(), 2.0);
  EXPECT_EQ(vecD2.y(), 3.0);
  EXPECT_EQ(vecD2.z(), 4.0);
}

TEST_F(QuaternionTest, FromAngleAxisConstructor) {
  float angleF = degreesToRadians(90.0f);
  Vector3F axisF{0.0f, 0.0f, 1.0f};
  QuaternionF qfFromAngleAxis = QuaternionF::fromAngleAxis(angleF, axisF);
  expectNearQuaternionValues(
      qfFromAngleAxis,
      QuaternionF{cos(angleF / 2.0f), 0.0f, 0.0f, sin(angleF / 2.0f)});

  double angleD = degreesToRadians(90.0);
  Vector3D axisD{0.0, 0.0, 1.0};
  QuaternionD qdFromAngleAxis = QuaternionD::fromAngleAxis(angleD, axisD);
  expectNearQuaternionValues(
      qdFromAngleAxis,
      QuaternionD{cos(angleD / 2.0), 0.0, 0.0, sin(angleD / 2.0)});
}

TEST_F(QuaternionTest, FromEulerAnglesZYXConstructor) {
  float pitchF = degreesToRadians(45.0f);
  float yawF = degreesToRadians(60.0f);
  float rollF = degreesToRadians(30.0f);
  QuaternionF qfFromEuler =
      QuaternionF::fromEulerAnglesXYZ(pitchF, yawF, rollF);
  expectNearQuaternionValues(qfFromEuler, QuaternionF{0.8223632f, 0.2005621f,
                                                      0.5319757f, 0.02226003f});

  double pitchD = degreesToRadians(45.0);
  double yawD = degreesToRadians(60.0);
  double rollD = degreesToRadians(30.0);
  QuaternionD qdFromEuler =
      QuaternionD::fromEulerAnglesXYZ(pitchD, yawD, rollD);
  expectNearQuaternionValues(
      qdFromEuler, QuaternionD{0.8223631719059994, 0.20056212114657512,
                               0.5319756951821666, 0.02226002671473378});
}

TEST_F(QuaternionTest, FromEulerAnglesZYXVectorConstructor) {
  Vector3F eulerF = degreesToRadians(Vector3F{45.0f, 60.0f, 30.0f});
  QuaternionF qfFromEuler = QuaternionF::fromEulerAnglesXYZ(eulerF);
  expectNearQuaternionValues(qfFromEuler, QuaternionF{0.8223632f, 0.2005621f,
                                                      0.5319757f, 0.02226003f});

  Vector3D eulerD = degreesToRadians(Vector3D{45.0, 60.0, 30.0});
  QuaternionD qdFromEuler = QuaternionD::fromEulerAnglesXYZ(eulerD);
  expectNearQuaternionValues(
      qdFromEuler, QuaternionD{0.8223631719059994, 0.20056212114657512,
                               0.5319756951821666, 0.02226002671473378});
}

TEST_F(QuaternionTest, AssignmentOperator) {
  QuaternionF qf{0.5f, 0.6f, 0.7f, 0.8f};
  qf = quaternionf;
  expectNearQuaternionValues(qf, quaternionf);

  QuaternionD qd{0.5, 0.6, 0.7, 0.8};
  qd = quaterniond;
  expectNearQuaternionValues(qd, quaterniond);
}

TEST_F(QuaternionTest, PlusEqualOperator) {
  QuaternionF qf{0.5f, 0.6f, 0.7f, 0.8f};
  qf += quaternionf;
  expectNearQuaternionValues(qf, QuaternionF{1.5f, 2.6f, 3.7f, 4.8f});

  QuaternionD qd{0.5, 0.6, 0.7, 0.8};
  qd += quaterniond;
  expectNearQuaternionValues(qd, QuaternionD{1.5, 2.6, 3.7, 4.8});
}
}  // namespace Neat