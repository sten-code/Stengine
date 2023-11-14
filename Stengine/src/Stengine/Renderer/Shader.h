#pragma once

#include <string>

namespace Sten
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<Shader> Create(const std::string& vertexPath, const std::string& fragmentPath);
		static Ref<Shader> CreateFromSource(const std::string& vertexSrc, const std::string& fragmentSrc);
	private:
		static std::string ReadFile(const std::string& filePath);
	};
}