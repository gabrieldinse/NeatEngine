#pragma once

#include <string.h>

#include "Neat/Core/Core.h"
#include "Neat/Core/Timestep.h"
#include "Neat/Events/Event.h"


namespace Neat
{
   class Layer
   {
   public:
      Layer(const std::string& name = "Layer");
      virtual ~Layer();

      const std::string& getName() const { return this->name; }

      virtual void onAttach() {}
      virtual void onDetach() {}
      virtual void onUpdate(Timestep dt) {}
      virtual void onRender() {}
      virtual void onImGuiRender() {}
      virtual void onEvent(Event& event) {}

   private:
      std::string name;
   };
}