#pragma once
#include "component.h"
#include "scene.h"
#include "renderedPosition.h"
class camera2D : public component
{
public:
	inline void start(SDL_Renderer* renderer) {

	}
	inline void update(SDL_Renderer* renderer)
	{
		if (this->a_entityFocusID == -1)
		{
			if (currentWorld != nullptr)
			{
				for (auto entities: currentWorld->getEntityList())
				{
					if (entities.second->getComponentEX<renderedPosition*>() != nullptr)
					{
						entities.second->getComponentEX<renderedPosition*>()->position.x = entities.second->getComponentEX<renderedPosition*>()->position.x + this->position.x;
						entities.second->getComponentEX<renderedPosition*>()->position.y = entities.second->getComponentEX<renderedPosition*>()->position.y + this->position.y;
					}
				}

			}
		}
		else {
			if (currentWorld != nullptr)
			{
				for (auto entities : currentWorld->getEntityList())
				{
					if (entities.second->getComponentEX<camera2D*>() != nullptr)
					{
						entities.second->getComponentEX<renderedPosition*>()->position.x = (entities.second->getComponentEX<renderedPosition*>()->position.x + this->position.x) +
							entities.second->getComponentEX<transform*>()->w  - (cameraSize.x/ 2);
						entities.second->getComponentEX<renderedPosition*>()->position.y = (entities.second->getComponentEX<renderedPosition*>()->position.y + this->position.y) +
							entities.second->getComponentEX<transform*>()->h - (cameraSize.x/2);
					}
					else {
						entities.second->getComponentEX<renderedPosition*>()->position.x = entities.second->getComponentEX<renderedPosition*>()->position.x + this->position.x;
						entities.second->getComponentEX<renderedPosition*>()->position.y = entities.second->getComponentEX<renderedPosition*>()->position.y + this->position.y;
					}
				}


			}


		}
	}

	inline void init(sceneManager* manager)
	{
		if (manager->getCurrent() != nullptr && currentWorld == nullptr)
		{
			this->currentWorld = manager->getCurrent();
		}
		else { std::cout << "No current world selected! -> " << typeid(this).name() << std::endl; }
	}

	void setEntityFocus(int focus) { a_entityFocusID = focus; }
	void setCameraPosition(tools::vec2 newPos) { this->position.x = newPos.x; this->position.y = newPos.y; }
	tools::vec2 getCameraPosition() { return this->position; }
	// constructor destructor
	camera2D() {

	}
	~camera2D()
	{
		delete this->currentWorld;
		delete this;
	}
private:
	int a_entityFocusID = -1;
	tools::vec2 cameraSize = { 800,600 };
	tools::vec2 position = { 0,0 };
	world* currentWorld = nullptr;
};

