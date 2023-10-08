#pragma once
#include <iostream>
#include <map>
#include "image.h"
#include "time.h"
#include "component.h"
#include "sprite.h"

class animationHandler2D : public component
{
public:
	std::map<int, image> frames;
	void setTime(int timeinMS) { this->timeBetweenEachFrameMS = timeinMS; }
	bool initAnimationHandler();
	inline void update(SDL_Renderer* renderer);
	inline void start(SDL_Renderer* renderer);
private:
	timer t; // used for animationdelay
	int entParentId = -1;
	int timeBetweenEachFrameMS = 0.0f;
};