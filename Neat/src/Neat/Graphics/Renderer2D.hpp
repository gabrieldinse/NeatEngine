#pragma once

#include <array>
#include <memory>

#include "Neat/Core/Types.hpp"
#include "Neat/Graphics/Color.hpp"
#include "Neat/Graphics/Texture2D.hpp"
#include "Neat/Graphics/VertexArray.hpp"
#include "Neat/Graphics/ShaderProgram.hpp"
#include "Neat/Components/RenderableSpriteComponent.hpp"
#include "Neat/Components/CameraComponent.hpp"
#include "Neat/Components/TransformComponent.hpp"

namespace Neat {
class Renderer2D {
 public:
  static void initialize();
  static void shutdown();

  static void beginScene(const CameraComponent &camera,
                         const TransformComponent &cameraTransform);
  static void beginScene(const Matrix4F &cameraProjection,
                         const Matrix4F &cameraView);
  static void endScene();

  static void drawSprite(const TransformComponent &transform,
                         const RenderableSpriteComponent &renderableSprite);
  static void drawSprite(const Matrix4F &transform,
                         const RenderableSpriteComponent &renderableSprite);
  static void drawQuad(const Matrix4F &transform, const Ref<Texture2D> &texture,
                       const Vector4F &tint, float tilingFactor);
  static void drawQuad(const Matrix4F &transform, const Vector4F &color);
  static void drawQuad(const Vector2F &position, const Vector2F &size,
                       const Vector4F &color);

  static void drawQuad(const Vector3F &position, const Vector2F &size,
                       const Vector4F &color);

  static void drawQuad(const Vector2F &position, const Vector2F &size,
                       const Ref<Texture2D> &texture,
                       const Vector4F &tint = Vector4F(1.0f),
                       float tilingFactor = 1.0f);

  static void drawQuad(const Vector3F &position, const Vector2F &size,
                       const Ref<Texture2D> &texture,
                       const Vector4F &tint = Vector4F(1.0f),
                       float tilingFactor = 1.0f);

  static void drawRotatedQuad(const Vector2F &position, const Vector2F &size,
                              float angleDegrees, const Vector4F &color);

  static void drawRotatedQuad(const Vector3F &position, const Vector2F &size,
                              float angleDegrees, const Vector4F &color);

  static void drawRotatedQuad(const Vector2F &position, const Vector2F &size,
                              float angleDegrees, const Ref<Texture2D> &texture,
                              const Vector4F &tint = Vector4F(1.0f),
                              float tilingFactor = 1.0f);

  static void drawRotatedQuad(const Vector3F &position, const Vector2F &size,
                              float angleDegrees, const Ref<Texture2D> &texture,
                              const Vector4F &tint = Vector4F(1.0f),
                              float tilingFactor = 1.0f);
  // ----------------------------------------------------------------------

  struct Statistics {
    UInt32 drawCalls = 0;
    UInt32 quadCount = 0;

    UInt32 getTotalVertexCount() const { return quadCount * 4; }
    UInt32 getTotalIndexCount() const { return quadCount * 6; }
  };

  static Statistics getStats();
  static void resetStats();

 private:
  static void flush();
  static void startNewBatch();
  static bool reachedBatchDataLimit() {
    return s_data->quadVextexDataBuffer.indexCount >=
           QuadVextexDataBuffer::maxIndexes;
  }

 private:
  struct QuadVertexData {
    Vector4F position{0.0f};
    Vector4F color{1.0f, 0.0f, 1.0f, 1.0f};
    Vector2F textureCoordinate{0.0f, 0.0f};
    Int32 textureIndex = 0;
    float tilingFactor = 1.0f;
  };

  struct QuadVextexDataBuffer {
    static constexpr UInt32 maxQuads = 10000;
    static constexpr UInt32 maxVertices = maxQuads * 4;
    static constexpr UInt32 maxIndexes = maxQuads * 6;
    static constexpr Vector4F centeredQuadPositions[4] = {
        {-0.5f, -0.5f, 0.0f, 1.0f},
        {0.5f, -0.5f, 0.0f, 1.0f},
        {0.5f, 0.5f, 0.0f, 1.0f},
        {-0.5f, 0.5f, 0.0f, 1.0f}};

    UInt32 indexCount = 0;
    std::array<QuadVertexData, QuadVextexDataBuffer::maxVertices> data;
    QuadVertexData *currentPos = nullptr;

    void addQuad(const Matrix4F &modelMatrix, const Vector4F &color,
                 const Vector2F *textureCoordinates, Int32 textureIndex,
                 float tilingFactor) {
      for (std::size_t i = 0; i < 4; ++i) {
        currentPos->position = modelMatrix * centeredQuadPositions[i];
        currentPos->color = color;
        currentPos->textureCoordinate = textureCoordinates[i];
        currentPos->textureIndex = textureIndex;
        currentPos->tilingFactor = tilingFactor;
        currentPos++;
      }
      indexCount += 6;
    }

    UInt32 getDataSize() const {
      return (UInt32)((Byte *)(currentPos) - (Byte *)(data.data()));
    }

    void reset() {
      indexCount = 0;
      currentPos = data.data();
    }
  };

  struct Renderer2DData {
    // TODO: RenderCapatilities
    static constexpr const UInt32 maxTextureSlots = 32;

    Ref<VertexArray> quadVertexArray;
    Ref<VertexBuffer> quadVertexBuffer;
    Ref<ShaderProgram> textureShader;
    Ref<Texture2D> whiteTexture;

    QuadVextexDataBuffer quadVextexDataBuffer;

    std::array<Ref<Texture2D>, maxTextureSlots> textureSlots;
    UInt32 textureSlotIndex = 1;  // unit 0 = default white texture

    Statistics stats;
  };

 private:
  static Scope<Renderer2DData> s_data;
};
}  // namespace Neat
