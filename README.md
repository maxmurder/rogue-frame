# rogue-frame
Framework for roguelike games.
This will be long term enducational/hobby project. The goal is to create a framework
for building various roguelike games/experiments. The scope/design/focus is likely to
change over time.

##Desired Feautres:

	###UI Framework.
        - Graphical and SDL Unicode tile rendering
		- Frontend
		- Ingame
		- User Input

	###Component based cusotmizable game framework.
		- Save/Load functionality.
		- 3D gameworld framework.
			- Area loading/offloading.
			- Terrain/level generator
		- Component based entity framework.
		- Dwarf Fortress style material system.

##Dependencies:
	SDL2, SDL2_ttf, SDL2_image, Lua

##Compiling:
	###Linux:
		Install Dependencies:
			`sudo apt-get install libsdl2 libsdl2_ttf libsdl2_image liblua5.2`
		Run scons:
			`scons`

	###Mac:
		####Install Dependencies:
			`brew install sdl2 sdl2_ttf sdl2_image lua`
		####Run Scons:
			`scons --mac`
