#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"

class _sdlWindow
{
private:
	SDL_Renderer* renderer;
	SDL_Surface* surf;

public:
	SDL_Window* window = NULL;
	int w;
	int h;
	const char* windowName;
	_sdlWindow(int w, int h, int posx, int posy, const char* windowName, Uint32 flags);
	~_sdlWindow()
	{
		SDL_DestroyWindow(window);
		delete renderer;
		delete window;
		delete this;
	}
	const inline SDL_Surface* getSurface() { return this->surf; }
	SDL_Renderer* getRenderer(Uint32 flags) // *& so whatever instance copied will have same memory address saves memory.
	{
		if (window != NULL)
		{
			SDL_Renderer* R = SDL_CreateRenderer(this->window, NULL, flags);
			if (!IMG_Init(IMG_INIT_PNG))
			{
				printf("ERR loading image");

			}
			else
			{
				surf = SDL_GetWindowSurface(this->window);
			}
			return R;
		}
	}
};