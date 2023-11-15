#pragma once

#include "Stengine/Core/Timestep.h"

#include "Stengine/Event/ApplicationEvent.h"
#include "Stengine/Event/Event.h"

#include "Stengine/ImGui/ImGuiLayer.h"
#include "Stengine/Core/LayerStack.h"

#include "Stengine/Core/Window.h"

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
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}
