#include <utility>
#include <optional>

namespace Neat {
template <typename T>
SafeQueue<T>::SafeQueue() {}

template <typename T>
SafeQueue<T>::~SafeQueue() {}

template <typename T>
std::optional<T> SafeQueue<T>::tryPop(UInt64 timeoutMilliseconds) {
  std::unique_lock unique_lock{m_mutex};
  if (not m_queue.empty() or
      m_queueNotEmptyCondition.wait_for(
          unique_lock, std::chrono::milliseconds(timeoutMilliseconds),
          [this] { return not m_queue.empty(); })) {
    T element = std::move(m_queue.front());
    m_queue.pop();
    return element;
  }
  return {};
}

template <typename T>
void SafeQueue<T>::push(T &&element) {
  std::lock_guard lock_guard(m_mutex);
  m_queue.push(std::move(element));
  m_queueNotEmptyCondition.notify_one();
}

template <typename T>
void SafeQueue<T>::push(const T &element) {
  std::lock_guard lock_guard(m_mutex);
  m_queue.push(element);
  m_queueNotEmptyCondition.notify_one();
}
}  // namespace Neat