#include <gtest/gtest.h>

#include "TestUtils.hpp"
#include "Utils/TypeID.hpp"

namespace Neat {
TEST(TypeIdTest, GetTypeId) {
  auto id1 = getTypeID<MyStruct>();
  auto id2 = getTypeID<MyOtherStruct>();
  auto id3 = getTypeID<MyStruct>();
  auto id4 = getTypeID<ThirdStruct>();
  EXPECT_EQ(id1, id3);
  EXPECT_NE(id1, id2);
  EXPECT_NE(id2, id3);
  EXPECT_NE(id4, id3);
  EXPECT_NE(id4, id2);
  EXPECT_EQ(getTypeID<int>(), getTypeID<int>());
  EXPECT_NE(getTypeID<float>(), getTypeID<int>());
  EXPECT_NE(getTypeID<double>(), getTypeID<float>());
}

TEST(TypeIdTest, GetTypeIdConst) {
  auto id1 = getTypeID<const MyStruct>();
  auto id2 = getTypeID<MyStruct>();
  auto id3 = getTypeID<const MyOtherStruct>();
  auto id4 = getTypeID<MyOtherStruct>();
  EXPECT_EQ(id1, id2);
  EXPECT_NE(id1, id3);
  EXPECT_NE(id1, id4);
  EXPECT_NE(id2, id3);
  EXPECT_EQ(id3, id4);
}

TEST(TypeIdTest, GetTypeIdReference) {
  auto id1 = getTypeID<MyStruct &>();
  auto id2 = getTypeID<MyStruct>();
  auto id3 = getTypeID<MyStruct &&>();
  EXPECT_EQ(id1, id2);
  EXPECT_EQ(id1, id3);
  EXPECT_EQ(id2, id3);
}

TEST(TypeIdTest, GetTypeIdConstReference) {
  auto id1 = getTypeID<MyStruct &>();
  auto id2 = getTypeID<MyStruct>();
  auto id3 = getTypeID<MyStruct &&>();
  auto id4 = getTypeID<const MyStruct &>();
  auto id5 = getTypeID<const MyStruct>();
  EXPECT_EQ(id1, id2);
  EXPECT_EQ(id1, id3);
  EXPECT_EQ(id1, id4);
  EXPECT_EQ(id1, id5);
  EXPECT_EQ(id2, id3);
  EXPECT_EQ(id2, id4);
  EXPECT_EQ(id2, id5);
  EXPECT_EQ(id3, id4);
  EXPECT_EQ(id3, id5);
  EXPECT_EQ(id4, id5);
}

TEST(TypeIdTest, GetMethodId) {
  auto id1 = getMethodID<&MyOtherStruct::method>();
  auto id2 = getMethodID<&MyStruct::foo>();
  auto id3 = getMethodID<&MyOtherStruct::method>();
  EXPECT_EQ(id1, id3);
  EXPECT_NE(id1, id2);
  EXPECT_NE(id2, id3);
  EXPECT_EQ(getMethodID<&printf>(), getMethodID<&printf>());
}

TEST(TypeIdTest, GetInstanceID) {
  MyStruct a, b;
  MyStruct &refA = a;
  MyStruct *ptrA = &a;
  MyOtherStruct c;
  EXPECT_NE(getInstanceID(a), getInstanceID(b));
  EXPECT_NE(getInstanceID(a), getInstanceID(c));
  EXPECT_NE(getInstanceID(b), getInstanceID(c));
  EXPECT_EQ(getInstanceID(a), getInstanceID(a));
  EXPECT_EQ(getInstanceID(b), getInstanceID(b));
  EXPECT_EQ(getInstanceID(c), getInstanceID(c));
  EXPECT_EQ(getInstanceID(a), getInstanceID(refA));
  EXPECT_EQ(getInstanceID(a), getInstanceID(*ptrA));
}

TEST(TypeIdTest, GetMethodIdWithCallable) {
  auto lambda = [](int x) { return x * 2; };
  auto lambda2 = [](int x) { return x * 2; };

  auto id1 = getMethodID<&MyOtherStruct::method>();
  auto id2 = getMethodID(lambda);
  auto id3 = getMethodID(lambda);
  auto id4 = getMethodID(lambda2);

  EXPECT_EQ(id2, id3);
  EXPECT_NE(id1, id2);
  EXPECT_NE(id1, id3);
  EXPECT_NE(id1, id4);
  EXPECT_NE(id2, id4);
}

TEST(TypeIdTest, GetMethodIdPlainFunction) {
  auto id1 = getMethodID<&func1>();
  auto id2 = getMethodID<&func1>();
  auto id3 = getMethodID<&func2>();

  EXPECT_EQ(id1, id2);
  EXPECT_NE(id1, id3);
}
}  // namespace Neat