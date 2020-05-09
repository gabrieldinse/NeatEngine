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

      std::string toString() const override
      {
         std::stringstream ss;
         ss << "WindowResizeEvent: " << getWidth() << ", " << getHeight();
         return ss.str();
      }

      virtual Int getCategoryFlags() const override
      {
         return EventCategoryApplication;
      }

      virtual const Char* getName() const override
      {
         return "WindowResize";
      }

   private:
      UInt width;
      UInt height;
   };


   class  WindowCloseEvent : public Event
   {
   public:
      WindowCloseEvent() = default;

      std::string toString() const override
      {
         std::stringstream ss;
         ss << "WindowCloseEvent";
         return ss.str();
      }

      virtual Int getCategoryFlags() const override
      {
         return EventCategoryApplication;
      }

      virtual const Char* getName() const override
      {
         return "WindowClose";
      }
   };


   class  AppTickEvent : public Event
   {
   public:
      AppTickEvent() = default;

      virtual Int getCategoryFlags() const override
      {
         return EventCategoryApplication;
      }

      virtual const Char* getName() const override
      {
         return "AppTick";
      }
   };


   class  AppUpdateEvent : public Event
   {
   public:
      AppUpdateEvent() = default;

      virtual Int getCategoryFlags() const override
      {
         return EventCategoryApplication;
      }

      virtual const Char* getName() const override
      {
         return "AppUpdate";
      }
   };


   class  AppRendererEvent : public Event
   {
   public:
      AppRendererEvent() = default;

      virtual Int getCategoryFlags() const override
      {
         return EventCategoryApplication;
      }

      virtual const Char* getName() const override
      {
         return "AppRenderer";
      }
   };
}


