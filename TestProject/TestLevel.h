#pragma once
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include "windowClass.h"
#include "sprite.h"
#include "scene.h"
#include <vector>
#include "boxCollider.h"
#include "time.h"
#include "rigidBody2D.h"
#include "Camera.h"
class TestLevel
{
private:
	world* thisWorld = new world;
	int thisWorldID = -1;
	SDL_Event e;
	int x, y;
	const Uint8* keys;
	Camera* camera = new Camera();
	int keycode;
	int mSpeed = 4;
public:
	void update(SDL_Renderer* renderer, sceneManager* manager, unsigned int deltaTime);
	void start(SDL_Renderer* renderer, sceneManager* manager);
	timer t_timer;
};

void TestLevel::start(SDL_Renderer* renderer, sceneManager* manager)
{
	manager->addWorld(thisWorld, thisWorldID);
	manager->loadWorld(thisWorldID);


	// def entities
	entity* cube = thisWorld->createEntity();
	cube->addComponent(camera);
	cube->tag = "Weinus";
	transform* _transform = new transform;
	sprite* _sprite = new sprite;
	boxCollider2D* collider = new boxCollider2D;
	rigidBody2D* _rigidBody = new rigidBody2D;
	/// Wall ent
	entity* wall = thisWorld->createEntity();
	boxCollider2D* collider2 = new boxCollider2D;
	transform* _transform2 = new transform;
	_transform2->position = { 700,0 };
	_transform2->w = 50;
	_transform2->h = 600;
	wall->addComponent(_transform2);
	wall->addComponent(collider2);
	wall->tag = "Wall";

	cube->addComponent(_transform);
	cube->addComponent(_sprite);
	cube->addComponent(collider);
	cube->addComponent(_rigidBody);

	cube->getComponentEX<transform*>()->position = { 100,100 };
	cube->getComponentEX<transform*>()->w = 100;
	cube->getComponentEX<transform*>()->h = 100;
	cube->getComponentEX<sprite*>()->init(cube);

	collider2->drawDebugGeometry();
	collider2->initColliderPosition(manager, wall->getEID());
	_rigidBody->init(manager, cube->getEID());
	collider->initColliderPosition(manager, cube->getEID());
	collider->drawDebugGeometry();

	//camera
	this->camera->setFocus(this->thisWorld,cube->getEID());

}
void TestLevel::update(SDL_Renderer* renderer, sceneManager* manager, unsigned int deltaTime)
{
	SDL_PollEvent(&e);
	keys = SDL_GetKeyboardState(& keycode);
	SDL_GetMouseState(&this->x, &this->y);
	//manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<transform*>()->position.x = manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<transform*>()->position.x + 1;
	manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<boxCollider2D*>()->updateColliderPosition(manager);
	manager->getCurrent()->getEntityByTag("Wall")->getComponentEX<boxCollider2D*>()->updateColliderPosition(manager);
	
	if (keys[SDL_SCANCODE_W])
		manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<rigidBody2D*>()->applyVelocity(0, mSpeed);
	if (keys[SDL_SCANCODE_A])
		manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<rigidBody2D*>()->applyVelocity(-mSpeed, 0);
	if (keys[SDL_SCANCODE_S])
		manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<rigidBody2D*>()->applyVelocity(0,-mSpeed);
	if (keys[SDL_SCANCODE_D])
		manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<rigidBody2D*>()->applyVelocity(mSpeed, 0);

	t_timer.start_recursiveTimerMS(1000,deltaTime);
	if (t_timer.c_recursiveTimerDelay())
	{
	}

}