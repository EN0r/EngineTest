#pragma once
#include "component.h"
#include "position2D.h"
#include "Camera.h"
#include "renderedPosition.h"
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
			if (entityAssigned->getComponentEX<renderedPosition*>() != nullptr && entityAssigned->getComponentEX<transform*>() != nullptr)
			{
				int diffx = transform2D->position.x - (int)entityAssigned->getComponentEX<renderedPosition*>()->position.x;
				int diffy = transform2D->position.y - (int)entityAssigned->getComponentEX<renderedPosition*>()->position.y;
				this->rect = { (int)entityAssigned->getComponentEX<renderedPosition*>()->position.x - diffx
							  ,(int)entityAssigned->getComponentEX<renderedPosition*>()->position.y - diffy
						      ,transform2D->w,transform2D->h };
				std::cout << (int)entityAssigned->getComponentEX<renderedPosition*>()->position.x << std::endl;
				img.createImage(renderer, rect, transform2D->angle);
			}
			else {
				std::cout << " no rendered position!!" << std::endl;
			}
		}
	}

	inline void init(entity* e, const char* path = "NULL")
	{
		if (e->getComponentEX<transform*>() != nullptr) // why do i check twice?
		{
			this->entityAssigned = e;
			this->transform2D = e->getComponentEX<transform*>();
			if (e->getComponentEX<renderedPosition*>() != nullptr)
			{
				if (e->getComponentEX<transform*>() != nullptr)
				{
					this->rect = { (int)entityAssigned->getComponentEX<renderedPosition*>()->position.x,(int)entityAssigned->getComponentEX<renderedPosition*>()->position.y,transform2D->w,transform2D->h };
				}
				if (path != "NULL")
				{
					img.setPath(path);
				}

			}
		}
		else {
			std::cout << "no RenderedPosition" << std::endl;
		}
	}

};