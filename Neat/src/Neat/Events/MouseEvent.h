#pragma once

#include <sstream>

#include "Neat/Events/Event.h"
#include "Neat/Core/Input.h"


namespace Neat
{
   class MouseButtonEvent : public Event
   {
   public:
      MouseCode getButton() const { return this->button; }

   protected:
      MouseButtonEvent(MouseCode button)
         : button(button) {}

      MouseCode button;
   };


   class MouseButtonPressedEvent : public MouseButtonEvent
   {
   public:
      MouseButtonPressedEvent(MouseCode button)
         : MouseButtonEvent(button) {}


      virtual std::string toString() const override
      {
         std::stringstream ss;
         ss << "MouseButtonPressedEvent: " << getButton();
         return ss.str();
      }

      virtual const Char* getName() const override { return "MouseButtonPressed"; }
      static EventType type() { return EventType::KeyTyped; }
      virtual EventType getType() const override { return type(); }
   };


   class MouseButtonReleasedEvent : public MouseButtonEvent
   {
   public:
      MouseButtonReleasedEvent(MouseCode button)
         : MouseButtonEvent(button) {}

      virtual std::string toString() const override
      {
         std::stringstream ss;
         ss << "MouseButtonReleasedEvent: " << getButton();
         return ss.str();
      }

      virtual const Char* getName() const override { return "MouseButtonReleased"; }
      static EventType type() { return EventType::KeyTyped; }
      virtual EventType getType() const override { return type(); }
   };

      
   class MouseMovedEvent : public Event
   {
   public:
      MouseMovedEvent(Float mouseX, Float mouseY)
         : mouseX(mouseX), mouseY(mouseY) {}

      Float getX() const { return this->mouseX; }
      Float getY() const { return this->mouseY; }

      virtual std::string toString() const override
      {
         std::stringstream ss;
         ss << "MouseMovedEvent: " << getX() << ", " << getY();
         return ss.str();
      }

      virtual const Char* getName() const override { return "MouseMoved"; }

      constexpr static EventType type() { return EventType::MouseMoved; }
      virtual EventType getType() const override { return type(); }

   private:
      Float mouseX;
      Float mouseY;
   };


   class  MouseScrolledEvent : public Event
   {
   public:
      MouseScrolledEvent(Float offsetX, Float offsetY)
         : offsetX(offsetX), offsetY(offsetY) {}
      
      Float getXOffset() const { return this->offsetX; }
      Float getYOffset() const { return this->offsetY; }

      virtual std::string toString() const override
      {
         std::stringstream ss;
         ss << "MouseScrolledEvent: " << getXOffset() << ", " << getYOffset();
         return ss.str();
      }

      virtual const Char* getName() const override { return "MouseScrolled"; }

      constexpr static EventType type() { return EventType::MouseScrolled; }
      virtual EventType getType() const override { return type(); }

   private:
      Float offsetX;
      Float offsetY;
   };
}