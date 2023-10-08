#include "Camera.h"

void Camera::setFocus(world* world, int entityID, const char* tag) // probs just call this each frame tbf.
{
	if(cWorld == nullptr)
		this->cWorld = world;
	this->a_eEntityFocus = entityID;
	this->a_eEntTag = tag;

	if (world->getEntity(entityID) != nullptr)
	{
		if (world->getEntity(entityID)->getComponentEX<transform*>() != nullptr)
		{
			this->cameraSize.x = (((world->getEntity(entityID)->getComponentEX<transform*>()->position.x)
				+ (world->getEntity(entityID)->getComponentEX<transform*>()->w) / 2) - screenWidth)/2;
			this->cameraSize.y = (((world->getEntity(entityID)->getComponentEX<transform*>()->position.y)
				+ (world->getEntity(entityID)->getComponentEX<transform*>()->h) / 2) - screenHeight)/2;
			std::cout << cameraSize.x << cameraSize.y << std::endl;
		}
		return;
	}
	if (world->getEntityByTag(tag) != nullptr)
	{
		if (world->getEntity(entityID)->getComponentEX<transform*>() != nullptr)
		{
			this->cameraSize.x = (((world->getEntity(entityID)->getComponentEX<transform*>()->position.x)
				+ (world->getEntity(entityID)->getComponentEX<transform*>()->w) / 2 - screenWidth) / 2);
			this->cameraSize.y = (((world->getEntity(entityID)->getComponentEX<transform*>()->position.y)
				+ (world->getEntity(entityID)->getComponentEX<transform*>()->h) / 2) - screenHeight) / 2;
			std::cout << cameraSize.x << cameraSize.y << std::endl;
		}
		return;
	}
}


void Camera::updateCamera(world* world)
{

}
