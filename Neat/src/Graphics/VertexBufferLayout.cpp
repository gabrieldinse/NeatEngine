#include "NeatPCH.hpp"

#include "VertexBufferLayout.hpp"

namespace Neat {
VertexBufferLayout::VertexBufferLayout(
    const std::initializer_list<VertexBufferElement> &elements)
    : m_elements(elements) {
  UInt32 index = 0;
  for (auto &element : m_elements) {
    element.index = index++;
    element.offset = m_offset;
    m_offset += element.size;
  }
}
}  // namespace Neat