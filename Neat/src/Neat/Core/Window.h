#pragma once

#include <string>
#include <functional>
#include <memory>

#include "Neat/Core/Base.h"
#include "Neat/Core/Types.h"
#include "Neat/Events/EventManager.h"


struct GLFWwindow;


namespace Neat
{
   class Window
   {
   public:
      struct WindowImpl;

      // WindowProps ----------------------------------------------------------
      struct WindowProps
      {
         std::string title;
         Int32 width;
         Int32 height;

         WindowProps(const std::string& title = "Neat Engine",
                     Int32 width = 1280,
                     Int32 height = 720)
            : title(title), width(width), height(height)
         {
         }
      };
      // ----------------------------------------------------------------------

   public:
      Window(EventManager& eventManager,
         const WindowProps& props = WindowProps());
      ~Window();

      void swapBuffers();
      void pollEvents();

      Int32 getWidth() const;
      Int32 getHeight() const;

      void* getNativeWindow() const;

      bool isMinimized() const;

      void setVSync(bool enabled);
      bool isSync() const;

   private:
      std::unique_ptr<WindowImpl> m_impl;
   };
}