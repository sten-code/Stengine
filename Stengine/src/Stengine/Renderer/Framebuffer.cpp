#include "stpch.h"
#include "Framebuffer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

#include "Stengine/Renderer/Renderer.h"

namespace Sten
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		ST_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ST_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLFramebuffer>(spec);
		}

		ST_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}