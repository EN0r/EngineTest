#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include "windowClass.h"
#include "world.h"
#include "component.h"
#include "scene.h"
#include "image.h"
#include "position2D.h"
#include "sprite.h"
#include "TestLevel.h"


int main(int argc, char* args[]) {

	int screenWidth = 800;
	int screenHeight = 600;
	_sdlWindow window(screenWidth, screenHeight,100,100,"Hello World!", SDL_WINDOW_RESIZABLE );
	SDL_Renderer* renderer = window.getRenderer(SDL_RENDERER_ACCELERATED);
	SDL_Event e;
	
	sceneManager* sManager = new sceneManager;
	TestLevel level1;
	/*
		position2D* pos = new position2D;
		//sprite* _sprite = new sprite;
		pos->position.x = 100;
		world* level1 = new world;
		world* cWorld;
		sManager->addWorld(level1, level1ID);
		sManager->loadWorld(level1ID,cWorld);
		entity* ent = level1->createEntity();
		//ent->addComponent(_sprite);
		ent->addComponent(pos);
	*/

	image img;
	img.initImage(renderer);

	IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG || IMG_INIT_TIF);

	if (!SDL_Init(SDL_INIT_EVERYTHING))
		std::cout << SDL_GetError() << std::endl;
	level1.start(renderer,sManager);
	sManager->startCurrent(renderer);
	//tools::frameTime = 0;
	while (true)
	{
		Uint64 start = SDL_GetPerformanceCounter();
		switch (SDL_PollEvent(&e))
		{
		case SDL_QUIT:
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			SDL_MinimizeWindow(window.window);
		case SDL_WINDOWEVENT_MAXIMIZED:
			SDL_MaximizeWindow(window.window);
			SDL_GetWindowSize(window.window, &screenWidth, &screenHeight);
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		
		level1.update(renderer, sManager);

		// Dont delete
		// sManager updates all components
		sManager->updateCurrent(renderer);
		SDL_RenderPresent(renderer);
		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		SDL_Delay(floor(16.666f - elapsedMS));
	}

	return -1;
}
