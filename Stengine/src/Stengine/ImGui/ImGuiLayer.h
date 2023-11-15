#pragma once

#include "Stengine/Event/ApplicationEvent.h"
#include "Stengine/Event/MouseEvent.h"
#include "Stengine/Event/KeyEvent.h"

#include "Stengine/Core/Layer.h"

namespace Sten
{
	class STEN_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}
