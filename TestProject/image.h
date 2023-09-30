#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "gMath.hpp"

class image
{
public:
	image(const char* path = "./resources/placeholder/error.png"){
		this->filePath = path;
	}
	~image()
	{
		delete this->surf;
	}
	bool initImage(SDL_Renderer* renderer);
	bool createImageEX(SDL_Renderer* renderer, tools::vec2 vec, tools::_2DSize size, double ang = 0.0f, bool flipped = false); // Takes renderer, vec2 for x,y pos and size for width and height of rendered object
	bool createImage(SDL_Renderer* renderer,SDL_Rect rect, double ang = 0.0f, bool flipped = false); // Takes renderer, vec2 for x,y pos and size for width and height of rendered object
	void setPath(const char* path = "NULL") { if (path != "NULL") { filePath = path; } }
private:
	const char* filePath;
	SDL_Surface* surf = NULL;
	SDL_Texture* textureBuf = NULL;
	SDL_Rect imageSize = { 0,0,0,0 };
};