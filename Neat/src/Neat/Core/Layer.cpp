#include "NeatPCH.hpp"

#include "Layer.hpp"

namespace Neat {
Layer::~Layer() {}

void Layer::enable(const Ref<EventDispatcher> &eventDispatcher) {
  m_enabled = true;
  if (eventDispatcher) {
    eventDispatcher->enable(m_layerID);
  }
}

void Layer::disable(const Ref<EventDispatcher> &eventDispatcher) {
  m_enabled = false;
  if (eventDispatcher) {
    eventDispatcher->disable(m_layerID);
  }
}
}  // namespace Neat