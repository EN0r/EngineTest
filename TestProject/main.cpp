#include <iostream>
#include "SDL_ttf.h"
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
#include "fBirdClone.h"
#include "frameRate.h"
#include "fileSystem.h"

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
	if (!TTF_Init())
		std::cout << SDL_GetError() << std::endl;
	//imguiMenuUI::init(renderer,window.window);
	//tools::frameTime = 0;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer(window.window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);
	fBirdClone level;
	level.start(renderer,sManager);
	sManager->startCurrent(renderer);

	while (true)
	{
		FPS f;
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
		
		
		level.update(renderer, sManager,dt);
		// Dont delete
		// sManager updates all components
		sManager->updateCurrent(renderer);
		SDL_RenderPresent(renderer);
		Uint64 end = SDL_GetPerformanceCounter();
 		FPS::delayFPS(FPS::fpsLockToMS(360),FPS::fpsCount(start,end));
		//std::cout << (float)1000/60 << std::endl;

		//float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		//std::cout << elapsedMS << std::endl;
		ImGui_ImplSDL2_ProcessEvent(&e);
		//SDL_Delay(16.6666666f - elapsedMS);
	}
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	TTF_Quit();
	SDL_Quit();
	return -1;
}
