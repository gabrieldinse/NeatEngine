#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <type_traits>

#include "Neat/Core/Utility.h"


namespace Neat
{
   enum class EventType : Int
   {
      None = 0,
      WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		ApplicationTick, ApplicationUpdate, ApplicationRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
   };


   class Event
   {
      template<typename T>
      using eventFunction = std::function<Bool(T&)>;

   public:
      virtual ~Event() = default;
      virtual const Char* getName() const = 0;
      virtual EventType getType() const = 0;
      virtual std::string toString() const { return getName(); }
      
      Bool isHandled() const { return this->handled; }

      template<typename T>
      Bool dispatch(eventFunction<T> function)
      {
         if (this->getType() == T::type())
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
