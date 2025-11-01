#include <gtest/gtest.h>

#include <Core/LayerGroup.hpp>
#include <TestUtils.hpp>

namespace Neat {
TEST(LayerGroupTest, PushLayers) {
  LayerGroup layerGroup;
  EXPECT_EQ(layerGroup.size(), 0);

  layerGroup.pushLayer<TestingLayer>();
  layerGroup.pushLayer<TestingLayer>();
  layerGroup.pushOverlay<TestingLayer>();
  layerGroup.pushOverlay<TestingLayer>();

  EXPECT_EQ(layerGroup.size(), 4);
  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>(layerGroup.begin()->get())->attached);
  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->attached);
  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>((layerGroup.end() - 2)->get())->attached);
  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>((layerGroup.end() - 1)->get())->attached);
  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>(layerGroup.begin()->get())->detached);
  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->detached);
  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>((layerGroup.end() - 2)->get())->detached);
  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>((layerGroup.end() - 1)->get())->detached);
}
}  // namespace Neat