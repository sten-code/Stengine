#pragma once

namespace Sten
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL
	};


	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
		inline static RendererAPI SetAPI(RendererAPI api) { s_RendererAPI = api; }
	private:
		static RendererAPI s_RendererAPI;

	};
}