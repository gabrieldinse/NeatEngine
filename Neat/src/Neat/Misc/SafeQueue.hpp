#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

#include "Neat/Core/Types.hpp"

namespace Neat {
template <typename T>
class SafeQueue {
 public:
  SafeQueue();
  ~SafeQueue();
  std::optional<T> tryPop(UInt64 timeoutMilliseconds = 500);
  void push(T &&element);
  void push(const T &element);

 private:
  std::queue<T> m_queue;
  mutable std::mutex m_mutex;
  std::condition_variable m_queueNotEmptyCondition;
};
}  // namespace Neat

#include "Neat/Misc/SafeQueue.inl"