#include "stpch.h"
#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include "Stengine/Renderer/Renderer.h"

namespace Sten
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ST_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}

		ST_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}