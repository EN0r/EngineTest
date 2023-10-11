#include "image.h"

bool image::initImage(SDL_Renderer* renderer)
{
	this->surf = IMG_Load(this->filePath);
	textureBuf = SDL_CreateTextureFromSurface(renderer, this->surf);
	printf(SDL_GetError());
	if (textureBuf != NULL)
	{
		return true;
	}
	return false;
}

bool image::createImageEX(SDL_Renderer* renderer, tools::vec2 vec, tools::_2DSize size, double ang, bool flipped)
{
	this->imageSize = { (int)vec.x,(int)vec.y,(int)size.w,(int)size.h };
	if (flipped)
	{
		if (SDL_RenderCopyEx(renderer, textureBuf, NULL, &this->imageSize, ang, NULL, SDL_FLIP_HORIZONTAL) != 0)
		{
			std::cout << "ERROR RENDERCOPY" << std::endl;
			return false;
		} else { return true; }

	}
	else {
		if (SDL_RenderCopyEx(renderer, textureBuf, NULL, &this->imageSize, ang, NULL, SDL_FLIP_NONE) != 0)
		{
			std::cout << "ERROR RENDERCOPY" << std::endl;
			return false;
		} else { return true; }
	}
	return false;
}

bool image::createImage(SDL_Renderer* renderer, SDL_Rect rect, double ang, bool flipped)
{
	this->imageSize = rect;
	if (flipped)
	{
		if (SDL_RenderCopyEx(renderer, textureBuf, NULL, &this->imageSize, ang, NULL, SDL_FLIP_HORIZONTAL) != 0)
		{
			std::cout << SDL_GetError() << std::endl;
			return false;
		}
		else { return true; }

	}
	else {
		if (SDL_RenderCopyEx(renderer, textureBuf, NULL, &this->imageSize, ang, NULL, SDL_FLIP_NONE) != 0)
		{
			std::cout << "ERROR RENDERCOPY" << std::endl;
			std::cout << SDL_GetError() << std::endl;
			return false;
		}
		else { return true; }
	}
	return false;
}
