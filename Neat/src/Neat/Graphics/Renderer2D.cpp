#include "NeatPCH.hpp"

#include "Neat/Graphics/RenderCommand.hpp"
#include "Neat/Graphics/Renderer2D.hpp"
#include "Neat/Graphics/ShaderDataType.hpp"
#include "Neat/Math/Transform.hpp"
#include "Neat/Math/Trigonometric.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
Scope<Renderer2D::Renderer2DData> Renderer2D::s_data =
    makeScope<Renderer2D::Renderer2DData>();

void Renderer2D::init() {
  NT_PROFILE_FUNCTION();
  s_data->quadVertexArray = VertexArray::create();
  s_data->quadVertexBuffer =
      VertexBuffer::create(QuadVextexDataBuffer::maxVertices *
                           static_cast<UInt32>(sizeof(QuadVertexData)));

  s_data->quadVertexBuffer->setLayout(
      {{ShaderDataType::Vector4F, "position"},
       {ShaderDataType::Vector4F, "color"},
       {ShaderDataType::Vector2F, "textureCoordinate"},
       {ShaderDataType::Float, "textureIndex"},
       {ShaderDataType::Float, "tilingFactor"}});
  s_data->quadVertexArray->addVertexBuffer(s_data->quadVertexBuffer);

  std::array<UInt32, QuadVextexDataBuffer::maxIndexes> quadIndexes;
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

  auto squareIB = IndexBuffer::create(quadIndexes.data(), quadIndexes.size());

  s_data->quadVertexArray->setIndexBuffer(squareIB);

  s_data->whiteTexture = Texture2D::create(1, 1);
  UInt32 white_texture_data = 0xffffffff;
  s_data->whiteTexture->setData(&white_texture_data,
                                static_cast<UInt32>(sizeof(UInt32)));

  // Assign each sampler to a texture unit (sampler2d's 0-31 to texture
  // units 0-31)
  Int32 samplers[Renderer2DData::maxTextureSlots];
  for (std::size_t i = 0; i < Renderer2DData::maxTextureSlots; ++i)
    samplers[i] = (Int32)i;
  s_data->textureShader =
      ShaderProgram::create("./Resources/Shaders/Texture.glsl");
  s_data->textureShader->bind();
  s_data->textureShader->set(
      "u_textures[0]", samplers,
      static_cast<Int32>(sizeof(samplers) / sizeof(Int32)));

  s_data->textureSlots[0] = s_data->whiteTexture;
}

void Renderer2D::shutdown() {
  NT_PROFILE_FUNCTION();
  s_data.reset();
}

void Renderer2D::beginScene(const CameraComponent &camera,
                            const TransformComponent &cameraTransform) {
  NT_PROFILE_FUNCTION();
  beginScene(camera.getProjection(), inverse(cameraTransform.getTransform()));
}

void Renderer2D::beginScene(const Matrix4F &cameraProjection,
                            const Matrix4F &cameraView) {
  NT_PROFILE_FUNCTION();
  Matrix4F cameraTransform = cameraProjection * cameraView;
  s_data->textureShader->bind();
  s_data->textureShader->set("u_cameraTransform", cameraTransform);
  startNewBatch();
}

void Renderer2D::endScene() {
  NT_PROFILE_FUNCTION();
  flush();
}

void Renderer2D::startNewBatch() {
  NT_PROFILE_FUNCTION();
  s_data->quadVextexDataBuffer.reset();
  s_data->textureSlotIndex = 1;
}

void Renderer2D::flush() {
  NT_PROFILE_FUNCTION();
  s_data->textureShader->bind();

  s_data->quadVertexBuffer->setData(s_data->quadVextexDataBuffer.data.data(),
                                    s_data->quadVextexDataBuffer.getDataSize());

  for (UInt32 i = 0; i < s_data->textureSlotIndex; ++i) {
    s_data->textureSlots[i]->bind(i);
  }

  RenderCommand::drawIndexed(s_data->quadVertexArray,
                             s_data->quadVextexDataBuffer.indexCount);

  s_data->stats.drawCalls++;
}

void Renderer2D::drawSprite(const TransformComponent &transform,
                            const RenderableSpriteComponent &renderableSprite) {
  NT_PROFILE_FUNCTION();
  drawSprite(transform.getTransform(), renderableSprite);
}

