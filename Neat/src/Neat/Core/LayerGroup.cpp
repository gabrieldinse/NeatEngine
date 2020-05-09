#include "Neat/Core/LayerGroup.h"
#include "Neat/Core/Log.h"


namespace Neat
{
   LayerGroup::LayerGroup()
      : insertIndex(0)
   {
   }

   LayerGroup::~LayerGroup()
   {
   }

   void LayerGroup::pushLayer(std::unique_ptr<Layer>&& layer)
   {
      layer->onAttach();
      layers.emplace(this->begin() + this->insertIndex, std::move(layer));
      this->insertIndex++;
   }

   void LayerGroup::pushOverlay(std::unique_ptr<Layer>&& layer)
   {
      layer->onAttach();
      this->layers.push_back(std::move(layer));
   }

   std::unique_ptr<Layer> LayerGroup::popLayer(Int position)
   {
      NT_CORE_ASSERT(position < this->layers.size(), "Invalid layer position!");
      auto layer = std::move(this->layers[position]);
      layer->onDetach();
      this->layers.erase(this->layers.begin() + position);
      this->insertIndex--;
      return layer;
   }

   std::unique_ptr<Layer> LayerGroup::popLayer(const std::string& name)
   {
      auto it = std::find_if(this->begin(), this->end(),
         [&name](const std::unique_ptr<Layer>& layer)
         {
            return (layer->getName() == name);
         }
      );

      if (it != this->end())
      {
         auto layer = std::move(*it);
         layer->onDetach();
         this->layers.erase(it);
         this->insertIndex--;
         return layer;
      }

      NT_CORE_ASSERT(false, "Layer doesn't exists!");
      return nullptr;
   }

   std::unique_ptr<Layer> LayerGroup::popOverlay(Int position)
   {
      NT_CORE_ASSERT(position < this->layers.size(), "Invalid overlay position!");
      auto layer = std::move(this->layers[position]);
      layer->onDetach();
      this->layers.erase(this->layers.begin() + position);
      return layer;
   }

   std::unique_ptr<Layer> LayerGroup::popOverlay(const std::string& name)
   {
      auto it = std::find_if(this->begin(), this->end(),
         [&name](const std::unique_ptr<Layer>& layer)
         {
            return (layer->getName() == name);
         }
      );

      if (it != this->end())
      {
         auto layer = std::move(*it);
         layer->onDetach();
         this->layers.erase(it);
         return layer;
      }

      NT_CORE_ASSERT(false, "Overlay doesn't exists!");
      return nullptr;
   }
}