#include <iostream>
#include "windowClass.h"
#include "world.h"
#include "component.h"
#include "scene.h"
#include "image.h"
#include "position2D.h"
#include "sprite.h"
#include "TestLevel.h"
#include "namespaces.hpp"
#include "physicsEngine.h"
#include "imguiMenuUI.h"

int main(int argc, char* args[]) {

	unsigned int dt = 0;
	int screenWidth = 800;
	int screenHeight = 600;
	_sdlWindow window(screenWidth, screenHeight,100,100,"Hello World!", SDL_WINDOW_RESIZABLE );
	SDL_Renderer* renderer = window.getRenderer(SDL_RENDERER_ACCELERATED);
	SDL_Event e;
	
	sceneManager* sManager = new sceneManager;
	TestLevel level1;


	IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG || IMG_INIT_TIF);
	
	if (!SDL_Init(SDL_INIT_EVERYTHING))
		std::cout << SDL_GetError() << std::endl;
	level1.start(renderer,sManager);
	sManager->startCurrent(renderer);

	//imguiMenuUI::init(renderer,window.window);
	//tools::frameTime = 0;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer(window.window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);

	while (true)
	{
		Uint64 start = SDL_GetPerformanceCounter();
		physicsVariables::deltaTime++;
		dt++;
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
		SDL_GetKeyboardState(&keyBoard::keyDown);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		
		
		level1.update(renderer, sManager,dt);

		// Dont delete
		// sManager updates all components
		sManager->updateCurrent(renderer);
		SDL_RenderPresent(renderer);
		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		ImGui_ImplSDL2_ProcessEvent(&e);
		SDL_Delay(floor(16.666f - elapsedMS));
	}
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	SDL_Quit();
	return -1;
}
