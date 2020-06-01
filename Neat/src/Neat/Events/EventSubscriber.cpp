#include "Neat/Events/EventSubscriber.h"


namespace Neat
{
   bool operator<(EventPriority priorityA, EventPriority priorityB)
   {
      return
         static_cast<UIntShort>(priorityA) < static_cast<UIntShort>(priorityB);
   }

   bool operator==(EventPriority priorityA, EventPriority priorityB)
   {
      return
         static_cast<UIntShort>(priorityA) == static_cast<UIntShort>(priorityB);
   }
}
