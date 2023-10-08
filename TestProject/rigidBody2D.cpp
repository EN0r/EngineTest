#include "rigidBody2D.h"
#include "physicsEngine.h"
#include "boxCollider.h"
// impl code here

void rigidBody2D::init(sceneManager* manager, int entityID)
{
	if (this->cWorld == nullptr)
		this->cWorld = manager->getCurrent();
	if (this->a_entityID == -1)
	{
		a_entityID = manager->getCurrent()->getEntity(entityID)->getEID();

			if (this->a_transformID == -1)
			{
				if (manager->getCurrent()->getEntity(a_entityID)->getComponentEX<boxCollider2D*>() == nullptr)
					this->collider = false;
				else
					collider = true;
				a_transformID = manager->getCurrent()->getEntity(a_entityID)->getComponentEX<transform*>()->ID;
			}
	}
}

void rigidBody2D::dCall(sceneManager* manager)
{
	if (!collider)
	{
		if (this->velocity.x <= 0 || this->velocity.y <= 0 || this->velocity.x >= 0 || this->velocity.y >= 0)
		{
			if (manager->getCurrent()->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID) != nullptr)
			{
				// physics math here for the new position
				for (int x = 0; x < velocity.x; x++)
				{
					manager->getCurrent()->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.x = manager->getCurrent()->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.x+x;
					for (int y = 0; y < velocity.y; y++)
					{
						manager->getCurrent()->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.y = manager->getCurrent()->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.y+y;
					}
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
		if (manager->getCurrent()->getEntity(a_entityID)->getComponentEX<boxCollider2D*>()->isColliding(manager))
		{
			return;
		}
		else {
		if (this->velocity.x <= 0 || this->velocity.y <= 0 || this->velocity.x >= 0 || this->velocity.y >= 0)
		{
			if (manager->getCurrent()->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID) != nullptr)
			{
				// physics math here for the new position
				for (int x = 0; x < velocity.x; x++)
				{
					manager->getCurrent()->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.x = manager->getCurrent()->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.x + x;
					for (int y = 0; y < velocity.y; y++)
					{
						manager->getCurrent()->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.y = manager->getCurrent()->getEntity(this->a_entityID)->getComponent<transform*>(this->a_transformID)->position.y + y;
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
}

tools::vec2 rigidBody2D::applyVelocity(int xvelocity, int yvelocity)
{
	tools::vec2 n_v = { xvelocity,yvelocity };
	this->velocity = (this->velocity + n_v);
	return this->velocity;
}
