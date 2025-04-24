workspace "Tasaly"
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

IncludeDir["GLFW"] = "Tasaly/vendor/GLFW/include"
IncludeDir["Glad"] = "Tasaly/vendor/Glad/include"
IncludeDir["ImGui"] = "Tasaly/vendor/imgui"

include "Tasaly/vendor/GLFW"
include "Tasaly/vendor/Glad"
include "Tasaly/vendor/imgui"

project "Tasaly"
	location "Tasaly"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
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
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "TS_DEBUG"
		runtime "Debug"
		symbols "On"
			
	filter "configurations:Release"
		defines "TS_RELEASE"
		runtime "Release"
		optimize "On"
			
	filter "configurations:Dist"
		defines "TS_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
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
		"Tasaly/vendor/spdlog/include",
		"Tasaly/src"
	}

	filter "system:windows"
		cppdialect "C++17"
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
		runtime "Debug"
		symbols "On"
			
	filter "configurations:Release"
		defines "TS_RELEASE"
		runtime "Release"
		optimize "On"
			
	filter "configurations:Dist"
		defines "TS_DIST"
		runtime "Release"
		optimize "On"


