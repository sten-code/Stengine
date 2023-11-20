#include "stpch.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "Stengine/Renderer/Renderer.h"
#include "Stengine/Renderer/VertexArray.h"


namespace Sten
{
	Ref<VertexArray> VertexArray::Create()
	{
		ST_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ST_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		ST_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}