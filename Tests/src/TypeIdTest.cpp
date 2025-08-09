#include <gtest/gtest.h>

#include "Neat/Utils/TypeId.hpp"

namespace Neat {
struct MyStruct {
  void foo() {}
};
struct MyOtherStruct {
  int method(int) { return 0x123; }
};
struct ThirdStruct : public MyStruct {};

TEST(TypeIdTest, GetTypeIdTest) {
  auto id1 = getTypeId<MyStruct>();
  auto id2 = getTypeId<MyOtherStruct>();
  auto id3 = getTypeId<MyStruct>();
  auto id4 = getTypeId<ThirdStruct>();
  EXPECT_EQ(id1, id3);
  EXPECT_NE(id1, id2);
  EXPECT_NE(id2, id3);
  EXPECT_NE(id4, id3);
  EXPECT_NE(id4, id2);
  EXPECT_EQ(getTypeId<int>(), getTypeId<int>());
  EXPECT_NE(getTypeId<float>(), getTypeId<int>());
  EXPECT_NE(getTypeId<double>(), getTypeId<float>());
}

TEST(TypeIdTest, GetTypeIdConstTest) {
  auto id1 = getTypeId<const MyStruct>();
  auto id2 = getTypeId<MyStruct>();
  auto id3 = getTypeId<const MyOtherStruct>();
  auto id4 = getTypeId<MyOtherStruct>();
  EXPECT_EQ(id1, id2);
  EXPECT_NE(id1, id3);
  EXPECT_NE(id1, id4);
  EXPECT_NE(id2, id3);
  EXPECT_EQ(id3, id4);
}

TEST(TypeIdTest, GetTypeIdReferenceTest) {
  auto id1 = getTypeId<MyStruct &>();
  auto id2 = getTypeId<MyStruct>();
  auto id3 = getTypeId<MyStruct &&>();
  EXPECT_EQ(id1, id2);
  EXPECT_EQ(id1, id3);
  EXPECT_EQ(id2, id3);
}

TEST(TypeIdTest, GetTypeIdConstReferenceTest) {
  auto id1 = getTypeId<MyStruct &>();
  auto id2 = getTypeId<MyStruct>();
  auto id3 = getTypeId<MyStruct &&>();
  auto id4 = getTypeId<const MyStruct &>();
  auto id5 = getTypeId<const MyStruct>();
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

TEST(TypeIdTest, GetMethodIdTest) {
  auto id1 = getMethodId<&MyOtherStruct::method>();
  auto id2 = getMethodId<&MyStruct::foo>();
  auto id3 = getMethodId<&MyOtherStruct::method>();
  EXPECT_EQ(id1, id3);
  EXPECT_NE(id1, id2);
  EXPECT_NE(id2, id3);
  EXPECT_EQ(getMethodId<&printf>(), getMethodId<&printf>());
}
}  // namespace Neat