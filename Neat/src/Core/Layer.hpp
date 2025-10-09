#pragma once

#include <string>

#include "PlatformDetection.hpp"
#include "Types.hpp"

#include "EventDispatching/EventDispatcher.hpp"

namespace Neat {
class Layer {
 public:
  Layer() = default;
  virtual ~Layer() = 0;

  virtual void attach() {}
  virtual void detach() {}
  virtual void update([[maybe_unused]] double deltaTimeSeconds) {}
  virtual bool isEnabled() const { return m_enabled; }
  LayerID getLayerID() const { return m_layerID; }
  void enable(const Ref<EventDispatcher> &eventDispatcher = nullptr);
  void disable(const Ref<EventDispatcher> &eventDispatcher = nullptr);

 private:
  static LayerID getNewLayerID() {
    static LayerID layerIdCounter = 0;
    return layerIdCounter++;
  }

 private:
  LayerID m_layerID = getNewLayerID();
  bool m_enabled = true;
};
}  // namespace Neat