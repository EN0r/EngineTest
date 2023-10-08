#pragma once
#include "entity.h"
#include "renderedPosition.h"
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
	renderedPosition* rendPos = new renderedPosition;
	if (this->getComponentEX<transform*>() != nullptr)
	{
		rendPos->position.x = this->getComponentEX<transform*>()->position.x;
		rendPos->position.y = this->getComponentEX<transform*>()->position.y;
		std::cout << "RenderedPosition:" << rendPos->position.x << "," << rendPos->position.y << std::endl;
	}
	else { std::cout << "this ent has no transform: " << typeid(this).name() << std::endl; }
	this->addComponent(rendPos);
	for (auto comp : this->componentList)
	{
		if (comp.first != -1)
			comp.second->start(renderer);
	}
}