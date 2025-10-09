#include "NeatPCH.hpp"

#include "LayerGroup.hpp"
#include "Log.hpp"

namespace Neat {
LayerGroup::LayerGroup() : m_insertIndex(0) {}

LayerGroup::~LayerGroup() {}

void LayerGroup::pushLayer(Scope<Layer> &&layer) {
  layer->attach();
  m_layers.emplace(begin() + m_insertIndex, std::move(layer));
  m_insertIndex++;
}

void LayerGroup::pushOverlay(Scope<Layer> &&layer) {
  layer->attach();
  m_layers.push_back(std::move(layer));
}

Scope<Layer> LayerGroup::popLayer(UInt32 position) {
  NT_CORE_ASSERT(position < m_layers.size(), "Invalid layer position!");
  auto layer = std::move(m_layers[position]);
  layer->detach();
  m_layers.erase(m_layers.begin() + position);
  m_insertIndex--;
  return layer;
}

Scope<Layer> LayerGroup::popOverlay(UInt32 position) {
  NT_CORE_ASSERT(position < m_layers.size(), "Invalid overlay position!");
  auto layer = std::move(m_layers[position]);
  layer->detach();
  m_layers.erase(m_layers.begin() + position);
  return layer;
}

void LayerGroup::update(double deltaTimeSeconds) {
  NT_PROFILE_FUNCTION();
  for (auto &layer : m_layers) {
    if (layer->isEnabled()) {
      layer->update(deltaTimeSeconds);
    }
  }
}
}  // namespace Neat