#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include "scene.h"
#include "time.h"
#include "camera2D.h"
#include "windowClass.h"
#include "sprite.h"
#include <vector>
#include "boxCollider.h"
#include "rigidBody2D.h"
#include "UIFrame.h"
#include "text.h"

class fBirdClone
{
private:
	SDL_Rect backDropRect = { 0,0,800,600 };
	SDL_Rect backDropAboveRect = { 0,-600,800,600 };
	SDL_Rect backDropRectBelow = { 0,600,800,600 };
	unsigned int gameState = 1;
	image backDrop;
	image backDropAbove;
	world* thisWorld = new world;
	int thisWorldID = -1;
	entity* player = thisWorld->createEntity();
	game_Text Score;
	game_Text ScoreValue;
	unsigned int playerScore = 0;
	bool jumping = false;
	std::vector<unsigned int> spawnedID;

	SDL_Event e;
	int x, y;
	const Uint8* keys;
	camera2D* camera = new camera2D();
	const std::string files[4] = { "./resources/flapgameresource/backdrop.png","./resources/flapgameresource/character.png","./resources/flapgameresource/cursor.png","./resources/flapgameresource/SteamingCoffee.png"};
	int keycode;
	int mSpeed = 4;
public:
	void update(SDL_Renderer* renderer, sceneManager* manager, unsigned int deltaTime);
	void start(SDL_Renderer* renderer, sceneManager* manager);
	timer t_timer;
};

