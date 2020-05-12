#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "Neat/Core/Types.h"
#include "Neat/Renderer/Uniform.h"
#include "Neat/Math/Vector.h"
#include "Neat/Math/Matrix.h"



namespace Neat
{
   class ShaderProgram
   {
   public:
      ShaderProgram(const std::string& filepath);
      ShaderProgram(const std::string& name, const std::string& filepath);
      ShaderProgram(
         const std::string& name,
         const std::string& vertexSource,
         const std::string& fragmentSource);
      virtual ~ShaderProgram();

      void bind() const;
      void unbind() const;

      const std::string& getName() const { return this->name; }
      void setName(const std::string& name) { this->name = name; }

      UInt getRendererID() const { return this->id; }

      const UniformLibrary& getUniformLibrary() const { return *this->uniformLibrary; }

   private:
      void compile(
         const std::unordered_map<UInt, std::string>& shaderSources);

   private:
      UInt id = 0;
      std::unique_ptr<UniformLibrary> uniformLibrary;
      std::string name;
   };


   class ShaderLibrary
   {
   public:
      void add(const std::shared_ptr<ShaderProgram>& shader);
      void add(const std::string& name, const std::shared_ptr<ShaderProgram>& shader);
      std::shared_ptr<ShaderProgram> load(const std::string& filepath);
      std::shared_ptr<ShaderProgram> load(
         const std::string& name, const std::string& filepath);
      std::shared_ptr<ShaderProgram> get(const std::string& name);

      Bool exists(const std::string& name) const;

   private:
      std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> shaders;
   };
}