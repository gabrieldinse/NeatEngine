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

      template <typename E, typename Subscriber>
      std::size_t add(Subscriber& subscriber)
      {
         bool (Subscriber::*receive)(const E&) = &Subscriber::receive;

         auto callback = EventCallbackWrapper<E>(
            std::bind(receive, &subscriber, std::placeholders::_1));

         m_callbacks.emplace_back(
            std::make_shared<EventCallback>(callback));
         
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
         executeCallbacks(&event);
      }

      template <typename E>
      void publish(std::unique_ptr<E> event)
      {
         executeCallbacks(event.get());
      }

      template <typename E, typename... Args>
      void publish(Args&&... args)
      {
         E event(std::forward<Args>(args)...);
         executeCallbacks(&event);
      }


      UInt size() const { return (UInt)m_callbacks.size(); }

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

      void executeCallbacks(const void* event)
      {
         for (auto& callback : m_callbacks)
            if (callback)
            {
               bool handled = (*callback)(event);
               if (handled)
                  break;
            }
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
         for (auto& subscription_pair : m_subscriptions)
         {
            auto& subscription = subscription_pair.second.first;
            if (!subscription.expired())
               subscription.lock()->remove(subscription_pair.second.second);
         }
      }

      UInt BaseEventSubscriber::getNumberOfConnectedSignals() const
      {
         UInt count = 0;
         for (auto& subscription_pair : m_subscriptions)
            if (!subscription_pair.second.first.expired())
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
   struct EventSubscriber : public BaseEventSubscriber
   {
      virtual ~EventSubscriber() {}
   };


   // ---------------------------------------------------------------------- //
   // Window events -------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   struct WindowResizeEvent
   {
      WindowResizeEvent(UInt width, UInt height)
         : width(width), height(height) {}

      UInt width;
      UInt height;
   };


   struct WindowCloseEvent
   {
      WindowCloseEvent() = default;
   };


   // ---------------------------------------------------------------------- //
   // Mouse events --------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   struct MouseButtonEvent
   {
      MouseCode m_button;

   protected:
      MouseButtonEvent(MouseCode button)
         : m_button(button) {}
   };


   struct MouseButtonPressedEvent : public MouseButtonEvent
   {
      MouseButtonPressedEvent(MouseCode button)
         : MouseButtonEvent(button) {}
   };


   struct MouseButtonReleasedEvent : public MouseButtonEvent
   {
      MouseButtonReleasedEvent(MouseCode button)
         : MouseButtonEvent(button) {}
   };


   struct MouseMovedEvent
   {
      MouseMovedEvent(float xPos, float yPos)
         : xPos(xPos), yPos(yPos) {}

      float xPos;
      float yPos;
   };


   struct MouseScrolledEvent
   {
   public:
      MouseScrolledEvent(float xOffset, float yOffset)
         : xOffset(xOffset), yOffset(yOffset) {}

      float xOffset;
      float yOffset;
   };


   // ---------------------------------------------------------------------- //
   // Key events ----------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   struct KeyEvent
   {
      KeyCode m_keyCode;

   protected:
      KeyEvent(KeyCode keyCode)
         : m_keyCode(keyCode) {}
   };


   struct KeyPressedEvent : public KeyEvent
   {
   public:
      KeyPressedEvent(KeyCode keyCode, Int repeatCount = 0)
         : KeyEvent(keyCode), repeatCount(repeatCount) {}

      Int repeatCount;
   };


   struct KeyReleasedEvent : public KeyEvent
   {
      KeyReleasedEvent(KeyCode keycode)
         : KeyEvent(keycode) {}
   };


   struct KeyTypedEvent : public KeyEvent
   {
      KeyTypedEvent(KeyCode keyCode)
         : KeyEvent(keyCode) {}
   };

}