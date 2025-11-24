#include <gtest/gtest.h>

#include <ranges>

#include <TestUtils.hpp>

namespace Neat {
TEST(LayerGroupTest, PushLayers) {
  LayerGroup layerGroup;
  EXPECT_EQ(layerGroup.size(), 0);

  layerGroup.pushLayer<TestingLayer>();
  EXPECT_EQ(layerGroup.size(), 1);

  layerGroup.pushLayer<TestingLayer>();
  EXPECT_EQ(layerGroup.size(), 2);

  layerGroup.pushOverlay<TestingLayer>();
  EXPECT_EQ(layerGroup.size(), 3);

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

TEST(LayerGroupTest, PopLayersAndOverlays) {
  LayerGroup layerGroup;
  layerGroup.pushLayer<TestingLayer>();
  layerGroup.pushLayer<TestingLayer>();
  layerGroup.pushOverlay<TestingLayer>();
  layerGroup.pushOverlay<TestingLayer>();

  EXPECT_EQ(layerGroup.size(), 4);

  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>(layerGroup.begin()->get())->detached);
  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->detached);
  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>((layerGroup.end() - 2)->get())->detached);
  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>((layerGroup.end() - 1)->get())->detached);

  auto layer1 = layerGroup.popLayer(0);
  EXPECT_EQ(layerGroup.size(), 3);
  EXPECT_TRUE(dynamic_cast<TestingLayer *>(layer1.get())->detached);

  auto layer2 = layerGroup.popLayer(0);
  EXPECT_EQ(layerGroup.size(), 2);
  EXPECT_TRUE(dynamic_cast<TestingLayer *>(layer2.get())->detached);

  auto overlay1 = layerGroup.popOverlay(1);
  EXPECT_EQ(layerGroup.size(), 1);
  EXPECT_TRUE(dynamic_cast<TestingLayer *>(overlay1.get())->detached);

  auto overlay2 = layerGroup.popOverlay(0);
  EXPECT_EQ(layerGroup.size(), 0);
  EXPECT_TRUE(dynamic_cast<TestingLayer *>(overlay2.get())->detached);
}

TEST(LayerGroupTest, DisableAndEnableLayers) {
  LayerGroup layerGroup;
  layerGroup.pushLayer<TestingLayer>();
  layerGroup.pushOverlay<TestingLayer>();

  EXPECT_EQ(layerGroup.size(), 2);
  EXPECT_TRUE(layerGroup.begin()->get()->isEnabled());
  EXPECT_TRUE((layerGroup.begin() + 1)->get()->isEnabled());
  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>((layerGroup.begin())->get())->detached);
  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>((layerGroup.begin())->get())->attached);
  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>((layerGroup.begin())->get())->updated);
  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->detached);
  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->attached);
  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->updated);

  layerGroup.update(0.16);
  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>((layerGroup.begin())->get())->updated);
  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->updated);

  // One disabled
  dynamic_cast<TestingLayer *>((layerGroup.begin())->get())->updated = false;
  dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->updated =
      false;

  (*layerGroup.begin())->disable();
  EXPECT_FALSE((*layerGroup.begin())->isEnabled());
  EXPECT_TRUE((*(layerGroup.begin() + 1))->isEnabled());

  layerGroup.update(0.16);

  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>((layerGroup.begin())->get())->updated);
  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->updated);

  // Both disabled
  dynamic_cast<TestingLayer *>((layerGroup.begin())->get())->updated = false;
  dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->updated =
      false;

  (*(layerGroup.begin() + 1))->disable();
  EXPECT_FALSE((*layerGroup.begin())->isEnabled());
  EXPECT_FALSE((*(layerGroup.begin() + 1))->isEnabled());

  layerGroup.update(0.16);

  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>((layerGroup.begin())->get())->updated);
  EXPECT_FALSE(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->updated);

  // Both enabled again
  dynamic_cast<TestingLayer *>((layerGroup.begin())->get())->updated = false;
  dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->updated =
      false;

  for (auto &layer : layerGroup) {
    layer->enable();
  }
  EXPECT_TRUE((*layerGroup.begin())->isEnabled());
  EXPECT_TRUE((*(layerGroup.begin() + 1))->isEnabled());

  layerGroup.update(0.16);

  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>((layerGroup.begin())->get())->updated);
  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->updated);
}

TEST(LayerGroupTest, PushLayersAndOverlays) {
  LayerGroup layerGroup;

  layerGroup.pushLayer<TestingLayer>();
  EXPECT_EQ(layerGroup.size(), 1);

  layerGroup.pushOverlay<TestingLayer>();
  EXPECT_EQ(layerGroup.size(), 2);

  layerGroup.pushLayer<TestingLayer>();
  EXPECT_EQ(layerGroup.size(), 3);

  layerGroup.pushOverlay<TestingLayer>();
  EXPECT_EQ(layerGroup.size(), 4);

  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>(layerGroup.begin()->get())->attached);
  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->attached);
  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 2)->get())->attached);
  EXPECT_TRUE(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 3)->get())->attached);
}

TEST(LayerGroupTest, UpdateLayersAndOverlays) {
  LayerGroup layerGroup;

  TestingLayer::layerIDCounter = 0;
  layerGroup.pushLayer<TestingLayer>();    // first, id: 1
  layerGroup.pushOverlay<TestingLayer>();  // third, id: 2
  layerGroup.pushLayer<TestingLayer>();    // second, id: 3
  layerGroup.pushOverlay<TestingLayer>();  // fourth, id: 4

  for (auto &layer : layerGroup) {
    EXPECT_FALSE(dynamic_cast<TestingLayer *>(layer.get())->updated);
  }

  for (auto &&[index, layer] : std::ranges::views::enumerate(layerGroup)) {
    layer->update(0.16);
    dynamic_cast<TestingLayer *>(layer.get())->updateIndex = index;
    EXPECT_EQ(dynamic_cast<TestingLayer *>(layer.get())->updateIndex, index);
  }

  for (auto &layer : layerGroup) {
    EXPECT_TRUE(dynamic_cast<TestingLayer *>(layer.get())->updated);
  }

  EXPECT_EQ(dynamic_cast<TestingLayer *>((layerGroup.begin() + 0)->get())
                ->updateIndex,
            0);
  EXPECT_EQ(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 0)->get())->layerID,
      0);

  EXPECT_EQ(dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())
                ->updateIndex,
            1);
  EXPECT_EQ(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 1)->get())->layerID,
      2);

  EXPECT_EQ(dynamic_cast<TestingLayer *>((layerGroup.begin() + 2)->get())
                ->updateIndex,
            2);
  EXPECT_EQ(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 2)->get())->layerID,
      1);

  EXPECT_EQ(dynamic_cast<TestingLayer *>((layerGroup.begin() + 3)->get())
                ->updateIndex,
            3);
  EXPECT_EQ(
      dynamic_cast<TestingLayer *>((layerGroup.begin() + 3)->get())->layerID,
      3);
}
}  // namespace Neat