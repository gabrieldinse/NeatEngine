#pragma once

#include "Neat/Core/Types.h"


namespace Neat
{
   class Timestep
   {
   public:
      Timestep(Float time = 0.0f)
         : time(time)
      {
      }

      operator Float() const { return this->time; }

      Float getSeconds() const { return this->time; }
      Float getMiliseconds() const {return this->time * 1000; }

   private:
      Float time;
   };
}