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

      const std::string& getName() const { return m_name; }
      void setName(const std::string& name) { m_name = name; }

      UInt getRendererID() const { return m_id; }

      const UniformLibrary& getUniformLibrary() const { return *m_uniformLibrary; }

   private:
      void compile(
         const std::unordered_map<UInt, std::string>& shaderSources);
      std::string readFile(const std::string& filepath);
      std::unordered_map<UInt, std::string> preprocessShaderSource(
         const std::string& source);

   private:
      UInt m_id = 0;
      std::unique_ptr<UniformLibrary> m_uniformLibrary;
      std::string m_name;
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

      bool exists(const std::string& name) const;

   private:
      std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> m_shaders;
   };
}