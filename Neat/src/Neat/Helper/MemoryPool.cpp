#include "Neat/Helper/MemoryPool.h"


namespace Neat
{
   BaseMemoryPool::~BaseMemoryPool()
   {
      for (Byte* ptr : m_memoryBlocks)
         delete[] ptr;
   }

   void BaseMemoryPool::resize(std::size_t count)
   {
      if (count > m_size)
      {
         if (count > m_capacity)
            reserve(count);
         m_size = count;
      }
   }

   void BaseMemoryPool::reserve(std::size_t count)
   {
      while (m_capacity < count)
      {
         auto block = new Byte[m_elementSize * m_blockSize];
         m_memoryBlocks.push_back(block);
         m_capacity += m_blockSize;
      }
   }
}