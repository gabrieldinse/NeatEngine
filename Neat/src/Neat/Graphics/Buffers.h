#pragma once

#include <string>
#include <initializer_list>
#include <vector>
#include <memory>

#include "Neat/Core/Core.h"
#include "Neat/Core/Types.h"
#include "Neat/Graphics/ShaderDataType.h"


namespace Neat
{
   // ---------------------------------------------------------------------- //
   // BufferElement -------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   struct BufferElement
   {
      ShaderDataType type;
      std::string name;
      UInt componentCount;
      UInt dataType;
      UInt normalized;
      UInt size;
      UInt offset = 0;
      UInt index = 0;

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

      UInt getOffset() const { return m_offset; }
      const BufferElementsVector& getElements() const { return m_elements; }

      BufferElementsVectorIt begin() { return m_elements.begin(); }
      BufferElementsVectorIt end() { return m_elements.end(); }
      BufferElementsVectorConstIt begin() const { return m_elements.begin(); }
      BufferElementsVectorConstIt end() const { return m_elements.end(); }

   private:
      BufferElementsVector m_elements;
      UInt m_offset = 0;
   };


   // ---------------------------------------------------------------------- //
   // VertexBuffer --------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class VertexBuffer
   {
   public:
      VertexBuffer(UInt size);
      VertexBuffer(float* vertices, UInt size);
      ~VertexBuffer();

      void bind() const;
      void unbind() const;

      void setData(const void* m_data, IntLong size);

      const BufferLayout& getLayout() const { return m_layout; }
      void setLayout(const BufferLayout& layout);

   private:
      UInt m_id = 0;
      BufferLayout m_layout;
   };


   // ---------------------------------------------------------------------- //
   // Indexbuffer ---------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class IndexBuffer
   {
   public:
      IndexBuffer(UInt* indices, Int count);
      ~IndexBuffer();

      void bind() const;
      void unbind() const;

      Int getCount() const { return m_count; }

   private:
      UInt m_id = 0;
      Int m_count;
   };
}