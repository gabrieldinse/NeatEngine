#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "Neat/Core/Types.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class Texture
   {
   public:
      virtual ~Texture() = default;

      virtual Int getWidth() const = 0;
      virtual Int getHeight() const = 0;

      virtual void setData(void* data, UInt size) = 0;

      virtual void bind(UInt slot = 0) const = 0;

      virtual Bool operator==(const Texture& other) const = 0;
   };

   class Texture2D : public Texture
   {
   public:
      Texture2D(Int width, Int height);
      Texture2D(const std::string& filepath);
      ~Texture2D();

      Int getWidth() const { return this->width; }
      Int getHeight() const { return this->height; }

      virtual const Vec2* getCoordinates() const
      {
         return this->coordinates;
      };

      void setData(void* data, UInt size);

      void bind(UInt slot) const;

      Bool operator==(const Texture& other) const
      {
         return
            (this->rendererID ==
               static_cast<const Texture2D&>(other).rendererID);
      }

   private:
      UInt rendererID;
      Int width;
      Int height;
      UInt internalFormat;
      UInt dataFormat;
      const Vec2 coordinates[4] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };
   };
}