workspace "Pixie"
    architecture "x86_64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Pixie/vendor/GLFW"
include "Pixie/vendor/Glad"
include "Pixie/vendor/imgui"

project "Pixie"
    location "Pixie"
    kind "StaticLib" 
    language "C++"
    cppdialect "C++17"

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
        "Pixie/vendor/stb_image"
	}

    files 
    { 
        "Pixie/src/**.h", 
        "Pixie/src/**.cpp",
        "Pixie/vendor/stb_image/**.h",
		"Pixie/vendor/stb_image/**.cpp",
		"Pixie/vendor/glm/glm/**.hpp",
		"Pixie/vendor/glm/glm/**.inl",
    }

    links
    {
        "GLFW",
        "opengl32.lib",
        "Glad",
        "ImGui",
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp" 
    language "C++"
    cppdialect "C++17"

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
        "Pixie/vendor/glm"
	}

	links
	{
		"Pixie"
	}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"
