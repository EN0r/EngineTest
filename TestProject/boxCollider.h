#pragma once
#include "component.h"
#include "scene.h"
#include "gMath.hpp"
#include "renderedPosition.h"

class  boxCollider2D : public component
{
public:
	boxCollider2D()
	{

	}
	bool colliding = false;
	inline void update(SDL_Renderer* renderer)
	{
		if (drawDebugGeo)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			int diffx = currentWorld->getEntity(aEntityAssigned)->getComponentEX<transform*>()->position.x - currentWorld->getEntity(aEntityAssigned)->getComponentEX<renderedPosition*>()->position.x;
			int diffy = currentWorld->getEntity(aEntityAssigned)->getComponentEX<transform*>()->position.y - currentWorld->getEntity(aEntityAssigned)->getComponentEX<renderedPosition*>()->position.y;
		
			SDL_Rect r = { currentWorld->getEntity(aEntityAssigned)->getComponentEX<renderedPosition*>()->position.x - diffx ,currentWorld->getEntity(aEntityAssigned)->getComponentEX<renderedPosition*>()->position.y - diffy,colliderRect.w,colliderRect.h};
			SDL_RenderDrawRect(renderer, &r);
			//std::cout << aEntityAssigned << ":" << colliderRect.x << "," << colliderRect.y << std::endl;
		}
	}
	inline void start(SDL_Renderer* renderer)
	{

	}
	inline void setEntityAssigned(int x) { this->aEntityAssigned = x; }
	bool isCollidingEX(world* world);
	bool updateColliderPosition(sceneManager* manager); // Takes screenManager as parameter, it updates colliderposition depending on the transform thats found in the entity.
	inline SDL_Rect getColliderPosition() { return this->colliderRect; }
	bool initColliderPosition(sceneManager* manager, int eId); // This initalizes the collider. Input is ScreenManager and Entity ID
	bool isColliding(sceneManager* manager); // Returns true if the collider is colliding with a object. Need to implement a reference to the object which it's colliding with or a alternate function
	inline void drawDebugGeometry() // draws a green box around all collider objects.
	{
		this->drawDebugGeo = true;
	}


private:
	SDL_Rect lBuffer;
	world* currentWorld = nullptr;
	int aEntityAssigned = -1;
	SDL_Rect colliderRect = { 0,0,0,0 };
	bool drawDebugGeo = false;
};