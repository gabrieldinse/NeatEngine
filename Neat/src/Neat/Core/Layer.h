#pragma once

#include <string>

#include "Neat/Core/Base.h"
#include "Neat/Core/Types.h"


namespace Neat
{
   class Layer
   {
   public:
      Layer() = default;
      virtual ~Layer() = default;

      virtual void attach() {}
      virtual void detach() {}
      virtual void update(DeltaTime deltaTime) {}
      virtual void render() {}
      virtual void inGuiRender() {}
   };
}