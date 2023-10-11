#pragma once
#include <iostream>
#include "gMath.hpp"
#include "SDL.h"
#include "SDL_ttf.h"
class game_Text
{
public:
	bool init(SDL_Renderer* renderer,const char* text, unsigned int size,tools::vec2 pos,SDL_Color color = { 0,0,0,255 }, const char* path = "./resources/comicSans/COMIC.TTF");
	void renderText(SDL_Renderer* renderer);

	~game_Text()
	{
		if (font != nullptr)
			TTF_CloseFont(font);
		delete this->surface;
		delete this->texture;
		delete this->defaultPath;
		delete this->font;
	}
	SDL_Rect size = { 0,0,0,0 };
private:
	TTF_Font* font = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Color defaultColor = {0,0,0,255};
	const char* defaultPath = "./resources/comicSans/COMIC.TTF";
};

