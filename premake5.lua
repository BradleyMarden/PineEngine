workspace "Pine"
    architecture "x64"

    configurations
    {

        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "Pine"
        location "Pine"
        kind    "SharedLib"
        language "C++"
        targetdir("bin/" .. outputdir .. "/%{prj.name}") 
        objDir("bin-int/" .. outputdir .. "/%{prj.name}") 

        files
        {
            "%{prj.name}/Source/**.h"
            "%{prj.name}/Source/**.cpp"


        }

        include
        {
            "%{prj.name}/Vendor/spdlog/include"

        }

        filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0"
        defines
        {
            "PINE_PLATFORM_WINDOWS",
            "PINE_BUILD_DLL"
        }
  
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/PMyGame")
        }

        filter "configurations:Debug"
        defines "PINE_DEBUG"
        symbols "On"

        filter "configurations:Release"
        defines "PINE_RELEASE"
        optimize "On"

        filter "configurations:Dist"
        defines "PINE_DIST"
        optimize "On"

        project "PMyGame"
        location "pMyGame"
        kind "ConsoleApp"
        language "C++"

        targetdir("bin/" .. outputdir .. "/%{prj.name}") 
        objDir("bin-int/" .. outputdir .. "/%{prj.name}") 

        files
        {
            "%{prj.name}/Source/**.h"
            "%{prj.name}/Source/**.cpp"
        }

        include
        {
            "%{prj.name}/Vendor/spdlog/include",
            "Pine/Source"

        }

        filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0"
        defines
        {
            "PINE_PLATFORM_WINDOWS"
        }

        links
        {
            "Pine"
        }
  

        filter "configurations:Debug"
        defines "PINE_DEBUG"
        symbols "On"

        filter "configurations:Release"
        defines "PINE_RELEASE"
        optimize "On"

        filter "configurations:Dist"
        defines "PINE_DIST"
        optimize "On"

