#pragma once

#include <sstream>

#include "Neat/Events/Event.h"
#include "Neat/Core/Input.h"


namespace Neat
{
   class  KeyEvent : public Event
   {
   public:
      inline KeyCode getKeyCode() const { return this->keyCode; }

      virtual Int getCategoryFlags() const override
      {
         return EventCategoryInput | EventCategoryKeyboard;
      }

   protected:
      KeyEvent(KeyCode keyCode)
         : keyCode(keyCode) {}

      KeyCode keyCode;
   };


   class  KeyPressedEvent : public KeyEvent
   {
   public:
      KeyPressedEvent(KeyCode keyCode, Int repeatCount = 0)
         : KeyEvent(keyCode), repeatCount(repeatCount) {}

      Int getRepeatCount() const { return this->repeatCount; }

      std::string toString() const override
      {
         std::stringstream ss;
         ss << "KeyPressedEvent: " << getKeyCode() << " (" << getRepeatCount() << " repeats)";
         return ss.str();
      }

      virtual const Char* getName() const override
      {
         return "KeyPressed";
      }

   private:
      Int repeatCount;
   };


   class  KeyReleasedEvent : public KeyEvent
   {
   public:
      KeyReleasedEvent(KeyCode keycode)
         : KeyEvent(keycode) {}
      
      std::string toString() const override
      {
         std::stringstream ss;
         ss << "KeyReleasedEvent: " << getKeyCode();
         return ss.str();
      }

      virtual const Char* getName() const override
      {
         return "KeyReleased";
      }
   };


   class  KeyTypedEvent : public KeyEvent
   {
   public:
      KeyTypedEvent(KeyCode keyCode)
         : KeyEvent(keyCode) {}

      std::string toString() const override
      {
         std::stringstream ss;
         ss << "KeyTypedEvent: " << getKeyCode();
         return ss.str();
      }

      virtual const Char* getName() const override
      {
         return "KeyTyped";
      }
   };
}
