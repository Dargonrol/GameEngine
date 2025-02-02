project (AppName)
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   includedirs
   {
      "src",

	  -- Include Core
	  ("../" .. CoreName .. "/src"),
	  -- additional libs
	  ("../" .. AppName .. "/Vendor/spdlog/include")
   }

   links
   {
      (CoreName)
   }

   targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
   objdir ("../bin/Intermediates/" .. OutputDir .. "/%{prj.name}")

	filter "system:windows"
		systemversion "latest"
		defines { "CORE_PLATFORM_WINDOWS" }
		buildoptions { "/utf-8" }
		
		filter "architecture:x86"
			-- libdirs { "../Vendor/bin/SDL/Windows/32" }
			postbuildcommands 
			{
				-- ('{COPY} "../Vendor/bin/SDL/Windows/32/SDL3.dll" "%{cfg.targetdir}"')
			}
	   
		filter "architecture:x86_64"
			-- libdirs { "../Vendor/bin/SDL/Windows/64" }
			postbuildcommands 
			{
				-- ('{COPY} "../Vendor/bin/SDL/Windows/64/SDL3.dll" "%{cfg.targetdir}"')
			}
			
		filter "architecture:ARM64"
			-- libdirs { "../Vendor/bin/SDL/arm64" }
			postbuildcommands 
			{
				-- ('{COPY} "../Vendor/bin/SDL/Windows/arm64/SDL3.dll" "%{cfg.targetdir}"')
			}
		 
		   
	filter "system:linux"
        pic "On"
        defines { "LINUX" }
        -- libdirs { "../Vendor/bin/SDL/Unix" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"
	   
	   
	   
	filter "system:windows"
		postbuildcommands
			{
				('{COPY} "%{wks.location}/bin/%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}/' .. CoreName .. '/' .. CoreName .. '.dll" ../bin/' .. OutputDir .. "/%{prj.name}")
			}
	   
	   