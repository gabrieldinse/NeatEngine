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

      ~BaseMemoryPool() = default;


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
            m_blocks.push_back(block);
         }
      }


      void* operator[](std::size_t n)
      {
         NT_CORE_ASSERT(n < m_size, "Memory pool index out of range!");

         return &m_blocks[n / m_blockSize][(n % m_blockSize) * m_elementSize];
      }

      const void* operator[](std::size_t n) const
      {
         NT_CORE_ASSERT(n < m_size, "Memory pool index out of range!");

         return &m_blocks[n / m_blockSize][(n % m_blockSize) * m_elementSize];
      }


      virtual void destroy(std::size_t n) = 0;

   protected:
      std::vector<Byte*> m_blocks;
      std::size_t m_blockSize;
      std::size_t m_elementSize;
      std::size_t m_size = 0;
      std::size_t m_capacity = 0;
   };


   // ---------------------------------------------------------------------- //
   // MemoryPool ----------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   template <typename T, std::size_t blockSize = 8192>
   class MemoryPool : public BaseMemoryPool
   {
   public:
      MemoryPool() : BaseMemoryPool(sizeof(T), blockSize) {}

      virtual ~MemoryPool() = default;


      virtual void destroy(std::size_t n) override
      {
         NT_CORE_ASSERT(n < m_size, "Memory pool index out of range!");

         T* ptr = static_cast<T*>(*this)[n]);
         ptr->~T();
      }
   };
}