#pragma once

// For use by Stengine Applications

// ----------------- Core -----------------
#include "Stengine/Core/Application.h"
#include "Stengine/Core/Layer.h"
#include "Stengine/Core/Log.h"
#include "Stengine/Core/Timestep.h"

// IO
#include "Stengine/Core/Input.h"
#include "Stengine/Core/KeyCodes.h"
#include "Stengine/Core/MouseCodes.h"
// ----------------------------------------

// Layers
#include "Stengine/ImGui/ImGuiLayer.h"

// Events
#include "Stengine/Event/ApplicationEvent.h"
#include "Stengine/Event/Event.h"
#include "Stengine/Event/KeyEvent.h"
#include "Stengine/Event/MouseEvent.h"

// Scene
#include "Stengine/Scene/Components.h"
#include "Stengine/Scene/Entity.h"
#include "Stengine/Scene/Scene.h"
#include "Stengine/Scene/ScriptableEntity.h"

// ----------------- Renderer -----------------
#include "Stengine/Renderer/Renderer.h"
#include "Stengine/Renderer/Renderer2D.h"
#include "Stengine/Renderer/RenderCommand.h"
#include "Stengine/Renderer/Camera.h"
#include "Stengine/Renderer/EditorCamera.h"

// Resources
#include "Stengine/Renderer/Buffer.h"
#include "Stengine/Renderer/Framebuffer.h"
#include "Stengine/Renderer/Shader.h"
#include "Stengine/Renderer/Texture.h"
#include "Stengine/Renderer/SubTexture2D.h"
#include "Stengine/Renderer/VertexArray.h"
// --------------------------------------------
