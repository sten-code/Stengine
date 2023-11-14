#include "stpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Sten
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}