project "osdialog"
	kind "StaticLib"
	language "C"
	staticruntime "on"
	warnings "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"osdialog.c",
		"osdialog.h",
	}

  filter "system:linux"
		pic "On"
		systemversion "latest"
    
    files
    {
      "osdialog_gtk3.c",
    }

    buildoptions { "`pkg-config --cflags gtk+-3.0`" }
    linkoptions { "`pkg-config --libs gtk+-3.0`" }
    links { "gtk-3", "glib-2.0", "gobject-2.0" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"
