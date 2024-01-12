workspace "Stengine"
	architecture "x86_64"
	startproject "Steditor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

-- The output directory based on the configuration
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

VULKAN_SDK = "/home/sten/vulkansdk/x86_64"

IncludeDir = {}
IncludeDir["spdlog"] 			= "%{wks.location}/Stengine/vendor/spdlog/include"
IncludeDir["GLFW"] 			  = "%{wks.location}/Stengine/vendor/GLFW/include"
IncludeDir["Glad"] 			  = "%{wks.location}/Stengine/vendor/Glad/include"
IncludeDir["ImGui"] 		  = "%{wks.location}/Stengine/vendor/imgui"
IncludeDir["ImGuizmo"] 		= "%{wks.location}/Stengine/vendor/ImGuizmo"
IncludeDir["Box2D"]			  = "%{wks.location}/Stengine/vendor/Box2D/include"
IncludeDir["glm"] 			  = "%{wks.location}/Stengine/vendor/glm"
IncludeDir["entt"] 			  = "%{wks.location}/Stengine/vendor/entt/include"
IncludeDir["stb_image"] 	= "%{wks.location}/Stengine/vendor/stb_image"
IncludeDir["yaml_cpp"] 		= "%{wks.location}/Stengine/vendor/yaml-cpp/include"
IncludeDir["osdialog"] 		= "%{wks.location}/Stengine/vendor/osdialog"
IncludeDir["VulkanSDK"] 	= "%{VULKAN_SDK}/include"


filter {}

-- Create a solution folder inside visual studio
group "Dependencies"
	include "Stengine/vendor/GLFW"
	include "Stengine/vendor/Glad"
	include "Stengine/vendor/imgui"
	include "Stengine/vendor/Box2D"
	include "Stengine/vendor/yaml-cpp"
	include "Stengine/vendor/osdialog"
group "" -- End the solution folder here

-- Include the premake5.lua files inside these project folders so that they get added to the build system
include "Stengine"
include "Steditor"
include "Sandbox"
