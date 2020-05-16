#pragma once

#include <string>

#include "Neat/Core/Core.h"
#include "Neat/Core/Types.h"


namespace Neat
{
   class Layer
   {
   public:
      Layer(const std::string& name = "Layer");
      virtual ~Layer();

      const std::string& getName() const { return m_name; }

      virtual void onAttach() {}
      virtual void onDetach() {}
      virtual void onUpdate(Timestep deltaTime) {}
      virtual void onRender() {}
      virtual void onImGuiRender() {}

   private:
      std::string m_name;
   };
}