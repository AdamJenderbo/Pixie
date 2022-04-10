workspace "Pixie"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Pixie/vendor/GLFW"
include "Pixie/vendor/Glad"

project "Pixie"
    location "Pixie"
    kind "StaticLib" 
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    includedirs
	{
		"%{prj.name}/src",
        "%{prj.name}/vendor/GLFW/include",
        "%{prj.name}/vendor/Glad/include"
	}

    links
    {
        "GLFW",
        "opengl32.lib",
        "Glad"
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
        "Pixie/vendor/GLFW/include"
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
