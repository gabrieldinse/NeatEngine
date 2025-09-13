#pragma once

#include <initializer_list>
#include <vector>

#include "VertexBufferElement.hpp"

#include "Neat/Core/PlatformDetection.hpp"
#include "Neat/Core/Types.hpp"

namespace Neat {
class VertexBufferLayout {
 public:
  using BufferElementsVector = std::vector<VertexBufferElement>;
  using BufferElementsVectorIt = BufferElementsVector::iterator;
  using BufferElementsVectorConstIt = BufferElementsVector::const_iterator;

 public:
  VertexBufferLayout() = default;

  VertexBufferLayout(
      const std::initializer_list<VertexBufferElement> &elements);

  UInt32 getOffset() const { return m_offset; }
  const BufferElementsVector &getElements() const { return m_elements; }

  BufferElementsVectorIt begin() { return m_elements.begin(); }
  BufferElementsVectorIt end() { return m_elements.end(); }
  BufferElementsVectorConstIt begin() const { return m_elements.begin(); }
  BufferElementsVectorConstIt end() const { return m_elements.end(); }

 private:
  BufferElementsVector m_elements;
  UInt32 m_offset = 0;
};
}  // namespace Neat