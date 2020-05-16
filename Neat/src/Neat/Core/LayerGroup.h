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

      LayerVectorIt begin() { return m_layers.begin(); }
      LayerVectorIt end() { return m_layers.end(); }
      LayerVectorConstIt begin() const { return m_layers.begin(); }
      LayerVectorConstIt end() const { return m_layers.end(); }
      LayerVectorRevIt rbegin() { return m_layers.rbegin(); }
      LayerVectorRevIt rend() { return m_layers.rend(); }
      LayerVectorConstRevIt rbegin() const { return m_layers.rbegin(); }
      LayerVectorConstRevIt rend() const { return m_layers.rend(); }

   private:
      LayerVector m_layers;
      LayerVector::size_type m_insertIndex;
   };
}