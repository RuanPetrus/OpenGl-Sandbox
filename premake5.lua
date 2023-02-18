workspace "ImguiDemo"
  configurations {"Debug", "Release"}

project "ImguiDemo"
  kind "WindowedApp"
  language "C++"

  targetdir ("bin/%{cfg.buildcfg}/%{prj.name}")
  objdir ("bin-int/%{cfg.buildcfg}/%{prj.name}")

  files
  {
    "src/**.h",
    "src/**.cpp",
    "vendor/imgui/*.cpp",
    "vendor/imgui/backends/imgui_impl_glfw.cpp",
    "vendor/imgui/backends/imgui_impl_opengl3.cpp",
  }

  includedirs
  {
    "vendor/imgui",
    "vendor/imgui/backends"
  }

  filter { "system:linux"}
    buildoptions { "`pkg-config --cflags glfw3`" }
    linkoptions { "-lGL `pkg-config --static --libs glfw3`" }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

   filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
