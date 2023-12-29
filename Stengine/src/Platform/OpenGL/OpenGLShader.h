#pragma once

#include "Stengine/Renderer/Shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <shaderc/shaderc.hpp>

namespace Sten
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertex, const std::string& fragment, bool isSource = false); // isSource -> if true the vertex and fragment params are the glsl source code, 
																															  //			 if false the vertex and fragment params are file paths to the source code
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat3(const std::string& name, const glm::mat3& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }
	private:
		void CompileOrGetVulkanBinaries(const std::string& vertexSrc, const std::string& fragmentSrc);
		void CompileShader(shaderc::Compiler& compiler, shaderc::CompileOptions& options, const std::string& filePath, const std::string& source, bool isVertex);
		void CompileOrGetOpenGLBinaries();
		void CreateProgram();
		void Reflect(GLenum stage, const std::vector<uint32_t>& shaderData);
	private:
		std::string ReadFile(const std::string& filePath);
	private:
		uint32_t m_RendererID = 0;
		std::string m_Name;
		std::string m_VertexPath;
		std::string m_FragmentPath;

		std::unordered_map<GLenum, std::vector<uint32_t>> m_VulkanSPIRV;
		std::unordered_map<GLenum, std::vector<uint32_t>> m_OpenGLSPIRV;

		std::unordered_map<GLenum, std::string> m_OpenGLSourceCode;
	};
}