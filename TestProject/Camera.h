#pragma once
#include "gMath.hpp"
#include "scene.h"
#include "component.h"
class Camera : public component
{
public:
	bool enabled = true;
	inline void start(SDL_Renderer* renderer)
	{

	}
	inline void update(SDL_Renderer* renderer)
	{
		if (cWorld != nullptr)
		{
			if (cWorld->getEntity(a_eEntityFocus) != nullptr)
			{
				if (cWorld->getEntity(a_eEntityFocus)->getComponentEX<transform*>() != nullptr)
				{
					this->cameraSize.x = (((cWorld->getEntity(a_eEntityFocus)->getComponentEX<transform*>()->position.x)
						+ cWorld->getEntity(a_eEntityFocus)->getComponentEX<transform*>()->w) / 2) - screenWidth / 2;
					this->cameraSize.y = (((cWorld->getEntity(a_eEntityFocus)->getComponentEX<transform*>()->position.y)
						+ cWorld->getEntity(a_eEntityFocus)->getComponentEX<transform*>()->h) / 2) - screenHeight / 2;
				}
				return;
			}
		}
		else {
			std::cout << "cWorld == nullptr" << std::endl;
		}
	}

	~Camera()
	{
		delete this->cWorld;
	}
	inline void setCameraPosition(SDL_Rect newPosition) { this->cameraSize.x = newPosition.x; this->cameraSize.y = newPosition.y;}
	inline void setCameraSize(SDL_Rect newPosition) { this->cameraSize.w = newPosition.w; this->cameraSize.h = newPosition.h; }
	inline SDL_Rect getCameraSize() { return this->cameraSize; }
	void setFocus(world* world,int entityID = -1, const char* tag = "-1"); // use either entityID or entity Tag -- call Each frame to update position.
	void updateCamera(world* world);
private:
	int a_eEntityFocus = -1;
	world* cWorld = nullptr;
	int screenWidth = 800;
	int screenHeight = 600;

	const char* a_eEntTag = "-1";
	SDL_Rect cameraSize = { 0,0, 800,600 };
};

