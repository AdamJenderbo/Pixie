workspace "Pixie"
    architecture "x86_64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

VULKAN_SDK = os.getenv("VULKAN_SDK")

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "vendor/VulkanSDK/Lib"
LibraryDir["VulkanSDK_DebugDLL"] = "%{wks.location}/Pixie/vendor/VulkanSDK/Bin"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"


group "Dependencies"
    include "Pixie/vendor/GLFW"
    include "Pixie/vendor/Glad"
    include "Pixie/vendor/imgui"
    include "Pixie/vendor/yaml"
group ""

project "Pixie"
    location "Pixie"
    kind "StaticLib" 
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pxpch.h"
	pchsource "Pixie/src/pxpch.cpp"

    includedirs
	{
		"Pixie/src",
        "Pixie/vendor/GLFW/include",
        "Pixie/vendor/Glad/include",
        "Pixie/vendor/imgui",
        "Pixie/vendor/glm",
        "Pixie/vendor/entt/include",
        "Pixie/vendor/stb_image",
        "Pixie/vendor/yaml/include",
        "Pixie/vendor/ImGuizmo",
        "Pixie/vendor/shaderc/include",
        "Pixie/vendor/SPIRV-Cross",
        "%{VULKAN_SDK}/Include"
	}

    files 
    { 
        "Pixie/src/**.h", 
        "Pixie/src/**.cpp",
        "Pixie/vendor/stb_image/**.h",
		"Pixie/vendor/stb_image/**.cpp",
		"Pixie/vendor/glm/glm/**.hpp",
		"Pixie/vendor/glm/glm/**.inl",

        -- "vendor/ImGuizmo/ImGuizmo.h",
		-- "vendor/ImGuizmo/ImGuizmo.cpp"
    }

    links
    {
        "GLFW",
        "opengl32.lib",
        "Glad",
        "ImGui",
        "yaml",
        
    }


    defines 
    {
        "YAML_CPP_STATIC_DEFINE"
    }

    filter "files:Pixie/src/Pixie/ImGui/**.cpp"
	    flags { "NoPCH" }


    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "on"

        links
		{
			"%{Library.ShaderC_Debug}",
			"%{Library.SPIRV_Cross_Debug}",
			"%{Library.SPIRV_Cross_GLSL_Debug}"
		}

        postbuildcommands
		{
			"{COPYDIR} \"%{LibraryDir.VulkanSDK_DebugDLL}\" \"%{cfg.targetdir}\""
		}

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "on"

        links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp" 
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Pixie/src",
        "Pixie/vendor/GLFW/include",
        "Pixie/vendor/glm",
        "Pixie/vendor/imgui"
	}

	links
	{
		"Pixie"
	}

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"

project "Editor"
    location "Editor"
    kind "ConsoleApp" 
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Editor/src",
        "Pixie/src",
        "Pixie/vendor/GLFW/include",
        "Pixie/vendor/glm",
        "Pixie/vendor/imgui",
        "Pixie/vendor/entt/include",
        "Pixie/vendor/yaml/include"
    }

    links
    {
        "Pixie"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

        postbuildcommands
		{
			"{COPYDIR} \"%{LibraryDir.VulkanSDK_DebugDLL}\" \"%{cfg.targetdir}\""
		}

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
    