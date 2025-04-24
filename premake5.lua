workspace "Tasaly"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}

IncludeDir["GLFW"] = "Tasaly/vendor/GLFW/include"
IncludeDir["Glad"] = "Tasaly/vendor/Glad/include"

include "Tasaly/vendor/GLFW"
include "Tasaly/vendor/Glad"

project "Tasaly"
	location "Tasaly"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "tspch.h"
	pchsource "Tasaly/src/tspch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GLFW_INCLUDE_NONE",

			"TS_PLATFORM_WINDOWS",
			"TS_ENABLE_ASSERTS",
			"TS_BUILD_DLL"
		}

		buildoptions
		{
			"/utf-8",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "TS_DEBUG"
		buildoptions "/MDd"
		symbols "On"
			
	filter "configurations:Release"
		defines "TS_RELEASE"
		buildoptions "/MD"
		optimize "On"
			
	filter "configurations:Dist"
		defines "TS_DIST"
		buildoptions "/MDd"
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
		"Tasaly/vendor/spdlog/include",
		"Tasaly/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TS_PLATFORM_WINDOWS",
		}

		links
		{
			"Tasaly"
		}

		buildoptions
		{
			"/utf-8",
		}

	filter "configurations:Debug"
		defines "TS_DEBUG"
		symbols "On"
			
	filter "configurations:Release"
		defines "TS_RELEASE"
		optimize "On"
			
	filter "configurations:Dist"
		defines "TS_DIST"
		optimize "On"


