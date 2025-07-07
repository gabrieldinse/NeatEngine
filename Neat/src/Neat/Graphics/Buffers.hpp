#pragma once

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "Neat/Core/PlatformDetection.hpp"
#include "Neat/Core/Types.hpp"
#include "Neat/Graphics/ShaderDataType.hpp"

namespace Neat {
// ---------------------------------------------------------------------- //
// BufferElement -------------------------------------------------------- //
// ---------------------------------------------------------------------- //
struct BufferElement {
  ShaderDataType type;
  std::string name;
  UInt32 componentCount;
  bool normalized;
  UInt32 size;
  UInt32 offset = 0;
  UInt32 index = 0;

  BufferElement() = default;

  BufferElement(ShaderDataType type, const std::string &name,
                bool normalized = false);
};

// ---------------------------------------------------------------------- //
// BUfferLayout --------------------------------------------------------- //
// ---------------------------------------------------------------------- //
class BufferLayout {
 public:
  using BufferElementsVector = std::vector<BufferElement>;
  using BufferElementsVectorIt = BufferElementsVector::iterator;
  using BufferElementsVectorConstIt = BufferElementsVector::const_iterator;

 public:
  BufferLayout() = default;

  BufferLayout(const std::initializer_list<BufferElement> &elements);

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

// ---------------------------------------------------------------------- //
// VertexBuffer --------------------------------------------------------- //
// ---------------------------------------------------------------------- //
class VertexBuffer {
 public:
  virtual ~VertexBuffer() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual UInt32 getId() const = 0;

  virtual const BufferLayout &getLayout() const = 0;
  virtual void setLayout(const BufferLayout &layout) = 0;

  virtual void setData(const void *data, UInt32 size) = 0;

  static std::shared_ptr<VertexBuffer> create(UInt32 size);
  static std::shared_ptr<VertexBuffer> create(float *vertices, UInt32 size);
};

// ---------------------------------------------------------------------- //
// Indexbuffer ---------------------------------------------------------- //
// ---------------------------------------------------------------------- //
class IndexBuffer {
 public:
  virtual ~IndexBuffer() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual UInt32 getCount() const = 0;
  static std::shared_ptr<IndexBuffer> create(UInt32 *indices, UInt32 count);
};
}  // namespace Neat