#pragma once

#include <vector>

#include "Neat/Core/Assert.hpp"
#include "Neat/Core/Types.hpp"

namespace Neat {
// ---------------------------------------------------------------------- //
// BaseMemoryPool ------------------------------------------------------- //
// ---------------------------------------------------------------------- //
class BaseMemoryPool {
 public:
  explicit BaseMemoryPool(std::size_t elementSize, std::size_t blockSize)
      : m_elementSize(elementSize), m_blockSize(blockSize) {}

  virtual ~BaseMemoryPool();

  UInt32 size() const { return static_cast<UInt32>(m_size); }
  UInt32 capacity() const { return static_cast<UInt32>(m_capacity); }
  UInt32 chunks() const { return static_cast<UInt32>(m_memoryBlocks.size()); }

  void resize(std::size_t count);
  void reserve(std::size_t count);

  void *at(std::size_t n) {
    NT_CORE_ASSERT(n < m_size, "Memory pool index out of range!");

    return &m_memoryBlocks[n / m_blockSize][(n % m_blockSize) * m_elementSize];
  }

  const void *at(std::size_t n) const {
    NT_CORE_ASSERT(n < m_size, "Memory pool index out of range!");

    return &m_memoryBlocks[n / m_blockSize][(n % m_blockSize) * m_elementSize];
  }

  void *operator[](std::size_t n) { return at(n); }
  const void *operator[](std::size_t n) const { return at(n); }

  virtual void destroy(std::size_t n) = 0;

 protected:
  std::size_t m_elementSize;
  std::size_t m_blockSize;
  std::vector<Byte *> m_memoryBlocks;
  std::size_t m_size = 0;
  std::size_t m_capacity = 0;
};

// ---------------------------------------------------------------------- //
// MemoryPool ----------------------------------------------------------- //
// ---------------------------------------------------------------------- //
template <typename T, std::size_t BlockSize = 8192>
class MemoryPool : public BaseMemoryPool {
 public:
  MemoryPool() : BaseMemoryPool(sizeof(T), BlockSize) {}

  virtual ~MemoryPool() = default;

  virtual void destroy(std::size_t n) override {
    T *ptr = static_cast<T *>(this->at(n));
    ptr->~T();
  }

  template <typename... Args>
  void construct(std::size_t n, Args &&...args) {
    new (this->at(n)) T(std::forward<Args>(args)...);
  }
};
}  // namespace Neat