#pragma once

#include <string>
#include <initializer_list>
#include <vector>
#include <memory>

#include "Neat/Core/Base.hpp"
#include "Neat/Core/Types.hpp"
#include "Neat/Graphics/ShaderDataType.hpp"


namespace Neat
{
   // ---------------------------------------------------------------------- //
   // BufferElement -------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   struct BufferElement
   {
      ShaderDataType type;
      std::string name;
      UInt32 componentCount;
      UInt32 dataType;
      UInt32 normalized;
      UInt32 size;
      UInt32 offset = 0;
      UInt32 index = 0;

      BufferElement() = default;

      BufferElement(ShaderDataType type, const std::string& name,
         bool normalized = false);
   };


   // ---------------------------------------------------------------------- //
   // BUfferLayout --------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class BufferLayout
   {
   public:
      using BufferElementsVector = std::vector<BufferElement>;
      using BufferElementsVectorIt = BufferElementsVector::iterator;
      using BufferElementsVectorConstIt = BufferElementsVector::const_iterator;

   public:
      BufferLayout() = default;
      
      BufferLayout(const std::initializer_list<BufferElement>& elements);

      UInt32 getOffset() const { return m_offset; }
      const BufferElementsVector& getElements() const { return m_elements; }

      BufferElementsVectorIt begin() { return m_elements.begin(); }
      BufferElementsVectorIt end() { return m_elements.end(); }
      BufferElementsVectorConstIt begin() const { return m_elements.begin(); }
      BufferElementsVectorConstIt end() const { return m_elements.end(); }

   private:
      BufferElementsVector m_elements;
      UInt32 m_offset = 0;
   };


   // ---------------------------------------------------------------------- //
   // VertexBuffer --------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class VertexBuffer
   {
   public:
      VertexBuffer(UInt32 size);
      VertexBuffer(float* vertices, UInt32 size);
      ~VertexBuffer();

      void bind() const;
      void unbind() const;

      UInt32 getId() const { return m_id; }

      const BufferLayout& getLayout() const { return m_layout; }
      void setLayout(const BufferLayout& layout);

      void setData(const void* data, UInt32 size);

   private:
      UInt32 m_id = 0;
      BufferLayout m_layout;
   };


   // ---------------------------------------------------------------------- //
   // Indexbuffer ---------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class IndexBuffer
   {
   public:
      IndexBuffer(UInt32* indices, UInt32 count);
      ~IndexBuffer();

      void bind() const;
      void unbind() const;

      UInt32 getCount() const { return m_count; }

   private:
      UInt32 m_id = 0;
      UInt32 m_count;
   };
}