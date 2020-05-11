#include "Neat/Renderer/Renderer2D.h"
#include "Neat/Renderer/RenderCommand.h"
#include "Neat/Renderer/ShaderDataTypes.h"
#include "Neat/Debug/Instrumentator.h"
#include "Neat/Math/Transforms.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   Renderer2D::Renderer2DData Renderer2D::data;

   void Renderer2D::init()
   {
      NT_PROFILE_FUNCTION();

      data.quadVertexArray = std::make_shared<VertexArray>();
      data.quadVertexBuffer = std::make_shared<VertexBuffer>(
         QuadVextexDataBuffer::maxVertices * (UInt)sizeof(QuadVertexData));

      data.quadVertexBuffer->setLayout({
         { ShaderDataType::Vec3, "a_position" },
         { ShaderDataType::Vec4, "a_color"},
         { ShaderDataType::Vec2, "a_textureCoordinate"},
         { ShaderDataType::Float, "a_textureIndex"},
         { ShaderDataType::Float, "a_tilingFactor"}
         });
      data.quadVertexArray->addVertexBuffer(data.quadVertexBuffer);

      auto quadIndexes = std::make_unique<UInt[]>(
         QuadVextexDataBuffer::maxIndexes);
      UInt offset = 0;
      for (SizeType i = 0; i < QuadVextexDataBuffer::maxIndexes; i += 6, offset += 4)
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

      data.quadVertexArray->setIndexBuffer(squareIB);

      data.whiteTexture = std::make_shared<Texture2D>(1, 1);
      UInt white_texture_data = 0xffffffff;
      data.whiteTexture->setData(&white_texture_data, sizeof(UInt));

      Int samplers[Renderer2DData::maxTextureSlots];
      for (Int i = 0; i < Renderer2DData::maxTextureSlots; ++i)
         samplers[i] = i;

      data.textureShader = std::make_shared<TextureShader>(
         "assets/glsl/texture.glsl");
      data.textureShader->setTextures(samplers, sizeof(samplers));

      data.textureSlots[0] = data.whiteTexture;
   }

   void Renderer2D::shutdown()
   {
      NT_PROFILE_FUNCTION();

   }

   void Renderer2D::beginScene(const OrthographicCamera& camera)
   {
      NT_PROFILE_FUNCTION();

      data.textureShader->setviewProjection(camera.getViewProjectionMatrix());

      startNewBatch();
   }

   void Renderer2D::endScene()
   {
      NT_PROFILE_FUNCTION();

      draw();
   }

   void Renderer2D::startNewBatch()
   {
      data.quadVextexDataBuffer.reset();
      data.textureSlotIndex = 1;
   }

   void Renderer2D::draw()
   {
      data.quadVertexBuffer->setData(data.quadVextexDataBuffer.data.get(),
         data.quadVextexDataBuffer.getDataSize());

      UInt index = 0;
      for (SizeType i = 0; i < data.textureSlotIndex; ++i, ++index)
         data.textureSlots[i]->bind(index);

      RenderCommand::drawIndexed(data.quadVertexArray, data.quadVextexDataBuffer.indexCount);

      data.stats.drawCalls++;
   }

   void Renderer2D::drawQuad(const Vec2& position, const Vec2& size,
      const Vec4 color)
   {
      drawQuad({position.x, position.y, 0.0f}, size, color);
   }

   // Quads
   void Renderer2D::drawQuad(const Vec3& position, const Vec2& size,
      const Vec4 color)
   {
      NT_PROFILE_FUNCTION();

      if (data.quadVextexDataBuffer.indexCount >= QuadVextexDataBuffer::maxIndexes)
      {
         draw();
         startNewBatch();
      }

      constexpr Int textureIndex = 0; // white texture;
      constexpr Float tilingFactor = 1.0f;
      constexpr Vec2 textureCoordinates[] = {
         {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}
      };

      auto transform = translate(position) * scale(Vec3(size.x, size.y, 1.0f));
      
      data.quadVextexDataBuffer.addQuad(
         transform, color, textureCoordinates, textureIndex, tilingFactor);

      data.stats.quadCount++;
   }

   void Renderer2D::drawQuad(const Vec2& position,const Vec2& size,
      const std::shared_ptr<Texture2D>& texture, const Vec4& tint,
      Float tilingFactor)
   {
      drawQuad(
         {position.x, position.y, 0.0f}, size, texture, tint, tilingFactor);
   }

   void Renderer2D::drawQuad(
      const Vec3& position, const Vec2& size,
      const std::shared_ptr<Texture2D>& texture, const Vec4& tint,
      Float tilingFactor)
   {
      NT_PROFILE_FUNCTION();

      if (data.quadVextexDataBuffer.indexCount >= QuadVextexDataBuffer::maxIndexes)
      {
         draw();
         startNewBatch();
      }

      Int textureIndex = 0;
      for (Int i = 1; i < data.textureSlotIndex; ++i)
      {
         if (*data.textureSlots[i] == *texture)
         {
            textureIndex = i;
            break;
         }
      }

      if (textureIndex == 0)
      {
         textureIndex = data.textureSlotIndex;
         data.textureSlots[data.textureSlotIndex] = texture;
         data.textureSlotIndex++;
      }

      auto transform = translate(position) * scale(Vec3(size.x, size.y, 1.0f));

      data.quadVextexDataBuffer.addQuad(
         transform, tint, texture->getCoordinates(), textureIndex, tilingFactor);

      data.stats.quadCount++;
   }

   // Rotated Quads 
   void Renderer2D::drawRotatedQuad(const Vec2& position, const Vec2& size,
      Float angleDegrees, const Vec4 color)
   {
      drawRotatedQuad(
         { position.x, position.y, 0.0f }, size, angleDegrees, color);
   }

   void Renderer2D::drawRotatedQuad(const Vec3& position, const Vec2& size,
      Float angleDegrees, const Vec4 color)
   {
      NT_PROFILE_FUNCTION();

      if (data.quadVextexDataBuffer.indexCount >= QuadVextexDataBuffer::maxIndexes)
      {
         draw();
         startNewBatch();
      }

      constexpr Int textureIndex = 0; // white texture;
      constexpr Float tilingFactor = 1.0f;
      constexpr Vec2 textureCoordinates[] = {
         {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}
      };

      auto transform =
         translate(Mat4(1.0f),position) *
         rotate(degreesToRadians(angleDegrees), { 0, 0, 1 }) *
         scale(Vec3(size.x, size.y, 1.0f));

      data.quadVextexDataBuffer.addQuad(
         transform, color, textureCoordinates, textureIndex, tilingFactor);

      data.stats.quadCount++;
   }

   void Renderer2D::drawRotatedQuad(const Vec2& position, const Vec2& size,
      Float angleDegrees, const std::shared_ptr<Texture2D>& texture,
      const Vec4& tint, Float tilingFactor)
   {
      drawRotatedQuad(
         { position.x, position.y, 0.0f },
         size, angleDegrees, texture, tint, tilingFactor);
   }

   void Renderer2D::drawRotatedQuad(
      const Vec3& position, const Vec2& size,
      Float angleDegrees, const std::shared_ptr<Texture2D>& texture,
      const Vec4& tint, Float tilingFactor)
   {
      NT_PROFILE_FUNCTION();

      if (data.quadVextexDataBuffer.indexCount >= QuadVextexDataBuffer::maxIndexes)
      {
         draw();
         startNewBatch();
      }

      Int textureIndex = 0;
      for (Int i = 1; i < data.textureSlotIndex; ++i)
      {
         if (*data.textureSlots[i] == *texture)
         {
            textureIndex = i;
            break;
         }
      }

      if (textureIndex == 0)
      {
         textureIndex = data.textureSlotIndex;
         data.textureSlots[data.textureSlotIndex] = texture;
         data.textureSlotIndex++;
      }

      auto transform =
         translate(position) *
         rotate(degreesToRadians(angleDegrees), { 0, 0, 1 }) *
         scale(Vec3(size.x, size.y, 1.0f));

      data.quadVextexDataBuffer.addQuad(
         transform, tint, texture->getCoordinates(), textureIndex, tilingFactor);

      data.stats.quadCount++;
   }

   // Statistics
   Renderer2D::Statistics Renderer2D::getStats()
   {
      return data.stats; 
   }

   void Renderer2D::resetStats()
   {
      std::memset(&data.stats, 0, sizeof(Statistics));
   }
}


