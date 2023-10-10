#pragma once
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include "scene.h"
#include "time.h"
#include "camera2D.h"
class TestLevel
{
private:
	world* thisWorld = new world;
	int thisWorldID = -1;
	SDL_Event e;
	int x, y;
	const Uint8* keys;

	camera2D* camera = new camera2D();
	
	int keycode;
	int mSpeed = 4;
public:
	void update(SDL_Renderer* renderer, sceneManager* manager, unsigned int deltaTime);
	void start(SDL_Renderer* renderer, sceneManager* manager);
	timer t_timer;
};
