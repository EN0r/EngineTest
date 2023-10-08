#pragma once
#include "component.h"
struct renderedPosition : component // should be inaccessible to engine. This should never be changed by anything but the camera.
{
	tools::vec2 position = { 0,0 };

	inline void update(SDL_Renderer* renderer ){

	}
	inline void start(SDL_Renderer* renderer) {

	}
};

