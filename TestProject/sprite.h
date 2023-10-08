#pragma once
#include "component.h"
#include "position2D.h"
#include "Camera.h"
class sprite : public component
{
private:
	SDL_Rect rect = { 0,0,0,0 };
	image img;
	entity* entityAssigned;
	transform* transform2D;
	const char* filePath;
	bool visible = true;
	bool inited = false;
public:
	sprite()
	{

	}
	inline void start(SDL_Renderer* renderer)
	{
		img.initImage(renderer);
		inited = true;
	}
	inline void update(SDL_Renderer* renderer)
	{
		if (inited == true)
		{
			if (entityAssigned->getComponentEX<Camera*>() != nullptr)
			{
				this->rect = { (int)transform2D->position.x - entityAssigned->getComponentEX<Camera*>()->getCameraSize().x
					,(int)transform2D->position.y- entityAssigned->getComponentEX<Camera*>()->getCameraSize().y
					,transform2D->w,transform2D->h };
				img.createImage(renderer, rect, transform2D->angle);
			}
		}
	}

	inline void init(entity* e, const char* path = "NULL")
	{
		if (e->getComponentEX<transform*>() != nullptr) // why do i check twice?
		{
			this->entityAssigned = e;
			if (e->getComponentEX<transform*>() != nullptr)
			{
				this->transform2D = e->getComponentEX<transform*>();
				this->rect = { (int)transform2D->position.x,(int)transform2D->position.y,transform2D->w,transform2D->h };
			}
			if (path != "NULL")
			{
				img.setPath(path);
			}
		}
	}

};