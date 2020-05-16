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

      virtual void setData(void* m_data, UInt size) = 0;

      virtual void bind(UInt slot = 0) const = 0;
   };

   class Texture2D : public Texture
   {
   public:
      Texture2D(Int width, Int height);
      Texture2D(const std::string& filepath);
      ~Texture2D();

      Int getWidth() const { return m_width; }
      Int getHeight() const { return m_height; }

      virtual const Vec2* getCoordinates() const
      {
         return m_coordinates;
      };

      void setData(void* m_data, UInt size);

      void bind(UInt slot) const;

      bool operator==(const Texture2D& other) const
      {
         return (m_id == other.m_id);
      }

   private:
      UInt m_id;
      Int m_width;
      Int m_height;
      UInt m_internalFormat;
      UInt m_dataFormat;
      const Vec2 m_coordinates[4] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };
   };
}