#pragma once

#include <string>

#include "Neat/Core/Core.h"
#include "Neat/Core/Types.h"
#include "Neat/Math/Vector.h"
#include "Neat/Math/Matrix.h"
#include "Neat/Math/MatrixOperations.h"
#include "Neat/Renderer/ShaderDataTypes.h"


namespace Neat
{
   struct UniformData;


	// ---------------------------------------------------------------------- //
	// UniformLibrary-------------------------------------------------------- //
	// ---------------------------------------------------------------------- //
	class UniformLibrary
	{
	public:
		UniformLibrary(UInt shaderId);
		UniformLibrary() = delete;
		~UniformLibrary();

		bool exists(const std::string& name) const;

		UniformData& operator[](const std::string& name);
		const UniformData& operator[](const std::string& name) const;

	private:
		std::unordered_map<std::string, std::unique_ptr<UniformData>> uniforms;
		UInt m_shaderId = 0;
	};


	// ---------------------------------------------------------------------- //
	// UniformBase ---------------------------------------------------------- //
	// ---------------------------------------------------------------------- //
   struct UniformBase
   {
		virtual ~UniformBase();

      const std::string& getName() const;
      Int getType() const;
      Int getSize() const;
      Int getLocation() const;

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
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(float value);
	};

	template<>
	struct Uniform<ShaderDataType::Vector2> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Vector2 values);
	};

	template<>
	struct Uniform<ShaderDataType::Vector3> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Vector3 values);
	};

	template<>
	struct Uniform<ShaderDataType::Vector4> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Vector4 values);
	};

	template<>
	struct Uniform<ShaderDataType::Int> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Int value);
	};

	template<>
	struct Uniform<ShaderDataType::IntArray> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Int* values, Int count);
	};

	template<>
	struct Uniform<ShaderDataType::Matrix3> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Matrix3 matrix);
	};

	template<>
	struct Uniform<ShaderDataType::Matrix4> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Matrix4 matrix);
	};
}