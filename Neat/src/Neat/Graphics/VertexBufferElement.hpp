#pragma once

#include <string>

#include "Neat/Core/Types.hpp"
#include "Neat/Graphics/ShaderDataType.hpp"

namespace Neat {
struct VertexBufferElement {
  ShaderDataType type;
  std::string name;
  UInt32 componentCount;
  bool normalized;
  UInt32 size;
  UInt32 offset = 0;
  UInt32 index = 0;

  VertexBufferElement() = default;

  VertexBufferElement(ShaderDataType type, const std::string &name,
                      bool normalized = false);
};
}  // namespace Neat