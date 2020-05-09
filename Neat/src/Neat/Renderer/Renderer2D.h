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
      struct QuadVertex
      {
         Vec3 position;
         Vec4 color;
         Vec2 textureCoordinate;
         Float textureIndex;
         Float tilingFactor;
      };


      struct Renderer2DData
      {
         static constexpr const UInt maxQuads = 10000;
         static constexpr const UInt maxVertices = maxQuads * 4;
         static constexpr const UInt maxIndexes = maxQuads * 6;
         static constexpr const UInt maxTextureSlots = 32; // TODO: RenderCapatilities

         std::shared_ptr<VertexArray> quadVertexArray;
         std::shared_ptr<VertexBuffer> quadVertexBuffer;
         std::shared_ptr<TextureShader> textureShader;
         std::shared_ptr<Texture2D> whiteTexture;

         UInt quadIndexCount = 0;
         std::unique_ptr<QuadVertex[]> quadVertexBufferBase;
         QuadVertex* quadVertexBufferPtr = nullptr;

         std::array<std::shared_ptr<Texture2D>, maxTextureSlots> textureSlots;
         UInt textureSlotIndex = 1; // 0 = white texture

         Vec4 quadVertexPositions[4];

         Statistics stats;
      };

   private:
      static Renderer2DData data;
   };
}
