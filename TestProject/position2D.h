#pragma once
#include "component.h"
struct position2D : component
{
	tools::vec2 position = { 0,0 }; // default position 0,0
	inline void update(SDL_Renderer* renderer = NULL);
	inline void start(SDL_Renderer* renderer = NULL);
};

inline void position2D::update(SDL_Renderer* renderer)
{
	
	
}
inline void position2D::start(SDL_Renderer* renderer)
{
	
}