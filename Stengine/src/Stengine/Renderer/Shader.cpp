#include "stpch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "Stengine/Renderer/Renderer.h"

#include <fstream>

namespace Sten
{
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertexSrc = ReadFile(vertexPath);
		std::string fragmentSrc = ReadFile(fragmentPath);
		return CreateFromSource(name, vertexSrc, fragmentSrc);
	}

	Ref<Shader> Shader::CreateFromSource(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		Ref<Shader> shader = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ST_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			shader = std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
			break;
		default:
			ST_CORE_ASSERT(false, "Unknown Renderer API");
			return nullptr;
		}

		shader->SetName(name);
		return shader;
	}

	std::string Shader::ReadFile(const std::string& filePath)
	{
		std::string content;
		std::ifstream io(filePath, std::ios::in | std::ios::binary);
		if (!io)
		{
			ST_CORE_ERROR("Couldn't find file: '{0}'", filePath);
			return "";
		}

		io.seekg(0, std::ios::end);
		content.resize(io.tellg());
		io.seekg(0, std::ios::beg);
		io.read(&content[0], content.size());
		io.close();
		return content;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		Add(shader->GetName(), shader);
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		ST_CORE_ASSERT(!Exists(name), "Shader already exists.");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
	{
		Ref<Shader> shader = Shader::Create(name, vertexPath, fragmentPath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		ST_CORE_ASSERT(Exists(name), "Shader doesn't exist.");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}