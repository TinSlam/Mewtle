projectName = "Done"

workspace (projectName)
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project (projectName)
	location (projectName)
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "MewtlePrecompiledHeaders.h"
	pchsource "Mewtle/precompiledHeaders/MewtlePrecompiledHeaders.cpp"

	files{
		(projectName .. "/**.h"),
		(projectName .. "/**.cpp"),
		"Mewtle/precompiledHeaders/**.h",
		"Mewtle/precompiledHeaders/**.cpp"
	}

	includedirs{
		"Mewtle/includes",
		"Mewtle/dependencies",
		"Mewtle/precompiledHeaders"
	}

	links{
		"Mewtle/lib/Mewtle.lib",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines{
			"MTL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MTL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MTL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MTL_DIST"
		runtime "Release"
		optimize "On"

os.execute("mkdir " .. projectName)

os.copyfile("Mewtle/EntryPoint.cpp", (projectName .. "/EntryPoint.cpp"))
os.execute(("mkdir " .. projectName .. "\\src"))
os.execute(("mkdir bin\\Debug-windows-x86_64\\" .. projectName))
os.execute(("mkdir bin\\Release-windows-x86_64\\" .. projectName))
os.execute(("mkdir bin\\Dist-windows-x86_64\\" .. projectName))

local popen = io.popen
for filename in popen('dir "' .. "Mewtle/dlls" .. '" /b'):lines() do
	os.copyfile(("Mewtle/dlls/" .. filename), ("bin/Debug-windows-x86_64/" .. projectName .. "/" .. filename))
	os.copyfile(("Mewtle/dlls/" .. filename), ("bin/Release-windows-x86_64/" .. projectName .. "/" .. filename))
	os.copyfile(("Mewtle/dlls/" .. filename), ("bin/Dist-windows-x86_64/" .. projectName .. "/" .. filename))
end

function copyDirectory(src, dst)
	local popen = io.popen
	for filename in popen('dir "' .. src .. '" /b'):lines() do
		if(os.isdir(src .. "\\" .. filename)) then
			os.execute("mkdir " .. dst .. "\\" .. filename)
			copyDirectory(src .. "\\" .. filename, dst .. "\\" .. filename)
		else
			os.copyfile(src .. "\\" .. filename, dst .. "\\" .. filename)
		end
	end
end

os.execute("mkdir " .. projectName .. "\\assets")
copyDirectory("Mewtle\\assets", (projectName .. "\\assets"))