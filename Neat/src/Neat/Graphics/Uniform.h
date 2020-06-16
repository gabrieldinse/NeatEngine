#pragma once

#include <string>

#include "Neat/Core/Base.h"
#include "Neat/Core/Types.h"
#include "Neat/Math/Vector.h"
#include "Neat/Math/Matrix.h"
#include "Neat/Math/MatrixOperations.h"
#include "Neat/Graphics/ShaderDataType.h"


namespace Neat
{
   template <ShaderDataType UniformType>
   struct Uniform;
   struct UniformData;
   class ShaderProgram;


   // ---------------------------------------------------------------------- //
   // UniformLibrary-------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class UniformLibrary
   {
   public:
      UniformLibrary(ShaderProgram& shader);
      UniformLibrary() = delete;
      ~UniformLibrary();

      bool exists(const std::string& name) const;

      UniformData& operator[](const std::string& name);
      const UniformData& operator[](const std::string& name) const;

   private:
      std::unordered_map<std::string, std::unique_ptr<UniformData>> m_uniforms;
      ShaderProgram& m_shader;
   };


   // ---------------------------------------------------------------------- //
   // UniformBase ---------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class UniformBase
   {
   public:
      virtual ~UniformBase();

      const std::string& getName() const;
      Int32 getType() const;
      Int32 getSize() const;
      Int32 getLocation() const;

   protected:
      void checkUniform(ShaderDataType uniformType,
         const std::string& name, const UniformLibrary& uniformLibrary);

   protected:
      std::unique_ptr<UniformData> m_data;
   };


   // ---------------------------------------------------------------------- //
   // Uniform -------------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   template <ShaderDataType uniformType>
   struct Uniform : public UniformBase {};

   template<>
   struct Uniform<ShaderDataType::Float> : public UniformBase
   {
      void set(float value);

   private:
      friend class ShaderProgram;
      Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
   };

   template<>
   struct Uniform<ShaderDataType::Vector2> : public UniformBase
   {
      void set(Vector2 values);

   private:
      friend class ShaderProgram;
      Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
   };

   template<>
   struct Uniform<ShaderDataType::Vector3> : public UniformBase
   {
      void set(Vector3 values);

   private:
      friend class ShaderProgram;
      Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
   };

   template<>
   struct Uniform<ShaderDataType::Vector4> : public UniformBase
   {
      void set(Vector4 values);

   private:
      friend class ShaderProgram;
      Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
   };

   template<>
   struct Uniform<ShaderDataType::Int> : public UniformBase
   {
      void set(Int32 value);

   private:
      friend class ShaderProgram;
      Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
   };

   template<>
   struct Uniform<ShaderDataType::IntArray> : public UniformBase
   {
      void set(Int32* values, UInt32 count);

   private:
      friend class ShaderProgram;
      Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
   };

   template<>
   struct Uniform<ShaderDataType::Matrix3> : public UniformBase
   {
      void set(Matrix3 matrix);

   private:
      friend class ShaderProgram;
      Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
   };

   template<>
   struct Uniform<ShaderDataType::Matrix4> : public UniformBase
   {
      void set(Matrix4 matrix);

   private:
      friend class ShaderProgram;
      Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
   };
}