#pragma once

#include <vector>

#include "EventConnectionHandle.hpp"

namespace Neat {
class EventConnectionHandles {
 public:
  EventConnectionHandles() = default;
  ~EventConnectionHandles() = default;

  void add(const Ref<BaseEventConnectionHandle> &handle) {
    m_connectionHandles.push_back(handle);
  }

 private:
  std::vector<Ref<BaseEventConnectionHandle>> m_connectionHandles;
};
}  // namespace Neat