# rogue-frame
Framework for ncurses roguelike games.

This will be a rather ambitious and long term  project. The goal is to create 
a framework for building various ascii roguelike games. Idealy this will be 
a highly customizable framework where most game rules, creatures, worlds are
defined at run-time by configuration files (json).

Desired Feautres: 

	Modular frontend UI with various menus/options.

	Ncurses and graphical tiles rendering.

	Game framework with modular and extendable rule set.
		- Modular ingame UI framework.
			- Menus.
			- Player Controls.
			- Debugging.
		- Save/Load functionality.
		- 3D gameworld framework.
			- Area loading/offloading.
		- Modular creature framework.
			- Definable matierals/parts/creatures (DF Style).
		- Extensible environment interaction / combat framework.


