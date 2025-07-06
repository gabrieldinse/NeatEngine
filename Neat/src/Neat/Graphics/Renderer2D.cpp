#include "NeatPCH.hpp"

#include "Neat/Graphics/RenderCommand.hpp"
#include "Neat/Graphics/Renderer2D.hpp"
#include "Neat/Graphics/ShaderDataType.hpp"
#include "Neat/Math/Transform.hpp"
#include "Neat/Math/Trigonometric.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
Renderer2D::Renderer2DData *Renderer2D::s_data =
    new Renderer2D::Renderer2DData();

void Renderer2D::init() {
  s_data->quadVertexArray = std::make_shared<VertexArray>();
  s_data->quadVertexBuffer = std::make_shared<VertexBuffer>(
      QuadVextexDataBuffer::maxVertices * (UInt32)sizeof(QuadVertexData));

  s_data->quadVertexBuffer->setLayout(
      {{ShaderDataType::Vector4F, "position"},
       {ShaderDataType::Vector4F, "color"},
       {ShaderDataType::Vector2F, "textureCoordinate"},
       {ShaderDataType::Float, "textureIndex"},
       {ShaderDataType::Float, "tilingFactor"}});
  s_data->quadVertexArray->addVertexBuffer(s_data->quadVertexBuffer);

  auto quadIndexes =
      std::make_unique<UInt32[]>(QuadVextexDataBuffer::maxIndexes);
  UInt32 offset = 0;
  for (UInt32 i = 0; i < QuadVextexDataBuffer::maxIndexes;
       i += 6, offset += 4) {
    quadIndexes[(std::size_t)i + 0] = offset + 0;
    quadIndexes[(std::size_t)i + 1] = offset + 1;
    quadIndexes[(std::size_t)i + 2] = offset + 2;

    quadIndexes[(std::size_t)i + 3] = offset + 2;
    quadIndexes[(std::size_t)i + 4] = offset + 3;
    quadIndexes[(std::size_t)i + 5] = offset + 0;
  }

  auto squareIB = std::make_shared<IndexBuffer>(
      quadIndexes.get(), QuadVextexDataBuffer::maxIndexes);

  s_data->quadVertexArray->setIndexBuffer(squareIB);

  s_data->whiteTexture = std::make_shared<Texture2D>(1, 1);
  UInt32 white_texture_data = 0xffffffff;
  s_data->whiteTexture->setData(&white_texture_data, (UInt32)sizeof(UInt32));

  // Assign each sampler to a texture unit (sampler2d's 0-31 to texture
  // units 0-31)
  Int32 samplers[Renderer2DData::maxTextureSlots];
  for (std::size_t i = 0; i < Renderer2DData::maxTextureSlots; ++i)
    samplers[i] = (Int32)i;
  s_data->textureShader =
      std::make_shared<TextureShader>("./assets/shader_source/texture.glsl");
  s_data->textureShader->setTextures(samplers, (Int32)sizeof(samplers));

  s_data->textureSlots[0] = s_data->whiteTexture;
}

void Renderer2D::shutdown() { delete s_data; }

void Renderer2D::beginScene(const Camera &camera) {
  s_data->textureShader->setCameraTransform(camera.getCameraTransform());

  startNewBatch();
}

void Renderer2D::endScene() { draw(); }

void Renderer2D::startNewBatch() {
  s_data->quadVextexDataBuffer.reset();
  s_data->textureSlotIndex = 1;
}

void Renderer2D::draw() {
  s_data->textureShader->use();

  s_data->quadVertexBuffer->setData(s_data->quadVextexDataBuffer.data.get(),
                                    s_data->quadVextexDataBuffer.getDataSize());

  for (UInt32 i = 0; i < s_data->textureSlotIndex; ++i)
    s_data->textureSlots[i]->bind(i);

  RenderCommand::drawIndexed(s_data->quadVertexArray,
                             s_data->quadVextexDataBuffer.indexCount);

  s_data->stats.drawCalls++;
}

void Renderer2D::drawQuad(const Vector2F &position, const Vector2F &size,
                          const Vector4F color) {
  drawQuad({position.x, position.y, 0.0f}, size, color);
}

