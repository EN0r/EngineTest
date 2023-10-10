#include "TestLevel.h"
#include "windowClass.h"
#include "sprite.h"
#include <vector>
#include "boxCollider.h"
#include "rigidBody2D.h"
#include "UIFrame.h"




void TestLevel::start(SDL_Renderer* renderer, sceneManager* manager)
{
	// init ui


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
	camera->init(manager);
	//camera->setEntityFocus(cube->getEID());
}
void TestLevel::update(SDL_Renderer* renderer, sceneManager* manager, unsigned int deltaTime)
{
	SDL_PollEvent(&e);
	keys = SDL_GetKeyboardState(&keycode);
	SDL_GetMouseState(&this->x, &this->y);
	//manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<transform*>()->position.x = manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<transform*>()->position.x + 1;
	manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<boxCollider2D*>()->updateColliderPosition(manager);
	manager->getCurrent()->getEntityByTag("Wall")->getComponentEX<boxCollider2D*>()->updateColliderPosition(manager);
	//manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<camera2D*>()->setCameraPosition({ 0 ,manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<camera2D*>()->getCameraPosition().y + 1 });

	if (keys[SDL_SCANCODE_W])
		thisWorld->getEntityByTag("Weinus")->getComponentEX<rigidBody2D*>()->applyVelocity(2, 0);
	if (keys[SDL_SCANCODE_A])
	{
		manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<camera2D*>()->setCameraPosition({ manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<camera2D*>()->getCameraPosition().x + 1 ,0 });
	}
	if (keys[SDL_SCANCODE_D])
	{
		manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<camera2D*>()->setCameraPosition({ manager->getCurrent()->getEntityByTag("Weinus")->getComponentEX<camera2D*>()->getCameraPosition().x - 1 ,0 });
	}
	t_timer.start_recursiveTimerMS(1000, deltaTime);
	if (t_timer.c_recursiveTimerDelay())
	{
	}
}