void Renderer2D::drawSprite(const Matrix4F &transform,
                            const RenderableSpriteComponent &renderableSprite) {
  NT_PROFILE_FUNCTION();
  if (renderableSprite.hasTexture()) {
    drawQuad(transform, renderableSprite.texture, renderableSprite.color,
             renderableSprite.tilingFactor);
  } else {
    drawQuad(transform, renderableSprite.color);
  }
}

void Renderer2D::drawQuad(const Matrix4F &transform,
                          const Ref<Texture2D> &texture, const Vector4F &tint,
                          float tilingFactor) {
  if (reachedBatchDataLimit()) {
    flush();
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

  s_data->quadVextexDataBuffer.addQuad(
      transform, tint, texture->getCoordinates(), textureIndex, tilingFactor);

  s_data->stats.quadCount++;
}

void Renderer2D::drawQuad(const Matrix4F &transform, const Vector4F &color) {
  NT_PROFILE_FUNCTION();
  if (reachedBatchDataLimit()) {
    flush();
    startNewBatch();
  }

  constexpr Int32 textureIndex = 0;  // white texture;
  constexpr float tilingFactor = 1.0f;
  constexpr Vector2F textureCoordinates[] = {
      {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

  s_data->quadVextexDataBuffer.addQuad(transform, color, textureCoordinates,
                                       textureIndex, tilingFactor);

  s_data->stats.quadCount++;
}

void Renderer2D::drawQuad(const Vector2F &position, const Vector2F &size,
                          const Vector4F &color) {
  NT_PROFILE_FUNCTION();
  drawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::drawQuad(const Vector3F &position, const Vector2F &size,
                          const Vector4F &color) {
  NT_PROFILE_FUNCTION();
  Matrix4F model_matrix =
      translate(position) * scale(Vector3F(size.x, size.y, 1.0f));
  drawQuad(model_matrix, color);
}

void Renderer2D::drawQuad(const Vector2F &position, const Vector2F &size,
                          const Ref<Texture2D> &texture, const Vector4F &tint,
                          float tilingFactor) {
  NT_PROFILE_FUNCTION();
  drawQuad({position.x, position.y, 0.0f}, size, texture, tint, tilingFactor);
}

void Renderer2D::drawQuad(const Vector3F &position, const Vector2F &size,
                          const Ref<Texture2D> &texture, const Vector4F &tint,
                          float tilingFactor) {
  NT_PROFILE_FUNCTION();
  Matrix4F model_matrix =
      translate(position) * scale(Vector3F(size.x, size.y, 1.0f));
  drawQuad(model_matrix, texture, tint, tilingFactor);
}

// Rotated Quads
void Renderer2D::drawRotatedQuad(const Vector2F &position, const Vector2F &size,
                                 float angleDegrees, const Vector4F &color) {
  NT_PROFILE_FUNCTION();
  drawRotatedQuad({position.x, position.y, 0.0f}, size, angleDegrees, color);
}

void Renderer2D::drawRotatedQuad(const Vector3F &position, const Vector2F &size,
                                 float angleDegrees, const Vector4F &color) {
  NT_PROFILE_FUNCTION();
  Matrix4F model_matrix = translate(Matrix4F(1.0f), position) *
                          rotateZ(degreesToRadians(angleDegrees)) *
                          scale(Vector3F(size.x, size.y, 1.0f));
  drawQuad(model_matrix, color);
}

void Renderer2D::drawRotatedQuad(const Vector2F &position, const Vector2F &size,
                                 float angleDegrees,
                                 const Ref<Texture2D> &texture,
                                 const Vector4F &tint, float tilingFactor) {
  NT_PROFILE_FUNCTION();
  drawRotatedQuad({position.x, position.y, 0.0f}, size, angleDegrees, texture,
                  tint, tilingFactor);
}

void Renderer2D::drawRotatedQuad(const Vector3F &position, const Vector2F &size,
                                 float angleDegrees,
                                 const Ref<Texture2D> &texture,
                                 const Vector4F &tint, float tilingFactor) {
  NT_PROFILE_FUNCTION();
  Matrix4F model_matrix = translate(position) *
                          rotateZ(degreesToRadians(angleDegrees)) *
                          scale(Vector3F(size.x, size.y, 1.0f));
  drawQuad(model_matrix, texture, tint, tilingFactor);
}

// Statistics
Renderer2D::Statistics Renderer2D::getStats() { return s_data->stats; }

void Renderer2D::resetStats() { s_data->stats = Statistics{}; }
}  // namespace Neat
