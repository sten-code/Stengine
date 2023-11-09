#include "stpch.h"
#include "Stengine/Renderer/Renderer.h"

#include "Stengine/Renderer/RenderCommand.h"

namespace Sten
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}