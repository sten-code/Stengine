#include "stpch.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "Stengine/Renderer/Renderer.h"
#include "Stengine/Renderer/VertexArray.h"


namespace Sten
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ST_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		ST_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}