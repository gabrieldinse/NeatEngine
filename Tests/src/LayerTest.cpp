#include <gtest/gtest.h>

#include <Core/Layer.hpp>
#include <TestUtils.hpp>

namespace Neat {
TEST(LayerTest, LayerID) {
  TestingLayer layer1;
  TestingLayer layer2;
  TestingLayer layer3;

  EXPECT_NE(layer1.getLayerID(), layer2.getLayerID());
  EXPECT_NE(layer1.getLayerID(), layer3.getLayerID());
  EXPECT_NE(layer2.getLayerID(), layer3.getLayerID());

  EXPECT_GT(layer3.getLayerID(), layer2.getLayerID());
  EXPECT_GT(layer2.getLayerID(), layer1.getLayerID());
}

TEST(LayerTest, EnableAndDisable) {
  TestingLayer layer;

  EXPECT_TRUE(layer.isEnabled());

  layer.disable();
  EXPECT_FALSE(layer.isEnabled());

  layer.enable();
  EXPECT_TRUE(layer.isEnabled());
}
}  // namespace Neat