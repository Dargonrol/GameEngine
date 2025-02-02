-- premake5.lua
AppName = "App.example"
CoreName = "Engine"

workspace "GameEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject (AppName)

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group ""
include (CoreName .. "/Build-Engine.lua")
group ""

include (AppName .. "/Build-App.lua")