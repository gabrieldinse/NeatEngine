#pragma once

#include <memory>
#include <array>

#include "Neat/Core/Types.h"
#include "Neat/Renderer/OrthographicCamera.h"
#include "Neat/Renderer/CustomShaders/TextureShader.h"
#include "Neat/Renderer/VertexArray.h"
#include "Neat/Renderer/Texture.h"


namespace Neat
{
   class Renderer2D
   {
   public:
      static void init();
      static void shutdown();

      static void beginScene(const OrthographicCamera& camera);
      static void endScene();

      // Primitives -----------------------------------------------------------
      // Quads
      static void drawQuad(const Vec2& position, const Vec2& size,
         const Vec4 color);

      static void drawQuad(const Vec3& position, const Vec2& size,
         const Vec4 color);

      static void drawQuad(const Vec2& position, const Vec2& size,
         const std::shared_ptr<Texture2D>& texture,
         const Vec4& tint = Vec4(1.0f), Float tilingFactor = 1.0f);

      static void drawQuad(const Vec3& position, const Vec2& size,
         const std::shared_ptr<Texture2D>& texture,
         const Vec4& tint = Vec4(1.0f), Float tilingFactor = 1.0f);

      // Rotated Quads
      static void drawRotatedQuad(const Vec2& position, const Vec2& size,
         Float angleDegrees, const Vec4 color);

      static void drawRotatedQuad(const Vec3& position, const Vec2& size,
         Float angleDegrees, const Vec4 color);

      static void drawRotatedQuad(const Vec2& position, const Vec2& size,
         Float angleDegrees, const std::shared_ptr<Texture2D>& texture,
         const Vec4& tint = Vec4(1.0f), Float tilingFactor = 1.0f);

      static void drawRotatedQuad(const Vec3& position, const Vec2& size,
         Float angleDegrees, const std::shared_ptr<Texture2D>& texture,
         const Vec4& tint = Vec4(1.0f), Float tilingFactor = 1.0f);
      // ----------------------------------------------------------------------

      struct Statistics
      {
         UInt drawCalls = 0;
         UInt quadCount = 0;

         UInt getTotalVertexCount() const { return quadCount * 4; }
         UInt getTotalIndexCount() const { return quadCount * 6; }
      };

      static Statistics getStats();
      static void resetStats();

   private:
      static void draw();
      static void startNewBatch();

   private:
      struct QuadVertexData
      {
         Vec3 position;
         Vec4 color;
         Vec2 textureCoordinate;
         Int textureIndex;
         Float tilingFactor;
      };

      struct QuadVextexDataBuffer
      {
         static constexpr UInt maxQuads = 10000;
         static constexpr UInt maxVertices = maxQuads * 4;
         static constexpr UInt maxIndexes = maxQuads * 6;
         static constexpr Vec4 defaultPositions[4] = {
               { -0.5f, -0.5f, 0.0f, 1.0f },
               { 0.5f, -0.5f, 0.0f, 1.0f },
               { 0.5f,  0.5f, 0.0f, 1.0f },
               { -0.5f,  0.5f, 0.0f, 1.0f }
               };

         UInt indexCount = 0;
         std::unique_ptr<QuadVertexData[]> data;
         QuadVertexData* currentPos = nullptr;

         QuadVextexDataBuffer()
            : data(std::make_unique<QuadVertexData[]>(
               QuadVextexDataBuffer::maxVertices))
         {
         }

         void addQuad(const Mat4& transform, const Vec4& color,
            const Vec2* textureCoordinates, Int textureIndex,
            Float tilingFactor)
         {
            for (SizeType i = 0; i < 4; ++i)
            {
               this->currentPos->position = transform * defaultPositions[i];
               this->currentPos->color = color;
               this->currentPos->textureCoordinate = textureCoordinates[i];
               this->currentPos->textureIndex = textureIndex;
               this->currentPos->tilingFactor = tilingFactor;
               this->currentPos++;
            }
            this->indexCount += 6;
         }

         IntLong getDataSize() const
         {
            return (IntLong)((Byte*)(this->currentPos) -
               (Byte*)(this->data.get())
               );
         }

         void reset()
         {
            this->indexCount = 0;
            this->currentPos = this->data.get();
         }
      };

      struct Renderer2DData
      {
         static constexpr const UInt maxTextureSlots = 32; // TODO: RenderCapatilities

         std::shared_ptr<VertexArray> quadVertexArray;
         std::shared_ptr<VertexBuffer> quadVertexBuffer;
         std::shared_ptr<TextureShader> textureShader;
         std::shared_ptr<Texture2D> whiteTexture;

         QuadVextexDataBuffer quadVextexDataBuffer;

         std::array<std::shared_ptr<Texture2D>, maxTextureSlots> textureSlots;
         Int textureSlotIndex = 1; // 0 = white texture

         Statistics stats;
      };

   private:
      static Renderer2DData data;
   };
}
