#pragma once

#include <unordered_map>
#include <utility>
#include <memory>

#include "Neat/Core/Types.h"
#include "Neat/Core/MouseCodes.h"
#include "Neat/Core/KeyCodes.h"

#include "SimpleSignal.h"


namespace Neat
{
   class EventManager;

   using EventSignal = Simple::Signal<bool (const void*)>;

   // ---------------------------------------------------------------------- //
   // BaseEvent ------------------------------------------------------------ //
   // ---------------------------------------------------------------------- //
   class BaseEvent
   {
   public:
      using Family = UIntLong;

      virtual ~BaseEvent() {}

   protected:
      static Family s_familyCounter;
   };


   // ---------------------------------------------------------------------- //
   // Event ---------------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   template <typename Derived>
   class Event : public BaseEvent
   {
   private:
      friend class EventManager;

      static Family getFamily()
      {
         static Family family = s_familyCounter++;
         return family;
      }
   };


   // ---------------------------------------------------------------------- //
   // BaseEventReceiver ---------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class BaseEventReceiver
   {
   public:
      BaseEventReceiver::~BaseEventReceiver()
      {
         for (auto& connection : m_connections)
         {
            auto& ptr = connection.second.first;
            if (!ptr.expired())
               ptr.lock()->disconnect(connection.second.second);
         }
      }

      std::size_t BaseEventReceiver::getNumberOfConnectedSignals() const
      {
         std::size_t count = 0;
         for (auto& connection : m_connections)
            if (!connection.second.first.expired())
               ++count;

         return count;
      }

   private:
      friend class EventManager;

      std::unordered_map<
         BaseEvent::Family,
         std::pair<std::weak_ptr<EventSignal>, std::size_t>
         > m_connections;
   };


   // ---------------------------------------------------------------------- //
   // EventReceiver -------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   template <typename Derived>
   class EventReceiver : public BaseEventReceiver
   {
   public:
      virtual ~EventReceiver() {}
   };


   // ---------------------------------------------------------------------- //
   // Window events -------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class WindowResizeEvent
   {
   public:
      WindowResizeEvent(UInt width, UInt height)
         : m_width(width), m_height(height) {}

      UInt getWidth() const { return m_width; }
      UInt getHeight() const { return m_height; }

   private:
      UInt m_width;
      UInt m_height;
   };


   class WindowCloseEvent
   {
   public:
      WindowCloseEvent() = default;
   };


   // ---------------------------------------------------------------------- //
   // Mouse events --------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class MouseButtonEvent
   {
   public:
      MouseCode getButton() const { return m_button; }

   protected:
      MouseButtonEvent(MouseCode button)
         : m_button(button) {}

      MouseCode m_button;
   };


   class MouseButtonPressedEvent : public MouseButtonEvent
   {
   public:
      MouseButtonPressedEvent(MouseCode button)
         : MouseButtonEvent(button) {}
   };


   class MouseButtonReleasedEvent : public MouseButtonEvent
   {
   public:
      MouseButtonReleasedEvent(MouseCode button)
         : MouseButtonEvent(button) {}
   };


   class MouseMovedEvent
   {
   public:
      MouseMovedEvent(float mouseX, float mouseY)
         : m_mouseX(mouseX), m_mouseY(mouseY) {}

      float getX() const { return m_mouseX; }
      float getY() const { return m_mouseY; }

   private:
      float m_mouseX;
      float m_mouseY;
   };


   class  MouseScrolledEvent
   {
   public:
      MouseScrolledEvent(float offsetX, float offsetY)
         : m_offsetX(offsetX), m_offsetY(offsetY) {}
      
      float getXOffset() const { return m_offsetX; }
      float getYOffset() const { return m_offsetY; }

   private:
      float m_offsetX;
      float m_offsetY;
   };


   // ---------------------------------------------------------------------- //
   // Key events ----------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class KeyEvent
   {
   public:
      inline KeyCode getKeyCode() const { return m_keyCode; }

   protected:
      KeyEvent(KeyCode keyCode)
         : m_keyCode(keyCode) {}

      KeyCode m_keyCode;
   };


   class KeyPressedEvent : public KeyEvent
   {
   public:
      KeyPressedEvent(KeyCode keyCode, Int repeatCount = 0)
         : KeyEvent(keyCode), m_repeatCount(repeatCount) {}

      Int getRepeatCount() const { return m_repeatCount; }

   private:
      Int m_repeatCount;
   };


   class  KeyReleasedEvent : public KeyEvent
   {
   public:
      KeyReleasedEvent(KeyCode keycode)
         : KeyEvent(m_keyCode) {}
   };


   class  KeyTypedEvent : public KeyEvent
   {
   public:
      KeyTypedEvent(KeyCode keyCode)
         : KeyEvent(keyCode) {}
   };
}