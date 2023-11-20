#pragma once

#include "Stengine/Core/KeyCodes.h"
#include "Stengine/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Sten
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
	};
}