#include "stpch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "Stengine/Renderer/Renderer.h"

#include <fstream>

namespace Sten
{
	Ref<Shader> Shader::Create(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertexSrc = ReadFile(vertexPath);
		std::string fragmentSrc = ReadFile(fragmentPath);
		return CreateFromSource(vertexSrc, fragmentSrc);
	}

	Ref<Shader> Shader::CreateFromSource(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ST_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		}

		ST_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	std::string Shader::ReadFile(const std::string& filePath)
	{
		std::string content;
		std::ifstream io(filePath, std::ios::in, std::ios::binary);
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
}