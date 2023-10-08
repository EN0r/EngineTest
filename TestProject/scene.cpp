#include "scene.h"
#include "Camera.h"
component* sceneManager::getCurrentCamera()
{
	for (auto entity : currentWorld->getEntityList())
	{
		if (entity.second->getComponentEX<Camera*>() != nullptr)
			if(entity.second->getComponentEX<Camera*>()->enabled== true)
				return entity.second->getComponentEX<Camera*>();
	}
	return nullptr;
}
