workspace "Stengine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Stengine/vendor/GLFW/include"
IncludeDir["Glad"] = "Stengine/vendor/Glad/include"
IncludeDir["imgui"] = "Stengine/vendor/imgui"
IncludeDir["glm"] = "Stengine/vendor/glm"
IncludeDir["stb_image"] = "Stengine/vendor/stb_image"

include "Stengine/vendor/GLFW"
include "Stengine/vendor/Glad"
include "Stengine/vendor/imgui"

project "Stengine"
	location "Stengine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "stpch.h"
	pchsource "Stengine/src/stpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ST_PLATFORM_WINDOWS",
			"ST_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "ST_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "ST_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ST_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Stengine/vendor/spdlog/include",
		"Stengine/src",
		"Stengine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Stengine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ST_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "ST_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "ST_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "ST_DIST"
		runtime "Release"
		optimize "On"
