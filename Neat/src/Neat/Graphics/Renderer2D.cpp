#include "Neat/Graphics/Renderer2D.h"
#include "Neat/Graphics/RenderCommand.h"
#include "Neat/Graphics/ShaderDataType.h"
#include "Neat/Math/Transforms.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   Renderer2D::Renderer2DData Renderer2D::s_data;

   void Renderer2D::init()
   {
      s_data.quadVertexArray = std::make_shared<VertexArray>();
      s_data.quadVertexBuffer = std::make_shared<VertexBuffer>(
         QuadVextexDataBuffer::maxVertices * (UInt)sizeof(QuadVertexData));

      s_data.quadVertexBuffer->setLayout({
         { ShaderDataType::Vector4, "position" },
         { ShaderDataType::Vector4, "color"},
         { ShaderDataType::Vector2, "textureCoordinate"},
         { ShaderDataType::Float, "textureIndex"},
         { ShaderDataType::Float, "tilingFactor"}
         });
      s_data.quadVertexArray->addVertexBuffer(s_data.quadVertexBuffer);

      auto quadIndexes = std::make_unique<UInt[]>(
         QuadVextexDataBuffer::maxIndexes);
      UInt offset = 0;
      for (std::size_t i = 0; i < QuadVextexDataBuffer::maxIndexes; i += 6, offset += 4)
      {
         quadIndexes[i + 0] = offset + 0;
         quadIndexes[i + 1] = offset + 1;
         quadIndexes[i + 2] = offset + 2;

         quadIndexes[i + 3] = offset + 2;
         quadIndexes[i + 4] = offset + 3;
         quadIndexes[i + 5] = offset + 0;
      }

      auto squareIB = std::make_shared<IndexBuffer>(
         quadIndexes.get(), QuadVextexDataBuffer::maxIndexes);

      s_data.quadVertexArray->setIndexBuffer(squareIB);

      s_data.whiteTexture = std::make_shared<Texture2D>(1, 1);
      UInt white_texture_data = 0xffffffff;
      s_data.whiteTexture->setData(&white_texture_data, sizeof(UInt));

      Int samplers[Renderer2DData::maxTextureSlots];
      for (Int i = 0; i < Renderer2DData::maxTextureSlots; ++i)
         samplers[i] = i;

      s_data.textureShader = std::make_shared<TextureShader>(
         "assets/glsl/texture.glsl");
      s_data.textureShader->setTextures(samplers, sizeof(samplers));

      s_data.textureSlots[0] = s_data.whiteTexture;
   }

   void Renderer2D::shutdown()
   {
   }

   void Renderer2D::beginScene(const OrthographicCamera& camera)
   {
      s_data.textureShader->setProjectionViewMatrix(camera.getViewProjectionMatrix());

      startNewBatch();
   }

   void Renderer2D::endScene()
   {
      draw();
   }

   void Renderer2D::startNewBatch()
   {
      s_data.quadVextexDataBuffer.reset();
      s_data.textureSlotIndex = 1;
   }

   void Renderer2D::draw()
   {
      s_data.textureShader->bind();

      s_data.quadVertexBuffer->setData(
         s_data.quadVextexDataBuffer.m_data.get(),
         s_data.quadVextexDataBuffer.getDataSize());

      UInt index = 0;
      for (std::size_t i = 0; i < s_data.textureSlotIndex; ++i, ++index)
         s_data.textureSlots[i]->bind(index);

      RenderCommand::drawIndexed(s_data.quadVertexArray,
         s_data.quadVextexDataBuffer.indexCount);

      s_data.stats.drawCalls++;
   }

   void Renderer2D::drawQuad(const Vector2& position, const Vector2& size,
      const Vector4 color)
   {
      drawQuad({position.x, position.y, 0.0f}, size, color);
   }

   // Quads
   void Renderer2D::drawQuad(const Vector3& position, const Vector2& size,
      const Vector4 color)
   {
      if (s_data.quadVextexDataBuffer.indexCount >= QuadVextexDataBuffer::maxIndexes)
      {
         draw();
         startNewBatch();
      }

      constexpr Int textureIndex = 0; // white texture;
      constexpr float tilingFactor = 1.0f;
      constexpr Vector2 textureCoordinates[] = {
         {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}
      };

      auto transform = translate(position) * scale(Vector3(size.x, size.y, 1.0f));
      
      s_data.quadVextexDataBuffer.addQuad(
         transform, color, textureCoordinates, textureIndex, tilingFactor);

      s_data.stats.quadCount++;
   }

   void Renderer2D::drawQuad(const Vector2& position,const Vector2& size,
      const std::shared_ptr<Texture2D>& texture, const Vector4& tint,
      float tilingFactor)
   {
      drawQuad(
         {position.x, position.y, 0.0f}, size, texture, tint, tilingFactor);
   }

   void Renderer2D::drawQuad(
      const Vector3& position, const Vector2& size,
      const std::shared_ptr<Texture2D>& texture, const Vector4& tint,
      float tilingFactor)
   {
      if (s_data.quadVextexDataBuffer.indexCount >= QuadVextexDataBuffer::maxIndexes)
      {
         draw();
         startNewBatch();
      }

      Int textureIndex = 0;
      for (Int i = 1; i < s_data.textureSlotIndex; ++i)
      {
         if (*s_data.textureSlots[i] == *texture)
         {
            textureIndex = i;
            break;
         }
      }

      if (textureIndex == 0)
      {
         textureIndex = s_data.textureSlotIndex;
         s_data.textureSlots[s_data.textureSlotIndex] = texture;
         s_data.textureSlotIndex++;
      }

      auto transform = translate(position) * scale(Vector3(size.x, size.y, 1.0f));

      s_data.quadVextexDataBuffer.addQuad(
         transform, tint, texture->getCoordinates(), textureIndex, tilingFactor);

      s_data.stats.quadCount++;
   }

   // Rotated Quads 
   void Renderer2D::drawRotatedQuad(const Vector2& position, const Vector2& size,
      float angleDegrees, const Vector4 color)
   {
      drawRotatedQuad(
         { position.x, position.y, 0.0f }, size, angleDegrees, color);
   }

   void Renderer2D::drawRotatedQuad(const Vector3& position, const Vector2& size,
      float angleDegrees, const Vector4 color)
   {
      if (s_data.quadVextexDataBuffer.indexCount >= QuadVextexDataBuffer::maxIndexes)
      {
         draw();
         startNewBatch();
      }

      constexpr Int textureIndex = 0; // white texture;
      constexpr float tilingFactor = 1.0f;
      constexpr Vector2 textureCoordinates[] = {
         {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}
      };

      auto transform =
         translate(Matrix4(1.0f),position) *
         rotate(degreesToRadians(angleDegrees), { 0, 0, 1 }) *
         scale(Vector3(size.x, size.y, 1.0f));

      s_data.quadVextexDataBuffer.addQuad(
         transform, color, textureCoordinates, textureIndex, tilingFactor);

      s_data.stats.quadCount++;
   }

   void Renderer2D::drawRotatedQuad(const Vector2& position, const Vector2& size,
      float angleDegrees, const std::shared_ptr<Texture2D>& texture,
      const Vector4& tint, float tilingFactor)
   {
      drawRotatedQuad(
         { position.x, position.y, 0.0f },
         size, angleDegrees, texture, tint, tilingFactor);
   }

   void Renderer2D::drawRotatedQuad(
      const Vector3& position, const Vector2& size,
      float angleDegrees, const std::shared_ptr<Texture2D>& texture,
      const Vector4& tint, float tilingFactor)
   {
      if (s_data.quadVextexDataBuffer.indexCount >= QuadVextexDataBuffer::maxIndexes)
      {
         draw();
         startNewBatch();
      }

      Int textureIndex = 0;
      for (Int i = 1; i < s_data.textureSlotIndex; ++i)
      {
         if (*s_data.textureSlots[i] == *texture)
         {
            textureIndex = i;
            break;
         }
      }

      if (textureIndex == 0)
      {
         textureIndex = s_data.textureSlotIndex;
         s_data.textureSlots[s_data.textureSlotIndex] = texture;
         s_data.textureSlotIndex++;
      }

      auto transform =
         translate(position) *
         rotate(degreesToRadians(angleDegrees), { 0, 0, 1 }) *
         scale(Vector3(size.x, size.y, 1.0f));

      s_data.quadVextexDataBuffer.addQuad(
         transform, tint, texture->getCoordinates(), textureIndex, tilingFactor);

      s_data.stats.quadCount++;
   }

   // Statistics
   Renderer2D::Statistics Renderer2D::getStats()
   {
      return s_data.stats; 
   }

   void Renderer2D::resetStats()
   {
      std::memset(&s_data.stats, 0, sizeof(Statistics));
   }
}


