#pragma once
#include "component.h"
class physics2D : component
{
public:
	entity*& ent; // from here we can get entityList

	inline void update(SDL_Renderer* renderer = NULL);
	inline void start(SDL_Renderer* renderer = NULL);
	void setParent(entity* _entity) { ent = _entity; }

};