#include "Neat/Events/EventListener.h"


namespace Neat
{
   bool operator<(EventPriority priorityA, EventPriority priorityB)
   {
      return
         static_cast<UInt16>(priorityA) < static_cast<UInt16>(priorityB);
   }

   bool operator==(EventPriority priorityA, EventPriority priorityB)
   {
      return
         static_cast<UInt16>(priorityA) == static_cast<UInt16>(priorityB);
   }
}
