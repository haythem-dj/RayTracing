workspace "RayTracing"
	architecture "x64"
	startproject "RayTracing"
	configurations {"Debug", "Release"}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

include "RayTracing"
include "HEngine/HEngine"
-- include "glm"

filter "configurations:Debug"
	defines "DEBUG"

filter "configurations:Release"
	defines "NDEBUG"
	optimize "On"