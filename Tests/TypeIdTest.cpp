#include <gtest/gtest.h>

#include "Neat/Misc/TypeId.hpp"

struct MyStruct {};
struct MyOtherStruct {};
struct ThirdStruct : public MyStruct {};

TEST(TypeIdTest, TestDifferentClassesIds) {
  auto id1 = Neat::typeId<MyStruct>();
  auto id2 = Neat::typeId<MyOtherStruct>();
  auto id3 = Neat::typeId<MyStruct>();
  auto id4 = Neat::typeId<ThirdStruct>();
  EXPECT_EQ(id1, id3);
  EXPECT_NE(id1, id2);
  EXPECT_NE(id2, id3);
  EXPECT_NE(id4, id3);
  EXPECT_NE(id4, id2);
}