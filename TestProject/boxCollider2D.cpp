#include "boxCollider.h"
#include "Camera.h"
bool boxCollider2D::initColliderPosition(sceneManager* manager, int eId)
{
	// basic debounce
	if(this->aEntityAssigned == -1)
		this->aEntityAssigned = eId;
	if (aEntityAssigned != -1)
	{
		if (manager->getCurrent()->getEntity(this->aEntityAssigned)->getComponentEX<transform*>() != nullptr)
		{
			// entity has a transform
			this->colliderRect.x = manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<transform*>()->position.x;
			this->colliderRect.y = manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<transform*>()->position.y;
			this->colliderRect.w = manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<transform*>()->w;
			this->colliderRect.h = manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<transform*>()->h;
			return true;
		}else { return false;
		std::cout << "Object does not have a transform!" << std::endl;
		}
	}
	return false;
}
bool boxCollider2D::updateColliderPosition(sceneManager* manager)
{
	// basic debounce
	if (aEntityAssigned != -1)
	{
		if (manager->getCurrent()->getEntity(this->aEntityAssigned)->getComponentEX<transform*>() != nullptr)
		{
			// entity has a transform
			if (manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<Camera*>() != nullptr)
			{
				this->colliderRect.x = (manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<transform*>()->position.x - 
					manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<Camera*>()->getCameraSize().x);
				this->colliderRect.y = (manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<transform*>()->position.y -
					manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<Camera*>()->getCameraSize().y);
				this->colliderRect.w = manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<transform*>()->w;
				this->colliderRect.h = manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<transform*>()->h;
				
			}
			else {
				Camera* cCamera = dynamic_cast<Camera*>(manager->getCurrentCamera());
				this->colliderRect.x = manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<transform*>()->position.x -
					cCamera->getCameraSize().x;
					this->colliderRect.y = manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<transform*>()->position.y -
					cCamera->getCameraSize().y;
				this->colliderRect.w = manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<transform*>()->w;
				this->colliderRect.h = manager->getCurrent()->getEntity(aEntityAssigned)->getComponentEX<transform*>()->h;
			}

			return true;
		}else { 
		std::cout << "Object does not have a transform!" << std::endl;
		return false;
		}
	}

	return false;
}

bool boxCollider2D::isColliding(sceneManager* manager)
{
	// loop through current scene
	for (auto ent : manager->getCurrent()->getEntityList())
	{
		if (tools::AABB(ent.second->getComponentEX<boxCollider2D*>()->getColliderPosition(), this->colliderRect) && ent.second->getEID() != this->aEntityAssigned)
		{
			// colliding
			colliding = true;
			return true;
		}
	}
	colliding = false;
	return false;
}
bool boxCollider2D::isCollidingEX(world* world)
{
	// loop through current scene
	for (auto ent : world->getEntityList())
	{
		if (tools::AABB(ent.second->getComponentEX<boxCollider2D*>()->getColliderPosition(), this->colliderRect) && ent.second->getEID() != this->aEntityAssigned)
		{
			// colliding
			colliding = true;
			return true;
		}
	}
	colliding = false;
	return false;
}