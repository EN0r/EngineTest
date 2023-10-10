#pragma once
#include "UI.h"
class UIButton : UI
{
public:
	void start(SDL_Renderer* renderer)
	{

	}

	void update(SDL_Renderer* renderer)
	{

	}


private:
	const char* defaultPath = "./resources/placeholder/uiComponents/default/defaultButton.png";
	SDL_Rect size = { 0,0,100,20 };



};

