#pragma once

#include <sstream>

#include "Neat/Events/Event.h"


namespace Neat
{
   class  WindowResizeEvent : public Event
   {
   public:
      WindowResizeEvent(UInt width, UInt height)
         : width(width), height(height) {}

      UInt getWidth() const { return this->width; }
      UInt getHeight() const { return this->height; }

      virtual std::string toString() const override
      {
         std::stringstream ss;
         ss << "WindowResizeEvent: " << getWidth() << ", " << getHeight();
         return ss.str();
      }

      virtual const Char* getName() const override { return "WindowResize"; }
      static EventType type() { return EventType::WindowResize; }
      virtual EventType getType() const override { return type(); }

   private:
      UInt width;
      UInt height;
   };


   class  WindowCloseEvent : public Event
   {
   public:
      WindowCloseEvent() = default;

      virtual std::string toString() const override
      {
         std::stringstream ss;
         ss << "WindowCloseEvent";
         return ss.str();
      }

      virtual const Char* getName() const override { return "WindowClose"; }
      static EventType type() { return EventType::WindowClose; }
      virtual EventType getType() const override { return type(); }
   };


   class  ApplicationTickEvent : public Event
   {
   public:
      ApplicationTickEvent() = default;

      virtual const Char* getName() const override { return "ApplicationTick"; }
      static EventType type() { return EventType::ApplicationTick; }
      virtual EventType getType() const override { return type(); }
   };


   class  ApplicationUpdateEvent : public Event
   {
   public:
      ApplicationUpdateEvent() = default;

      virtual const Char* getName() const override { return "ApplicationUpdate"; }
      static EventType type() { return EventType::ApplicationUpdate; }
      virtual EventType getType() const override { return type(); }
   };


   class  ApplicationRenderEvent : public Event
   {
   public:
      ApplicationRenderEvent() = default;

      virtual const Char* getName() const override { return "ApplicationRender"; }
      static EventType type() { return EventType::ApplicationRender; }
      virtual EventType getType() const override { return type(); }
   };
}


