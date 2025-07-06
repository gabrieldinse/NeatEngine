#pragma once

#include <array>
#include <memory>

#include "Neat/Core/Types.hpp"
#include "Neat/Graphics/Cameras/Camera.hpp"
#include "Neat/Graphics/Shaders.hpp"
#include "Neat/Graphics/Texture.hpp"
#include "Neat/Graphics/VertexArray.hpp"

namespace Neat {
class Renderer2D {
 public:
  static void init();
  static void shutdown();

  static void beginScene(const Camera &camera);
  static void endScene();

  // Primitives -----------------------------------------------------------
  // Quads
  static void drawQuad(const Vector2F &position, const Vector2F &size,
                       const Vector4F color);

  static void drawQuad(const Vector3F &position, const Vector2F &size,
                       const Vector4F color);

  static void drawQuad(const Vector2F &position, const Vector2F &size,
                       const std::shared_ptr<Texture2D> &texture,
                       const Vector4F &tint = Vector4F(1.0f),
                       float tilingFactor = 1.0f);

  static void drawQuad(const Vector3F &position, const Vector2F &size,
                       const std::shared_ptr<Texture2D> &texture,
                       const Vector4F &tint = Vector4F(1.0f),
                       float tilingFactor = 1.0f);

  // Rotated Quads
  static void drawRotatedQuad(const Vector2F &position, const Vector2F &size,
                              float angleDegrees, const Vector4F color);

  static void drawRotatedQuad(const Vector3F &position, const Vector2F &size,
                              float angleDegrees, const Vector4F color);

  static void drawRotatedQuad(const Vector2F &position, const Vector2F &size,
                              float angleDegrees,
                              const std::shared_ptr<Texture2D> &texture,
                              const Vector4F &tint = Vector4F(1.0f),
                              float tilingFactor = 1.0f);

  static void drawRotatedQuad(const Vector3F &position, const Vector2F &size,
                              float angleDegrees,
                              const std::shared_ptr<Texture2D> &texture,
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
  static void draw();
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
    static constexpr Vector4F defaultPositions[4] = {{-0.5f, -0.5f, 0.0f, 1.0f},
                                                     {0.5f, -0.5f, 0.0f, 1.0f},
                                                     {0.5f, 0.5f, 0.0f, 1.0f},
                                                     {-0.5f, 0.5f, 0.0f, 1.0f}};

    UInt32 indexCount = 0;
    std::unique_ptr<QuadVertexData[]> data;
    QuadVertexData *currentPos = nullptr;

    QuadVextexDataBuffer()
        : data(std::make_unique<QuadVertexData[]>(
              QuadVextexDataBuffer::maxVertices)) {}

    void addQuad(const Matrix4F &modelMatrix, const Vector4F &color,
                 const Vector2F *textureCoordinates, Int32 textureIndex,
                 float tilingFactor) {
      for (std::size_t i = 0; i < 4; ++i) {
        currentPos->position = modelMatrix * defaultPositions[i];
        currentPos->color = color;
        currentPos->textureCoordinate = textureCoordinates[i];
        currentPos->textureIndex = textureIndex;
        currentPos->tilingFactor = tilingFactor;
        currentPos++;
      }
      indexCount += 6;
    }

    UInt32 getDataSize() const {
      return (UInt32)((Byte *)(currentPos) - (Byte *)(data.get()));
    }

    void reset() {
      indexCount = 0;
      currentPos = data.get();
    }
  };

  struct Renderer2DData {
    // TODO: RenderCapatilities
    static constexpr const UInt32 maxTextureSlots = 32;

    std::shared_ptr<VertexArray> quadVertexArray;
    std::shared_ptr<VertexBuffer> quadVertexBuffer;
    std::shared_ptr<TextureShader> textureShader;
    std::shared_ptr<Texture2D> whiteTexture;

    QuadVextexDataBuffer quadVextexDataBuffer;

    std::array<std::shared_ptr<Texture2D>, maxTextureSlots> textureSlots;
    UInt32 textureSlotIndex = 1;  // unit 0 = default white texture

    Statistics stats;
  };

 private:
  static Renderer2DData *s_data;
};
}  // namespace Neat
