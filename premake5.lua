workspace "Neat"
    architecture "x64"
    startproject "Sandbox"
    
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {} -- Added a variable
IncludeDir["GLFW"] = "Neat/vendor/GLFW/include"
IncludeDir["Glad"] = "Neat/vendor/Glad/include"
IncludeDir["ImGui"] = "Neat/vendor/ImGui"
IncludeDir["stb_image"] = "Neat/vendor/stb_image"
IncludeDir["spdlog"] = "Neat/vendor/spdlog/include"

group "Dependencies"
    include "Neat/vendor/GLFW"
    include "Neat/vendor/Glad"
    include "Neat/vendor/ImGui"

group ""

project "Neat"
    location "Neat" -- Neat project is inside Neat folder
    kind "StaticLib"
    language "C++"
    cppdialect "c++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    -- Add this files to the be used in the project
    -- OBS: Can exclude platform specifics and add them
    -- in the respective filter
    files
    {
        "%{prj.name}/src/Neat/**.h", -- ** = folders and subfolders
        "%{prj.name}/src/Neat/**.hpp",
        "%{prj.name}/src/Neat/**.cpp",
        "%{prj.name}/src/Neat/**.inl",
        "%{prj.name}/src/*.h", -- ** = folders and subfolders
        "%{prj.name}/src/*.hpp",
        "%{prj.name}/src/*.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.hpp",
        "%{prj.name}/vendor/stb_image/**.cpp"
    }


    includedirs
    {
        -- Same as the VS project configs
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.stb_image}"
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
            "GLFW_INCLUDE_NONE" -- Glad
        }

        files
        {
            "%{prj.name}/src/Platform/Windows/**.h", -- ** = folders and subfolders
            "%{prj.name}/src/Platform/Windows/**.hpp",
            "%{prj.name}/src/Platform/Windows/**.cpp",
        }
    
    -- Set specific macro variables
    filter "configurations:Debug"
        defines "NT_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "NT_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "NT_DIST"
        runtime "Release"
        optimize "on"

    
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "c++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


    files
    {
        "%{prj.name}/src/**.h", -- ** = folders and subfolders
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        -- Same as the VS project configs
        "Neat/vendor/spdlog/include",
        "Neat/src",
        "Neat/vendor"
    }

    links
    {
        "Neat"
    }

    filter "system:windows"
        systemversion "latest"
    
    -- Set specific macro variables
    filter "configurations:Debug"
        defines "NT_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "NT_RELEASE"
        runtime "Release"
        optimize "on"
           
    filter "configurations:Dist"
        defines "NT_DIST"
        runtime "Release"
        optimize "on"