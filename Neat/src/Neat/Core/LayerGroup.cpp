#include "Neat/Core/LayerGroup.hpp"
#include "Neat/Core/Log.hpp"


namespace Neat
{
   LayerGroup::LayerGroup()
      : m_insertIndex(0)
   {
   }

   LayerGroup::~LayerGroup()
   {
   }

   void LayerGroup::pushLayer(std::unique_ptr<Layer>&& layer)
   {
      layer->attach();
      m_layers.emplace(begin() + m_insertIndex, std::move(layer));
      m_insertIndex++;
   }

   void LayerGroup::pushOverlay(std::unique_ptr<Layer>&& layer)
   {
      layer->attach();
      m_layers.push_back(std::move(layer));
   }

   std::unique_ptr<Layer> LayerGroup::popLayer(Int32 position)
   {
      NT_CORE_ASSERT(position < m_layers.size(), "Invalid layer position!");
      auto layer = std::move(m_layers[position]);
      layer->detach();
      m_layers.erase(m_layers.begin() + position);
      m_insertIndex--;
      return layer;
   }

   std::unique_ptr<Layer> LayerGroup::popOverlay(Int32 position)
   {
      NT_CORE_ASSERT(position < m_layers.size(), "Invalid overlay position!");
      auto layer = std::move(m_layers[position]);
      layer->detach();
      m_layers.erase(m_layers.begin() + position);
      return layer;
   }
}