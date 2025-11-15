#include <gtest/gtest.h>

#include "TestUtils.hpp"
#include "Math/Common.hpp"

namespace Neat {
TEST(MathCommonTest, Min) {
  EXPECT_EQ(min(3, 5), 3);
  EXPECT_EQ(min(-1.5f, -2.5f), -2.5f);
  EXPECT_EQ(min(2.0, 3.0), 2.0);
  EXPECT_EQ(min(4.0f, 4.0f), 4.0f);
}

TEST(MathCommonTest, Max) {
  EXPECT_EQ(max(3, 5), 5);
  EXPECT_EQ(max(-1.5f, -2.5f), -1.5f);
  EXPECT_EQ(max(2.0, 3.0), 3.0);
  EXPECT_EQ(max(4.0f, 4.0f), 4.0f);
}

TEST(MathCommonTest, Abs) {
  EXPECT_EQ(abs(-5), 5);
  EXPECT_EQ(abs(3), 3);
  EXPECT_FLOAT_EQ(abs(-2.5f), 2.5f);
  EXPECT_FLOAT_EQ(abs(4.0f), 4.0f);
  EXPECT_DOUBLE_EQ(abs(-3.5), 3.5);
  EXPECT_DOUBLE_EQ(abs(6.0), 6.0);
}

TEST(MathCommonTest, Round) {
  EXPECT_EQ(round(3.2f), 3);
  EXPECT_EQ(round(3.5f), 4);
  EXPECT_EQ(round(3.7f), 4);
  EXPECT_EQ(round(-2.3f), -2);
  EXPECT_EQ(round(-2.5f), -3);
  EXPECT_EQ(round(-2.7f), -3);

  EXPECT_EQ(round(4.2), 4);
  EXPECT_EQ(round(4.5), 5);
  EXPECT_EQ(round(4.7), 5);
  EXPECT_EQ(round(-3.3), -3);
  EXPECT_EQ(round(-3.5), -4);
  EXPECT_EQ(round(-3.8), -4);
}

TEST(MathCommonTest, Trunc) {
  EXPECT_EQ(trunc(3.9f), 3);
  EXPECT_EQ(trunc(-2.9f), -2);
  EXPECT_EQ(trunc(4.8), 4);
  EXPECT_EQ(trunc(-3.8), -3);
  EXPECT_EQ(trunc(5.0), 5);
}

TEST(MathCommonTest, Fract) {
  EXPECT_FLOAT_EQ(fract(3.75f), 0.75f);
  EXPECT_FLOAT_EQ(fract(-2.25f), 0.75f);
  EXPECT_DOUBLE_EQ(fract(4.6), 0.6);
  EXPECT_DOUBLE_EQ(fract(-3.4), 0.6);
  EXPECT_DOUBLE_EQ(fract(5.0), 0.0);
}

TEST(MathCommonTest, Mod) {
  EXPECT_FLOAT_EQ(mod(5.3f, 2.0f), 1.3f);
  EXPECT_FLOAT_EQ(mod(-5.3f, 2.0f), -1.3f);
  EXPECT_DOUBLE_EQ(mod(7.8, 3.0), 1.8);
  EXPECT_DOUBLE_EQ(mod(-7.8, 3.0), -1.8);
  EXPECT_EQ(mod(4.0, 2.0), 0.0);
  EXPECT_EQ(mod(-4.0, 2.0), 0.0);
  EXPECT_EQ(mod(5, 3), 2);
  EXPECT_EQ(mod(-3, 5), 2);
  EXPECT_EQ(mod(3, 5), 3);
}

TEST(MathCommonTest, Clamp) {
  EXPECT_EQ(clamp(5, 1, 10), 5);
  EXPECT_EQ(clamp(-2, 0, 5), 0);
  EXPECT_EQ(clamp(8, 0, 5), 5);

  EXPECT_FLOAT_EQ(clamp(3.5f, 1.0f, 4.0f), 3.5f);
  EXPECT_FLOAT_EQ(clamp(-1.0f, 0.0f, 2.0f), 0.0f);
  EXPECT_FLOAT_EQ(clamp(5.0f, 0.0f, 4.0f), 4.0f);

  EXPECT_DOUBLE_EQ(clamp(2.5, 1.0, 3.0), 2.5);
  EXPECT_DOUBLE_EQ(clamp(-2.0, 0.0, 4.0), 0.0);
  EXPECT_DOUBLE_EQ(clamp(6.0, 1.0, 5.0), 5.0);
}

TEST(MathCommonTest, Floor) {
  EXPECT_EQ(floor(3.7f), 3);
  EXPECT_EQ(floor(-2.3f), -3);
  EXPECT_EQ(floor(4.9), 4);
  EXPECT_EQ(floor(-3.1), -4);
}

TEST(MathCommonTest, Ceil) {
  EXPECT_EQ(ceil(3.2f), 4);
  EXPECT_EQ(ceil(-2.8f), -2);
  EXPECT_EQ(ceil(4.1), 5);
  EXPECT_EQ(ceil(-3.6), -3);
}

TEST(MathCommonTest, VectorMin) {
  Vector3F vecA{3.0f, 5.0f, 2.0f};
  Vector3F vecB{4.0f, 1.0f, 6.0f};
  Vector3F result = min(vecA, vecB);
  expectNearVectorValues(result, (Vector3F{3.0f, 1.0f, 2.0f}));

  Vector4D vecC{2.0, 7.0, 4.0, 9.0};
  Vector4D vecD{5.0, 3.0, 6.0, 1.0};
  Vector4D resultD = min(vecC, vecD);

  expectNearVectorValues(resultD, (Vector4D{2.0, 3.0, 4.0, 1.0}));
}

TEST(MathCommonTest, VectorMax) {
  Vector3F vecA{3.0f, 5.0f, 2.0f};
  Vector3F vecB{4.0f, 1.0f, 6.0f};
  Vector3F result = max(vecA, vecB);
  expectNearVectorValues(result, (Vector3F{4.0f, 5.0f, 6.0f}));

  Vector4D vecC{2.0, 7.0, 4.0, 9.0};
  Vector4D vecD{5.0, 3.0, 6.0, 1.0};
  Vector4D resultD = max(vecC, vecD);
  expectNearVectorValues(resultD, (Vector4D{5.0, 7.0, 6.0, 9.0}));
}

TEST(MathCommonTest, VectorAbs) {
  Vector3F vecA{-3.0f, 5.0f, -2.0f};
  Vector3F result = abs(vecA);
  expectNearVectorValues(result, (Vector3F{3.0f, 5.0f, 2.0f}));

  Vector4D vecB{-2.0, -7.0, 4.0, -9.0};
  Vector4D resultD = abs(vecB);
  expectNearVectorValues(resultD, (Vector4D{2.0, 7.0, 4.0, 9.0}));
}

TEST(MathCommonTest, VectorRound) {
  Vector3F vecA{3.2f, 5.5f, -2.7f};
  Vector3F result = round(vecA);
  expectNearVectorValues(result, (Vector3F{3.0f, 6.0f, -3.0f}));

  Vector4D vecB{-2.3, -7.5, 4.6, 9.1};
  Vector4D resultD = round(vecB);
  expectNearVectorValues(resultD, (Vector4D{-2.0, -8.0, 5.0, 9.0}));
}

TEST(MathCommonTest, VectorTrunc) {
  Vector3F vecA{3.9f, -5.1f, 2.7f};
  Vector3F result = trunc(vecA);
  expectNearVectorValues(result, (Vector3F{3.0f, -5.0f, 2.0f}));

  Vector4D vecB{-2.8, 7.4, -4.9, 9.6};
  Vector4D resultD = trunc(vecB);
  expectNearVectorValues(resultD, (Vector4D{-2.0, 7.0, -4.0, 9.0}));
}

TEST(MathCommonTest, VectorFract) {
  Vector3F vecA{3.75f, -5.25f, 2.6f};
  Vector3F result = fract(vecA);
  expectNearVectorValues(result, (Vector3F{0.75f, 0.75f, 0.6f}));

  Vector4D vecB{-2.4, 7.9, -4.1, 9.0};
  Vector4D resultD = fract(vecB);
  expectNearVectorValues(resultD, (Vector4D{0.6, 0.9, 0.9, 0.0}));
}

TEST(MathCommonTest, VectorMod) {
  Vector3F vecA{5.3f, -5.3f, 7.8f};
  Vector3F vecA2{2.0f, 3.0f, 1.5f};
  Vector3F result = mod(vecA, vecA2);
  expectNearVectorValues(result, (Vector3F{1.3f, -2.3f, 0.3f}));

  Vector4D vecB{-7.8, 7.8, -9.6, 9.6};
  Vector4D vecB2{3.0, 3.0, 2.5, 4.0};
  Vector4D resultD = mod(vecB, vecB2);
  expectNearVectorValues(resultD, (Vector4D{-1.8, 1.8, -2.1, 1.6}));
}

TEST(MathCommonTest, VectorAndScalarMod) {
  Vector3F vecA{5.3f, -5.3f, 7.8f};
  float scalarA = 2.0f;
  Vector3F result = mod(vecA, scalarA);
  expectNearVectorValues(result, (Vector3F{1.3f, -1.3f, 1.8f}));

  Vector4D vecB{-7.8, 7.8, -9.6, 9.6};
  double scalarB = 3.0;
  Vector4D resultD = mod(vecB, scalarB);
  expectNearVectorValues(resultD, (Vector4D{-1.8, 1.8, -0.6, 0.6}));
}

TEST(MathCommonTest, VectorClamp) {
  Vector3F vecA{5.0f, -2.0f, 8.0f};
  Vector3F minVecA{1.0f, 0.0f, 3.0f};
  Vector3F maxVecA{6.0f, 4.0f, 7.0f};
  Vector3F result = clamp(vecA, minVecA, maxVecA);
  expectNearVectorValues(result, (Vector3F{5.0f, 0.0f, 7.0f}));

  Vector4D vecB{-2.0, 9.0, 4.0, -5.0};
  Vector4D minVecB{0.0, 3.0, 2.0, -1.0};
  Vector4D maxVecB{5.0, 7.0, 6.0, 1.0};
  Vector4D resultD = clamp(vecB, minVecB, maxVecB);
  expectNearVectorValues(resultD, (Vector4D{0.0, 7.0, 4.0, -1.0}));
}

TEST(MathCommonTest, VectorClampWithScalars) {
  Vector3F vecA{5.0f, -2.0f, 8.0f};
  float minA = 1.0f;
  float maxA = 6.0f;
  Vector3F result = clamp(vecA, minA, maxA);
  expectNearVectorValues(result, (Vector3F{5.0f, 1.0f, 6.0f}));

  Vector4D vecB{-2.0, 9.0, 4.0, -5.0};
  double minB = 0.0;
  double maxB = 7.0;
  Vector4D resultD = clamp(vecB, minB, maxB);
  expectNearVectorValues(resultD, (Vector4D{0.0, 7.0, 4.0, 0.0}));
}

TEST(MathCommonTest, VectorFloor) {
  Vector3F vecA{3.7f, -5.1f, 2.9f};
  Vector3F result = floor(vecA);
  expectNearVectorValues(result, (Vector3F{3.0f, -6.0f, 2.0f}));

  Vector4D vecB{-2.3, 7.8, -4.1, 9.6};
  Vector4D resultD = floor(vecB);
  expectNearVectorValues(resultD, (Vector4D{-3.0, 7.0, -5.0, 9.0}));
}

TEST(MathCommonTest, VectorCeil) {
  Vector3F vecA{3.2f, -5.8f, 2.1f};
  Vector3F result = ceil(vecA);
  expectNearVectorValues(result, (Vector3F{4.0f, -5.0f, 3.0f}));

  Vector4D vecB{-2.7, 7.1, -4.9, 9.2};
  Vector4D resultD = ceil(vecB);
  expectNearVectorValues(resultD, (Vector4D{-2.0, 8.0, -4.0, 10.0}));
}

TEST(MathCommonTest, VectorReflect) {
  Vector3F incident{1.0f, -1.0f, 0.0f};
  Vector3F normal{0.0f, 1.0f, 0.0f};
  Vector3F result = reflect(incident, normal);
  expectNearVectorValues(result, (Vector3F{1.0f, 1.0f, 0.0f}));

  Vector4D incidentD{2.0, -3.0, 1.0, 0.0};
  Vector4D normalD{0.0, 1.0, 0.0, 0.0};
  Vector4D resultD = reflect(incidentD, normalD);
  expectNearVectorValues(resultD, (Vector4D{2.0, 3.0, 1.0, 0.0}));
}

TEST(MathCommonTest, VectorRefract) {
  Vector3F incident{1.0f, -1.0f, 0.0f};
  incident = normalize(incident);
  Vector3F normal{0.0f, 1.0f, 0.0f};
  float eta = 1.0f / 1.5f;
  Vector3F result = refract(incident, normal, eta);
  Vector3F expected3{0.47140452f, -0.88191710f, 0.0f};

  expectNearVectorValues(result, expected3);

  Vector4D incidentD{2.0, -3.0, 1.0, 0.0};
  incidentD = normalize(incidentD);
  Vector4D normalD{0.0, 1.0, 0.0, 0.0};
  double etaD = 1.0 / 1.5;
  Vector4D resultD = refract(incidentD, normalD, etaD);
  Vector4D expected4{0.35634832254989918, -0.91766200000000000,
                     0.17817416127494959, 0.0};

  expectNearVectorValues(resultD, expected4);
}

}  // namespace Neat