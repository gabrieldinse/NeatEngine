#pragma once

#include <vector>

#include "Neat/Core/Log.h"
#include "Neat/Core/Types.h"


namespace Neat
{
   // ---------------------------------------------------------------------- //
   // BaseMemoryPool ------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class BaseMemoryPool
   {
   public:
      explicit BaseMemoryPool(std::size_t elementSize, std::size_t blockSize)
         : m_elementSize(elementSize), m_blockSize(blockSize) {}

      ~BaseMemoryPool()
      {
         for (Byte* ptr : m_memoryBlocks)
            delete [] ptr;
      }


      UInt size() const { return (UInt)m_size; }
      UInt capacity() const { return (UInt)m_capacity; }
      UInt chunks() const { return (UInt)m_memoryBlocks.size(); }


      void resize(std::size_t count)
      {
         if (count > m_size)
         {
            if (count > m_capacity)
               reserve(count);
            m_size = count;
         }
      }

      void reserve(std::size_t count)
      {
         while (m_capacity < count)
         {
            auto block = new Byte [m_elementSize * m_blockSize];
            m_memoryBlocks.push_back(block);
            m_capacity += m_blockSize;
         }
      }


      void* at(std::size_t n)
      {
         NT_CORE_ASSERT(n < m_size, "Memory pool index out of range!");

         return &m_memoryBlocks[n / m_blockSize][(n % m_blockSize) * m_elementSize];
      }

      const void* at(std::size_t n) const
      {
         NT_CORE_ASSERT(n < m_size, "Memory pool index out of range!");

         return &m_memoryBlocks[n / m_blockSize][(n % m_blockSize) * m_elementSize];
      }

      void* operator[](std::size_t n)
      {
         return at(n);
      }

      const void* operator[](std::size_t n) const
      {
         return at(n);
      }


      virtual void destroy(std::size_t n) = 0;

   protected:
      std::vector<Byte*> m_memoryBlocks;
      std::size_t m_blockSize;
      std::size_t m_elementSize;
      std::size_t m_size = 0;
      std::size_t m_capacity = 0;
   };


   // ---------------------------------------------------------------------- //
   // MemoryPool ----------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   template <typename T, std::size_t BlockSize = 8192>
   class MemoryPool : public BaseMemoryPool
   {
   public:
      MemoryPool() : BaseMemoryPool(sizeof(T), BlockSize) {}

      virtual ~MemoryPool() = default;

      virtual void destroy(std::size_t n) override
      {
         NT_CORE_ASSERT(n < m_size, "Memory pool index out of range!");

         T* ptr = static_cast<T*>(this->at(n));
         ptr->~T();
      }
   };
}