#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

#include "Core/Types.hpp"

namespace Neat {
template <typename T>
class SafeQueue {
 public:
  SafeQueue();
  ~SafeQueue();
  std::optional<T> tryPop(UInt64 timeoutMilliseconds = 0);
  void push(T &&element);
  void push(const T &element);
  bool empty() { return m_queue.empty(); }

 private:
  std::queue<T> m_queue;
  mutable std::mutex m_mutex;
  std::condition_variable m_queueNotEmptyCondition;
};
}  // namespace Neat

#include "Utils/SafeQueue.inl"