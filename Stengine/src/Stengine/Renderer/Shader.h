#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

namespace Sten
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		const std::string& GetName() const { return m_Name; };
		void SetName(const std::string& name) { m_Name = name; }

		static Ref<Shader> Create(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
		static Ref<Shader> CreateFromSource(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	private:
		static std::string ReadFile(const std::string& filePath);
	private:
		std::string m_Name;
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);

		Ref<Shader> Get(const std::string& name);
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}