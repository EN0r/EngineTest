#pragma once
#include "entity.h"

void entity::update(SDL_Renderer* renderer)
{
	for (auto comp : this->componentList)
	{
		if (comp.first != -1)
			comp.second->update(renderer);
	}
}

void entity::start(SDL_Renderer* renderer)
{
	for (auto comp : this->componentList)
	{
		if (comp.first != -1)
			comp.second->start(renderer);
	}
}