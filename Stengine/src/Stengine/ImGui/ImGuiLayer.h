#pragma once

#include "Stengine/Event/ApplicationEvent.h"
#include "Stengine/Event/MouseEvent.h"
#include "Stengine/Event/KeyEvent.h"

#include "Stengine/Core/Layer.h"

namespace Sten
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		void SetThemeColors();
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}
