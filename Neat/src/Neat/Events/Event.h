#pragma once

#include <unordered_map>
#include <utility>
#include <memory>
#include <functional>
#include <list>
#include <algorithm>

#include "Neat/Core/Types.h"
#include "Neat/Core/MouseCodes.h"
#include "Neat/Core/KeyCodes.h"


namespace Neat
{
   class EventManager;


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
   // EventSubscription ---------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   using EventCallback = std::function<bool (const void*)>;



   class EventSubscription
   {
   public:
      EventSubscription() = default;

      template <typename E, typename Receiver>
      std::size_t add(Receiver& receiver)
      {
         bool (Receiver::*receive)(const E&) = &Receiver::receive;

         auto event_callback_wrapper = EventCallbackWrapper<E>(
            std::bind(receive, &receiver, std::placeholders::_1));

         m_callbacks.emplace_back(
            std::make_shared<EventCallback>(event_callback_wrapper));
         
         return (std::size_t)m_callbacks.back().get();
      }

      bool remove(std::size_t id)
      {
         auto it = std::remove_if(m_callbacks.begin(), m_callbacks.end(),
            [id](const std::shared_ptr<EventCallback>& callback)
            {
               return (std::size_t)callback.get() == id;
            });

         bool removed = it != m_callbacks.end();
         m_callbacks.erase(it, m_callbacks.end());

         return removed;
      }

      template <typename E>
      void publish(const E& event)
      {
         callCallbacks(&event);
      }

      template <typename E>
      void publish(std::unique_ptr<E> event)
      {
         callCallbacks(event.get());
      }

      template <typename E, typename... Args>
      void publish(Args&&... args)
      {
         E event(std::forward<Args>(args)...);
         callCallbacks(&event);
      }


      std::size_t size() const { return m_callbacks.size(); }

   private:
      template <typename E>
      struct EventCallbackWrapper
      {
         std::function<bool(const E &)> callback;

         EventCallbackWrapper(std::function<bool(const E &)> callback)
            : callback(callback) {}

         bool operator()(const void* event)
         {
            return callback(*(static_cast<const E*>(event)));
         }
      };

      void callCallbacks(const void* event)
      {
         for (auto& callback : m_callbacks)
            if (callback)
               if ((*callback)(event))
                  break;
      }

   private:
      std::list<std::shared_ptr<EventCallback>> m_callbacks;
   };


   // ---------------------------------------------------------------------- //
   // BaseEventSubscriber -------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class BaseEventSubscriber
   {
   public:
      BaseEventSubscriber::~BaseEventSubscriber()
      {
         for (auto& event_subscription_pair : m_subscriptions)
         {
            auto& subscription = event_subscription_pair.second.first;
            if (!subscription.expired())
               subscription.lock()->remove(event_subscription_pair.second.second);
         }
      }

      std::size_t BaseEventSubscriber::getNumberOfConnectedSignals() const
      {
         std::size_t count = 0;
         for (auto& event_subscription_pair : m_subscriptions)
            if (!event_subscription_pair.second.first.expired())
               ++count;

         return count;
      }

   private:
      friend class EventManager;

      std::unordered_map<
         BaseEvent::Family,
         std::pair<std::weak_ptr<EventSubscription>, std::size_t>
         > m_subscriptions;
   };


   // ---------------------------------------------------------------------- //
   // EventSubscriber -------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   template <typename Derived>
   class EventSubscriber : public BaseEventSubscriber
   {
   public:
      virtual ~EventSubscriber() {}
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