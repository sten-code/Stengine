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

-- The output directory based on the configurations
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] 			= "%{wks.location}/Stengine/vendor/GLFW/include"
IncludeDir["Glad"] 			= "%{wks.location}/Stengine/vendor/Glad/include"
IncludeDir["ImGui"] 		= "%{wks.location}/Stengine/vendor/imgui"
IncludeDir["ImGuizmo"] 		= "%{wks.location}/Stengine/vendor/ImGuizmo"
IncludeDir["Box2D"]			= "%{wks.location}/Stengine/vendor/Box2D/include"
IncludeDir["glm"] 			= "%{wks.location}/Stengine/vendor/glm"
IncludeDir["entt"] 			= "%{wks.location}/Stengine/vendor/entt/include"
IncludeDir["stb_image"] 	= "%{wks.location}/Stengine/vendor/stb_image"
IncludeDir["yaml_cpp"] 		= "%{wks.location}/Stengine/vendor/yaml-cpp/include"
IncludeDir["VulkanSDK"] 	= "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["VulkanSDK"] 		= "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] 	= "%{wks.location}/Stengine/vendor/VulkanSDK/Lib"

Library = {}
Library["Vulkan"] 					= "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] 				= "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] 			= "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] 		= "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] 	= "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] 		= "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] 			= "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] 		= "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

--------------------------------- Linux ---------------------------------
-- Library = {}
-- Library["Vulkan"] 					= "%{LibraryDir.VulkanSDK}/libvulkan.so.1"
-- Library["VulkanUtils"] 				= "%{LibraryDir.VulkanSDK}/libVkLayer_utils.a"

-- Library["ShaderC_Debug"] 			= "%{LibraryDir.VulkanSDK_Debug}/libshaderc_shared.so"
-- Library["SPIRV_Cross_Debug"] 		= "%{LibraryDir.VulkanSDK_Debug}/libspirv-cross-core.a"
-- Library["SPIRV_Cross_GLSL_Debug"] 	= "%{LibraryDir.VulkanSDK_Debug}/libspirv-cross-glsl.a"
-- Library["SPIRV_Tools_Debug"] 		= "%{LibraryDir.VulkanSDK_Debug}/libSPIRV-Tools.a"

-- Library["ShaderC_Release"] 			= "%{LibraryDir.VulkanSDK}/libshaderc_shared.so"
-- Library["SPIRV_Cross_Release"] 		= "%{LibraryDir.VulkanSDK}/libspirv-cross-core.a"
-- Library["SPIRV_Cross_GLSL_Release"]  = "%{LibraryDir.VulkanSDK}/libspirv-cross-glsl.a"

-- Create a solution folder inside visual studio
group "Dependencies"
	include "Stengine/vendor/GLFW"
	include "Stengine/vendor/Glad"
	include "Stengine/vendor/imgui"
	include "Stengine/vendor/Box2D"
	include "Stengine/vendor/yaml-cpp"
group "" -- End the solution folder here

-- Include the premake5.lua files inside these project folders so that they get added to the build system
include "Stengine"
include "Sandbox"
include "Steditor"