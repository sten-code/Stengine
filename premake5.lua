workspace "Stengine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Stengine"
	location "Stengine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ST_PLATFORM_WINDOWS",
			"ST_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "ST_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "ST_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ST_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Stengine/src"
	}

	links
	{
		"Stengine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ST_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "ST_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "ST_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ST_DIST"
		optimize "On"
