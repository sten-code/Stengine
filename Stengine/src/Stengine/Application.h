#pragma once
#include "stpch.h"

#include "Stengine/Core.h"

#include "Stengine/Event/ApplicationEvent.h"
#include "Stengine/Event/Event.h"

#include "Stengine/ImGui/ImGuiLayer.h"
#include "Stengine/LayerStack.h"

#include "Stengine/Renderer/Buffer.h"
#include "Stengine/Renderer/Shader.h"
#include "Stengine/Renderer/VertexArray.h"

#include "Stengine/Window.h"

namespace Sten
{
	class STEN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance;  }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<Shader> m_Shader2;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}
