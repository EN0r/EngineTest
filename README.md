# EngineTest
This is my current primary project. Working on a compact light SDL2 game engine with imgui implementation. Currently working on components and creating new systems for it.


This game engine is designed to be a quick test for a new component system that i created. All of this remaking engines will lead up to me working on a opengl engine.

For the most part this engine is very straight forward to use and create games in. All that is required is each *scene* derives from the engine class. It has virtual members START and Update which will be called once the scene is loaded
by the scene manager.

I am currently rebuilding this from the ground up as there's ALOT of room for improvement especially in terms of memory usage. There's a test game built in the engine which was created within a day.
In terms of the TextLabel system i need to rework it as it's very easy to create memory leaks with it.

The end goal of all the engines is to get to a solid point where 2d games are simple and easy to create with alot of documentation and it to be completely open source.

As it stands this project is dead and i will no longer be working on it as im recreating it with alot of improvements especially the component system which has much to be desired.
