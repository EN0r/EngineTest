# EngineTest
This is my current primary project. Working on a compact light SDL2 game engine with imgui implementation. Currently working on components and creating new systems for it.


This game engine is designed to be a quick test for a new component system that i created. All of this remaking engines will lead up to me working on a opengl engine.

For the most part this engine is very straight forward to use and create games in. All that is required is each *scene* derives from the engine class. It has virtual members START and Update which will be called once the scene is loaded
by the scene manager.
