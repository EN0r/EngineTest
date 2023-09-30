#pragma once
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include "windowClass.h"
#include "sprite.h"
#include "scene.h"
#include <vector>
class TestLevel
{
private:
	world* thisWorld = new world;
	int thisWorldID = -1;
	SDL_Event e;
	int x, y;
public:
	void update(SDL_Renderer* renderer, sceneManager* manager);
	void start(SDL_Renderer* renderer, sceneManager* manager);
};

void TestLevel::start(SDL_Renderer* renderer, sceneManager* manager)
{
	manager->addWorld(thisWorld, thisWorldID);
	manager->loadWorld(thisWorldID);
	// def entities
	entity* cube = thisWorld->createEntity();
	cube->tag = "Weinus";
	transform* _transform = new transform;
	sprite* _sprite = new sprite;

	cube->addComponent(_transform);
	cube->getComponentEX<transform*>()->position = { 100,100 };
	cube->getComponentEX<transform*>()->w = 100;
	cube->getComponentEX<transform*>()->h = 100;

	cube->addComponent(_sprite);
	cube->getComponentEX<sprite*>()->init(cube);

	

}
void TestLevel::update(SDL_Renderer* renderer, sceneManager* manager)
{
	SDL_PollEvent(&e);
	
	SDL_GetMouseState(&this->x, &this->y);

	manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<transform*>()->position.x = manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<transform*>()->position.x + 1;

}