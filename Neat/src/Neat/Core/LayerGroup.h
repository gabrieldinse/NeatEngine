#pragma once

#include <vector>
#include <functional>
#include <memory>

#include "Neat/Core/Layer.h"


namespace Neat
{
   class LayerGroup
   {
   public:
      using LayerVector = std::vector<std::unique_ptr<Layer>>;
      using LayerVectorIt = LayerVector::iterator;
      using LayerVectorConstIt = LayerVector::const_iterator;
      using LayerVectorRevIt = LayerVector::reverse_iterator;
      using LayerVectorConstRevIt = LayerVector::const_reverse_iterator;

   public:

      LayerGroup();
      ~LayerGroup();

      void pushLayer(std::unique_ptr<Layer>&& layer);
      void pushOverlay(std::unique_ptr<Layer>&& layer);
      std::unique_ptr<Layer> popLayer(Int position);
      std::unique_ptr<Layer> popOverlay(Int position);
      std::unique_ptr<Layer> popLayer(const std::string& name);
      std::unique_ptr<Layer> popOverlay(const std::string& name);

      LayerVectorIt begin() { return this->layers.begin(); }
      LayerVectorIt end() { return this->layers.end(); }
      LayerVectorConstIt begin() const { return this->layers.begin(); }
      LayerVectorConstIt end() const { return this->layers.end(); }
      LayerVectorRevIt rbegin() { return this->layers.rbegin(); }
      LayerVectorRevIt rend() { return this->layers.rend(); }
      LayerVectorConstRevIt rbegin() const { return this->layers.rbegin(); }
      LayerVectorConstRevIt rend() const { return this->layers.rend(); }

   private:
      LayerVector layers;
      LayerVector::size_type insertIndex;
   };
}