// Quads
void Renderer2D::drawQuad(const Vector3F &position, const Vector2F &size,
                          const Vector4F color) {
  if (reachedBatchDataLimit()) {
    draw();
    startNewBatch();
  }

  constexpr Int32 textureIndex = 0;  // white texture;
  constexpr float tilingFactor = 1.0f;
  constexpr Vector2F textureCoordinates[] = {
      {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

  auto model_matrix =
      translate(position) * scale(Vector3F(size.x, size.y, 1.0f));

  s_data->quadVextexDataBuffer.addQuad(model_matrix, color, textureCoordinates,
                                       textureIndex, tilingFactor);

  s_data->stats.quadCount++;
}

void Renderer2D::drawQuad(const Vector2F &position, const Vector2F &size,
                          const std::shared_ptr<Texture2D> &texture,
                          const Vector4F &tint, float tilingFactor) {
  drawQuad({position.x, position.y, 0.0f}, size, texture, tint, tilingFactor);
}

void Renderer2D::drawQuad(const Vector3F &position, const Vector2F &size,
                          const std::shared_ptr<Texture2D> &texture,
                          const Vector4F &tint, float tilingFactor) {
  if (reachedBatchDataLimit()) {
    draw();
    startNewBatch();
  }

  UInt32 textureIndex = 0;
  for (UInt32 i = 1; i < s_data->textureSlotIndex; ++i) {
    if (*s_data->textureSlots[i] == *texture) {
      textureIndex = i;
      break;
    }
  }

  if (textureIndex == 0) {
    textureIndex = s_data->textureSlotIndex;
    s_data->textureSlots[s_data->textureSlotIndex] = texture;
    s_data->textureSlotIndex++;
  }

  auto model_matrix =
      translate(position) * scale(Vector3F(size.x, size.y, 1.0f));

  s_data->quadVextexDataBuffer.addQuad(model_matrix, tint,
                                       texture->getCoordinates(), textureIndex,
                                       tilingFactor);

  s_data->stats.quadCount++;
}

// Rotated Quads
void Renderer2D::drawRotatedQuad(const Vector2F &position, const Vector2F &size,
                                 float angleDegrees, const Vector4F color) {
  drawRotatedQuad({position.x, position.y, 0.0f}, size, angleDegrees, color);
}

void Renderer2D::drawRotatedQuad(const Vector3F &position, const Vector2F &size,
                                 float angleDegrees, const Vector4F color) {
  if (reachedBatchDataLimit()) {
    draw();
    startNewBatch();
  }

  constexpr Int32 textureIndex = 0;  // white texture;
  constexpr float tilingFactor = 1.0f;
  constexpr Vector2F textureCoordinates[] = {
      {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

  auto model_matrix = translate(Matrix4F(1.0f), position) *
                      rotateZ(radians(angleDegrees)) *
                      scale(Vector3F(size.x, size.y, 1.0f));

  s_data->quadVextexDataBuffer.addQuad(model_matrix, color, textureCoordinates,
                                       textureIndex, tilingFactor);

  s_data->stats.quadCount++;
}

void Renderer2D::drawRotatedQuad(const Vector2F &position, const Vector2F &size,
                                 float angleDegrees,
                                 const std::shared_ptr<Texture2D> &texture,
                                 const Vector4F &tint, float tilingFactor) {
  drawRotatedQuad({position.x, position.y, 0.0f}, size, angleDegrees, texture,
                  tint, tilingFactor);
}

void Renderer2D::drawRotatedQuad(const Vector3F &position, const Vector2F &size,
                                 float angleDegrees,
                                 const std::shared_ptr<Texture2D> &texture,
                                 const Vector4F &tint, float tilingFactor) {
  if (reachedBatchDataLimit()) {
    draw();
    startNewBatch();
  }

  UInt32 textureIndex = 0;
  for (UInt32 i = 1; i < s_data->textureSlotIndex; ++i) {
    if (*s_data->textureSlots[i] == *texture) {
      textureIndex = i;
      break;
    }
  }

  if (textureIndex == 0) {
    textureIndex = s_data->textureSlotIndex;
    s_data->textureSlots[s_data->textureSlotIndex] = texture;
    s_data->textureSlotIndex++;
  }

  auto model_matrix = translate(position) * rotateZ(radians(angleDegrees)) *
                      scale(Vector3F(size.x, size.y, 1.0f));

  s_data->quadVextexDataBuffer.addQuad(model_matrix, tint,
                                       texture->getCoordinates(), textureIndex,
                                       tilingFactor);

  s_data->stats.quadCount++;
}

// Statistics
Renderer2D::Statistics Renderer2D::getStats() { return s_data->stats; }

void Renderer2D::resetStats() {
  std::memset(&s_data->stats, 0, sizeof(Statistics));
}
}  // namespace Neat
