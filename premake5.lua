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
IncludeDir["glm"] = "Tasaly/vendor/glm"
IncludeDir["stb_image"] = "Tasaly/vendor/stb_image"

include "Tasaly/vendor/GLFW"
include "Tasaly/vendor/Glad"
include "Tasaly/vendor/imgui"

project "Tasaly"
	location "Tasaly"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "tspch.h"
	pchsource "Tasaly/src/tspch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",

		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
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
		symbols "on"
			
	filter "configurations:Release"
		defines "TS_RELEASE"
		runtime "Release"
		optimize "on"
			
	filter "configurations:Dist"
		defines "TS_DIST"
		runtime "Release"
		optimize "on"

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
		"Tasaly/vendor/spdlog/include",
		"Tasaly/src",
		"Tasaly/vendor",
		"%{IncludeDir.glm}",
	}

	filter "system:windows"
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
		symbols "on"
			
	filter "configurations:Release"
		defines "TS_RELEASE"
		runtime "Release"
		optimize "on"
			
	filter "configurations:Dist"
		defines "TS_DIST"
		runtime "Release"
		optimize "on"


