workspace "Stengine"
	architecture "x64"
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

-- The output directory based on the configurations
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] 		= "%{wks.location}/Stengine/vendor/GLFW/include"
IncludeDir["Glad"] 		= "%{wks.location}/Stengine/vendor/Glad/include"
IncludeDir["ImGui"] 	= "%{wks.location}/Stengine/vendor/imgui"
IncludeDir["glm"] 		= "%{wks.location}/Stengine/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Stengine/vendor/stb_image"
IncludeDir["entt"] 		= "%{wks.location}/Stengine/vendor/entt/include"
IncludeDir["yaml_cpp"] 	= "%{wks.location}/Stengine/vendor/yaml-cpp/include"

-- Create a solution folder inside visual studio
group "Dependencies"
	include "Stengine/vendor/GLFW"
	include "Stengine/vendor/Glad"
	include "Stengine/vendor/imgui"
	include "Stengine/vendor/yaml-cpp"
group "" -- End the solution folder here

-- Include the premake5.lua files inside these project folders so that they get added to the build system
include "Stengine"
include "Sandbox"
include "Steditor"