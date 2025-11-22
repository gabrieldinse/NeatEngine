#pragma once

#include <string>
#include <unordered_map>

#include "Core/Types.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Math/Types/Matrix4x4.hpp"
#include "Math/Types/Matrix3x3.hpp"
#include "Math/Types/Vector4.hpp"
#include "Math/Types/Vector3.hpp"
#include "Math/Types/Vector2.hpp"

namespace Neat {
class OpenGLShaderProgram : public ShaderProgram {
 public:
  OpenGLShaderProgram(const std::string &filepath);
  OpenGLShaderProgram(const std::string &name, const std::string &filepath);
  OpenGLShaderProgram(const std::string &name, const std::string &vertexSource,
                      const std::string &fragmentSource);
  virtual ~OpenGLShaderProgram();

  virtual void bind() const override;
  virtual void unbind() const override;

  virtual const std::string &getName() const override { return m_name; }
  virtual void setName(const std::string &name) override { m_name = name; }
  virtual void set(const std::string &name, float value) override;
  virtual void set(const std::string &name, Vector2F values) override;
  virtual void set(const std::string &name, Vector3F values) override;
  virtual void set(const std::string &name, Vector4F values) override;
  virtual void set(const std::string &name, Int32 value) override;
  virtual void set(const std::string &name, Int32 *values,
                   UInt32 count) override;
  virtual void set(const std::string &name, Matrix3F matrix) override;
  virtual void set(const std::string &name, Matrix4F matrix) override;

 private:
  void build(const std::string &filepath);
  void build(std::unordered_map<UInt32, std::string> &shader_sources);
  UInt32 compileShader(UInt32 type, const std::string &source);
  std::unordered_map<UInt32, std::string> splitShaderSources(
      const std::string &shaderSources);
  void linkProgram(std::vector<UInt32> shaderIDs);
  Int32 getUniformLocation(const std::string &name);

 private:
  UInt32 m_id = 0;
  std::string m_name;
  std::unordered_map<std::string, Int32> m_uniformLocationCache;
};
}  // namespace Neat