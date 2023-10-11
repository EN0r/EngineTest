#include "text.h"

bool game_Text::init(SDL_Renderer* renderer, const char* text, unsigned int size,tools::vec2 pos,SDL_Color color, const char* path)
{
    this->defaultColor = color;
    this->defaultPath = path;
    this->font = TTF_OpenFont(path, size);
    this->surface = TTF_RenderText_Solid(font, text,defaultColor);
    this->texture = SDL_CreateTextureFromSurface(renderer,surface);
    this->size = { (int)pos.x,(int)pos.y,surface->w,surface->h };
    if (texture == NULL)
        return false;

    return true;
}

void game_Text::renderText(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, this->texture, NULL, &this->size, NULL, NULL, SDL_FLIP_NONE);
}
