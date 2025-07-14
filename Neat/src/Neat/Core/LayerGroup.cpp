#include "NeatPCH.hpp"

#include "Neat/Core/LayerGroup.hpp"
#include "Neat/Core/Log.hpp"

namespace Neat {
LayerGroup::LayerGroup() : m_insertIndex(0) {}

LayerGroup::~LayerGroup() {}

void LayerGroup::pushLayer(Scope<Layer> &&layer) {
  layer->onAttach();
  m_layers.emplace(begin() + m_insertIndex, std::move(layer));
  m_insertIndex++;
}

void LayerGroup::pushOverlay(Scope<Layer> &&layer) {
  layer->onAttach();
  m_layers.push_back(std::move(layer));
}

Scope<Layer> LayerGroup::popLayer(UInt32 position) {
  NT_CORE_ASSERT(position < m_layers.size(), "Invalid layer position!");
  auto layer = std::move(m_layers[position]);
  layer->onDetach();
  m_layers.erase(m_layers.begin() + position);
  m_insertIndex--;
  return layer;
}

Scope<Layer> LayerGroup::popOverlay(UInt32 position) {
  NT_CORE_ASSERT(position < m_layers.size(), "Invalid overlay position!");
  auto layer = std::move(m_layers[position]);
  layer->onDetach();
  m_layers.erase(m_layers.begin() + position);
  return layer;
}
}  // namespace Neat