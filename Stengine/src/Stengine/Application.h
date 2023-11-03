#pragma once
#include "stpch.h"

#include "Stengine/Core.h"

#include "Stengine/Event/ApplicationEvent.h"
#include "Stengine/Event/Event.h"
#include "Stengine/LayerStack.h"
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
		bool m_Running;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}
