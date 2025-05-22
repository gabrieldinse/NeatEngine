#pragma once

#include "Neat/Core/Types.hpp"
#include "Neat/Core/Exceptions.hpp"


namespace Neat
{
   constexpr std::size_t maxComponents = 64;


   // ---------------------------------------------------------------------- //
   // BaseComponent -------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   struct BaseComponent
   {
      using Family = UInt32;

      void operator delete(void* ptr) { fail(); }
      void operator delete[](void* ptr) { fail(); }

   protected:
      static void fail() { throw BadComponentAllocationError(); }

      static Family s_familyCounter;
   };


   // ---------------------------------------------------------------------- //
   // Component ------------------------------------------------------------ //
   // ---------------------------------------------------------------------- //
   template <typename Derived>
   struct Component : public BaseComponent
   {
   private:
      friend class EntityManager;

      static Family getFamily()
      {
         static Family family = s_familyCounter++;
         if (family >= maxComponents)
            throw MaximumNumberOfComponentsError();

         return family;
      }
   };
}