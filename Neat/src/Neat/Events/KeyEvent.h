#pragma once

#include <sstream>

#include "Neat/Events/Event.h"
#include "Neat/Core/Input.h"


namespace Neat
{
   class KeyEvent : public Event
   {
   public:
      using Event::Event;
      inline KeyCode getKeyCode() const { return this->keyCode; }

   protected:
      KeyEvent(KeyCode keyCode)
         : keyCode(keyCode) {}

      KeyCode keyCode;
   };


   class KeyPressedEvent : public KeyEvent
   {
   public:
      KeyPressedEvent(KeyCode keyCode, Int repeatCount = 0)
         : KeyEvent(keyCode), repeatCount(repeatCount) {}

      Int getRepeatCount() const { return this->repeatCount; }

      virtual std::string toString() const override
      {
         std::stringstream ss;
         ss << "KeyPressedEvent: " << getKeyCode() << " (" << getRepeatCount() << " repeats)";
         return ss.str();
      }

      virtual const Char* getName() const override { return "KeyPressed"; }
      static EventType type() { return EventType::KeyPressed; }
      virtual EventType getType() const override { return type(); }

   private:
      Int repeatCount;
   };


   class  KeyReleasedEvent : public KeyEvent
   {
   public:
      KeyReleasedEvent(KeyCode keycode)
         : KeyEvent(keyCode) {}
      
      virtual std::string toString() const override
      {
         std::stringstream ss;
         ss << "KeyReleasedEvent: " << getKeyCode();
         return ss.str();
      }

      virtual const Char* getName() const override{return "KeyReleased"; }
      static EventType type() { return EventType::KeyReleased; }
      virtual EventType getType() const override { return type(); }
   };


   class  KeyTypedEvent : public KeyEvent
   {
   public:
      KeyTypedEvent(KeyCode keyCode)
         : KeyEvent(keyCode) {}

      virtual std::string toString() const override
      {
         std::stringstream ss;
         ss << "KeyTypedEvent: " << getKeyCode();
         return ss.str();
      }

      virtual const Char* getName() const override { return "KeyTyped"; }
      static EventType type() { return EventType::KeyTyped; }
      virtual EventType getType() const override { return type(); }
   };
}
