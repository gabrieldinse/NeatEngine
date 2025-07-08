#include "NeatPCH.hpp"

#include "Neat/Graphics/VertexBufferElement.hpp"

namespace Neat {
VertexBufferElement::VertexBufferElement(ShaderDataType type,
                                         const std::string &name,
                                         bool normalized)
    : type(type),
      name(name),
      size(getShaderDataTypeSize(type)),
      componentCount(getShaderDataTypeComponentCount(type)),
      normalized(normalized) {}
}  // namespace Neat