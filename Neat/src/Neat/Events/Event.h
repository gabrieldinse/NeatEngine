#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <type_traits>

#include "Neat/Core/Core.h"
#include "Neat/Core/Types.h"


namespace Neat
{
   static constexpr Int set_bit(Int n) { return (1 << n); }

   enum EventCategory
   {
      None = 0,
      EventCategoryApplication = set_bit(0),
      EventCategoryInput = set_bit(1),
      EventCategoryKeyboard = set_bit(2),
      EventCategoryMouse = set_bit(3),
      EventCategoryMouseButton = set_bit(3)
   };

   class  Event
   {
      template<typename T>
      using eventFunction = std::function<Bool(T&)>;

   public:
      virtual const Char* getName() const = 0;
      virtual Int getCategoryFlags() const = 0;
      virtual std::string toString() const { return getName(); }
      Bool isHandled() const { return this->handled; }

      Bool isInCategory(EventCategory category)
      {
         return getCategoryFlags() & category;
      }

      template <typename T>
      Bool isType()
      {
         return (typeid(*this) == typeid(T));
      }

      template<typename T>
      Bool dispatch(eventFunction<T> function)
      {
         if (this->isType<T>())
         {
            this->handled = function(*static_cast<T*>(this));
            return true;
         }
         return false;
      }

   private:
      Bool handled = false;
   };

   inline std::ostream& operator<<(std::ostream& os, const Event& event)
   {
      return os << event.toString();
   }
}
