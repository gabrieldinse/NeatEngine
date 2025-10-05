#pragma once

#include <string>

#include "ShaderDataType.hpp"

#include "Core/Types.hpp"

namespace Neat {
struct VertexBufferElement {
  ShaderDataType type;
  std::string name;
  UInt32 size;
  UInt32 componentCount;
  bool normalized;
  UInt32 offset = 0;
  UInt32 index = 0;

  VertexBufferElement() = default;

  VertexBufferElement(ShaderDataType type, const std::string &name,
                      bool normalized = false);
};
}  // namespace Neat