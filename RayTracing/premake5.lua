project "RayTracing"
	kind "ConsoleApp"
	language "C++"
	targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")

files {
	"include/**.h",
	"src/**.cpp"
}

includedirs {
	"%{wks.location}/HEngine/HEngine/include",
	"%{wks.location}/glm",
	"include",
}

links {
	"HEngine"
}