#pragma once
#include "component.h"
namespace physicsVariables
{
	static float gravity = 0.3f;
	static unsigned int deltaTime = 0;
}
class physicsEngine : public component
{
public:
	
	physicsEngine()
	{

	}
	inline void update(SDL_Renderer* renderer);
	inline void start(SDL_Renderer* renderer);

	~physicsEngine()
	{

	}
private:

};

