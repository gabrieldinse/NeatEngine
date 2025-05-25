#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "Neat/Core/Layer.hpp"

namespace Neat {
class LayerGroup {
public:
  using LayerVector = std::vector<std::unique_ptr<Layer>>;
  using LayerVectorIt = LayerVector::iterator;
  using LayerVectorConstIt = LayerVector::const_iterator;
  using LayerVectorRevIt = LayerVector::reverse_iterator;
  using LayerVectorConstRevIt = LayerVector::const_reverse_iterator;

public:
  LayerGroup();
  ~LayerGroup();

  template <typename T, typename... Args> void pushLayer(Args &&...args);
  template <typename T, typename... Args> void pushOverlay(Args &&...args);
  void pushLayer(std::unique_ptr<Layer> &&layer);
  void pushOverlay(std::unique_ptr<Layer> &&layer);
  std::unique_ptr<Layer> popLayer(Int32 position);
  std::unique_ptr<Layer> popOverlay(Int32 position);

  LayerVectorIt begin() { return m_layers.begin(); }
  LayerVectorIt end() { return m_layers.end(); }
  LayerVectorConstIt begin() const { return m_layers.begin(); }
  LayerVectorConstIt end() const { return m_layers.end(); }
  LayerVectorRevIt rbegin() { return m_layers.rbegin(); }
  LayerVectorRevIt rend() { return m_layers.rend(); }
  LayerVectorConstRevIt rbegin() const { return m_layers.rbegin(); }
  LayerVectorConstRevIt rend() const { return m_layers.rend(); }

private:
  LayerVector m_layers;
  LayerVector::size_type m_insertIndex;
};

template <typename T, typename... Args>
void LayerGroup::pushLayer(Args &&...args) {
  pushLayer(std::make_unique<T>(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
void LayerGroup::pushOverlay(Args &&...args) {
  pushOverlay(std::make_unique<T>(std::forward<Args>(args)...));
}
} // namespace Neat