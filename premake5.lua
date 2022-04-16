workspace "Pixie"
    architecture "x86_64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Pixie/vendor/GLFW"
include "Pixie/vendor/Glad"
include "Pixie/vendor/imgui"
include "Pixie/vendor/yaml"

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
        "Pixie/vendor/ImGuizmo"
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
        "yaml"
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
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"

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

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
    