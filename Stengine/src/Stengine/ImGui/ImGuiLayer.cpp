#include "stpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#define IMGUI_IMPL_API
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Stengine/Core/Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <ImGuizmo.h>

namespace Sten
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") 
	{}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		io.Fonts->AddFontFromFileTTF("assets/fonts/JetBrainsMono/JetBrainsMono-Regular.ttf", 15.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans/OpenSans-Regular.ttf", 15.0f);

		ImGui::StyleColorsDark();
		
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		SetThemeColors();

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	static ImVec4 FromRGB(int r, int g, int b)
	{
		return ImVec4{ r / 255.0f, g / 255.0f, b / 255.0f, 1.0f };
	}

	void ImGuiLayer::SetThemeColors()
	{
		auto& style = ImGui::GetStyle();
		style.TabRounding = 4.0f;
		style.ChildRounding = 3.0f;
		style.FrameRounding = 3.0f;
		style.GrabRounding = 3.0f;
		style.WindowRounding = 3.0f;
		style.PopupRounding = 3.0f;

		style.Colors[ImGuiCol_WindowBg] = FromRGB(30, 30, 46);
		style.Colors[ImGuiCol_MenuBarBg] = FromRGB(24, 24, 37);

		// Header
		style.Colors[ImGuiCol_Header] = FromRGB(49, 50, 68);
		style.Colors[ImGuiCol_HeaderHovered] = FromRGB(69, 71, 90);
		style.Colors[ImGuiCol_HeaderActive] = FromRGB(49, 50, 68);

		// Buttons
		style.Colors[ImGuiCol_Button] = FromRGB(49, 50, 68);
		style.Colors[ImGuiCol_ButtonHovered] = FromRGB(69, 71, 90);
		style.Colors[ImGuiCol_ButtonActive] = FromRGB(49, 50, 68);

		// Frame BG
		style.Colors[ImGuiCol_FrameBg] = FromRGB(49, 50, 68);
		style.Colors[ImGuiCol_FrameBgHovered] = FromRGB(69, 71, 90);
		style.Colors[ImGuiCol_FrameBgActive] = FromRGB(49, 50, 68);

		// Tabs
		style.Colors[ImGuiCol_Tab] = FromRGB(137, 180, 250);
		style.Colors[ImGuiCol_TabHovered] = FromRGB(137, 180, 250);
		style.Colors[ImGuiCol_TabActive] = FromRGB(243, 139, 168);
		style.Colors[ImGuiCol_TabUnfocused] = FromRGB(235, 160, 172);
		style.Colors[ImGuiCol_TabUnfocusedActive] = FromRGB(137, 180, 250);

		// Title
		style.Colors[ImGuiCol_TitleBg] = FromRGB(24, 24, 37);
		style.Colors[ImGuiCol_TitleBgActive] = FromRGB(30, 30, 46);
		style.Colors[ImGuiCol_TitleBgCollapsed] = FromRGB(127, 132, 156);
	}
}