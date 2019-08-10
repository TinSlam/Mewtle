workspace "Mewtle"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Mewtle"
	location "Mewtle"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "PrecompiledHeaders.h"
	pchsource "Mewtle/enginePrecompiledHeaders/PrecompiledHeaders.cpp"

	files{
		"Mewtle/src/**.h",
		"Mewtle/src/**.cpp",
		"Mewtle/enginePrecompiledHeaders/**.h",
		"Mewtle/enginePrecompiledHeaders/**.cpp"
	}

	includedirs{
		"Mewtle/src",
		"Mewtle/dependencies",
		"Mewtle/enginePrecompiledHeaders"
	}

	links{
		"opengl32.lib",
		"glu32.lib",
		"$(SolutionDir)%{prj.name}/dependencies/glew-2.1.0/glew32.lib",
		"$(SolutionDir)%{prj.name}/dependencies/FreeType/freetype.lib",
		"$(SolutionDir)%{prj.name}/dependencies/glfw-3.3.bin.WIN64/glfw3dll.lib",
		"$(SolutionDir)%{prj.name}/dependencies/ObjParser/ObjParser.lib"
	}
	
	--postbuildcommands{
	--	("{COPY} %{cfg.buildtarget.relpath} Mewtle/dlls")
	--}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"MTL_PLATFORM_WINDOWS",
			"MTL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "MTL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MTL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MTL_DIST"
		runtime "Release"
		optimize "on"

-- Remove this after integration is over.
--project "ObjParser"
--	location "ObjParser"
--	kind "StaticLib"
--	language "C++"
--	cppdialect "C++17"
--	staticruntime "on"

--	targetdir("bin/" .. outputdir .. "/%{prj.name}")
--	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

--	files{
--		"%{prj.name}/**.h",
--		"%{prj.name}/**.cpp"
--	}

	--postbuildcommands{
	--	("{COPY} %{cfg.buildtarget.relpath} Mewtle/dependencies/ObjParser/ObjParser.lib")
	--}

--	filter "system:windows"
--		cppdialect "C++17"
--		staticruntime "On"
--		systemversion "latest"

--		defines{
--			"MTL_PLATFORM_WINDOWS"
--		}

--	filter "configurations:Debug"
--		defines "MTL_DEBUG"
--		runtime "Debug"
--		symbols "on"

--	filter "configurations:Release"
--		defines "MTL_RELEASE"
--		runtime "Release"
--		optimize "on"

--	filter "configurations:Dist"
--		defines "MTL_DIST"
--		runtime "Release"
--		optimize "on"		
