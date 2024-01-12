project "Stengine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "stpch.h"
	pchsource "src/stpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",

		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",

		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",

		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"YAML_CPP_STATIC_DEFINE"
	}
 
	includedirs
	{
		"src",
    "vendor",

    "%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.VulkanSDK}",
    "%{IncludeDir.osdialog}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"Box2D",
  	"yaml-cpp",
		"opengl32.lib",
	}

	filter "files:vendor/ImGuizmo/**.cpp"
		flags { "NoPCH" }
	
--[[ --------------------- Linux --------------------- ]]--

	filter "system:linux"
		systemversion "latest"
		defines { "ST_PLATFORM_LINUX" }
		
    buildoptions { "`pkg-config --cflags gtk+-3.0`" }
    linkoptions { "`pkg-config --libs gtk+-3.0`" }
    
    libdirs
    {
      "%{VULKAN_SDK}/lib",
    }

		links
		{
      "gtk-3", "glib-2.0", "gobject-2.0",
      "osdialog",
      "shaderc_combined",
      "spirv-cross-core",
      "spirv-cross-glsl",
		}
		
--[[ -------------------- Windows -------------------- ]]--

	filter "system:windows"
		systemversion "latest"
		defines { "ST_PLATFORM_WINDOWS" }
		
	filter { "configurations:Debug", "system:windows" }
		links
		{
			"%{wks.location}/Stengine/vendor/VulkanSDK/Lib/shaderc_sharedd.lib",
			"%{wks.location}/Stengine/vendor/VulkanSDK/Lib/spirv-cross-cored.lib",
			"%{wks.location}/Stengine/vendor/VulkanSDK/Lib/spirv-cross-glsld.lib",
		}

		postbuildcommands
		{
			"copy \"%{wks.location}Stengine\\vendor\\VulkanSDK\\bin\\shaderc_sharedd.dll\" \"%{wks.location}%{prj.name}\"",
			"copy \"%{wks.location}Stengine\\vendor\\VulkanSDK\\bin\\shaderc_sharedd.dll\" \"%{wks.location}\\bin\\" .. outputdir .. "\\%{prj.name}\"",
		}
		
	filter { "configurations:Release", "system:windows" }
		links
		{
			"%{VULKAN_SDK}/Lib/shaderc_shared.lib",
			"%{VULKAN_SDK}/Lib/spirv-cross-core.lib",
			"%{VULKAN_SDK}/Lib/spirv-cross-glsl.lib",
		}

	filter { "configurations:Dist", "system:windows" }
		links
		{
			"%{VULKAN_SDK}/Lib/shaderc_shared.lib",
			"%{VULKAN_SDK}/Lib/spirv-cross-core.lib",
			"%{VULKAN_SDK}/Lib/spirv-cross-glsl.lib",
		}

--[[ ------------------ Configurations ------------------ ]]--

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
