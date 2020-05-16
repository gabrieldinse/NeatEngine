#include "Neat/Core/LayerGroup.h"
#include "Neat/Core/Log.h"


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
      layer->onAttach();
      m_layers.emplace(begin() + m_insertIndex, std::move(layer));
      m_insertIndex++;
   }

   void LayerGroup::pushOverlay(std::unique_ptr<Layer>&& layer)
   {
      layer->onAttach();
      m_layers.push_back(std::move(layer));
   }

   std::unique_ptr<Layer> LayerGroup::popLayer(Int position)
   {
      NT_CORE_ASSERT(position < m_layers.size(), "Invalid layer position!");
      auto layer = std::move(m_layers[position]);
      layer->onDetach();
      m_layers.erase(m_layers.begin() + position);
      m_insertIndex--;
      return layer;
   }

   std::unique_ptr<Layer> LayerGroup::popLayer(const std::string& name)
   {
      auto it = std::find_if(begin(), end(),
         [&name](const std::unique_ptr<Layer>& layer)
         {
            return (layer->getName() == name);
         }
      );

      if (it != end())
      {
         auto layer = std::move(*it);
         layer->onDetach();
         m_layers.erase(it);
         m_insertIndex--;
         return layer;
      }

      NT_CORE_ASSERT(false, "Layer doesn't exists!");
      return nullptr;
   }

   std::unique_ptr<Layer> LayerGroup::popOverlay(Int position)
   {
      NT_CORE_ASSERT(position < m_layers.size(), "Invalid overlay position!");
      auto layer = std::move(m_layers[position]);
      layer->onDetach();
      m_layers.erase(m_layers.begin() + position);
      return layer;
   }

   std::unique_ptr<Layer> LayerGroup::popOverlay(const std::string& name)
   {
      auto it = std::find_if(begin(), end(),
         [&name](const std::unique_ptr<Layer>& layer)
         {
            return (layer->getName() == name);
         }
      );

      if (it != end())
      {
         auto layer = std::move(*it);
         layer->onDetach();
         m_layers.erase(it);
         return layer;
      }

      NT_CORE_ASSERT(false, "Overlay doesn't exists!");
      return nullptr;
   }
}