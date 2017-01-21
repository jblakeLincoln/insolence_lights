solution "lights"
	language "C++"
    objdir "obj"
	targetdir "bin"
	configurations { "Debug", "Release" }

	includedirs {
		"include",
	}

	libdirs {
		"bin",
		"lib"
	}

	defines { "INSOLENCE_OPENGL_DESKTOP" }
	links { "insolence"}

	dofile("./src/game.lua")

