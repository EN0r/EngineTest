#pragma once
#include "component.h"
#include "scene.h"
#include "boxCollider.h"

/*
	if (this->a_entityID == -1)
	{
		a_entityID =

		if (this->a_transformID == -1)
		{

		}
	}
	*/
class rigidBody2D : public component
{
public:
	rigidBody2D()
	{

	}
	~rigidBody2D()
	{
		delete cWorld;
	}
	inline void start(SDL_Renderer* renderer)
	{

	}
	inline void update(SDL_Renderer* renderer)
	{
		if (!collider)
		{
			if (this->velocity.x != 0 || this->velocity.y != 0)
			{
				if (cWorld->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID) != nullptr)
				{
					// physics math here for the new position
					for (int x = 0; x < velocity.x; x++)
					{
						cWorld->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.x = cWorld->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.x + x;

					}
					for (int y = 0; y < velocity.y; y++)
					{
						cWorld->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.y = cWorld->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.y + y;
					}
					this->velocity = { 0,0 }; // resetVelocity

				}
				else {
					printf("Transform Not found in object dCALL\n");
				}
			}
		}
		if (collider)
		{
			if (cWorld->getEntity(a_entityID)->getComponentEX<boxCollider2D*>()->isCollidingEX(cWorld))
			{
				return;
			}
			if (this->velocity.x != 0 || this->velocity.y != 0)
			{
				if (cWorld->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID) != nullptr)
				{
					// physics math here for the new position
					for (int x = 0; x < velocity.x; x++)
					{
						cWorld->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.x = cWorld->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.x + x;
						for (int y = 0; y < velocity.y; y++)
						{
							cWorld->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.y = cWorld->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.y + y;
						}
					}
					this->velocity = { 0,0 }; // resetVelocity
				}
				else {
					printf("Transform Not found in object dCALL\n");
				}
			}
		}
	}
	void init(sceneManager* manager, int entityID);
	void dCall(sceneManager* manager);
	tools::vec2 applyVelocity(int xvelocity, int yvelocity);
private:
	world* cWorld = nullptr;
	float _gravity = 0.0f;
	bool collider = false;
	tools::vec2 velocity = { 0,0 }; // always defaults to 0,0 - speed
	tools::vec2 force = { 0,0 };
	bool effectedByGravity = false;
	float mass = 0.0f;
	float drag = 0.0f;
	int a_entityID = -1;
	int a_transformID = -1;

};