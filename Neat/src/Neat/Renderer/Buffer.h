#pragma once

#include <string>
#include <initializer_list>
#include <vector>
#include <memory>

#include "Neat/Core/Core.h"
#include "Neat/Core/Types.h"
#include "Neat/Renderer/ShaderDataTypes.h"


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
         Bool normalized = false);
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
      
      BufferLayout(const std::initializer_list<BufferElement>& elements)
         : elements(elements)
      {
         UInt index = 0;
         for (auto& element : this->elements)
         {
            element.index = index++;
            element.offset = this->stride;
            this->stride += element.size;
         }
      }

      UInt getStride() const { return this->stride; }
      const BufferElementsVector& getElements() const { return this->elements; }

      BufferElementsVectorIt begin() { return this->elements.begin(); }
      BufferElementsVectorIt end() { return this->elements.end(); }
      BufferElementsVectorConstIt begin() const { return this->elements.begin(); }
      BufferElementsVectorConstIt end() const { return this->elements.end(); }

   private:
      BufferElementsVector elements;
      UInt stride = 0;
   };


   // ---------------------------------------------------------------------- //
   // VertexBuffer --------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class VertexBuffer
   {
   public:
      VertexBuffer(UInt size);
      VertexBuffer(Float* vertices, UInt size);
      ~VertexBuffer();

      void bind() const;
      void unbind() const;

      void setData(const void* data, IntLong size);

      const BufferLayout& getLayout() const { return this->layout; }
      void setLayout(const BufferLayout& layout);

   private:
      UInt id = 0;
      BufferLayout layout;
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

      Int getCount() const { return this->count; }

   private:
      UInt id = 0;
      Int count;
   };
}