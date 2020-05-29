#include "Neat/Events/EventSubscriber.h"


namespace Neat
{
   bool compareEventPriority(const CallbackElement& callbackElemment,
      UIntShort value)
   {
      return callbackElemment < value;
   }
}