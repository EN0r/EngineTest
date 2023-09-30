#pragma once
#include "world.h"
#include "gMath.hpp"
#include "image.h"
#include "entity.h"

struct velocity : component
{
	void update(SDL_Renderer* renderer);
	void start(SDL_Renderer* renderer);
	float x, y;
};
struct transform : component
{
	tools::vec2 position = { 0,0 };
	double angle = 0.0f;
	int w = 0; // scale
	int h = 0; // scale
	inline void update(SDL_Renderer* renderer)
	{

	}
	inline void start(SDL_Renderer* renderer)
	{

	}
};
