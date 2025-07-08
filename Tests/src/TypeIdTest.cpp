#include <gtest/gtest.h>

#include "Neat/Misc/TypeId.hpp"

struct MyStruct {
  void foo() {}
};
struct MyOtherStruct {
  int method(int) { return 0x123; }
};
struct ThirdStruct : public MyStruct {};

TEST(TypeIdTest, GetTypeIdTest) {
  auto id1 = Neat::getTypeId<MyStruct>();
  auto id2 = Neat::getTypeId<MyOtherStruct>();
  auto id3 = Neat::getTypeId<MyStruct>();
  auto id4 = Neat::getTypeId<ThirdStruct>();
  EXPECT_EQ(id1, id3);
  EXPECT_NE(id1, id2);
  EXPECT_NE(id2, id3);
  EXPECT_NE(id4, id3);
  EXPECT_NE(id4, id2);
  EXPECT_EQ(Neat::getTypeId<int>(), Neat::getTypeId<int>());
  EXPECT_NE(Neat::getTypeId<float>(), Neat::getTypeId<int>());
  EXPECT_NE(Neat::getTypeId<double>(), Neat::getTypeId<float>());
}

TEST(TypeIdTest, GetMethodIdTest) {
  auto id1 = Neat::getMethodId<&MyOtherStruct::method>();
  auto id2 = Neat::getMethodId<&MyStruct::foo>();
  auto id3 = Neat::getMethodId<&MyOtherStruct::method>();
  EXPECT_EQ(id1, id3);
  EXPECT_NE(id1, id2);
  EXPECT_NE(id2, id3);
  EXPECT_EQ(Neat::getMethodId<&printf>(), Neat::getMethodId<&printf>());
}